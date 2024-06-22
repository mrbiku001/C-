/*
  using internal oscillator 8 MHz
  and enabling PB6 & PB7 as GPIO via direct port addressing
*/

//  Example for XGZP6897D library
//  Simple read of temperature and pressure with a CFSensor I2C sensor
//  such as XGZP6897D
#include <XGZP6897D.h>
#include <EEPROM.h>
#include <avr/sleep.h>


//LCD
static const uint8_t   com_mode              = 0x52;
static const uint8_t  rc_osc                = 0x30;
static const uint8_t  lcd_on                = 0x06;
static const uint8_t  lcd_off               = 0x04;
static const uint8_t  sys_en                = 0x02;
static const uint8_t  ctrl_cmd              = 0x80;
static const uint8_t  data_cmd              = 0xa0;
static const uint8_t  delay_us              = 1;


//LCD Segments
// segment 1
// segment 1
#define       c_1A                driver_ram_1621[21][3]
#define       c_1B                driver_ram_1621[21][2]
#define       c_1C                driver_ram_1621[21][1]
#define       c_1D                driver_ram_1621[21][0]
#define       c_1E                driver_ram_1621[19][0]
#define       c_1F                driver_ram_1621[19][2]
#define       c_1G                driver_ram_1621[19][1]
// segment 2            
#define       c_2A                driver_ram_1621[25][3]
#define       c_2B                driver_ram_1621[25][2]
#define       c_2C                driver_ram_1621[25][1]
#define       c_2D                driver_ram_1621[25][0]
#define       c_2E                driver_ram_1621[23][0]
#define       c_2F                driver_ram_1621[23][2]
#define       c_2G                driver_ram_1621[23][1]
//segment 3
#define       c_3A                driver_ram_1621[11][3]
#define       c_3B                driver_ram_1621[11][2]
#define       c_3C                driver_ram_1621[11][1]
#define       c_3D                driver_ram_1621[11][0]
#define       c_3E                driver_ram_1621[13][1]
#define       c_3F                driver_ram_1621[13][3]
#define       c_3G                driver_ram_1621[13][2]
//segment 4
#define       c_4A                driver_ram_1621[8][3]
#define       c_4B                driver_ram_1621[8][2]
#define       c_4C                driver_ram_1621[8][1]
#define       c_4D                driver_ram_1621[8][0]
#define       c_4E                driver_ram_1621[9][1]
#define       c_4F                driver_ram_1621[9][3]
#define       c_4G                driver_ram_1621[9][2]
//segment 5               
#define       c_5A                driver_ram_1621[6][3]
#define       c_5B                driver_ram_1621[6][2]
#define       c_5C                driver_ram_1621[6][1]
#define       c_5D                driver_ram_1621[6][0]
#define       c_5E                driver_ram_1621[7][1]
#define       c_5F                driver_ram_1621[7][3]
#define       c_5G                driver_ram_1621[7][2]
//segmen      t 6               
#define       c_6A                driver_ram_1621[2][3]
#define       c_6B                driver_ram_1621[2][2]
#define       c_6C                driver_ram_1621[2][1]
#define       c_6D                driver_ram_1621[2][0]
#define       c_6E                driver_ram_1621[4][1]
#define       c_6F                driver_ram_1621[4][3]
#define       c_6G                driver_ram_1621[4][2]
                      
#define       c_T1                driver_ram_1621[15][1]
#define       c_T2                driver_ram_1621[15][2]
#define       c_T3                driver_ram_1621[27][3]
#define       c_T4                driver_ram_1621[19][3]
#define       c_T5                driver_ram_1621[15][3]
#define       c_T6                driver_ram_1621[23][3]
#define       c_T7                driver_ram_1621[15][0]
#define       c_T8                driver_ram_1621[17][2]
#define       c_T9                driver_ram_1621[17][1]
#define       c_T10               driver_ram_1621[17][0]
#define       c_T11               driver_ram_1621[27][2]
#define       c_T12               driver_ram_1621[27][1]
#define       c_T13               driver_ram_1621[27][0]
#define       c_T14               driver_ram_1621[29][0]
#define       c_T15               driver_ram_1621[29][1]
#define       c_T16               driver_ram_1621[31][3]
#define       c_T17               driver_ram_1621[29][3]
#define       c_T18               driver_ram_1621[29][2]
#define       c_T19               driver_ram_1621[31][0]
#define       c_T20               driver_ram_1621[31][1]
#define       c_T21               driver_ram_1621[31][2]
#define       c_T22               driver_ram_1621[13][3]
#define       c_T23               driver_ram_1621[9][0]
#define       c_T24               driver_ram_1621[7][0]
#define       c_T25               driver_ram_1621[4][0]
#define       c_T26               driver_ram_1621[1][3]
#define       c_T27               driver_ram_1621[1][2]
#define       c_T28               driver_ram_1621[1][1]
#define       c_T29               driver_ram_1621[1][0]

// buttons
#define       b_lock                        A2
#define       b_deflate                     11
#define       b_dec                         13
#define       b_mute                        A0
#define       b_power                       2
#define       b_hold                        A1
#define       b_inc                         12
#define       b_inflate                     10


//IOs
#define       pin_pump                      8
#define       pin_valve_pressure            6
#define       pin_valve_vaccum              7
#define       buzzer                        1
#define       rgb_led                       0
#define       backlight_led                 9

#define       c_pulse_pressure              100
#define       c_pulse_vaccum                100
#define       c_pulse_pressure_valve        30
#define       c_pulse_vaccum_valve          50
#define       c_band                        1


/* ******************* BMS ************************ */
#define       charging_status               A3
#define       charging_status_full          A3
#define       battery_gauge                 A3

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
// K value for a XGZP6897D  -1000-1000Pa
#define       K           512 // see table above for the correct value for your sensor, according to the sensitivity.
// create the sensor object, passing the correct K value.
XGZP6897D mysensor(K);

//*************************
//**** GLOBAL VARIABLES****
//*************************
unsigned long       gv_millis_old                 = 0;
unsigned long       gv_millis_new                 = 0;
unsigned long       gv_millis_delta               = 0;
unsigned long       prev_time, current_time;
float               pressure, temperature;
float               pressure_cmofH2O;

/*----------------------------------------------------------------*/
int                 hold_set_timer                = 99;
int                 set_pressure                  = 25;
int                 hold_pressure                 = 35;
int                 inflate_pressure              = 30;
int                 deflate_pressure              = 0;
int                 set_pressure_address          = 0;
int                 set_pressure_copy_address     = 2;
int                 inflate_pressure_address      = 4;
int                 deflate_pressure_address      = 6;
int                 hold_pressure_address         = 8;
int                 hold_set_timer_address        = 10;

/*----------------------------------------------------------------*/
int                 setting_mode                  = 0;

bool                set_default_pressure_after_hold = false;
bool                btn_flag                        = true;
//bool                sleep_mode                    = false;
bool                power_flag                      = false;
int                set_pressure_sucess_alarm        = 0;
int                 inc_dec_set_timer               = 3;
int                 leak_set_timer                  = 30;
int                 reset_timer                     = 0;
int                 buzzer_stop_timer               = 120;
int                 hold_timer                      = 0;
int                 leak_timer                      = leak_set_timer;
int                 press_mute_time                 = 0;
int                 press_lock_time                 = 0;
int                 inc_timer                       = inc_dec_set_timer;
int                 dec_timer                       = inc_dec_set_timer;
int                 blink_timer                     = 0;
int                 c_set_value_minimum             = 10;
int                 c_set_value_maximum             = 40;

int                 buttons[8]                      = {b_lock, b_deflate, b_dec, b_mute, b_power, b_hold, b_inc, b_inflate};
boolean             button_current_state[8]         = {1, 1, 1, 1, 1, 1, 1, 1};
boolean             button_prev_state[8]            = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long       press_time[8]                   = {0, 0, 0, 0, 0, 0, 0, 0};
boolean             flag                            = false;
int                 error_timer_in                  = 20;
int                 button_pressed                  = -1;

//buzzer tones
int                 inflate_tone[]                  = {261, 0, 277, 0};
int                 hold_tone[]                     = {261, 0, 277, 0};
int                 deflate_tone[]                  = {415, 0, 440, 0};
int                 sucess_tone[]                   = {150, 0, 200, 0};
int                 failure_tone[]                  = {500, 0, 550, 0};
int                 num_inflate_tone                = sizeof(inflate_tone) / sizeof(inflate_tone[0]);
int                 num_deflate_tone                = sizeof(deflate_tone) / sizeof(deflate_tone[0]);


// HT1621
const uint8_t       csPin                           = 5;   //Chip selection output
const uint8_t       wrPin                           = 3;   //Read clock output
const uint8_t       dataPin                         = 4; //Serial data output



bool driver_ram_1621[32][4]                         = {
                                                      // COMM3 COMM2 COMM1 COMM0
                                                      {0, 0, 0, 0},//ADDR 0
                                                      {0, 0, 0, 0},//ADDR 1
                                                      {0, 0, 0, 0},//ADDR 2
                                                      {0, 0, 0, 0},//ADDR 3
                                                      {0, 0, 0, 0},//ADDR 4
                                                      {0, 0, 0, 0},//ADDR 5
                                                      {0, 0, 0, 0},//ADDR 6
                                                      {0, 0, 0, 0},//ADDR 7
                                                      {0, 0, 0, 0},//ADDR 8
                                                      {0, 0, 0, 0},//ADDR 9
                                                      {0, 0, 0, 0},//ADDR 10
                                                      {0, 0, 0, 0},//ADDR 11
                                                      {0, 0, 0, 0},//ADDR 12
                                                      {0, 0, 0, 0},//ADDR 13
                                                      {0, 0, 0, 0},//ADDR 14
                                                      {0, 0, 0, 0},//ADDR 15
                                                      {0, 0, 0, 0},//ADDR 16
                                                      {0, 0, 0, 0},//ADDR 17
                                                      {0, 0, 0, 0},//ADDR 18
                                                      {0, 0, 0, 0},//ADDR 19
                                                      {0, 0, 0, 0},//ADDR 20
                                                      {0, 0, 0, 0},//ADDR 21
                                                      {0, 0, 0, 0},//ADDR 22
                                                      {0, 0, 0, 0},//ADDR 23
                                                      {0, 0, 0, 0},//ADDR 24
                                                      {0, 0, 0, 0},//ADDR 25
                                                      {0, 0, 0, 0},//ADDR 26
                                                      {0, 0, 0, 0},//ADDR 27
                                                      {0, 0, 0, 0},//ADDR 28
                                                      {0, 0, 0, 0},//ADDR 29
                                                      {0, 0, 0, 0},//ADDR 30
                                                      {0, 0, 0, 0} //ADDR 31
                                                    };

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** EEPROM ********************* */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void f_set_values(void) {
  if (EEPROM.read(set_pressure_address) == 255)           EEPROM.write(set_pressure_address, set_pressure);
  if (EEPROM.read(set_pressure_copy_address) == 255)      EEPROM.write(set_pressure_copy_address, 25);
  if (EEPROM.read(inflate_pressure_address) == 255)       EEPROM.write(inflate_pressure_address, inflate_pressure);
  if (EEPROM.read(deflate_pressure_address) == 255)       EEPROM.write(deflate_pressure_address, deflate_pressure);
  if (EEPROM.read(hold_pressure_address) == 255)          EEPROM.write(hold_pressure_address, hold_pressure);
  if (EEPROM.read(hold_set_timer_address) == 255)         EEPROM.write(hold_set_timer_address, hold_set_timer);
}

void f_get_values(void) {
  set_pressure                                            = EEPROM.read(set_pressure_address);
  hold_set_timer                                          = EEPROM.read(hold_set_timer_address);
  hold_pressure                                           = EEPROM.read(hold_pressure_address);
  inflate_pressure                                        = EEPROM.read(inflate_pressure_address);
  deflate_pressure                                        = EEPROM.read(deflate_pressure_address);
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void f_update_set_pressure(void) {
  EEPROM.update(set_pressure_address, set_pressure);
}

void f_update_hold_set_timer(void) {
  EEPROM.update(hold_set_timer_address, hold_set_timer);
}

void f_update_hold_pressure(void) {
  EEPROM.update(hold_pressure_address, hold_pressure);
}

void f_update_inflate_pressure(void) {
  EEPROM.update(inflate_pressure_address, inflate_pressure);
}

void f_update_deflate_pressure(void) {
  EEPROM.update(deflate_pressure_address, deflate_pressure);
}

void f_update_values(void) {
  EEPROM.update(set_pressure_address, set_pressure);
  EEPROM.update(hold_set_timer_address, hold_set_timer);
  EEPROM.update(hold_pressure_address, hold_pressure);
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Ceil and Floor for pressure_cmOfH2O ********************* */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
int f_pressure_cmofH2O(void){
  int x = pressure_cmofH2O;
  if(ceil(pressure_cmofH2O) == set_pressure){
    x = ceil(pressure_cmofH2O);
  }
  else if(floor(pressure_cmofH2O) == set_pressure){
    x = floor(pressure_cmofH2O);
  }
  return x;
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** LCD Driver HT1621 ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void SendBit_1621(uint8_t sdata, uint8_t cnt) {
  uint8_t i;
  for (i = 0; i < cnt; i++) {
    digitalWrite(wrPin, LOW);
    delayMicroseconds(delay_us);
    if (sdata & 0x80) digitalWrite(dataPin, HIGH);
    else digitalWrite(dataPin, LOW);
    digitalWrite(wrPin, HIGH);
    delayMicroseconds(delay_us);
    sdata <<= 1;
  }
}

void SendCmd_1621(uint8_t command) {
  digitalWrite(csPin, LOW);
  SendBit_1621(0x80, 4);
  SendBit_1621(command, 8);
  digitalWrite(csPin, HIGH);
}

void Write_1621(uint8_t addr, uint8_t sdata) {
  addr <<= 2;
  digitalWrite(csPin, LOW);
  SendBit_1621(0xa0, 3);
  SendBit_1621(addr, 6);
  SendBit_1621(sdata, 8);
  digitalWrite(csPin, HIGH);
}

void HT1621_all_off(uint8_t num) {
  uint8_t i;
  uint8_t addr = 0;
  for (i = 0; i < num; i++) {
    Write_1621(addr, 0x00);
    addr += 2;
  }
}

void HT1621_all_on(uint8_t num) {
  uint8_t i;
  uint8_t addr = 0;
  for (i = 0; i < num; i++) {
    Write_1621(addr, 0xff);
    addr += 2;
  }
}

void init_1621(void) {
  pinMode(csPin, OUTPUT);
  pinMode(wrPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(backlight_led, OUTPUT);
  
  digitalWrite(csPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(wrPin, HIGH);

  digitalWrite(backlight_led, HIGH);
  delay(50);

  SendCmd_1621(sys_en);
  SendCmd_1621(rc_osc);
  SendCmd_1621(com_mode);
  SendCmd_1621(lcd_on);
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void update_ram_1621() {
  byte lv_data = 0;
  byte i;
  for (i = 0; i < 32; i++) {
    bitWrite(lv_data, 7, driver_ram_1621[i][0]);
    bitWrite(lv_data, 6, driver_ram_1621[i][1]);
    bitWrite(lv_data, 5, driver_ram_1621[i][2]);
    bitWrite(lv_data, 4, driver_ram_1621[i][3]);

    Write_1621(i, lv_data);
  }
}

void set_current_pressure_tens(int pressure_tens) {
  switch (pressure_tens) {
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

void set_current_pressure_once(int pressure_once) {
  switch (pressure_once) {
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

void set_hold_timer_tens(int timer_tens) {
  switch (timer_tens) {
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

void set_hold_timer_once(int timer_once) {
  switch (timer_once) {
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

void set_pressure_tens(int pressure_once) {
  switch (pressure_once) {
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

void set_pressure_once(int pressure_once) {
  switch (pressure_once) {
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

void set_current_pressure_1621(int pressure) {
  if (pressure < 0 || pressure > 99) {
    set_current_pressure_once(10);
    set_current_pressure_tens(10);
  }
  else {
    set_current_pressure_once(pressure % 10);
    set_current_pressure_tens(pressure / 10);
  }
}

void set_pressure_1621(int pressure) {
  if (pressure < 0 || pressure > 99) {
    set_pressure_once(10);
    set_pressure_tens(10);
  }
  else {
    set_pressure_once(pressure % 10);
    set_pressure_tens(pressure / 10);
  }
}

void set_hold_timer_1621(int hold_timer) {
  set_hold_timer_once(((hold_timer) % 10));
  set_hold_timer_tens(hold_timer / 10);
  //  set_hold_timer_once(((hold_timer / 60) % 10)+1);
  //  set_hold_timer_tens(hold_timer / 600);
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

void f_setting_seg_enable() {
  c_T19 = 1;
}

void f_setting_seg_disable() {
  c_T19 = 0;
}

void f_alarm_seg_disable(void) {
  c_T7 = 0;
}

void f_alarm_seg_enable(void) {
  c_T7 = 0;
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

void f_symbol_off(void) {
  f_inflate_seg_disable();
  f_deflate_seg_disable();
}

void f_always_on_seg(void) {
  f_cm_of_h2o_seg_enable();
  c_T25 = 1;
  c_T1 = 1;
  c_T3 = 1;
  c_T2 = 1;
}

void f_battery_all_seg_enable(void){
  c_T3 = 1;
  c_T4 = 1;
  c_T5 = 1;
  c_T6 = 1;
}

void f_battery_all_seg_disable(void){
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
  set_pressure_1621(set_pressure);
  if (hold_timer) {
    set_default_pressure_after_hold = true;
    set_hold_timer_1621(hold_timer);
    c_T26 = 1;
  }
  else {
    if (set_default_pressure_after_hold) {
      set_pressure = EEPROM.read(set_pressure_copy_address);
      f_update_set_pressure();
      set_default_pressure_after_hold = false;
      hold_timer = reset_timer;
    error_timer_in = reset_timer;
    leak_timer = leak_set_timer;
    }
    f_set_hold_timer_1621_off();
    c_T26 = 0;
    f_hold_seg_disable();
  }
}

void f_blink_lock_seg(void){
  for(int i = 0; i < 3; i++){
    f_lock_seg_disable();
    update_ram_1621();
    delay(100);
    f_lock_seg_enable();
    update_ram_1621();
    delay(250);
  }
}
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************* BMS ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
void f_battery_gauge(void){
  float charge_percentage = ((analogRead(battery_gauge) - 655)/308) * 100;
  if(charge_percentage >= 67){
    c_T4 = 1;
    c_T5 = 1;
    c_T6 = 1;
  }
  else if(charge_percentage < 67 && charge_percentage >= 34){
    c_T4 = 1;
    c_T5 = 1;
    c_T6 = 0;
  }
  else if(charge_percentage < 34 && charge_percentage >= 10){
    c_T4 = 1;
    c_T5 = 0;
    c_T6 = 0;
  }
  else if(charge_percentage < 10 && charge_percentage >=0){
    c_T4 = 0;
    c_T5 = 0;
    c_T6 = 0;
  }
}

void f_charging(void){
  if(/*digitalRead(charging_status)*/1){
    if(/*digitalRead(charging_status_full)*/1){
      if(blink_timer%2){
        f_battery_all_seg_enable();
      }
      else{
        f_battery_all_seg_disable();
      }
    }
    else{
      if(blink_timer%4 == 0){
        c_T4 = 0;
        c_T5 = 0;
        c_T6 = 0;
      }
      else if(blink_timer%4 == 1){
        c_T4 = 1;
        c_T5 = 0;
        c_T6 = 0;
      }
      else if(blink_timer%4 == 2){
        c_T4 = 1;
        c_T5 = 1;
        c_T6 = 0;
      }
      else if(blink_timer%4 == 3){
        c_T4 = 1;
        c_T5 = 1;
        c_T6 = 1;
      }
    }
  }
  else{
    f_battery_gauge();
  }
  c_T3 =1;
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************* Valve Motor ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void f_pulse_pressure() {
  digitalWrite(pin_pump, HIGH);
  delay(c_pulse_pressure);
  digitalWrite(pin_valve_pressure, HIGH);
  delay(c_pulse_pressure_valve);
  digitalWrite(pin_pump, LOW);
  digitalWrite(pin_valve_pressure, LOW);
}

void f_pulse_vaccum() {
  digitalWrite(pin_pump, HIGH);
  delay(c_pulse_vaccum);
  digitalWrite(pin_valve_vaccum, HIGH);
  delay(c_pulse_pressure_valve);
  digitalWrite(pin_pump, LOW);
  digitalWrite(pin_valve_vaccum, LOW);
}

void f_set_pressure() {
  if (pressure_cmofH2O > set_pressure + c_band) {
    f_inc_seg_disable();
    f_dec_seg_enable();
    f_pulse_vaccum();
//    Serial.println("vaccum");
  } else if (pressure_cmofH2O < set_pressure - c_band) {
    f_dec_seg_disable();
    f_inc_seg_enable();
    f_pulse_pressure();
//    Serial.println("pressure");
  }
  else{
    f_dec_seg_disable();
    f_inc_seg_disable();
  }
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** get button status ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void f_get_button_state() {

  current_time = millis();
  // iterate arrays
  for (int i = 0; i < sizeof(button_current_state) / sizeof(button_current_state[0]); i++) {

    // if button pressed
    if (button_current_state[i] != digitalRead(buttons[i])) {
      button_prev_state[i] = button_current_state[i];
      button_current_state[i] = digitalRead(buttons[i]);
    }

    if (!button_current_state[i] && !flag) {
      prev_time = current_time;
      flag = true;
      button_pressed = i;
      Serial.print("btn pressed ");
      Serial.println(i);
    }

    if (button_current_state[button_pressed] && flag) {
      Serial.print("btn released ");
      Serial.println(i);
      flag = false;
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

  // for (int i = 0; i < 8; i++) {
  //   Serial.print(button_prev_state[i]);
  //   if (i != 7) {
  //     Serial.print(",");
  //   }
  // }
  // Serial.println();

  // for (int i = 0; i < 8; i++) {
  //   Serial.print(button_current_state[i]);
  //   if (i != 7) {
  //     Serial.print(",");
  //   }
  // }
  // Serial.println();

  // for (int i = 0; i < 8; i++) {
  //   Serial.print(press_time[i]);
  //   if (i != 7) {
  //     Serial.print(",");
  //   }
  // }Serial.println();
  // Serial.println(flag);
  // Serial.println();
  // delay(1000);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Buzzer ******************** */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

void f_beep_inflate(void) {
  for (int i = 0; i < sizeof(inflate_tone) / sizeof(inflate_tone[0]); i++) {
    tone(buzzer, inflate_tone[i], 250);
    delay(500);
  }
}

void f_beep_deflate(void) {
  for (int i = 0; i < sizeof(deflate_tone) / sizeof(deflate_tone[0]); i++) {
    tone(buzzer, deflate_tone[i], 250);
    delay(500);
  }
}

void f_beep_hold(void) {
  for (int i = 0; i < sizeof(hold_tone) / sizeof(hold_tone[0]); i++) {
    tone(buzzer, hold_tone[i], 250);
    delay(500);
  }
}

void f_beep_sucess(void) {
  for (int i = 0; i < sizeof(sucess_tone) / sizeof(sucess_tone[0]); i++) {
    tone(buzzer, sucess_tone[i], 250);
    delay(500);
  }
}

void f_beep_failure(void) {
  for (int i = 0; i < sizeof(failure_tone) / sizeof(failure_tone[0]); i++) {
    tone(buzzer, failure_tone[i], 250);
    delay(500);
  }
}

void f_beep_sucess_status(void) {
  if (set_pressure_sucess_alarm == 1) {
    f_beep_sucess();
    set_pressure_sucess_alarm = 2;
  }
}

void f_get_sucess_status() {
  if ((pressure_cmofH2O > set_pressure - c_band) && (pressure_cmofH2O < set_pressure + c_band) && (set_pressure_sucess_alarm == 0 /*signifies Not achieved yet*/)) {
    set_pressure_sucess_alarm = 1;
  }
  else if ((pressure_cmofH2O < set_pressure - c_band) || (pressure_cmofH2O > set_pressure + c_band)) {
    set_pressure_sucess_alarm = 0;
  }
}

void f_sucess_status_action(void) {
  f_get_sucess_status();
  f_beep_sucess_status();
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------*/
/* ******************** Button Functions ******************* */
/* ------------------------------------------------------------------------------------------------------------------------------------------------*/

// {b_lock, b_deflate, b_dec, b_mute, b_power, b_hold, b_inc, b_inflate};

//void f_sleep() {
//  sleep_enable();
//  attachInterrupt(0, wake_up, LOW);
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  sleep_mode();
//  sleep_disable();
//  detachInterrupt(0);
//  delay(1000);
//  digitalWrite(b_power, LOW);
//}
//
//void wake_up() {
//  sleep_mode = false;
//  digitalWrite(b_power, HIGH);
//}

int f_dec_by() {
  if (set_pressure == c_set_value_minimum) {
    return 0;
  }
  else {
    return 1;
  }
}

int f_inc_by() {
  if (set_pressure == c_set_value_maximum) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_inc_action() {
  // inc_trg
  if (press_time[6]) {
    set_pressure = set_pressure + f_inc_by();
    f_update_set_pressure();
    while (digitalRead(b_inc) == LOW) {}
    inc_timer = reset_timer;
    error_timer_in = reset_timer;
    leak_timer = leak_set_timer;
    f_hold_seg_disable();
    f_set_lcd();
    f_symbol_off();
    update_ram_1621();
    delay(10);
  }
}

void b_hold_setting_on(void) {
  //  hold_setting
  f_get_button_state();
  if (press_time[5] >= 8000) {
    if (setting_mode == 0) {
      f_beep_hold();
      setting_mode = 1;
      while (digitalRead(b_hold)) {}
    }
  }
}

void b_inflate_setting_on(void) {
  //inflate setting
  f_get_button_state();
  if (press_time[7] >= 8000) {
    f_beep_inflate();
    if (setting_mode == 0) {
      setting_mode = 2;
      while (digitalRead(b_inflate) == LOW) {}
    }
  }
}

void b_deflate_setting_on(void) {
  //deflate setting
  f_get_button_state();
  if (press_time[1] >= 8000) {
    f_beep_deflate();
    if (setting_mode == 0) {
      setting_mode = 3;
      while (digitalRead(b_deflate) == LOW) {}
    }
  }
}

void b_dec_action() {
  // dec_trg
  if (press_time[2]) {
    set_pressure = set_pressure - f_dec_by();
    f_update_set_pressure();
    while (digitalRead(b_dec) == LOW) {}
    dec_timer = reset_timer;
    error_timer_in = reset_timer;
    leak_timer = leak_set_timer;
    f_hold_seg_disable();
    f_set_lcd();
    f_symbol_off();
    update_ram_1621();
    delay(10);
  }
}

void b_inflate_action(void) {
  // inflate
  if (press_time[7] >= 3000) {
    f_beep_inflate();
    set_pressure = EEPROM.read(inflate_pressure_address);
    f_update_set_pressure();
    error_timer_in = reset_timer;
    leak_timer = leak_set_timer;
    f_symbol_off();
    f_hold_seg_disable();
    f_inflate_seg_enable();
    f_set_lcd();
    update_ram_1621();
    delay(10);
    while (digitalRead(b_inflate) == LOW) {
      b_inflate_setting_on();
    }
  }
}

void b_deflate_action(void) {
  // deflate
  if (press_time[1] >= 3000) {
    f_beep_inflate();
    set_pressure = EEPROM.read(deflate_pressure_address);
    f_update_set_pressure();
    error_timer_in = reset_timer;
    leak_timer = leak_set_timer;
    delay(10);
    f_symbol_off();
    f_hold_seg_disable();
    f_deflate_seg_enable();
    f_set_lcd();
    update_ram_1621();
    while ((digitalRead(b_deflate) == LOW)) {
      b_deflate_setting_on();
    }
  }
}

void b_hold_action(void) {
  // hold
  if (press_time[5] >= 3000) {
    if (hold_timer) {
      f_beep_hold();
      set_pressure = EEPROM.read(set_pressure_copy_address);
      f_update_set_pressure();
      f_hold_seg_disable();
      hold_timer = reset_timer;
      error_timer_in = reset_timer;
      leak_timer = leak_set_timer;
      f_set_hold_timer_1621_off();
      f_set_lcd();
      update_ram_1621();
      while (digitalRead(b_hold) == LOW) {
        b_hold_setting_on();
      }
    }
    else {
      f_beep_hold();
      //      set_pressure = 35;
      EEPROM.update(set_pressure_copy_address, EEPROM.read(set_pressure_address));
      set_pressure = EEPROM.read(hold_pressure_address);
      f_update_set_pressure();
      f_hold_seg_enable();
      hold_timer = hold_set_timer;
      error_timer_in = reset_timer;
      leak_timer = leak_set_timer;
      f_symbol_off();
      f_set_lcd();
      update_ram_1621();
      while (digitalRead(b_hold) == LOW) {
        b_hold_setting_on();
      }
      delay(10);
    }

  }
}

void b_mute_action(void) {
  //mute
  if (press_time[3] >= 2000) {
    buzzer_stop_timer = reset_timer;
    digitalWrite(buzzer, LOW);
    // while (press_time[3]) {}
    delay(10);
    f_set_lcd();
  }
}

void b_lock_action(void) {
  //b_lock
  if (press_time[0] >= 3000) {
    if (btn_flag == true) {
      btn_flag = false;
      f_lock_seg_enable();
      f_set_lcd();
      update_ram_1621();
      while (digitalRead(b_lock) == LOW) {}
    } else {
      btn_flag = true;
      f_lock_seg_disable();
      f_set_lcd();
      update_ram_1621();
      while (digitalRead(b_lock) == LOW) {}
    }
    //     while (press_time[0]) {}
    delay(10);
    f_set_lcd();
  }
}

void f_power_on(void) {
  //  set_pressure = 25;
  hold_timer = 0;
  power_flag = true;
  f_set_lcd();
  update_ram_1621();
  while (digitalRead(b_power) == LOW) {}
}

void f_blink_current_pressure_1621(void){
  for(int i = 0; i < 3; i++){
    set_current_pressure_once(11);
    set_current_pressure_tens(11);
    update_ram_1621();
    delay(100);
    set_current_pressure_1621(f_pressure_cmofH2O());
    update_ram_1621();
    delay(250);
  }
}

void f_power_off(void) {
  if (pressure_cmofH2O > -1 && pressure_cmofH2O < 1) {
    power_flag = false;
    HT1621_all_off(128);
    digitalWrite(pin_pump, LOW);
    digitalWrite(pin_valve_pressure, LOW);
    digitalWrite(pin_valve_vaccum, LOW);
    digitalWrite(buzzer, LOW);
    while (digitalRead(b_power) == LOW) {}
  }
  else{
    f_blink_current_pressure_1621();
//    set_current_pressure_1621(0);
  }

}

void b_power_action(void) {
  if (press_time[4] >= 3000) {
    if (power_flag == true) {
      f_power_off();
    } else {
      f_power_on();

    }
    //     while (press_time[0]) {}
    delay(10);
  }
}

void f_button_action() {
  if ((btn_flag == true || (press_time[0] >= 3000 && btn_flag == false)) && (power_flag == true || (power_flag == false && press_time[4] >= 3000)) || (btn_flag == false && press_time[3] >= 3000)) {
    b_inc_action();
    b_dec_action();
    b_inflate_action();
    b_deflate_action();
    b_hold_action();
    b_mute_action();
    b_lock_action();
    b_power_action();
  }
  else if (btn_flag == false && (digitalRead(b_inc) == LOW || digitalRead(b_dec) == LOW || digitalRead(b_inflate) == LOW || digitalRead(b_deflate) == LOW || digitalRead(b_power) == LOW ||digitalRead(b_hold))) {
      //    Serial.println("Locked");
      while (digitalRead(b_inc) == LOW || digitalRead(b_dec) == LOW || digitalRead(b_inflate) == LOW || digitalRead(b_deflate) == LOW || digitalRead(b_power) == LOW ||digitalRead(b_hold) == LOW) {
        f_blink_lock_seg();
      }
    }
}

int f_hold_set_timer_inc_by(void) {
  if (hold_set_timer == 99) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_hold_set_timer_inc(void) {
  if (press_time[6]) {
    hold_set_timer = hold_set_timer + f_hold_set_timer_inc_by();
    while (digitalRead(b_inc) == LOW) {}
  }
}

int f_hold_set_timer_dec_by(void) {
  if (hold_set_timer == 0) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_hold_set_timer_dec(void) {
  if (press_time[2]) {
    hold_set_timer = hold_set_timer - f_hold_set_timer_dec_by();
    while (digitalRead(b_dec) == LOW) {}
  }
}

int f_hold_pressure_inc_by(void) {
  if (hold_pressure == 40) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_hold_pressure_inc(void) {
  if (press_time[7]) {
    hold_pressure = hold_pressure + f_hold_pressure_inc_by();
    while (digitalRead(b_inflate) == LOW) {}
  }
}

int f_hold_pressure_dec_by(void) {
  if (hold_pressure == 10) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_hold_pressure_dec(void) {
  if (press_time[1]) {
    hold_pressure = hold_pressure - f_hold_pressure_dec_by();
    while (digitalRead(b_deflate) == LOW) {}
  }
}

void b_hold_setting_off(void) {
  if (press_time[4]) {
    if (setting_mode == 1) {
      f_update_hold_set_timer();
      f_update_hold_pressure();
      setting_mode = 0;
      f_setting_seg_disable();
    }
  }
}

void f_button_action_s1(void) {
  if ((power_flag == true || (power_flag == false && press_time[4] >= 3000))) {
    b_hold_setting_off();
    b_hold_set_timer_inc();
    b_hold_set_timer_dec();
    b_hold_pressure_inc();
    b_hold_pressure_dec();
  }
}

int f_inflate_pressure_inc_by(void) {
  if (inflate_pressure == c_set_value_maximum) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_inflate_pressure_inc(void) {
  if (press_time[6]) {
    inflate_pressure = inflate_pressure + f_inflate_pressure_inc_by();
    while (digitalRead(b_inc) == LOW) {}
  }
}

int f_inflate_pressure_dec_by(void) {
  if (inflate_pressure == c_set_value_minimum) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_inflate_pressure_dec(void) {
  if (press_time[2]) {
    inflate_pressure = inflate_pressure - f_inflate_pressure_dec_by();
    while (digitalRead(b_dec) == LOW) {}
  }
}

void b_inflate_setting_off(void) {
  if (press_time[4]) {
    if (setting_mode == 2) {
      f_update_inflate_pressure();
      setting_mode = 0;
      set_pressure = EEPROM.read(inflate_pressure_address);
      f_setting_seg_disable();
    }
  }
}

void f_button_action_s2(void) {
  if ((power_flag == true || (power_flag == false && press_time[4] >= 3000))) {
    b_inflate_setting_off();
    b_inflate_pressure_inc();
    b_inflate_pressure_dec();
  }
}

int f_deflate_pressure_inc_by(void) {
  if (deflate_pressure == c_set_value_maximum) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_deflate_pressure_inc(void) {
  if (press_time[6]) {
    deflate_pressure = deflate_pressure + f_deflate_pressure_inc_by();
    while (digitalRead(b_inc) == LOW) {}
  }
}

int f_deflate_pressure_dec_by(void) {
  if (deflate_pressure == 0) {
    return 0;
  }
  else {
    return 1;
  }
}

void b_deflate_pressure_dec(void) {
  if (press_time[2]) {
    deflate_pressure = deflate_pressure - f_deflate_pressure_dec_by();
    while (digitalRead(b_dec) == LOW) {}
  }
}

void b_deflate_setting_off(void) {
  if (press_time[4]) {
    if (setting_mode == 3) {
      f_update_deflate_pressure();
      setting_mode = 0;
      set_pressure = EEPROM.read(deflate_pressure_address);
      f_setting_seg_disable();
    }
  }
}

void f_button_action_s3(void) {
  if ((power_flag == true || (power_flag == false && press_time[4] >= 3000))) {
    b_deflate_setting_off();
    b_deflate_pressure_inc();
    b_deflate_pressure_dec();
  }
}
/* ******************** Error Signal ******************** */

//void f_buzzer() {
//  if (buzzer_stop_timer == 120) {
//    if (pressure_cmofH2O > set_pressure + c_band) {
//      digitalWrite(buzzer, HIGH);
//    } else if (pressure_cmofH2O < set_pressure - c_band) {
//      digitalWrite(buzzer, HIGH);
//    } else {
//      digitalWrite(buzzer, LOW);
//    }
//  }
//}

void f_buzzer_on(void){
  if(buzzer_stop_timer == 120) digitalWrite(buzzer,HIGH);
}

void f_buzzer_off(void){
  digitalWrite(buzzer,LOW);
}


void f_leak() {
  if (leak_timer == 0 && ((pressure_cmofH2O < set_pressure - c_band) || (pressure_cmofH2O > set_pressure + c_band)) && hold_timer == reset_timer) {
    f_leak_seg_enable();
    f_buzzer_on();
  }
  else {
    f_leak_seg_disable();
    f_buzzer_off();
    if ((pressure_cmofH2O > set_pressure - c_band) && (pressure_cmofH2O < set_pressure + c_band)) leak_timer = leak_set_timer;
  }
}

/* ******************** Clock ******************** */
void f_update_inc_timer(void) {
  if (inc_timer < inc_dec_set_timer) {
    inc_timer++;
  }
}

void f_update_dec_timer(void) {
  if (dec_timer < inc_dec_set_timer) {
    dec_timer++;
  }
}

void f_update_leak_timer(void) {
  if (leak_timer > 0) {
    leak_timer--;
  }
}

void f_update_hold_timer(void) {
  if (hold_timer > 0) {
    hold_timer--;
  }
}

void f_update_mute_timer(void) {
  if (buzzer_stop_timer < 120) {
    f_alarm_seg_disable();
    buzzer_stop_timer++;
  } else {
    f_alarm_seg_enable();
  }
}

void f_update_error_timer(void) {
  if (error_timer_in < 20) {
    error_timer_in++;
  }
}

void f_update_blink_timer(void){
  if(/*digitalRead(charging_status)*/1){
    blink_timer++;
  }
}

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




    if (digitalRead(b_mute) == LOW) {
      press_mute_time++;
    }
    if (digitalRead(b_lock) == LOW) {
      press_lock_time++;
    }
  }
}

void f_mode_0(void) {
  if (power_flag) {
    f_clock();
    f_get_button_state();
    //int             buttons_timer[8]            = {lock_timer, def_timer, dec_timer, mute_timer, power_timer, hold_timer, inc_timer, inflate_timer};
    boolean             pressure_flag           = (inc_timer == inc_dec_set_timer) & (dec_timer == inc_dec_set_timer) ;
    if (pressure_flag) f_set_pressure();
    f_leak();
    if (hold_timer == 0 || press_time[5] >= 3000) f_button_action();
    if (power_flag == true) update_ram_1621();

    //    f_sucess_status_action();
  }
  else {
    HT1621_all_off(128);
    digitalWrite(pin_pump, LOW);
    digitalWrite(pin_valve_pressure, LOW);
    digitalWrite(pin_valve_vaccum, LOW);
    digitalWrite(buzzer, LOW);
    f_clock();
    f_get_button_state();
    f_button_action();
  }
}

void set_screen_mode_1(void) {
  set_current_pressure_once(11);
  set_current_pressure_tens(11);
  set_pressure_1621(hold_pressure);
  set_hold_timer_1621(hold_set_timer);
  f_hold_seg_enable();
  f_setting_seg_enable();
  f_cm_of_h2o_seg_disable();
}

void f_mode_1(void) {
  f_clock();
  f_button_action_s1();
  //    HT1621_all_off(128);
  set_screen_mode_1();
  f_get_button_state();
  update_ram_1621();

}

void set_screen_mode_2(void) {
  set_current_pressure_once(11);
  set_current_pressure_tens(11);
  set_pressure_1621(inflate_pressure);
  f_inflate_seg_enable();
  f_setting_seg_enable();
  f_cm_of_h2o_seg_disable();
}

void f_mode_2(void) {
  f_clock();
  f_get_button_state();
  set_screen_mode_2();
  f_button_action_s2();
  //HT1621_all_off(128);
  update_ram_1621();
}

void set_screen_mode_3(void) {
  set_current_pressure_once(11);
  set_current_pressure_tens(11);
  set_pressure_1621(deflate_pressure);
  f_deflate_seg_enable();
  f_setting_seg_enable();
  f_cm_of_h2o_seg_disable();
}

void f_mode_3(void) {
  f_clock();
  f_get_button_state();
  set_screen_mode_3();
  f_button_action_s3();
  //HT1621_all_off(128);
  update_ram_1621();
}
/* ******************** Setup ******************** */

void setup() {
  f_set_values();
  f_get_values();
  f_update_set_pressure();
  f_update_hold_pressure();
  f_update_hold_set_timer();
  f_update_inflate_pressure();
  f_update_inflate_pressure();
  pinMode(pin_pump, OUTPUT);
  pinMode(pin_valve_pressure, OUTPUT);
  pinMode(pin_valve_vaccum, OUTPUT);

  pinMode(b_lock, INPUT_PULLUP);
  pinMode(b_deflate, INPUT_PULLUP);
  pinMode(b_dec, INPUT_PULLUP);
  pinMode(b_mute, INPUT_PULLUP); 
  pinMode(b_power, INPUT_PULLUP);
  pinMode(b_hold, INPUT_PULLUP);
  pinMode(b_inc, INPUT_PULLUP);
  pinMode(b_inflate, INPUT_PULLUP);

  init_1621();
  //  Serial.begin(9600);
  //  if (!mysensor.begin())  // initialize and check the device
  //  {
  //    Serial.println("Device not responding.");
  //    while (true)
  //      delay(10);
  //  }
  
}

/* ******************** LOOP ******************** */

void loop() {
  mysensor.readSensor(temperature, pressure);
  pressure_cmofH2O = pressure / 98.0665;
  
  if (setting_mode == 0) {
    f_mode_0();
  }
  else if (setting_mode == 1) {
    /*Hold setting mode*/
    f_mode_1();
  }
  else if (setting_mode == 2) {
    /*Inflate setting mode*/
    f_mode_2();
  }
  else if (setting_mode == 3) {
    /*deflate setting mode*/
    f_mode_3();
  }

  f_charging();
//  //  f_update_values();

}