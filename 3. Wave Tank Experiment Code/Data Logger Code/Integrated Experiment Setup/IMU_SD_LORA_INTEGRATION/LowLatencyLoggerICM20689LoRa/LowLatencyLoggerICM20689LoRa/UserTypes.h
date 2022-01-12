#ifndef UserTypes_h
#define UserTypes_h
#include "Arduino.h"
#define FILE_BASE_NAME "mpuraw"
#define TEST_SENSOR 1
#define LOG_DATA 2
#define CONVERT_TO_CSV 3
struct data_t {
  unsigned long time;
  int16_t ax;
  int16_t ay;
  int16_t az;
  int16_t gx;
  int16_t gy;
  int16_t gz;
};
void acquireData(data_t* data);
void printData(Print* pr, data_t* data);
void printHeader(Print* pr);
void userSetup();
void LoRaSetup();
void LoRaSend();
int LoRaReceive();
#endif  // UserTypes_h
