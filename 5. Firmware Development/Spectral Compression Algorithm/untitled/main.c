/*
    SHARC BUOY V3 Packet Decoder

    Author: Michael Noyce
    For   : University of Cape Town
    Date  : 17 July 2023

    Data:

    Name...........Type.............Description
    ID.............uint8_t..........packet identifier
    Epoch Time.....uint32_t.........Time and Date information represented in Epoch Time
    Latitude.......float............Float representing the GPS Latitude coordinates in DDMM.mmmm format
    Longitude......float............Float representing the GPS Longitude coordinates in DDMM.mmmm format
    HDOP...........float............Float representing the Horizontal Dilation of Precision
    PDOP...........float............Float representing the Positional Dilation of Precision
    VDOP...........float............Float representing the Vertical Dilation of Precision
    NumSats........uint8_t..........Number of satellites used to acquire the fix
    Fix_Type.......uint8_t..........How the measurement was obtained (2D,3D, No Fix, Dead Reckoning)
    Temperature....float............Ambient Temperature measurement
    V_shunt........float............Voltage across shunt resistor measured by current monitor (mV)
    V_Bus..........float............Voltage measured between the INA219 Terminals (V)
    Current........float............Battery Current (mA)
    Power..........float............power Dissipation (mW)

    Program Structure

    The program starts by taking in an input file. The program will check to see if the file exists
    If not, it will fail. The file must be in .csv format and formated in the same way the ROCKBLOCK logs are formated.
    Then, It will split the payload up into packets and decompress each packet storing the data in a new .csv File


    How To use:

    Step 1: set the variable dir_path to the folder your log is stored in
    Step 2: set the variable filename to the input file name
    Step 3: set the variable write_file to the desired output file name
    Step 4: Run the program
*/


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include <time.h>

#define DRIFT_DATA_SIZE 152
#define IMU_DATA_SIZE 338


typedef struct
{
    uint8_t ID;
    uint32_t Etime;
    float coord[2];
    float dop[3];
    uint8_t signal_type;
    uint8_t num_sats;
    float temp;
    float press;
    int16_t V_shunt,V_bus,Current,power;
}Packet;

//global variables
char* data;

char data_buffer[1024];
uint8_t getByte(char* msg);
void decode_Message(char* payload);
float get_float(unsigned char* bytestring);
void float_to_hex(float f,unsigned char* hexstring);
float IEEE754_Convert(uint32_t sign, uint32_t exp, uint32_t mant);
Packet packet;

//Main Program
int main()
{
    FILE* filepointer;
    FILE* writefilepointer;
    //open file in read mode
    char* filename=malloc(50*sizeof(char));; //file to read
    char* dirpath = malloc(256*sizeof(char));
    char* write_file = malloc(50*sizeof(char)); //file to write to
    //ask for input
    printf("Input folder/folder path (leave blank if in root): ");
    gets(dirpath);
    printf("Input File Name: ");
    gets(filename);
    printf("Output File Name: ");
    gets(write_file);

    //generate read and write paths
    int flen =  strlen(filename);
    int dirlen = *dirpath =='\0'? 0: strlen(dirpath);
    int wflen = strlen(write_file);
    char path[dirlen+flen+1];
    char writepath[dirlen+wflen+1];
    if(!dirlen)
    {
        sprintf(path,"%s%s",dirpath,filename);
    }else
    {
        sprintf(path,"%s\\%s",dirpath,filename);
    }
    sprintf(writepath,"%s",write_file);

    //check if write file exists
    writefilepointer = fopen(writepath,"r");
    if(writefilepointer == NULL)
    {
        printf("Write file does not exist, creating file...");
        writefilepointer = fopen(writepath,"w");
        char headings[1000];
        sprintf(headings,"Packet Type,Packet Number,Date,Time,Latitude,Longitude,HDOP,VDOP,PDOP,Signal Type,Num Satelites,Temperature, Pressure,V shunt,V Buss, I, P\n");
        fputs((char*)headings,writefilepointer);
        printf("Done\n");
    }else
    {
        fclose(writefilepointer);
        int valid = 0;
        do
        {
            char choice = 0;
            printf("File Exists. [A]ppend [O]verwrite ?");
            gets(&choice);
            if(choice == 'A' || choice == 'a')
            {
                valid = 1;
                writefilepointer = fopen(writepath,"a");
            }else if (choice == 'O' || choice == 'o')
            {
                valid =1;
                writefilepointer = fopen(writepath,"w");
            }else
            {
                printf("Error! please chose a valid option.\n");
            }
        }while(!valid);

    }

    //check if read file exists
    filepointer = fopen((char*)path,"rt");
    if(filepointer == NULL)
    {
        printf("\nError opening File: please check if file exists or is not currently in use.");
        return 0;
    }
    printf("Successfully opened file: %s\n",filename);

    //read untill end of file
    char line[1024];
    int packet_size = 2*DRIFT_DATA_SIZE/4;
    fgets(line,1024,filepointer);
    while(fgets(line,1024,filepointer) != NULL)
    {
        //split line into data filed
        char* data = strtok(line,",");
        for(int i = 0; i < 3;i++)
        {
            data = strtok(NULL,",");
        }
        //split into payload and byte size
        char* pdata = strtok(NULL,",");
        for(int i = 0; i < 2; i++ )
        {
            pdata = strtok(NULL,",");
        }


        int payloadsize = atoi(pdata);
        switch(payloadsize)
        {
            case DRIFT_DATA_SIZE:
                data+=2;
                for(int i = 0;i <4;i++)
                {
                    char packet_buffer[packet_size+1];

                    strncpy(packet_buffer,&data[packet_size*i],packet_size);
                    packet_buffer[packet_size] = 0;
                    decode_Message(packet_buffer);
                    printf("%s",(char*)data_buffer);
                    //save to file
                    fputs(data_buffer,writefilepointer);
                }
                break;
            case IMU_DATA_SIZE:
                break;
            default:
                break;

        }

        //chop off the rest

    }
    fclose(writefilepointer);
    fclose(filepointer);
    free(dirpath);free(filename);free(write_file);
    return 0;
}

void decode_Message(char* payload)
{
    /* Isolate ID */
    packet.ID = getByte(payload);
    payload+=2;
    /* Epoch Time */
    uint32_t Epoch_time = 0;
    for (int i = 0; i < 4; ++i)
    {
        uint8_t byte= getByte(payload);
        Epoch_time |= byte<<8*i;
        payload+=2;
    }
    //Convert uint32_t Epoch time to UTC Date Time
    time_t rawtime = Epoch_time;
    struct tm *info;
    info = localtime( &rawtime );
    char buffer[500];
    strftime(buffer,sizeof(buffer)/sizeof(buffer[0]),"%Y/%m/%d,%H:%M:%S",info);
    /* Coordinates*/
    unsigned char byte_arr[4] = {0};
    for (int k = 0; k < 2; ++k)
    {
        for (int j = 0; j < 4; ++j)
        {
            byte_arr[j] = getByte(payload);
            payload+=2;
        }
        packet.coord[k] = get_float(byte_arr);
    }
    /* Dilation of Precision*/

    for (int l = 0; l < 3; ++l)
    {
        packet.dop[l] = getByte(payload);
        payload+=2;
        packet.dop[l] += ((float)getByte(payload))/1000;
        payload+=2;
    }
    uint8_t signal = getByte(payload);
    payload+=2;
    packet.num_sats = (signal&0b11110000)>>2;
    packet.signal_type = (signal&0b11);
    uint32_t temp = 0;
    for(int j = 0; j < 4; j++)
    {

        temp |=  getByte(payload)<<(8*j);
        payload+=2;
    }
    packet.temp = (float)((int32_t)temp)/100.00;
    uint32_t press = 0;
    for(int j = 0; j < 4; j++)
    {

        press |=  getByte(payload)<<(8*j);
        payload+=2;
    }
    packet.press = (float)press;
    payload+=2;
    int16_t current_data[4] = {0};
    uint16_t* pptr = &packet.V_shunt;
    for(int i = 0; i < 4; i++)
    {
        int16_t temp =  (int16_t)getByte(payload);
        payload+=2;
        temp = (temp&0xFF)|(((int16_t)getByte(payload))<<8);
        payload+=2;
        *pptr++= temp;
    }

    sprintf(data_buffer,"GPS,%d,%s,%f,%f,%0.2f,%0.2f,%0.2f,%d,%d,%0.2f,%0.3f,%0.2f,%0.2f,%0.2f,%d\n",packet.ID+1,buffer,packet.coord[0],packet.coord[1],packet.dop[0],packet.dop[1],packet.dop[2],packet.signal_type,packet.num_sats,packet.temp,packet.press,(float)packet.V_shunt/100,(float)packet.V_bus/1000,(float)packet.Current/10,packet.power);
}
uint8_t getByte(char* msg)
{
    uint8_t byte = 0;
    for (int i = 0; i < 2; ++i)
    {
        if((msg[i]>= '0') &&(msg[i] <= '9'))
        {
            byte+= (msg[i]-'0');
        }
        if((msg[i]>='a') &&(msg[i] <= 'f'))
        {
            byte+= (msg[i]-87);
        }
        byte = byte<<4*(1-i);
    }
    return byte;
}

float get_float(unsigned char* bytestring)
{
    uint32_t num = 0;
    for (int i = 0; i < 4; ++i)
    {
        num = (num<<8) | bytestring[3-i];
    }
    // sign
    uint32_t sign = (num&(0b1<<31));
    num-= sign;
    sign = sign>>31;
    uint32_t exp = num&(0xFF<<23);
    uint32_t mant = (num-exp);
    exp = exp>>23;

    float temp = IEEE754_Convert(sign,exp,mant);
    return temp;
}

void float_to_hex(float f,unsigned char* hexstring)
{
    union {
        unsigned char * byte[4];
        float f;
    }floatasval;
    floatasval.f =f;
    memcpy(hexstring,floatasval.byte, sizeof(float));
}

float IEEE754_Convert(uint32_t sign, uint32_t exp, uint32_t mant)
{
    float temp = 1;
    for (int i = 0; i < 23; ++i)
    {
        //get bit
        uint32_t mask = 1<<(22-i);
        uint8_t bit = (mant & mask)>>(22-i);
        temp += ((float)bit)*(powf(2,-(i+1)));
    }
    float s = 1-2*((float) sign);
    float e = powf(2,(int)(exp-127));
    return s*e*temp;
}
