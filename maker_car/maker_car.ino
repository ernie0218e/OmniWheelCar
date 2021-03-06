#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "rc.h"
#include "led.h"
#include "battery.h"
#include "vehicle.h"
#include "printf.h"

#define printf(x, ...)

extern stRcPkt_t rcPacket;
extern volatile int test;

void setup() {
  Serial.begin(115200);      // open the serial port at 115200 bps:
  printf_begin();
  setup_rc(role_receiver);
  setup_vehicle();
  
}

void loop() {
 bool battNormal = false;

//  vehicleTestWheelPWM(WHEEL_NUM_REAR_LEFT, WHEEL_DIR_CW, 128);
//  vehicleTestWheelPWM(WHEEL_NUM_FRONT_LEFT, WHEEL_DIR_CCW, 128);
//  vehicleTestWheelPWM(WHEEL_NUM_FRONT_RIGHT, WHEEL_DIR_CCW, 128);
//  vehicleTestWheelPWM(WHEEL_NUM_REAR_RIGHT, WHEEL_DIR_CW, 128);
  //vehicleTestMove(VEHICLE_DIR_FORWARD_LEFT, 80, 80);
// Serial.println(rcPacket.payLoad.data.axis_left_x);
// Serial.println(rcPacket.payLoad.data.axis_left_y);
// Serial.println(rcPacket.payLoad.data.axis_right_x);
// Serial.println(rcPacket.payLoad.data.axis_right_y);
  delay(100);
}


