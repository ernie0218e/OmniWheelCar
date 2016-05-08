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

#if 1
stBattCell battCell[2] = {
  {A7, 0, ENUM_BATT_VOLT_NORMAL},
  {A6, 0, ENUM_BATT_VOLT_NORMAL}
};

stBatt batt = {
  2,
//  ENUM_BATT_VOLT_3_0_V,
//  ENUM_BATT_VOLT_3_2_V,
  3500,
  3300,
  ENUM_BATT_VOLT_NORMAL,
  battCell
};
#endif

void setup() {
  Serial.begin(115200);      // open the serial port at 115200 bps:
  printf_begin();
  setup_rc(role_receiver);
  setup_vehicle();
  setup_led();
  
  #if 1
  setup_batt(&batt);
  #endif
}

void loop() {
 bool battNormal = false;
  //onLed((ENUM_LED_CH_t)rcPacket.payLoad.data.led);
  //vehicleMove(rcPacket.payLoad.data.axis_left_x, rcPacket.payLoad.data.axis_left_y);
#if 1 // test battery module
  battNormal = get_batt(&batt);
  printf("Battery Status: %s\n", battNormal ? "Normal" : "Error");
  printf("Cells: (%d, %d)\n", batt.pCell[0].adcValue, batt.pCell[1].adcValue);
  printf("Volts: (%d, %d) mV\n", batt.pCell[0].volt, batt.pCell[1].volt);
  printf("Cell status: (%d, %d) mV\n", batt.pCell[0].voltStatus, batt.pCell[1].voltStatus);
  printf("Batt Status: %d\n", batt.Status);
  switch(batt.Status)
  {
    case ENUM_BATT_VOLT_NORMAL:
      onLedErrorState(false, ENUM_LED_CH_G);
      printf("Batt NORMAL!\n");
    break;
    case ENUM_BATT_VOLT_WARN:
      onLedErrorState(true, ENUM_LED_CH_YELLOW);
      printf("Batt WARN!\n");
    break;
    case ENUM_BATT_VOLT_ERROR:
      onLedErrorState(true, ENUM_LED_CH_R);
      printf("Batt ERROR!\n");
    break;
  }
#endif

  //vehicleTestWheelPWM(WHEEL_NUM_REAR_LEFT, WHEEL_DIR_CW, 128);
  //vehicleTestWheelPWM(WHEEL_NUM_FRONT_LEFT, WHEEL_DIR_CCW, 128);
  //vehicleTestWheelPWM(WHEEL_NUM_FRONT_RIGHT, WHEEL_DIR_CCW, 128);
  //vehicleTestWheelPWM(WHEEL_NUM_REAR_RIGHT, WHEEL_DIR_CW, 128);
  //vehicleTestMove(VEHICLE_DIR_FORWARD_LEFT, 80, 80);
  delay(500);
}


