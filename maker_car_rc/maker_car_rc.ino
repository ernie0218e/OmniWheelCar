#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include "joystick.h"
#include "rc.h"
#include "led.h"
#include "battery.h"

#define printf(x, ...)

uint8_t testPattern = 0xFF;

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
  setup_joystick();
  setup_rc(role_sender);
  setup_led();
  
  #if 1
  setup_batt(&batt);
  #endif
}

void loop() {
 static uint32_t count = 0;
 static uint32_t i = 0;
 bool battNormal = false;
 uint8_t button = 0;

 if(read_button(E_JOY_STICK_BTN_0))
   button |=  (1 << RC_RF24_BTN_LEFT);
 else
   button &=  ~(1 << RC_RF24_BTN_LEFT);
   
 if(read_button(E_JOY_STICK_BTN_1))
   button |=  (1 << RC_RF24_BTN_RIGHT);
 else
   button &=  ~(1 << RC_RF24_BTN_RIGHT);
#if 0
printf("left js (x, y) = (%4d, %4d)\n",read_joystick(E_JOY_STICK_CH_LEFT_X),
            read_joystick(E_JOY_STICK_CH_LEFT_Y) );
printf("right js (x, y) = (%4d, %4d)\n",read_joystick(E_JOY_STICK_CH_RIGHT_X),
            read_joystick(E_JOY_STICK_CH_RIGHT_Y) );
printf("button: 0x%2x\n", button);
#else
 update_rc( read_joystick(E_JOY_STICK_CH_LEFT_X),
            read_joystick(E_JOY_STICK_CH_LEFT_Y),
            read_joystick(E_JOY_STICK_CH_RIGHT_X),
            read_joystick(E_JOY_STICK_CH_RIGHT_Y),
            button,
	    count%8);
#endif
//uint32_t time = 0x22222222;
//send_rc(sizeof(uint32_t), (uint8_t*)&time);
printf("i=%d\n", i);

switch(count%8) {
  case 0:
    onLed(ENUM_LED_CH_R);
    break;
  case 1:
    onLed(ENUM_LED_CH_G);
    break;
  case 2:
    onLed(ENUM_LED_CH_B);
    break;
  case 3:
    onLed(ENUN_LED_CH_MAGENTA);
    break;
  case 4:
    onLed(ENUM_LED_CH_YELLOW);
    break;
  case 5:
    onLed(ENUM_LED_CH_CYAN);
    break;
  case 6:
    onLed(ENUM_LED_CH_WHITE);
    break;
  case 7:
    onLed(ENUM_LED_CH_OFF);
    break;
}

i++;
if(i%20 == 0) count++;

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

delay(20);
}


