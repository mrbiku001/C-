//  Example for XGZP6897D library
//  Simple read of temperature and pressure with a CFSensor I2C sensor
//  such as XGZP6897D
#include <XGZP6897D.h>
#include <avr/sleep.h>

//LCD
static const uint8_t 	ComMode 			= 0x52;
static const uint8_t 	RCosc 				= 0x30;
static const uint8_t 	LCD_on 				= 0x06;
static const uint8_t 	LCD_off 			= 0x04;
static const uint8_t 	Sys_en 				= 0x02;
static const uint8_t 	CTRl_cmd 			= 0x80;
static const uint8_t 	Data_cmd 			= 0xa0;
static const uint8_t 	delayUs 			= 1;


//LCD Segments
// segment 1
// segment 1
#define 			c_1A 						    driver_ram_1621[26][3]
#define 			c_1B 						    driver_ram_1621[26][2]
#define 			c_1C 						    driver_ram_1621[26][1]
#define 			c_1D 						    driver_ram_1621[26][0]
#define 			c_1E 						    driver_ram_1621[25][0]
#define 			c_1F 						    driver_ram_1621[25][2]
#define 			c_1G 						    driver_ram_1621[25][1]
// segment 2						
#define 			c_2A 						    driver_ram_1621[28][3]
#define 			c_2B 						    driver_ram_1621[28][2]
#define 			c_2C 								driver_ram_1621[28][1]
#define 			c_2D 								driver_ram_1621[28][0]
#define 			c_2E 								driver_ram_1621[27][0]
#define 			c_2F 								driver_ram_1621[27][2]
#define 			c_2G 								driver_ram_1621[27][1]
//segment 5								
#define 			c_5A 								driver_ram_1621[3][3]
#define 			c_5B 								driver_ram_1621[3][2]
#define 			c_5C 								driver_ram_1621[3][1]
#define 			c_5D 								driver_ram_1621[3][0]
#define 			c_5E 								driver_ram_1621[4][1]
#define 			c_5F 								driver_ram_1621[4][3]
#define 			c_5G 								driver_ram_1621[4][2]
//segmen			t 6								
#define 			c_6A 								driver_ram_1621[1][3]
#define 			c_6B 								driver_ram_1621[1][2]
#define 			c_6C 								driver_ram_1621[1][1]
#define 			c_6D 								driver_ram_1621[1][0]
#define 			c_6E 								driver_ram_1621[2][1]
#define 			c_6F 								driver_ram_1621[2][3]
#define 			c_6G 								driver_ram_1621[2][2]
											
#define 			c_T1 								driver_ram_1621[23][1]
#define 			c_T2 								driver_ram_1621[23][2]
#define 			c_T3 								driver_ram_1621[29][3]
#define 			c_T4 								driver_ram_1621[25][3]
#define 			c_T5 								driver_ram_1621[23][3]
#define 			c_T6 								driver_ram_1621[27][3]
#define 			c_T7 								driver_ram_1621[23][0]
#define 			c_T8 								driver_ram_1621[24][2]
#define 			c_T9 								driver_ram_1621[24][1]
#define 			c_T10								driver_ram_1621[24][0]
#define 			c_T11								driver_ram_1621[29][2]
#define 			c_T12								driver_ram_1621[29][1]
#define 			c_T13								driver_ram_1621[29][0]
#define 			c_T14								driver_ram_1621[30][0]
#define 			c_T15								driver_ram_1621[30][1]
#define 			c_T16								driver_ram_1621[31][3]
#define 			c_T17								driver_ram_1621[30][3]
#define 			c_T18								driver_ram_1621[30][2]
#define 			c_T19								driver_ram_1621[31][0]
#define 			c_T20								driver_ram_1621[31][1]
#define 			c_T21								driver_ram_1621[31][2]
#define 			c_T22								driver_ram_1621[8][3]
#define 			c_T23								driver_ram_1621[6][0]
#define 			c_T24								driver_ram_1621[4][0]
#define 			c_T25								driver_ram_1621[2][0]
#define 			c_T26								driver_ram_1621[0][3]
#define 			c_T27								driver_ram_1621[0][2]
#define 			c_T28								driver_ram_1621[0][1]
#define 			c_T29								driver_ram_1621[0][0]

 
// buttons
#define 			b_lock   						A1
#define 			b_def    						11
#define 			b_dec    						13
#define 			b_mute   						A0
#define 			b_power  						2
#define 			b_hold   						A2
#define 			b_inc    						12
#define 			b_inflate						10

#define 			SCREEN_WIDTH 			  128 // OLED display width, in pixels
#define 			SCREEN_HEIGHT			  64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
// #define 			OLED_RESET              					-1       // Reset pin # (or -1 if sharing Arduino reset pin)
// #define 			SCREEN_ADDRESS          					 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define 			pin_pump          					  8
#define 			pin_valve_pressure					  6
#define 			pin_valve_vaccum  					  7
#define 			buzzer            					  9
			
#define 			c_pulse_pressure 					    100
#define 			c_pulse_vaccum 						    100
#define 			c_pulse_pressure_valve 				30
#define 			c_pulse_vaccum_valve 				  50

// #define set_pressure            25
#define       c_band                        1

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
unsigned long       gv_millis_old           = 0;
unsigned long       gv_millis_new           = 0;
unsigned long       gv_millis_delta         = 0;
unsigned long       prev_time, current_time;
float               pressure, temperature;
float               pressure_cmofH2O;;
int                 set_pressure = 25;
boolean             btn_flag                = true;
boolean             sleep_mode              = false;
int                 buzzer_stop_timer       = 120;
int                 press_mute_time         = 0;
int                 press_lock_time         = 0;

int                 buttons[8]              = {b_lock, b_def, b_dec, b_mute, b_power, b_hold, b_inc, b_inflate};
boolean             button_current_state[8] = {1, 1, 1, 1, 1, 1, 1, 1};
boolean             button_prev_state[8]    = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long       press_time[8]           = {0, 0, 0, 0, 0, 0, 0, 0};
boolean             flag                    = false;
int                 error_timer_in          = 5;
int                 button_pressed          = -1;
// HT1621
const uint8_t       csPin                   = 5;   //Chip selection output
const uint8_t       wrPin                   = 3;   //Read clock output
const uint8_t       dataPin                 = 4; //Serial data output


bool driver_ram_1621[32][4]                 = {
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


/* ********************LCD Driver HT1621 Functions******************** */


void SendBit_1621(uint8_t sdata, uint8_t cnt) {
  uint8_t i;
  for (i = 0; i < cnt; i++) {
    digitalWrite(wrPin, LOW);
    delayMicroseconds(delayUs);
    if (sdata & 0x80) digitalWrite(dataPin, HIGH);
    else digitalWrite(dataPin, LOW);
    digitalWrite(wrPin, HIGH);
    delayMicroseconds(delayUs);
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
  digitalWrite(csPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(wrPin, HIGH);

  delay(50);

  SendCmd_1621(Sys_en);
  SendCmd_1621(RCosc);
  SendCmd_1621(ComMode);
  SendCmd_1621(LCD_on);
}

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
      // case 11:
      //   c_1A = 1; c_1B = 0; c_1C = 0; c_1D = 1; c_1E = 1; c_1F = 1; c_1G = 0;
      //   break;
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
      // case 11:
      //   c_2A = 1; c_2B = 1; c_2C = 1; c_2D = 1; c_2E = 0; c_2F = 0; c_2G = 0;
      //   break;
  }
}

void set_current_pressure_1621(int pressure) {
  if (pressure < 0 || pressure > 99) {
    set_current_pressure_once(10);
    set_current_pressure_tens(10);
  }
  // else if (pressure > 99) {
  //   set_current_pressure_once(11);
  //   set_current_pressure_tens(11);
  // }
  else {
    set_current_pressure_once(pressure % 10);
    set_current_pressure_tens(pressure / 10);
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
      // case 11:
      //   c_5A = 1; c_5B = 1; c_5C = 1; c_5D = 1; c_5E = 0; c_5F = 0; c_5G = 0;
      //   break;
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
      // case 11:
      //   c_6A = 1; c_6B = 1; c_6C = 1; c_6D = 1; c_6E = 0; c_6F = 0; c_6G = 0;
      //   break;
  }
}

void set_pressure_1621(int pressure) {
  if (pressure < 0 || pressure > 99) {
    set_pressure_once(10);
    set_pressure_tens(10);
  }
  // else if (pressure > 99) {
  //   set_pressure_once(11);
  //   set_pressure_tens(11);
  // }
  else {
    set_pressure_once(pressure % 10);
    set_pressure_tens(pressure / 10);
  }
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

void f_hold_seg_enable(void) {
  c_T10 = 1;
}

void f_hold_seg_disable(void) {
  c_T10 = 0;
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
  f_hold_seg_disable();
}

void f_always_on_seg(void) {
  c_T25 = 1;
  c_T28 = 0;
  c_T29 = 0;
  c_T17 = 1;
  c_T18 = 1;
  c_T1 = 1;
  c_T3 = 1;
  c_T4 = 1;
  c_T5 = 1;
  c_T6 = 1;
  c_T2 = 1;
}


void f_set_lcd(void) {
  f_always_on_seg();
  set_current_pressure_1621(pressure_cmofH2O);
  set_pressure_1621(set_pressure);
}



// Button Functions
void f_sleep() {
  sleep_enable();
  attachInterrupt(0, wake_up, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  sleep_disable();
  detachInterrupt(0);
  delay(1000);
  digitalWrite(b_power, LOW);
}

void wake_up() {
  sleep_mode = false;
  digitalWrite(b_power, HIGH);
}

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

void f_print_serial() {
  Serial.print(pressure);
  Serial.print("Pa");
  Serial.print("\t");

  Serial.print(pressure_cmofH2O);
  Serial.print("mm of H20");
  Serial.println();
  delay(100);
}

//void f_set_display(void)
//{
//  display.clearDisplay();
//
//  display.setTextSize(4);              // Normal 1:1 pixel scale
//  display.setTextColor(SSD1306_WHITE); // Draw white text
//  display.setCursor(0, 0);             // Start at top-left corner
//  // display.print(F("Pa:"));
//  // display.println(pressure);
//
//  display.print(pressure_cmofH2O, 0);
//  // display.setCursor(96,0);
//  display.println(F("cm"));
//  display.setTextSize(2);
//  display.setCursor(0, 48);
//  display.print("SET:");
//  display.print(set_pressure);
//  display.print("cm");
//  display.display();
//  // delay(2000);
//}

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

    if (button_current_state[button_pressed]) {
      if (press_time[i] == 0) {
      } else if (press_time[i] < 2000) {
        Serial.print("Short press btn ");
        Serial.println(i);
        Serial.println(press_time[button_pressed]);
      } else {
        Serial.print("long press btn ");
        Serial.println(i);
        Serial.println(press_time[button_pressed]);
      }
    }

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

void b_inc_action(void) {
  // inc_trg
  if (press_time[6]) {
    set_pressure = set_pressure + 1;
    // while (press_time[6]) {}
    error_timer_in = 0;
    f_inc_seg_enable();
    f_set_lcd();
    f_symbol_off();
    update_ram_1621();
    delay(10);
  }
  f_inc_seg_disable();
}

void b_dec_action(void) {
  // dec_trg
  if (press_time[2]) {
    set_pressure = set_pressure - 1;
    // while (press_time[2]) {}
    error_timer_in = 0;
    f_dec_seg_enable();
    f_set_lcd();
    f_symbol_off();
    update_ram_1621();
    delay(10);
  }
  f_dec_seg_disable();
}

void b_inflate_action(void) {
  // inflate
  if (press_time[7]) {
    set_pressure = 30;
    // while (press_time[7]) {}
    error_timer_in = 0;
    f_symbol_off();
    f_inflate_seg_enable();
    f_set_lcd();
    update_ram_1621();
    delay(10);
  }
}

void b_deflate_action(void) {
  // deflate
  if (press_time[1]) {
    set_pressure = 0;
    // while ((digitalRead(b_def) == LOW)) {}
    error_timer_in = 0;
    delay(10);
    f_symbol_off();
    f_deflate_seg_enable();
    f_set_lcd();
    update_ram_1621();
  }
}

void b_hold_action(void) {
  // hold
  if (press_time[5]) {
    set_pressure = 25;
    // while (press_time[5]) {}
    delay(10);
    error_timer_in = 0;
    f_symbol_off();
    f_hold_seg_enable();
    f_set_lcd();
    update_ram_1621();
  }
}

void b_mute_action(void) {
  //mute
  if (press_time[3] >= 2000) {
    buzzer_stop_timer = 0;
    digitalWrite(buzzer, LOW);
    // while (press_time[3]) {}
    delay(10);
    f_set_lcd();
  }
}

void b_lock_action(void) {
  //b_lock
  if (btn_flag == true) f_lock_seg_disable();
  if (press_time[0] >= 3000) {
    if (btn_flag == true) {
      btn_flag = false;
      f_lock_seg_enable();
    } else {
      btn_flag = true;
    }
    // while (press_time[0]) {}
    delay(10);
    f_set_lcd();
  }
}

void b_power_action(void) {
  if (press_time[4] >= 3000) {
    if (!sleep_mode) {
      f_sleep();
    }
    // while (press_time[4]) {}
    delay(10);
    f_set_lcd();
  }
  f_set_lcd();
}
void f_button_action() {
  if (btn_flag == true || (press_time[0] && btn_flag == false)) {
    b_inc_action();
    b_dec_action();
    b_inflate_action();
    b_deflate_action();
    b_hold_action();
    b_mute_action();
    b_lock_action();
    b_power_action();
  } else if (btn_flag == false && (press_time[1] || press_time[2] || press_time[3] || press_time[4] || press_time[5] || press_time[6] || press_time[7])) {
    Serial.println("Locked");
    while (btn_flag == false && (press_time[1] || press_time[2] || press_time[3] || press_time[4] || press_time[5] || press_time[6] || press_time[7])) {
    }
  }
}

void f_set_pressure() {
  if (pressure_cmofH2O > set_pressure + c_band) {
    f_pulse_vaccum();
    Serial.println("vaccum");
  } else if (pressure_cmofH2O < set_pressure - c_band) {
    f_pulse_pressure();
    Serial.println("pressure");
  }
}

void f_buzzer() {
  if (buzzer_stop_timer == 120 && error_timer_in == 5) {
    if (pressure_cmofH2O > set_pressure + c_band) {
      digitalWrite(buzzer, HIGH);
    } else if (pressure_cmofH2O < set_pressure - c_band) {
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }
  }
}

void setup() {
  pinMode(pin_pump, OUTPUT);
  pinMode(pin_valve_pressure, OUTPUT);
  pinMode(pin_valve_vaccum, OUTPUT);

  pinMode(b_lock, INPUT_PULLUP);
  pinMode(b_def, INPUT_PULLUP);
  pinMode(b_dec, INPUT_PULLUP);
  pinMode(b_mute, INPUT_PULLUP);
  pinMode(b_power, INPUT_PULLUP);
  pinMode(b_hold, INPUT_PULLUP);
  pinMode(b_inc, INPUT_PULLUP);
  pinMode(b_inflate, INPUT_PULLUP);

  init_1621();
  Serial.begin(9600);
  if (!mysensor.begin())  // initialize and check the device
  {
    Serial.println("Device not responding.");
    while (true)
      delay(10);
  }

  // // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  // {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for (;;)
  //     ; // Don't proceed, loop forever
  //   // Show initial display buffer contents on the screen --
  //   // the library initializes this with an Adafruit splash screen.
  //   display.display();
  //   delay(100); // Pause for 2 seconds

  //   // Clear the buffer
  //   display.clearDisplay();
}


//int i = -1;
void loop() {
  mysensor.readSensor(temperature, pressure);
  pressure_cmofH2O = pressure / 98.0665;

  gv_millis_new = millis();

  if (gv_millis_new - gv_millis_old > 1000) {
    gv_millis_old = gv_millis_new;
    //    f_set_display();
    f_set_lcd();
    f_print_serial();
    if (buzzer_stop_timer < 120) {
      f_alarm_seg_disable();
      buzzer_stop_timer++;
    } else {
      f_alarm_seg_enable();
    }

    if(error_timer_in < 5){
      error_timer_in++;
    }

    if (digitalRead(b_mute) == LOW) {
      press_mute_time++;
    }
    if (digitalRead(b_lock) == LOW) {
      press_lock_time++;
    }
  }

  f_get_button_state();
  f_buzzer();
  f_set_pressure();
  f_button_action();
  update_ram_1621();
}
