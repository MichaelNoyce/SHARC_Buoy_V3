// User data functions.  Modify these functions for your data items.
#include "UserTypes.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "ICM20689.h"
#include <RH_RF95.h>
//------------------------------------------------------------------------------
ICM20689 imu;
RH_RF95 rf95;

static uint32_t startMicros;
// Acquire a data record.
void acquireData(data_t* data) {
  data->time = micros();
  imu.getMotion6(&data->ax, &data->ay, &data->az, 
                 &data->gx, &data->gy, &data->gz);
}

void LoRaSetup() {
    while (!Serial) ; // Wait for serial port to be available
  if (!rf95.init())
    Serial.println("init failed");
  else
    Serial.println("init succeeded!"); 
    rf95.setFrequency(868.0);

}

void LoRaSend(){ 
  Serial.println("Sending to rf95_server");
  // Send a message to rf95_server
  uint8_t data[] = "Starting interface";
  rf95.send(data, sizeof(data));
  rf95.waitPacketSent();
}

int LoRaReceive(){
 
  // Now wait for a reply
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  
    if (rf95.waitAvailableTimeout(3000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("got reply: ");
      Serial.println((char*)buf);

      if ((char*)buf == "test"){
       return TEST_SENSOR;
      }

      if ((char*)buf == "log"){
       return LOG_DATA;
      }

      if ((char*)buf == "csv"){
       return CONVERT_TO_CSV;
      }
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf95_server running?");
  }
  delay(400);
 
}

// setup AVR I2C
void userSetup() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000);
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  imu.initialize();  
}

// Print a data record.
void printData(Print* pr, data_t* data) {
  if (startMicros == 0) {
    startMicros = data->time;
  }
  pr->print(data->time- startMicros);
  pr->write(',');
  pr->print(data->ax);
  pr->write(',');
  pr->print(data->ay);
  pr->write(',');
  pr->print(data->az);
  pr->write(',');
  pr->print(data->gx);
  pr->write(',');
  pr->print(data->gy);
  pr->write(',');
  pr->println(data->gz);
}

// Print data header.
void printHeader(Print* pr) {
  startMicros = 0;
  pr->println(F("micros,ax,ay,az,gx,gy,gz"));
}
