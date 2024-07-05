/*
  using internal oscillator 8 MHz
  and enabling PB6 & PB7 as GPIO via direct port addressing
*/

//  Example for XGZP6897D library
//  Simple read of temperature and pressure with a CFSensor I2C sensor
//  such as XGZP6897D
/*
   K value for XGZP6897D. It depend on the pressure range of the sensor.
   Table found in the data sheet from CFSensor.com
    https://cfsensor.com/product-category/i2c-sensor/https://cfsensor.com/product-category/i2c-sensor/
  pressure_range (kPa)   K value
  131<P≤260               32
  65<P≤131                64
  32<P≤65                 128
  16<P≤32                 256
  8<P≤16                  512
  4<P≤8                   1024
  2≤P≤4                   2048
  1≤P<2                   4096
  P<1                     8192
  the K value is selected according to the positive pressure value only,
  like -100～100kPa,the K value is 64.
*/


#include <XGZP6897D.h>
#include <EEPROM.h>
#include <TimerOne.h>

// Adafruit NeoPixel library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif


/*
////////////////
PIN DEFINATIONS
///////////////
*/
#define pin_pump 10
#define pin_valve_pressure 6
#define pin_valve_vaccum 7
#define pin_buzzer 1
#define pin_rgb_led 0
#define pin_backlight_led 9
#define pin_b_lock A2
#define pin_b_deflate 11
#define pin_b_dec 13
#define pin_b_mute A0
#define pin_b_power 2
#define pin_b_hold A1
#define pin_b_inc 12
#define pin_b_inflate 8

#define pin_charging_status A3
#define pin_charging_status_full A3
#define pin_battery_gauge A3

// HT1621
#define pin_csPin 5    //Chip selection output
#define pin_wrPin 3    //Read clock output
#define pin_dataPin 4  //Serial data output



/*
*******************************
********LCD DECLARATION********
*******************************
*/
//LCD COMMANDS
#define com_mode 0x52
#define rc_osc 0x30
#define lcd_on 0x06
#define lcd_off 0x04
#define sys_en 0x02
#define ctrl_cmd 0x80
#define data_cmd 0xa0
#define delay_us 1


//LCD Segments
// segment 1
#define c_1A driver_ram_1621[21][3]
#define c_1B driver_ram_1621[21][2]
#define c_1C driver_ram_1621[21][1]
#define c_1D driver_ram_1621[21][0]
#define c_1E driver_ram_1621[19][0]
#define c_1F driver_ram_1621[19][2]
#define c_1G driver_ram_1621[19][1]
// segment 2
#define c_2A driver_ram_1621[25][3]
#define c_2B driver_ram_1621[25][2]
#define c_2C driver_ram_1621[25][1]
#define c_2D driver_ram_1621[25][0]
#define c_2E driver_ram_1621[23][0]
#define c_2F driver_ram_1621[23][2]
#define c_2G driver_ram_1621[23][1]
//segment 3
#define c_3A driver_ram_1621[11][3]
#define c_3B driver_ram_1621[11][2]
#define c_3C driver_ram_1621[11][1]
#define c_3D driver_ram_1621[11][0]
#define c_3E driver_ram_1621[13][1]
#define c_3F driver_ram_1621[13][3]
#define c_3G driver_ram_1621[13][2]
//segment 4
#define c_4A driver_ram_1621[8][3]
#define c_4B driver_ram_1621[8][2]
#define c_4C driver_ram_1621[8][1]
#define c_4D driver_ram_1621[8][0]
#define c_4E driver_ram_1621[9][1]
#define c_4F driver_ram_1621[9][3]
#define c_4G driver_ram_1621[9][2]
//segment 5
#define c_5A driver_ram_1621[6][3]
#define c_5B driver_ram_1621[6][2]
#define c_5C driver_ram_1621[6][1]
#define c_5D driver_ram_1621[6][0]
#define c_5E driver_ram_1621[7][1]
#define c_5F driver_ram_1621[7][3]
#define c_5G driver_ram_1621[7][2]
//segmen      t 6
#define c_6A driver_ram_1621[2][3]
#define c_6B driver_ram_1621[2][2]
#define c_6C driver_ram_1621[2][1]
#define c_6D driver_ram_1621[2][0]
#define c_6E driver_ram_1621[4][1]
#define c_6F driver_ram_1621[4][3]
#define c_6G driver_ram_1621[4][2]

#define c_T1 driver_ram_1621[15][1]
#define c_T2 driver_ram_1621[15][2]
#define c_T3 driver_ram_1621[27][3]
#define c_T4 driver_ram_1621[19][3]
#define c_T5 driver_ram_1621[15][3]
#define c_T6 driver_ram_1621[23][3]
#define c_T7 driver_ram_1621[15][0]
#define c_T8 driver_ram_1621[17][2]
#define c_T9 driver_ram_1621[17][1]
#define c_T10 driver_ram_1621[17][0]
#define c_T11 driver_ram_1621[27][2]
#define c_T12 driver_ram_1621[27][1]
#define c_T13 driver_ram_1621[27][0]
#define c_T14 driver_ram_1621[29][0]
#define c_T15 driver_ram_1621[29][1]
#define c_T16 driver_ram_1621[31][3]
#define c_T17 driver_ram_1621[29][3]
#define c_T18 driver_ram_1621[29][2]
#define c_T19 driver_ram_1621[31][0]
#define c_T20 driver_ram_1621[31][1]
#define c_T21 driver_ram_1621[31][2]
#define c_T22 driver_ram_1621[13][3]
#define c_T23 driver_ram_1621[9][0]
#define c_T24 driver_ram_1621[7][0]
#define c_T25 driver_ram_1621[4][0]
#define c_T26 driver_ram_1621[1][3]
#define c_T27 driver_ram_1621[1][2]
#define c_T28 driver_ram_1621[1][1]
#define c_T29 driver_ram_1621[1][0]


/*
*******************************
********SYSTEM CONSTANTS*******
*******************************
*/
#define c_pulse_pressure_pump_ms 100  //milliseconds
#define c_pulse_vaccum_pump_ms 100    //milliseconds
#define c_pulse_pressure_valve 30
#define c_pulse_vaccum_valve 50
#define c_band 1

#define c_set_value_minimum 10
#define c_set_value_maximum 40

#define c_refresh_screen_time 500000  // microsec

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1  // Popular NeoPixel ring size

#define DELAYVAL 500  // Time (in milliseconds) to pause between pixels

/*
*******************************
******** CONSTANTS*******
*******************************
*/
//buzzer tones

const int c_tone_array[7][6] = {
  { 261, 200, 300, 200, 600, 200 },
  { 600, 200, 300, 200, 361, 200 },
  { 400, 100, 0, 100, 600, 100 },
  { 600, 100, 0, 100, 300, 100 },
  { 261, 200, 277, 200, 300, 200 },
  { 261, 200, 277, 200, 300, 200 },
  { 261, 200, 0, 0, 0, 0 }
};

#define c_tone_power_up 0
#define c_tone_power_down 1
#define c_tone_inflate 2
#define c_tone_deflate 3
#define c_tone_error 4
#define c_tone_success 5
#define c_tone_beep 6

/*
*******************************
********EEPROM ADDRESS*******
*******************************
*/
#define c_address_set_pressure 0
#define c_address_set_pressure_copy 2
#define c_address_deflate_pressure 6
#define c_address_hold_pressure 8
#define c_address_hold_set_timer 10

// K value for a XGZP6897D  -1000-1000Pa
#define K 512  // see table above for the correct value for your sensor, according to the sensitivity.
// create the sensor object, passing the correct K value.
XGZP6897D mysensor(K);

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, pin_rgb_led, NEO_GRB + NEO_KHZ800);

//*************************
//**** GLOBAL VARIABLES****
//*************************
unsigned long gv_millis_old = 0;
unsigned long gv_millis_new = 0;
unsigned long gv_millis_delta = 0;
unsigned long gv_millis_old2 = 0;
unsigned long gv_millis_new2 = 0;
unsigned long gv_millis_delta2 = 0;
unsigned long prev_time, current_time;

uint8_t gv_blink_counter = 0;
uint16_t gv_blink_current_millis = 0;
uint16_t gv_blink_prev_pressure_millis = 0;

float pressure, temperature;
float pressure_cmofH2O;

uint8_t gv_hold_set_timer = 99;
uint8_t gv_set_pressure = 25;
uint8_t gv_hold_pressure = 35;
uint8_t gv_deflate_pressure = 0;

uint8_t gv_setting_mode = 0;
bool gv_set_default_pressure_after_hold = false;
bool gv_chase_start_flag = false;
bool gv_btn_flag = true;
bool gv_deflate_flag = false;
bool gv_power_flag = false;
bool gv_hold_flag = false;
bool gv_change_flag = true;
bool gv_blink_current_pressure_1621_flag = false;
bool gv_blink_lock_seg_1621_flag = false;


bool gv_tone_power_up_flag = false;
bool gv_tone_power_down_flag = false;
bool gv_tone_inflate_flag = false;
bool gv_tone_deflate_flag = false;
bool gv_tone_error_flag = false;
bool gv_tone_success_flag = false;
bool gv_tone_beep_flag = false;
bool gv_rgb_flash = false;
bool gv_high_priority_alarm = false;
bool gv_low_priority_alarm = false;

uint8_t gv_play_tone = -1;

uint8_t gv_leak_set_timer = 30;
uint8_t gv_set_pressure_sucess_alarm = 0;
uint8_t gv_inc_dec_set_timer = 3;
uint8_t gv_reset_timer = 0;
uint8_t gv_buzzer_stop_timer = 120;
uint8_t gv_stable_pressure_timer = 0;
uint8_t gv_hold_timer = 0;
uint8_t gv_leak_timer = gv_leak_set_timer;
uint8_t gv_inc_timer = gv_inc_dec_set_timer;
uint8_t gv_dec_timer = gv_inc_dec_set_timer;
uint8_t gv_press_mute_time = 0;
uint8_t gv_press_lock_time = 0;
uint8_t gv_blink_timer = 0;


uint8_t buttons[8] = { pin_b_lock, pin_b_deflate, pin_b_dec, pin_b_mute, pin_b_power, pin_b_hold, pin_b_inc, pin_b_inflate };
boolean button_current_state[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
boolean button_prev_state[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned long press_time[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
bool gv_btn_status_flag = false;
uint8_t error_timer_in = 20;
uint8_t button_pressed = -1;

#define b_lock 0
#define b_deflate 1
#define b_dec 2
#define b_mute 3
#define b_power 4
#define b_hold 5
#define b_inc 6
#define b_inflate 7


bool driver_ram_1621[32][4] = {
  // COMM3 COMM2 COMM1 COMM0
  { 0, 0, 0, 0 },  //ADDR 0
  { 0, 0, 0, 0 },  //ADDR 1
  { 0, 0, 0, 0 },  //ADDR 2
  { 0, 0, 0, 0 },  //ADDR 3
  { 0, 0, 0, 0 },  //ADDR 4
  { 0, 0, 0, 0 },  //ADDR 5
  { 0, 0, 0, 0 },  //ADDR 6
  { 0, 0, 0, 0 },  //ADDR 7
  { 0, 0, 0, 0 },  //ADDR 8
  { 0, 0, 0, 0 },  //ADDR 9
  { 0, 0, 0, 0 },  //ADDR 10
  { 0, 0, 0, 0 },  //ADDR 11
  { 0, 0, 0, 0 },  //ADDR 12
  { 0, 0, 0, 0 },  //ADDR 13
  { 0, 0, 0, 0 },  //ADDR 14
  { 0, 0, 0, 0 },  //ADDR 15
  { 0, 0, 0, 0 },  //ADDR 16
  { 0, 0, 0, 0 },  //ADDR 17
  { 0, 0, 0, 0 },  //ADDR 18
  { 0, 0, 0, 0 },  //ADDR 19
  { 0, 0, 0, 0 },  //ADDR 20
  { 0, 0, 0, 0 },  //ADDR 21
  { 0, 0, 0, 0 },  //ADDR 22
  { 0, 0, 0, 0 },  //ADDR 23
  { 0, 0, 0, 0 },  //ADDR 24
  { 0, 0, 0, 0 },  //ADDR 25
  { 0, 0, 0, 0 },  //ADDR 26
  { 0, 0, 0, 0 },  //ADDR 27
  { 0, 0, 0, 0 },  //ADDR 28
  { 0, 0, 0, 0 },  //ADDR 29
  { 0, 0, 0, 0 },  //ADDR 30
  { 0, 0, 0, 0 }   //ADDR 31
};


/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** EEPROM ********************* */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void f_set_values(void) {
  if (EEPROM.read(c_address_set_pressure) == 255) EEPROM.write(c_address_set_pressure, gv_set_pressure);
  if (EEPROM.read(c_address_set_pressure_copy) == 255) EEPROM.write(c_address_set_pressure_copy, 25);
  if (EEPROM.read(c_address_deflate_pressure) == 255) EEPROM.write(c_address_deflate_pressure, gv_deflate_pressure);
  if (EEPROM.read(c_address_hold_pressure) == 255) EEPROM.write(c_address_hold_pressure, gv_hold_pressure);
  if (EEPROM.read(c_address_hold_set_timer) == 255) EEPROM.write(c_address_hold_set_timer, gv_hold_set_timer);
}

void f_get_values(void) {
  gv_set_pressure = EEPROM.read(c_address_set_pressure);
  gv_hold_set_timer = EEPROM.read(c_address_hold_set_timer);
  gv_hold_pressure = EEPROM.read(c_address_hold_pressure);
  gv_deflate_pressure = EEPROM.read(c_address_deflate_pressure);
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void f_update_set_pressure(void) {
  EEPROM.update(c_address_set_pressure, gv_set_pressure);
}

void f_update_hold_set_timer(void) {
  EEPROM.update(c_address_hold_set_timer, gv_hold_set_timer);
}

void f_update_hold_pressure(void) {
  EEPROM.update(c_address_hold_pressure, gv_hold_pressure);
}

void f_update_deflate_pressure(void) {
  EEPROM.update(c_address_deflate_pressure, gv_deflate_pressure);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Ceil and Floor for pressure_cmOfH2O ********************* */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
uint8_t f_pressure_cmofH2O(void) {
  uint8_t lv_pressure_cmofH2O = pressure_cmofH2O;
  uint8_t lv_pressure;

  if (gv_hold_flag) {
    lv_pressure = gv_hold_pressure;
  } else if (gv_deflate_flag) {
    lv_pressure = gv_deflate_pressure;
  } else {
    lv_pressure = gv_set_pressure;
  }


  if (ceil(pressure_cmofH2O) == lv_pressure) {
    lv_pressure_cmofH2O = ceil(pressure_cmofH2O);
  } else if (floor(pressure_cmofH2O) == lv_pressure) {
    lv_pressure_cmofH2O = floor(pressure_cmofH2O);
  }

  if (lv_pressure_cmofH2O < 0) {
    return 0;
  } else if (lv_pressure_cmofH2O > 99) {
    return 99;
  } else {
    return lv_pressure_cmofH2O;
  }
}

// Jay@123

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** LCD Driver HT1621 ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void SendBit_1621(uint8_t lv_sdata, uint8_t lv_cnt) {
  uint8_t i;
  for (i = 0; i < lv_cnt; i++) {
    digitalWrite(pin_wrPin, LOW);
    delayMicroseconds(delay_us);
    if (lv_sdata & 0x80) digitalWrite(pin_dataPin, HIGH);
    else digitalWrite(pin_dataPin, LOW);
    digitalWrite(pin_wrPin, HIGH);
    delayMicroseconds(delay_us);
    lv_sdata <<= 1;
  }
}

void SendCmd_1621(uint8_t lv_command) {
  digitalWrite(pin_csPin, LOW);
  SendBit_1621(0x80, 4);
  SendBit_1621(lv_command, 8);
  digitalWrite(pin_csPin, HIGH);
}

void Write_1621(uint8_t lv_addr, uint8_t lv_sdata) {
  lv_addr <<= 2;
  digitalWrite(pin_csPin, LOW);
  SendBit_1621(0xa0, 3);
  SendBit_1621(lv_addr, 6);
  SendBit_1621(lv_sdata, 8);
  digitalWrite(pin_csPin, HIGH);
}

void HT1621_all_off(uint8_t lv_num) {
  uint8_t i;
  uint8_t lv_addr = 0;
  for (i = 0; i < lv_num; i++) {
    Write_1621(lv_addr, 0x00);
    lv_addr += 2;
  }
}

void HT1621_all_on(uint8_t lv_num) {
  uint8_t i;
  uint8_t lv_addr = 0;
  for (i = 0; i < lv_num; i++) {
    Write_1621(lv_addr, 0xff);
    lv_addr += 2;
  }
}

void init_1621(void) {
  pinMode(pin_csPin, OUTPUT);
  pinMode(pin_wrPin, OUTPUT);
  pinMode(pin_dataPin, OUTPUT);
  pinMode(pin_backlight_led, OUTPUT);

  digitalWrite(pin_csPin, HIGH);
  digitalWrite(pin_dataPin, HIGH);
  digitalWrite(pin_wrPin, HIGH);

  delay(50);

  SendCmd_1621(sys_en);
  SendCmd_1621(rc_osc);
  SendCmd_1621(com_mode);
  SendCmd_1621(lcd_on);
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void update_ram_1621() {
  // byte lv_data = 0;
  byte i;
  for (i = 0; i < 32; i++) {
    byte lv_data = 0;
    bitWrite(lv_data, 7, driver_ram_1621[i][0]);
    bitWrite(lv_data, 6, driver_ram_1621[i][1]);
    bitWrite(lv_data, 5, driver_ram_1621[i][2]);
    bitWrite(lv_data, 4, driver_ram_1621[i][3]);

    Write_1621(i, lv_data);
  }
}

void set_current_pressure_tens(uint8_t lv_pressure_tens) {
  switch (lv_pressure_tens) {
    case 0:
      c_1A = 1;
      c_1B = 1;
      c_1C = 1;
      c_1D = 1;
      c_1E = 1;
      c_1F = 1;
      c_1G = 0;
      break;
    case 1:
      c_1A = 0;
      c_1B = 1;
      c_1C = 1;
      c_1D = 0;
      c_1E = 0;
      c_1F = 0;
      c_1G = 0;
      break;
    case 2:
      c_1A = 1;
      c_1B = 1;
      c_1C = 0;
      c_1D = 1;
      c_1E = 1;
      c_1F = 0;
      c_1G = 1;
      break;
    case 3:
      c_1A = 1;
      c_1B = 1;
      c_1C = 1;
      c_1D = 1;
      c_1E = 0;
      c_1F = 0;
      c_1G = 1;
      break;
    case 4:
      c_1A = 0;
      c_1B = 1;
      c_1C = 1;
      c_1D = 0;
      c_1E = 0;
      c_1F = 1;
      c_1G = 1;
      break;
    case 5:
      c_1A = 1;
      c_1B = 0;
      c_1C = 1;
      c_1D = 1;
      c_1E = 0;
      c_1F = 1;
      c_1G = 1;
      break;
    case 6:
      c_1A = 1;
      c_1B = 0;
      c_1C = 1;
      c_1D = 1;
      c_1E = 1;
      c_1F = 1;
      c_1G = 1;
      break;
    case 7:
      c_1A = 1;
      c_1B = 1;
      c_1C = 1;
      c_1D = 0;
      c_1E = 0;
      c_1F = 0;
      c_1G = 0;
      break;
    case 8:
      c_1A = 1;
      c_1B = 1;
      c_1C = 1;
      c_1D = 1;
      c_1E = 1;
      c_1F = 1;
      c_1G = 1;
      break;
    case 9:
      c_1A = 1;
      c_1B = 1;
      c_1C = 1;
      c_1D = 1;
      c_1E = 0;
      c_1F = 1;
      c_1G = 1;
      break;
    case 10:
      c_1A = 1;
      c_1B = 0;
      c_1C = 0;
      c_1D = 1;
      c_1E = 1;
      c_1F = 1;
      c_1G = 1;
      break;
    case 11:
      c_1A = 0;
      c_1B = 0;
      c_1C = 0;
      c_1D = 0;
      c_1E = 0;
      c_1F = 0;
      c_1G = 0;
      break;
  }
}

void set_current_pressure_once(uint8_t lv_pressure_once) {
  switch (lv_pressure_once) {
    case 0:
      c_2A = 1;
      c_2B = 1;
      c_2C = 1;
      c_2D = 1;
      c_2E = 1;
      c_2F = 1;
      c_2G = 0;
      break;
    case 1:
      c_2A = 0;
      c_2B = 1;
      c_2C = 1;
      c_2D = 0;
      c_2E = 0;
      c_2F = 0;
      c_2G = 0;
      break;
    case 2:
      c_2A = 1;
      c_2B = 1;
      c_2C = 0;
      c_2D = 1;
      c_2E = 1;
      c_2F = 0;
      c_2G = 1;
      break;
    case 3:
      c_2A = 1;
      c_2B = 1;
      c_2C = 1;
      c_2D = 1;
      c_2E = 0;
      c_2F = 0;
      c_2G = 1;
      break;
    case 4:
      c_2A = 0;
      c_2B = 1;
      c_2C = 1;
      c_2D = 0;
      c_2E = 0;
      c_2F = 1;
      c_2G = 1;
      break;
    case 5:
      c_2A = 1;
      c_2B = 0;
      c_2C = 1;
      c_2D = 1;
      c_2E = 0;
      c_2F = 1;
      c_2G = 1;
      break;
    case 6:
      c_2A = 1;
      c_2B = 0;
      c_2C = 1;
      c_2D = 1;
      c_2E = 1;
      c_2F = 1;
      c_2G = 1;
      break;
    case 7:
      c_2A = 1;
      c_2B = 1;
      c_2C = 1;
      c_2D = 0;
      c_2E = 0;
      c_2F = 0;
      c_2G = 0;
      break;
    case 8:
      c_2A = 1;
      c_2B = 1;
      c_2C = 1;
      c_2D = 1;
      c_2E = 1;
      c_2F = 1;
      c_2G = 1;
      break;
    case 9:
      c_2A = 1;
      c_2B = 1;
      c_2C = 1;
      c_2D = 1;
      c_2E = 0;
      c_2F = 1;
      c_2G = 1;
      break;
    case 10:
      c_2A = 1;
      c_2B = 1;
      c_2C = 1;
      c_2D = 0;
      c_2E = 1;
      c_2F = 1;
      c_2G = 1;
      break;
    case 11:
      c_2A = 0;
      c_2B = 0;
      c_2C = 0;
      c_2D = 0;
      c_2E = 0;
      c_2F = 0;
      c_2G = 0;
      break;
  }
}

void set_hold_timer_tens(uint8_t lv_timer_tens) {
  switch (lv_timer_tens) {
    case 0:
      c_3A = 1;
      c_3B = 1;
      c_3C = 1;
      c_3D = 1;
      c_3E = 1;
      c_3F = 1;
      c_3G = 0;
      break;
    case 1:
      c_3A = 0;
      c_3B = 1;
      c_3C = 1;
      c_3D = 0;
      c_3E = 0;
      c_3F = 0;
      c_3G = 0;
      break;
    case 2:
      c_3A = 1;
      c_3B = 1;
      c_3C = 0;
      c_3D = 1;
      c_3E = 1;
      c_3F = 0;
      c_3G = 1;
      break;
    case 3:
      c_3A = 1;
      c_3B = 1;
      c_3C = 1;
      c_3D = 1;
      c_3E = 0;
      c_3F = 0;
      c_3G = 1;
      break;
    case 4:
      c_3A = 0;
      c_3B = 1;
      c_3C = 1;
      c_3D = 0;
      c_3E = 0;
      c_3F = 1;
      c_3G = 1;
      break;
    case 5:
      c_3A = 1;
      c_3B = 0;
      c_3C = 1;
      c_3D = 1;
      c_3E = 0;
      c_3F = 1;
      c_3G = 1;
      break;
    case 6:
      c_3A = 1;
      c_3B = 0;
      c_3C = 1;
      c_3D = 1;
      c_3E = 1;
      c_3F = 1;
      c_3G = 1;
      break;
    case 7:
      c_3A = 1;
      c_3B = 1;
      c_3C = 1;
      c_3D = 0;
      c_3E = 0;
      c_3F = 0;
      c_3G = 0;
      break;
    case 8:
      c_3A = 1;
      c_3B = 1;
      c_3C = 1;
      c_3D = 1;
      c_3E = 1;
      c_3F = 1;
      c_3G = 1;
      break;
    case 9:
      c_3A = 1;
      c_3B = 1;
      c_3C = 1;
      c_3D = 1;
      c_3E = 0;
      c_3F = 1;
      c_3G = 1;
      break;
    case 10:
      c_3A = 1;
      c_3B = 1;
      c_3C = 1;
      c_3D = 0;
      c_3E = 1;
      c_3F = 1;
      c_3G = 1;
      break;
    case 11:
      c_3A = 0;
      c_3B = 0;
      c_3C = 0;
      c_3D = 0;
      c_3E = 0;
      c_3F = 0;
      c_3G = 0;
      break;
  }
}

void set_hold_timer_once(uint8_t lv_timer_once) {
  switch (lv_timer_once) {
    case 0:
      c_4A = 1;
      c_4B = 1;
      c_4C = 1;
      c_4D = 1;
      c_4E = 1;
      c_4F = 1;
      c_4G = 0;
      break;
    case 1:
      c_4A = 0;
      c_4B = 1;
      c_4C = 1;
      c_4D = 0;
      c_4E = 0;
      c_4F = 0;
      c_4G = 0;
      break;
    case 2:
      c_4A = 1;
      c_4B = 1;
      c_4C = 0;
      c_4D = 1;
      c_4E = 1;
      c_4F = 0;
      c_4G = 1;
      break;
    case 3:
      c_4A = 1;
      c_4B = 1;
      c_4C = 1;
      c_4D = 1;
      c_4E = 0;
      c_4F = 0;
      c_4G = 1;
      break;
    case 4:
      c_4A = 0;
      c_4B = 1;
      c_4C = 1;
      c_4D = 0;
      c_4E = 0;
      c_4F = 1;
      c_4G = 1;
      break;
    case 5:
      c_4A = 1;
      c_4B = 0;
      c_4C = 1;
      c_4D = 1;
      c_4E = 0;
      c_4F = 1;
      c_4G = 1;
      break;
    case 6:
      c_4A = 1;
      c_4B = 0;
      c_4C = 1;
      c_4D = 1;
      c_4E = 1;
      c_4F = 1;
      c_4G = 1;
      break;
    case 7:
      c_4A = 1;
      c_4B = 1;
      c_4C = 1;
      c_4D = 0;
      c_4E = 0;
      c_4F = 0;
      c_4G = 0;
      break;
    case 8:
      c_4A = 1;
      c_4B = 1;
      c_4C = 1;
      c_4D = 1;
      c_4E = 1;
      c_4F = 1;
      c_4G = 1;
      break;
    case 9:
      c_4A = 1;
      c_4B = 1;
      c_4C = 1;
      c_4D = 1;
      c_4E = 0;
      c_4F = 1;
      c_4G = 1;
      break;
    case 10:
      c_4A = 1;
      c_4B = 1;
      c_4C = 1;
      c_4D = 0;
      c_4E = 1;
      c_4F = 1;
      c_4G = 1;
      break;
    case 11:
      c_4A = 0;
      c_4B = 0;
      c_4C = 0;
      c_4D = 0;
      c_4E = 0;
      c_4F = 0;
      c_4G = 0;
      break;
  }
}

void set_pressure_tens(uint8_t lv_pressure_once) {
  switch (lv_pressure_once) {
    case 0:
      c_5A = 1;
      c_5B = 1;
      c_5C = 1;
      c_5D = 1;
      c_5E = 1;
      c_5F = 1;
      c_5G = 0;
      break;
    case 1:
      c_5A = 0;
      c_5B = 1;
      c_5C = 1;
      c_5D = 0;
      c_5E = 0;
      c_5F = 0;
      c_5G = 0;
      break;
    case 2:
      c_5A = 1;
      c_5B = 1;
      c_5C = 0;
      c_5D = 1;
      c_5E = 1;
      c_5F = 0;
      c_5G = 1;
      break;
    case 3:
      c_5A = 1;
      c_5B = 1;
      c_5C = 1;
      c_5D = 1;
      c_5E = 0;
      c_5F = 0;
      c_5G = 1;
      break;
    case 4:
      c_5A = 0;
      c_5B = 1;
      c_5C = 1;
      c_5D = 0;
      c_5E = 0;
      c_5F = 1;
      c_5G = 1;
      break;
    case 5:
      c_5A = 1;
      c_5B = 0;
      c_5C = 1;
      c_5D = 1;
      c_5E = 0;
      c_5F = 1;
      c_5G = 1;
      break;
    case 6:
      c_5A = 1;
      c_5B = 0;
      c_5C = 1;
      c_5D = 1;
      c_5E = 1;
      c_5F = 1;
      c_5G = 1;
      break;
    case 7:
      c_5A = 1;
      c_5B = 1;
      c_5C = 1;
      c_5D = 0;
      c_5E = 0;
      c_5F = 0;
      c_5G = 0;
      break;
    case 8:
      c_5A = 1;
      c_5B = 1;
      c_5C = 1;
      c_5D = 1;
      c_5E = 1;
      c_5F = 1;
      c_5G = 1;
      break;
    case 9:
      c_5A = 1;
      c_5B = 1;
      c_5C = 1;
      c_5D = 1;
      c_5E = 0;
      c_5F = 1;
      c_5G = 1;
      break;
    case 10:
      c_5A = 1;
      c_5B = 0;
      c_5C = 0;
      c_5D = 1;
      c_5E = 1;
      c_5F = 1;
      c_5G = 1;
      break;
    case 11:
      c_5A = 0;
      c_5B = 0;
      c_5C = 0;
      c_5D = 0;
      c_5E = 0;
      c_5F = 0;
      c_5G = 0;
      break;
  }
}

void set_pressure_once(uint8_t lv_pressure_once) {
  switch (lv_pressure_once) {
    case 0:
      c_6A = 1;
      c_6B = 1;
      c_6C = 1;
      c_6D = 1;
      c_6E = 1;
      c_6F = 1;
      c_6G = 0;
      break;
    case 1:
      c_6A = 0;
      c_6B = 1;
      c_6C = 1;
      c_6D = 0;
      c_6E = 0;
      c_6F = 0;
      c_6G = 0;
      break;
    case 2:
      c_6A = 1;
      c_6B = 1;
      c_6C = 0;
      c_6D = 1;
      c_6E = 1;
      c_6F = 0;
      c_6G = 1;
      break;
    case 3:
      c_6A = 1;
      c_6B = 1;
      c_6C = 1;
      c_6D = 1;
      c_6E = 0;
      c_6F = 0;
      c_6G = 1;
      break;
    case 4:
      c_6A = 0;
      c_6B = 1;
      c_6C = 1;
      c_6D = 0;
      c_6E = 0;
      c_6F = 1;
      c_6G = 1;
      break;
    case 5:
      c_6A = 1;
      c_6B = 0;
      c_6C = 1;
      c_6D = 1;
      c_6E = 0;
      c_6F = 1;
      c_6G = 1;
      break;
    case 6:
      c_6A = 1;
      c_6B = 0;
      c_6C = 1;
      c_6D = 1;
      c_6E = 1;
      c_6F = 1;
      c_6G = 1;
      break;
    case 7:
      c_6A = 1;
      c_6B = 1;
      c_6C = 1;
      c_6D = 0;
      c_6E = 0;
      c_6F = 0;
      c_6G = 0;
      break;
    case 8:
      c_6A = 1;
      c_6B = 1;
      c_6C = 1;
      c_6D = 1;
      c_6E = 1;
      c_6F = 1;
      c_6G = 1;
      break;
    case 9:
      c_6A = 1;
      c_6B = 1;
      c_6C = 1;
      c_6D = 1;
      c_6E = 0;
      c_6F = 1;
      c_6G = 1;
      break;
    case 10:
      c_6A = 1;
      c_6B = 1;
      c_6C = 1;
      c_6D = 0;
      c_6E = 1;
      c_6F = 1;
      c_6G = 1;
      break;
    case 11:
      c_6A = 0;
      c_6B = 0;
      c_6C = 0;
      c_6D = 0;
      c_6E = 0;
      c_6F = 0;
      c_6G = 0;
      break;
  }
}

void set_current_pressure_1621(uint8_t lv_pressure) {
  set_current_pressure_once(lv_pressure % 10);
  if (lv_pressure / 10 == 0) {
    set_current_pressure_tens(11);
  } else {
    set_current_pressure_tens(lv_pressure / 10);
  }
}

void set_current_pressure_1621_off(void) {
  set_current_pressure_once(11);
  set_current_pressure_tens(11);
}

void set_pressure_1621(uint8_t lv_pressure) {
  set_pressure_once(lv_pressure % 10);
  set_pressure_tens(lv_pressure / 10);
}

void set_hold_timer_1621(uint8_t lv_hold_timer) {
  set_hold_timer_once(((lv_hold_timer) % 10));
  set_hold_timer_tens(lv_hold_timer / 10);
  //  set_hold_timer_once(((lv_hold_timer / 60) % 10)+1);
  //  set_hold_timer_tens(lv_hold_timer / 600);
}

void f_mbar_enable(void) {
  c_T16 = 1;
}

void f_mbar_disable(void) {
  c_T16 = 0;
}

void f_cm_of_h2o_seg_enable(void) {
  c_T17 = 1;
  c_T18 = 1;
}

void f_cm_of_h2o_seg_disable(void) {
  c_T17 = 0;
  c_T18 = 0;
}

void f_setting_seg_enable(void) {
  c_T19 = 1;
}

void f_setting_seg_disable(void) {
  c_T19 = 0;
}

void f_alarm_seg_disable(void) {
  c_T7 = 0;
}

void f_alarm_seg_enable(void) {
  c_T7 = 1;
}

void f_lock_seg_enable(void) {
  c_T11 = 1;
}

void f_lock_seg_disable(void) {
  c_T11 = 0;
}

void f_inflate_seg_enable(void) {
  c_T8 = 1;
}

void f_inflate_seg_disable(void) {
  c_T8 = 0;
}

void f_deflate_seg_enable(void) {
  c_T9 = 1;
}

void f_deflate_seg_disable(void) {
  c_T9 = 0;
}

void f_leak_seg_enable(void) {
  c_T10 = 1;
}

void f_leak_seg_disable(void) {
  c_T10 = 0;
}

void f_hold_seg_enable(void) {
  c_T23 = 1;
}

void f_hold_seg_disable(void) {
  c_T23 = 0;
}

void f_inc_seg_enable(void) {
  c_T12 = 1;
  c_T13 = 1;
}

void f_inc_seg_disable(void) {
  c_T12 = 0;
  c_T13 = 0;
}

void f_dec_seg_enable(void) {
  c_T14 = 1;
  c_T15 = 1;
}

void f_dec_seg_disable(void) {
  c_T14 = 0;
  c_T15 = 0;
}

void f_always_on_seg(void) {
  if (pressure_cmofH2O > 1) {
    f_inflate_seg_enable();
  } else {
    f_inflate_seg_disable();
  }
  f_cm_of_h2o_seg_enable();
  c_T25 = 1;
  c_T1 = 1;
  c_T3 = 1;
  c_T2 = 1;
  c_T28 = 1;
  c_T29 = 1;
}

void f_battery_all_seg_enable(void) {
  c_T3 = 1;
  c_T4 = 1;
  c_T5 = 1;
  c_T6 = 1;
}

void f_battery_all_seg_disable(void) {
  c_T3 = 0;
  c_T4 = 0;
  c_T5 = 0;
  c_T6 = 0;
}

void f_set_hold_timer_1621_off() {
  set_hold_timer_once(11);
  set_hold_timer_tens(11);
  c_T26 = 0;
}

void f_set_lcd(void) {
  f_always_on_seg();
  set_current_pressure_1621(f_pressure_cmofH2O());

  if (gv_hold_flag) {
    set_pressure_1621(gv_hold_pressure);
  } else {
    set_pressure_1621(gv_set_pressure);
  }

  if (gv_hold_timer) {
    gv_set_default_pressure_after_hold = true;
    set_hold_timer_1621(gv_hold_timer);
    c_T26 = 1;
  } else {
    if (gv_set_default_pressure_after_hold) {
      gv_hold_flag = false;
      gv_set_default_pressure_after_hold = false;
      gv_hold_timer = gv_reset_timer;
      error_timer_in = gv_reset_timer;
      gv_leak_timer = gv_leak_set_timer;
      f_pulse_pressure();
      gv_change_flag = true;
      f_play_tone(c_tone_inflate);
    }
    f_set_hold_timer_1621_off();
    c_T26 = 0;
    f_hold_seg_disable();
  }
}

void f_blink_lock_seg(void) {
  Timer1.stop();
  if (!gv_btn_flag && gv_blink_lock_seg_1621_flag) {
    gv_blink_current_millis = millis();
    if (gv_blink_current_millis - gv_blink_prev_pressure_millis > 100) {
      gv_blink_prev_pressure_millis = gv_blink_current_millis;
      gv_blink_counter = gv_blink_counter + 1;
    }

    if (gv_blink_counter % 2) {
      f_lock_seg_disable();
    } else {
      f_lock_seg_enable();
    }

    update_ram_1621();

    if (gv_blink_counter == 4) {
      gv_blink_counter = 0;
      gv_blink_lock_seg_1621_flag = false;
    }
  }
  Timer1.restart();
}



void f_blink_current_pressure_1621(void) {
  Timer1.stop();
  if (gv_blink_current_pressure_1621_flag) {
    gv_blink_current_millis = millis();
    if (gv_blink_current_millis - gv_blink_prev_pressure_millis > 100) {
      gv_blink_prev_pressure_millis = gv_blink_current_millis;
      gv_blink_counter = gv_blink_counter + 1;
    }

    if (gv_blink_counter % 2) {
      set_current_pressure_1621_off();
    } else {
      set_current_pressure_1621(f_pressure_cmofH2O());
    }

    update_ram_1621();

    if (gv_blink_counter == 4) {
      gv_blink_counter = 0;
      gv_blink_current_pressure_1621_flag = false;
    }
  }
  Timer1.restart();
}

// bool f_check_screen_update(void) {
//   for (uint8_t i = 0; i < 32; i++) {
//     for (uint8_t j = 0; j < 4; j++) {
//       if (driver_ram_1621[i][j] != driver_old_ram_1621[i][j]) {
//         return true;
//       }
//     }
//   }
//   return false;
// }

// void f_update_old_ram_1621(void) {
//   for (uint8_t i = 0; i < 32; i++) {
//     for (uint8_t j = 0; j < 4; j++) {
//       driver_old_ram_1621[i][j] = driver_ram_1621[i][j];
//     }
//   }
// }

void f_refresh_screen(void) {

  // digitalWrite(pin_csPin, LOW);
  // SendBit_1621(0xa0, 3);
  // SendBit_1621(0, 6);
  // uint8_t lv_data = 0;
  // for (int lv_addr = 0; lv_addr < 8; lv_addr++) {
  //   lv_data = driver_ram_1621[lv_addr];
  //   SendBit_1621(lv_data, 8);
  // }
  // digitalWrite(pin_csPin, HIGH);
  /* ---------------------------------------------------------*/
  digitalWrite(pin_csPin, LOW);
  SendBit_1621(0xa0, 3);
  SendBit_1621(0, 6);
  for (int lv_addr = 0; lv_addr < 32; lv_addr++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(pin_wrPin, LOW);
      if (driver_ram_1621[lv_addr][j] & 0x01) digitalWrite(pin_dataPin, HIGH);
      else digitalWrite(pin_dataPin, LOW);
      digitalWrite(pin_wrPin, HIGH);
    }
  }
  digitalWrite(pin_csPin, HIGH);
  /* ---------------------------------------------------------- */
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************* BMS ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void f_battery_gauge(void) {
  float charge_percentage = ((analogRead(pin_battery_gauge) - 655) / 308) * 100;
  if (charge_percentage >= 67) {
    c_T4 = 1;
    c_T5 = 1;
    c_T6 = 1;
  } else if (charge_percentage < 67 && charge_percentage >= 34) {
    c_T4 = 1;
    c_T5 = 1;
    c_T6 = 0;
  } else if (charge_percentage < 34 && charge_percentage >= 10) {
    c_T4 = 1;
    c_T5 = 0;
    c_T6 = 0;
  } else if (charge_percentage < 10 && charge_percentage >= 0) {
    c_T4 = 0;
    c_T5 = 0;
    c_T6 = 0;
  }
}

void f_charging(void) {
  if (/*digitalRead(charging_status)*/ 1) {
    if (/*digitalRead(charging_status_full)*/ 1) {
      if (gv_blink_timer % 2) {
        f_battery_all_seg_enable();
      } else {
        f_battery_all_seg_disable();
      }
    } else {
      if (gv_blink_timer % 4 == 0) {
        c_T4 = 0;
        c_T5 = 0;
        c_T6 = 0;
      } else if (gv_blink_timer % 4 == 1) {
        c_T4 = 1;
        c_T5 = 0;
        c_T6 = 0;
      } else if (gv_blink_timer % 4 == 2) {
        c_T4 = 1;
        c_T5 = 1;
        c_T6 = 0;
      } else if (gv_blink_timer % 4 == 3) {
        c_T4 = 1;
        c_T5 = 1;
        c_T6 = 1;
      }
    }
  } else {
    f_battery_gauge();
  }
  c_T3 = 1;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************* Valve Motor ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void f_pulse_pressure() {
  digitalWrite(pin_pump, HIGH);
  delay(c_pulse_pressure_pump_ms);
  digitalWrite(pin_valve_pressure, HIGH);
  delay(c_pulse_pressure_valve);
  digitalWrite(pin_pump, LOW);
  digitalWrite(pin_valve_pressure, LOW);
}

void f_pulse_vaccum() {
  digitalWrite(pin_pump, HIGH);
  delay(c_pulse_vaccum_pump_ms);
  digitalWrite(pin_valve_vaccum, HIGH);
  delay(c_pulse_pressure_valve);
  digitalWrite(pin_pump, LOW);
  digitalWrite(pin_valve_vaccum, LOW);
}

void f_set_pressure() {
  if (gv_deflate_flag) {
    if (pressure_cmofH2O > gv_deflate_pressure + c_band) {
      f_inc_seg_disable();
      f_dec_seg_enable();
      f_pulse_vaccum();
      //    Serial.println("vaccum");
    } else if (pressure_cmofH2O < gv_deflate_pressure - c_band) {
      f_dec_seg_disable();
      f_inc_seg_enable();
      f_pulse_pressure();
      //    Serial.println("pressure");
    } else {
      f_dec_seg_disable();
      f_inc_seg_disable();
    }
  } else if (gv_hold_flag) {
    if (pressure_cmofH2O > gv_hold_pressure + c_band) {
      f_inc_seg_disable();
      f_dec_seg_enable();
      f_pulse_vaccum();
      //    Serial.println("vaccum");
    } else if (pressure_cmofH2O < gv_hold_pressure - c_band) {
      f_dec_seg_disable();
      f_inc_seg_enable();
      f_pulse_pressure();
      //    Serial.println("pressure");
    } else {
      f_dec_seg_disable();
      f_inc_seg_disable();
    }
  } else {
    if (pressure_cmofH2O > gv_set_pressure + c_band) {
      f_inc_seg_disable();
      f_dec_seg_enable();
      f_pulse_vaccum();
      //    Serial.println("vaccum");
    } else if (pressure_cmofH2O < gv_set_pressure - c_band) {
      f_dec_seg_disable();
      f_inc_seg_enable();
      f_pulse_pressure();
      //    Serial.println("pressure");
    } else {
      f_dec_seg_disable();
      f_inc_seg_disable();
    }
  }
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** get button status ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void f_get_button_state() {

  current_time = millis();
  // iterate arrays
  for (uint8_t i = 0; i < sizeof(button_current_state) / sizeof(button_current_state[0]); i++) {

    // if button pressed
    if (button_current_state[i] != digitalRead(buttons[i])) {
      button_prev_state[i] = button_current_state[i];
      button_current_state[i] = digitalRead(buttons[i]);
    }

    if (!button_current_state[i] && !gv_btn_status_flag) {
      prev_time = current_time;
      gv_btn_status_flag = true;
      button_pressed = i;
      Serial.print("btn pressed ");
      Serial.println(i);
    }

    if (button_current_state[button_pressed] && gv_btn_status_flag) {
      Serial.print("btn released ");
      Serial.println(i);
      gv_btn_status_flag = false;
    }

    //    if (button_current_state[button_pressed]) {
    //      if (press_time[i] == 0) {
    //      } else if (press_time[i] < 2000) {
    //        Serial.print("Short press btn ");
    //        Serial.println(i);
    //        Serial.println(press_time[button_pressed]);
    //      } else {
    //        Serial.print("long press btn ");
    //        Serial.println(i);
    //        Serial.println(press_time[button_pressed]);
    //      }
    //    }

    if (button_prev_state[i] && !button_current_state[i]) {
      press_time[i] = current_time - prev_time;
    }
    if (button_current_state[i]) {
      press_time[i] = 0;
    }
  }

  // for (uint8_t i = 0; i < 8; i++) {
  //   Serial.print(button_prev_state[i]);
  //   if (i != 7) {
  //     Serial.print(",");
  //   }
  // }
  // Serial.println();

  // for (uint8_t i = 0; i < 8; i++) {
  //   Serial.print(button_current_state[i]);
  //   if (i != 7) {
  //     Serial.print(",");
  //   }
  // }
  // Serial.println();

  // for (uint8_t i = 0; i < 8; i++) {
  //   Serial.print(press_time[i]);
  //   if (i != 7) {
  //     Serial.print(",");
  //   }
  // }Serial.println();
  // Serial.println(gv_btn_status_flag);
  // Serial.println();
  // delay(1000);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Buzzer ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void f_play_tone(uint8_t lv_case) {
  if (gv_buzzer_stop_timer == 120){
    for (uint8_t i = 0; i < 6; i = i + 2) {
    tone(pin_buzzer, c_tone_array[lv_case][i]);
    delay(c_tone_array[lv_case][i + 1]);
  }
  noTone(pin_buzzer);
  }
}

void f_get_sucess_status() {
  if ((pressure_cmofH2O > gv_set_pressure - c_band) && (pressure_cmofH2O < gv_set_pressure + c_band) && (gv_set_pressure_sucess_alarm == 0 /*signifies Not achieved yet*/)) {
    gv_set_pressure_sucess_alarm = 1;
  } else if ((pressure_cmofH2O < gv_set_pressure - c_band) || (pressure_cmofH2O > gv_set_pressure + c_band)) {
    gv_set_pressure_sucess_alarm = 0;
  }
}

void f_sucess_status_action(void) {
  f_get_sucess_status();
  //f_beep_sucess_status();
  f_play_tone(c_tone_success);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Button Functions ******************* */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

uint8_t f_dec_by() {
  if (gv_set_pressure == c_set_value_minimum) {
    return 0;
  } else {
    return 1;
  }
}

uint8_t f_inc_by() {
  if (gv_set_pressure == c_set_value_maximum) {
    return 0;
  } else {
    return 1;
  }
}

void b_inc_action() {
  // inc_trg
  if (press_time[b_inc]) {
    gv_deflate_flag = false;
    gv_set_pressure = gv_set_pressure + f_inc_by();
    f_update_set_pressure();
    while (digitalRead(pin_b_inc) == LOW) {}
    gv_inc_timer = gv_reset_timer;
    gv_chase_start_flag = true;
    gv_change_flag = true;
    error_timer_in = gv_reset_timer;
    gv_leak_timer = gv_leak_set_timer;
    f_hold_seg_disable();
    f_set_lcd();
    f_deflate_seg_disable();
    delay(10);
  }
}

void b_hold_setting_on(void) {
  //  hold_setting
  f_get_button_state();
  if (press_time[b_hold] >= 8000) {
    gv_deflate_flag = false;
    if (gv_setting_mode == 0) {
      f_play_tone(c_tone_beep);
      gv_setting_mode = 1;
      while (digitalRead(pin_b_hold)) {}
    }
  }
}


void b_deflate_setting_on(void) {
  //deflate setting
  f_get_button_state();
  if (press_time[b_deflate] >= 8000) {
    f_play_tone(c_tone_deflate);
    if (gv_setting_mode == 0) {
      gv_setting_mode = 3;
      while (digitalRead(pin_b_deflate) == LOW) {}
    }
  }
}

void b_dec_action() {
  // dec_trg
  if (press_time[b_dec]) {
    gv_deflate_flag = false;
    gv_set_pressure = gv_set_pressure - f_dec_by();
    f_update_set_pressure();
    gv_chase_start_flag = true;
    gv_change_flag = true;
    gv_dec_timer = gv_reset_timer;
    error_timer_in = gv_reset_timer;
    gv_leak_timer = gv_leak_set_timer;
    f_hold_seg_disable();
    f_set_lcd();
    f_deflate_seg_disable();
    while (digitalRead(pin_b_dec) == LOW) {}
    delay(10);
  }
}

void b_inflate_action(void) {
  // inflate
  if (press_time[b_inflate] >= 3000) {
    gv_deflate_flag = false;
    f_play_tone(c_tone_inflate);
    f_update_set_pressure();
    gv_chase_start_flag = true;
    gv_change_flag = true;
    gv_inc_timer = gv_inc_dec_set_timer;
    error_timer_in = gv_reset_timer;
    gv_leak_timer = gv_leak_set_timer;
    f_deflate_seg_disable();
    f_hold_seg_disable();
    f_set_lcd();
    delay(10);
    while (digitalRead(pin_b_inflate) == LOW) {
      f_inflate_seg_enable();
    }
  }
}

void b_deflate_action(void) {
  // deflate
  if (press_time[b_deflate] >= 3000) {
    f_play_tone(c_tone_deflate);
    gv_deflate_flag = true;
    error_timer_in = gv_reset_timer;
    gv_leak_timer = gv_leak_set_timer;
    gv_chase_start_flag = true;
    gv_change_flag = true;
    f_deflate_seg_disable();
    f_hold_seg_disable();
    f_deflate_seg_enable();
    f_set_lcd();
    while ((digitalRead(pin_b_deflate) == LOW)) {
      f_deflate_seg_enable();
      b_deflate_setting_on();
    }
    delay(10);
  }
}

void b_hold_action(void) {
  // hold
  if (press_time[b_hold] >= 3000) {
    if (gv_hold_timer) {
      f_play_tone(c_tone_deflate);
      gv_hold_flag = false;
      f_hold_seg_disable();
      gv_chase_start_flag = true;
      gv_hold_timer = gv_reset_timer;
      error_timer_in = gv_reset_timer;
      gv_leak_timer = gv_leak_set_timer;
      f_set_hold_timer_1621_off();
      f_set_lcd();
      while (digitalRead(pin_b_hold) == LOW) {
        b_hold_setting_on();
      }
    } else {
      f_play_tone(c_tone_beep);
      gv_hold_flag = true;
      f_hold_seg_enable();
      gv_hold_timer = gv_hold_set_timer;
      error_timer_in = gv_reset_timer;
      gv_leak_timer = gv_leak_set_timer;
      f_deflate_seg_disable();
      f_set_lcd();
      while (digitalRead(pin_b_hold) == LOW) {
        b_hold_setting_on();
      }
      delay(10);
      gv_chase_start_flag = true;
      gv_change_flag = true;
    }
  }
}

void b_mute_action(void) {
  //mute
  if (press_time[b_mute] >= 2000) {
    f_play_tone(c_tone_success);
    gv_buzzer_stop_timer = gv_reset_timer;
    while (digitalRead(pin_b_mute) == LOW) {}
    delay(10);
    f_set_lcd();
  }
}

void b_lock_action(void) {
  //b_lock
  if (press_time[b_lock] >= 3000) {
    if (gv_btn_flag == true) {
      gv_btn_flag = false;
      f_lock_seg_enable();
      f_set_lcd();
      f_play_tone(c_tone_success);
      while (digitalRead(pin_b_lock) == LOW) {}
    } else {
      gv_btn_flag = true;
      f_lock_seg_disable();
      f_set_lcd();
      f_play_tone(c_tone_success);
      while (digitalRead(pin_b_lock) == LOW) {}
    }
    delay(10);
  }
}

void f_power_on(void) {
  //  set_pressure = 25;
  gv_hold_timer = 0;
  gv_power_flag = true;
  f_deflate_seg_disable();
  f_set_lcd();
  f_play_tone(c_tone_power_up);

  while (digitalRead(pin_b_power) == LOW) {
    f_leak_seg_disable();
    digitalWrite(pin_backlight_led, HIGH);
  }
}


void f_power_off(void) {
  if (pressure_cmofH2O < gv_deflate_pressure + c_band && pressure_cmofH2O > gv_deflate_pressure - c_band) {
    f_play_tone(c_tone_power_down);
    gv_power_flag = false;
    HT1621_all_off(128);
    digitalWrite(pin_pump, LOW);
    digitalWrite(pin_valve_pressure, LOW);
    digitalWrite(pin_valve_vaccum, LOW);
    digitalWrite(pin_buzzer, LOW);
    digitalWrite(pin_backlight_led, LOW);
    pixels.clear();
    pixels.show();
    while (digitalRead(pin_b_power) == LOW) {}
  } else {
    gv_blink_current_pressure_1621_flag = true;
    f_play_tone(c_tone_error);
  }
}

void b_power_action(void) {
  if (press_time[b_power] >= 3000) {
    if (gv_power_flag == true) {
      f_power_off();
    } else {
      f_power_on();
    }
    delay(10);
  }
}

void f_button_action() {
  if ((gv_btn_flag == true || (press_time[0] >= 3000 && gv_btn_flag == false)) && (gv_power_flag == true || (gv_power_flag == false && press_time[4] >= 3000)) || (gv_btn_flag == false && press_time[3] >= 3000)) {
    b_inc_action();
    b_dec_action();
    b_inflate_action();
    b_deflate_action();
    b_hold_action();
    b_mute_action();
    b_lock_action();
    b_power_action();
  } else if (gv_power_flag && gv_btn_flag == false && (digitalRead(pin_b_inc) == LOW || digitalRead(pin_b_dec) == LOW || digitalRead(pin_b_inflate) == LOW || digitalRead(pin_b_deflate) == LOW || digitalRead(pin_b_power) == LOW || digitalRead(pin_b_hold))) {
    //    Serial.println("Locked");
    while (digitalRead(pin_b_inc) == LOW || digitalRead(pin_b_dec) == LOW || digitalRead(pin_b_inflate) == LOW || digitalRead(pin_b_deflate) == LOW || digitalRead(pin_b_power) == LOW || digitalRead(pin_b_hold) == LOW) {
      f_play_tone(c_tone_deflate);
      gv_blink_lock_seg_1621_flag = true;
    }
  }
}

uint8_t f_hold_set_timer_inc_by(void) {
  if (gv_hold_set_timer == 99) {
    return 0;
  } else {
    return 1;
  }
}

void b_hold_set_timer_inc(void) {
  if (press_time[b_inc]) {
    gv_hold_set_timer = gv_hold_set_timer + f_hold_set_timer_inc_by();
    while (digitalRead(pin_b_inc) == LOW) {}
  }
}

uint8_t f_hold_set_timer_dec_by(void) {
  if (gv_hold_set_timer == 0) {
    return 0;
  } else {
    return 1;
  }
}

void b_hold_set_timer_dec(void) {
  if (press_time[b_dec]) {
    gv_hold_set_timer = gv_hold_set_timer - f_hold_set_timer_dec_by();
    while (digitalRead(pin_b_dec) == LOW) {}
  }
}

uint8_t f_hold_pressure_inc_by(void) {
  if (gv_hold_pressure == 40) {
    return 0;
  } else {
    return 1;
  }
}

void b_hold_pressure_inc(void) {
  if (press_time[b_inflate]) {
    gv_hold_pressure = gv_hold_pressure + f_hold_pressure_inc_by();
    while (digitalRead(pin_b_inflate) == LOW) {}
  }
}

uint8_t f_hold_pressure_dec_by(void) {
  if (gv_hold_pressure == 10) {
    return 0;
  } else {
    return 1;
  }
}

void b_hold_pressure_dec(void) {
  if (press_time[b_deflate]) {
    gv_hold_pressure = gv_hold_pressure - f_hold_pressure_dec_by();
    while (digitalRead(pin_b_deflate) == LOW) {}
  }
}

void b_hold_setting_off(void) {
  if (press_time[b_hold]) {
    if (gv_setting_mode == 1) {
      gv_change_flag = true;
      f_update_hold_set_timer();
      f_update_hold_pressure();
      gv_setting_mode = 0;
      f_setting_seg_disable();
    }
  }
}

void f_button_action_s1(void) {
  if ((gv_power_flag == true || (gv_power_flag == false && press_time[4] >= 3000))) {
    b_hold_setting_off();
    b_hold_set_timer_inc();
    b_hold_set_timer_dec();
    b_hold_pressure_inc();
    b_hold_pressure_dec();
  }
}

uint8_t f_deflate_pressure_inc_by(void) {
  if (gv_deflate_pressure == c_set_value_maximum) {
    return 0;
  } else {
    return 1;
  }
}

void b_deflate_pressure_inc(void) {
  if (press_time[b_inc]) {
    gv_deflate_pressure = gv_deflate_pressure + f_deflate_pressure_inc_by();
    while (digitalRead(pin_b_inc) == LOW) {}
  }
}

uint8_t f_deflate_pressure_dec_by(void) {
  if (gv_deflate_pressure == 0) {
    return 0;
  } else {
    return 1;
  }
}

void b_deflate_pressure_dec(void) {
  if (press_time[b_dec]) {
    gv_deflate_pressure = gv_deflate_pressure - f_deflate_pressure_dec_by();
    while (digitalRead(pin_b_dec) == LOW) {}
  }
}

void b_deflate_setting_off(void) {
  if (press_time[b_deflate]) {
    if (gv_setting_mode == 3) {
      f_update_deflate_pressure();
      gv_setting_mode = 0;
      f_setting_seg_disable();
    }
  }
}

void f_button_action_s3(void) {
  if ((gv_power_flag == true || (gv_power_flag == false && press_time[4] >= 3000))) {
    b_deflate_setting_off();
    b_deflate_pressure_inc();
    b_deflate_pressure_dec();
  }
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Error Signal ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
// void f_high_priority_alarm(void) {
//   gv_millis_new2 = millis();
//   if (gv_high_priority_alarm) {
//     if (gv_millis_new2 - gv_millis_old2 > 500) {
//       gv_millis_old2 = gv_millis_new2;
//       if (gv_rgb_flash) {
//         gv_rgb_flash = false;
//         pixels.clear();
//         pixels.setPixelColor(0, pixels.Color(255, 0, 0));
//         pixels.show();
//         tone(pin_buzzer, 255);
//       } else {
//         gv_rgb_flash = true;
//         pixels.clear();
//         pixels.show();
//         noTone(pin_buzzer);
//       }
//     }
//   } else {
//     pixels.clear();
//     pixels.show();
//   }
// }

// void f_low_priority_alarm(void) {
//   gv_millis_new2 = millis();
//   if (gv_low_priority_alarm) {
//     if (gv_millis_new2 - gv_millis_old2 > 500) {
//       gv_millis_old2 = gv_millis_new2;
//       if (gv_rgb_flash) {
//         gv_rgb_flash = false;
//         pixels.clear();
//         pixels.setPixelColor(0, pixels.Color(255, 255, 0));
//         pixels.show();
//         tone(pin_buzzer, 255);
//       } else {
//         gv_rgb_flash = true;
//         pixels.clear();
//         pixels.show();
//       }
//     }
//   } else {
//     pixels.clear();
//     pixels.show();
//     noTone(pin_buzzer);
//   }
// }
void f_alarm(void) {
  gv_millis_new2 = millis();
  if (gv_low_priority_alarm || gv_high_priority_alarm) {
    if (gv_millis_new2 - gv_millis_old2 > 500) {
      gv_millis_old2 = gv_millis_new2;
      if (gv_rgb_flash) {
        gv_rgb_flash = false;
        pixels.clear();
        if (gv_low_priority_alarm) pixels.setPixelColor(0, pixels.Color(255, 255, 0));
        else pixels.setPixelColor(0, pixels.Color(255, 0, 0));
        pixels.show();
        if (gv_buzzer_stop_timer == 120) tone(pin_buzzer, 255);
        f_alarm_seg_enable();
      } else {
        gv_rgb_flash = true;
        pixels.clear();
        pixels.show();
        noTone(pin_buzzer);
        f_alarm_seg_disable();
      }
    }
  } else {
    pixels.clear();
    pixels.show();
    noTone(pin_buzzer);
    f_alarm_seg_disable();
  }
}

void f_leak() {
  bool lv_minor_leak_flag = (!gv_change_flag) && gv_stable_pressure_timer == 5;
  bool lv_major_leak_flag = (gv_leak_timer == 0) && gv_change_flag;
  if ((gv_chase_start_flag && !gv_deflate_flag && (pressure_cmofH2O < gv_set_pressure - c_band) || (pressure_cmofH2O > gv_set_pressure + c_band)) && gv_hold_timer == gv_reset_timer && (lv_minor_leak_flag || lv_major_leak_flag)) {
    f_leak_seg_enable();
    if (lv_minor_leak_flag) {
      gv_low_priority_alarm = true;
    } else {
      gv_high_priority_alarm = true;
      // gv_low_priority_alarm = false;
    }
  } else {
    if (gv_change_flag) {
      f_leak_seg_disable();
      gv_stable_pressure_timer = gv_reset_timer;
    }
    if ((pressure_cmofH2O > gv_set_pressure - c_band) && (pressure_cmofH2O < gv_set_pressure + c_band)) {
      gv_change_flag = false;
      gv_leak_timer = gv_leak_set_timer;
      gv_high_priority_alarm = false;
      gv_low_priority_alarm = false;
    }
    else if(gv_hold_flag){
      gv_change_flag = true;
      gv_leak_timer = gv_leak_set_timer;
    }
  }
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Clock ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void f_update_inc_timer(void) {
  if (gv_inc_timer < gv_inc_dec_set_timer) {
    gv_inc_timer++;
  }
}

void f_update_dec_timer(void) {
  if (gv_dec_timer < gv_inc_dec_set_timer) {
    gv_dec_timer++;
  }
}

void f_update_leak_timer(void) {
  if (gv_leak_timer > 0) {
    gv_leak_timer--;
  }
}

void f_update_hold_timer(void) {
  if (gv_hold_timer > 0) {
    gv_hold_timer--;
  }
}

void f_update_mute_timer(void) {
  if (gv_buzzer_stop_timer < 120) {
    gv_buzzer_stop_timer++;
  }
}

void f_update_error_timer(void) {
  if (error_timer_in < 20) {
    error_timer_in++;
  }
}

void f_update_blink_timer(void) {
  if (/*digitalRead(charging_status)*/ 1) {
    gv_blink_timer++;
  }
}

void f_update_stable_pressure_timer(void) {
  if (gv_stable_pressure_timer < 5) {
    gv_stable_pressure_timer++;
  }
}

// void f_clock2(void){
//   gv_millis_new2 = millis();
//   if (gv_millis_new2 - gv_millis_old2 > 100) {
//     gv_millis_old2 = gv_millis_new2;
//     f_flash_rgb();
//   }

// }
void f_clock(void) {
  gv_millis_new = millis();

  if (gv_millis_new - gv_millis_old > 1000) {
    gv_millis_old = gv_millis_new;
    f_set_lcd();

    f_update_inc_timer();
    f_update_dec_timer();
    f_update_leak_timer();
    f_update_hold_timer();
    f_update_mute_timer();
    f_update_error_timer();
    f_update_blink_timer();
    f_update_stable_pressure_timer();




    if (digitalRead(pin_b_mute) == LOW) {
      gv_press_mute_time++;
    }
    if (digitalRead(pin_b_lock) == LOW) {
      gv_press_lock_time++;
    }
  }
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ********************* Modes ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void f_mode_0(void) {
  if (gv_power_flag) {
    digitalWrite(pin_backlight_led, HIGH);
    f_clock();
    f_get_button_state();
    boolean lv_pressure_flag = (gv_inc_timer == gv_inc_dec_set_timer) & (gv_dec_timer == gv_inc_dec_set_timer) & (gv_chase_start_flag);
    if (lv_pressure_flag) f_set_pressure();
    f_leak();
    f_alarm();
    // f_low_priority_alarm();
    // f_high_priority_alarm();


    if (gv_hold_timer == 0 || press_time[5] >= 3000) f_button_action();

    //    f_sucess_status_action();
  } else {
    HT1621_all_off(128);
    digitalWrite(pin_pump, LOW);
    digitalWrite(pin_valve_pressure, LOW);
    digitalWrite(pin_valve_vaccum, LOW);
    digitalWrite(pin_buzzer, LOW);
    digitalWrite(pin_backlight_led, LOW);
    f_clock();
    f_get_button_state();
    f_button_action();
  }
}

void set_screen_mode_1(void) {
  set_current_pressure_1621_off();
  set_pressure_1621(gv_hold_pressure);
  set_hold_timer_1621(gv_hold_set_timer);
  f_hold_seg_enable();
  f_setting_seg_enable();
  f_cm_of_h2o_seg_disable();
}

void f_mode_1(void) {
  f_clock();
  set_screen_mode_1();
  f_button_action_s1();
  f_get_button_state();
}

void set_screen_mode_3(void) {
  set_current_pressure_1621_off();
  set_pressure_1621(gv_deflate_pressure);
  f_deflate_seg_enable();
  f_setting_seg_enable();
  f_cm_of_h2o_seg_disable();
}

void f_mode_3(void) {
  f_clock();
  f_get_button_state();
  set_screen_mode_3();
  f_button_action_s3();
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Setup ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup() {
  f_set_values();
  f_get_values();
  f_update_set_pressure();
  f_update_hold_pressure();
  f_update_hold_set_timer();
  pinMode(pin_pump, OUTPUT);
  pinMode(pin_valve_pressure, OUTPUT);
  pinMode(pin_valve_vaccum, OUTPUT);

  pinMode(pin_b_lock, INPUT_PULLUP);
  pinMode(pin_b_deflate, INPUT_PULLUP);
  pinMode(pin_b_dec, INPUT_PULLUP);
  pinMode(pin_b_mute, INPUT_PULLUP);
  pinMode(pin_b_power, INPUT_PULLUP);
  pinMode(pin_b_hold, INPUT_PULLUP);
  pinMode(pin_b_inc, INPUT_PULLUP);
  pinMode(pin_b_inflate, INPUT_PULLUP);

  init_1621();
  //  Serial.begin(9600);
  if (!mysensor.begin())  // initialize and check the device
  {
    Serial.println("Device not responding.");
    while (true)
      delay(10);
  }

  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)

  Timer1.initialize(c_refresh_screen_time);  // in microsec  == 200mllis
  Timer1.attachInterrupt(f_refresh_screen);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** LOOP ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void loop() {
  mysensor.readSensor(temperature, pressure);
  pressure_cmofH2O = pressure / 98.0665;

  if (gv_setting_mode == 0) {
    f_mode_0();
  } else if (gv_setting_mode == 1) {
    /*Hold setting mode*/
    f_mode_1();
  } else if (gv_setting_mode == 3) {
    /*deflate setting mode*/
    f_mode_3();
  }

  f_charging();
  f_blink_current_pressure_1621();
  f_blink_lock_seg();

  //   gv_millis_new2 = millis();
  // if (1) {
  //   if (gv_millis_new2 - gv_millis_old2 > 100) {
  //     gv_millis_old2 = gv_millis_new2;
  //     if (gv_rgb_flash) {
  //       gv_rgb_flash = false;
  //       pixels.clear();
  //       pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  //       pixels.show();
  //       tone(pin_buzzer, 255);
  //     } else {
  //       gv_rgb_flash = true;
  //       pixels.clear();
  //       pixels.show();
  //       noTone(pin_buzzer);
  //     }
  //   }
  // } else {
  //   pixels.clear();
  //   pixels.show();
  // }
  // f_buzzer_on();
}
