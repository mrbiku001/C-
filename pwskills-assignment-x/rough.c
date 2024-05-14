//  Example for XGZP6897D library
//  Simple read of temperature and pressure with a CFSensor I2C sensor
//  such as XGZP6897D
#include <XGZP6897D.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimerOne.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

// buttons
#define b_lock A1
#define b_def 11
#define b_dec 13
#define b_mute A0
#define b_power 2
#define b_hold A2
#define b_inc 12
#define b_inflate 10

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define NUMFLAKES 10 // Number of snowflakes in the animation example
#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16

#define pin_pump 8
#define pin_valve_pressure 6
#define pin_valve_vaccum 7
#define buzzer 9

#define c_pulse_pressure 100
#define c_pulse_vaccum 100
#define c_pulse_pressure_valve 30
#define c_pulse_vaccum_valve 50
// long c_pulse_pressure_timer = 0, c_pulse_valve_delay = 0 ;
// long c_pulse_pressure_delay = 100, c_pulse_valve_delay = 50;

// #define set_pressure            25
#define c_band 1

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
#define K 512 // see table above for the correct value for your sensor, according to the sensitivity.
// create the sensor object, passing the correct K value.
XGZP6897D mysensor(K);

//*************************
//**** GLOBAL VARIABLES****
//*************************
unsigned long gv_millis_old = 0;
unsigned long gv_millis_new = 0;
unsigned long gv_millis_delta = 0;

unsigned long prev_time, current_time;

float pressure, temperature;
float pressure_cmofH2O;
int set_pressure = 25;
// boolean device_status = true;
boolean btn_flag = true;
boolean sleep_mode = false;
int buzzer_stop_timer = 120;
int press_mute_time = 0;
int press_lock_time = 0;

int buttons[8] = {b_lock, b_def, b_dec, b_mute, b_power, b_hold, b_inc, b_inflate};
boolean button_current_state[8] = {1, 1, 1, 1, 1, 1, 1, 1};
boolean button_prev_state[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long press_time[8] = {0, 0, 0, 0, 0, 0, 0, 0};
boolean flag = false;
int button_pressed = -1;

void f_sleep()
{
    sleep_enable();
    attachInterrupt(0, wake_up, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    sleep_disable();
    detachInterrupt(0);
    delay(1000);
    digitalWrite(b_power, LOW);
}

void wake_up()
{
    sleep_mode = false;
    digitalWrite(b_power, HIGH);
}

// void f_pressure_low() {
//   digitalWrite(pin_pump, LOW);
//   digitalWrite(pin_valve_pressure, LOW);
// }

// void f_vaccum_high() {
//   digitalWrite(pin_pump, HIGH);
//   digitalWrite(pin_valve_vaccum, HIGH);
// }

// void f_vaccum_low() {
//   digitalWrite(pin_pump, LOW);
//   digitalWrite(pin_valve_vaccum, LOW);
// }

void f_pulse_pressure()
{
    digitalWrite(pin_pump, HIGH);
    delay(c_pulse_pressure);
    digitalWrite(pin_valve_pressure, HIGH);
    delay(c_pulse_pressure_valve);
    digitalWrite(pin_pump, LOW);
    digitalWrite(pin_valve_pressure, LOW);
}

void f_pulse_vaccum()
{
    digitalWrite(pin_pump, HIGH);
    delay(c_pulse_vaccum);
    digitalWrite(pin_valve_vaccum, HIGH);
    delay(c_pulse_pressure_valve);

    digitalWrite(pin_pump, LOW);
    digitalWrite(pin_valve_vaccum, LOW);
}

void f_print_serial()
{
    // Serial.print(temperature); Serial.print("C\t ");
    // 1pascal = 9.8066mmofh20
    Serial.print(pressure);
    Serial.print("Pa");
    Serial.print("\t");

    Serial.print(pressure_cmofH2O);
    Serial.print("mm of H20");
    Serial.println();
    delay(100);
}

void f_set_display(void)
{
    display.clearDisplay();

    display.setTextSize(4);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    // display.print(F("Pa:"));
    // display.println(pressure);

    display.print(pressure_cmofH2O, 0);
    // display.setCursor(96,0);
    display.println(F("cm"));
    display.setTextSize(2);
    display.setCursor(0, 48);
    display.print("SET:");
    display.print(set_pressure);
    display.print("cm");
    display.display();
    // delay(2000);
}

void f_get_button_state()
{

    current_time = millis();
    // iterate arrays
    for (int i = 0; i < sizeof(button_current_state) / sizeof(button_current_state[0]); i++)
    {

        // if button pressed
        if (button_current_state[i] != digitalRead(buttons[i]))
        {
            button_prev_state[i] = button_current_state[i];
            button_current_state[i] = digitalRead(buttons[i]);
        }

        if (!button_current_state[i] && !flag)
        {
            prev_time = current_time;
            flag = true;
            button_pressed = i;
            Serial.print("btn pressed ");
            Serial.println(i);
        }

        if (button_current_state[button_pressed] && flag)
        {
            Serial.print("btn released ");
            Serial.println(i);
            flag = false;
        }

        if (button_current_state[button_pressed])
        {
            if (press_time[i] == 0)
            {
            }
            else if (press_time[i] < 2000)
            {
                Serial.print("Short press btn ");
                Serial.println(i);
                Serial.println(press_time[button_pressed]);
            }
            else
            {
                Serial.print("long press btn ");
                Serial.println(i);
                Serial.println(press_time[button_pressed]);
            }
        }

        if (button_prev_state[i] && !button_current_state[i])
        {
            press_time[i] = current_time - prev_time;
        }
        if (button_current_state[i])
        {
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

void f_button_action()
{

    if (btn_flag == true || (press_time[0] && btn_flag == false))
    {

        // inc_trg
        if (press_time[6])
        {
            set_pressure = set_pressure + 1;
            // while (press_time[6]) {}
            delay(10);
            f_set_display();
        }

        // dec_trg
        if (press_time[2])
        {
            set_pressure = set_pressure - 1;
            // while (press_time[2]) {}
            delay(10);
            f_set_display();
        }

        // inflate
        if (press_time[7])
        {
            set_pressure = 30;
            // while (press_time[7]) {}
            delay(10);
            f_set_display();
        }

        // hold
        if (press_time[5])
        {
            set_pressure = 25;
            // while (press_time[5]) {}
            delay(10);
            f_set_display();
        }

        // deflate
        if (press_time[1])
        {
            set_pressure = 0;
            // while ((digitalRead(b_def) == LOW)) {}
            delay(10);
            f_set_display();
        }

        if (press_time[3] >= 2000)
        {
            buzzer_stop_timer = 0;
            digitalWrite(buzzer, LOW);
            // while (press_time[3]) {}
            delay(10);
            f_set_display();
        }

        if (press_time[0] >= 3000)
        {
            if (btn_flag == true)
            {
                btn_flag = false;
            }
            else
            {
                btn_flag = true;
            }
            // while (press_time[0]) {}
            delay(10);
            f_set_display();
        }

        if (press_time[4] >= 3000)
        {
            if (!sleep_mode)
            {
                f_sleep();
            }
            // while (press_time[4]) {}
            delay(10);
            f_set_display();
        }
        f_set_display();
    }
    else if (btn_flag == false && (press_time[1] || press_time[2] || press_time[3] || press_time[4] || press_time[5] || press_time[6] || press_time[7]))
    {
        Serial.println("Locked");
        while (btn_flag == false && (press_time[1] || press_time[2] || press_time[3] || press_time[4] || press_time[5] || press_time[6] || press_time[7]))
        {
        }
    }
}

void f_set_pressure()
{
    // if ((pressure_cmofH2O > set_pressure + c_band)) {
    //   f_vaccum_high();
    //   // Serial.println("vaccum");
    // } else {
    //   f_vaccum_low();
    // }

    // if (pressure_cmofH2O < set_pressure - c_band) {
    //   f_pressure_high();
    //   // Serial.println("pressure");
    // } else {
    //   f_pressure_low();
    // }

    if (pressure_cmofH2O > set_pressure + c_band)
    {
        f_pulse_vaccum();
        Serial.println("vaccum");
    }
    else if (pressure_cmofH2O < set_pressure - c_band)
    {
        f_pulse_pressure();
        Serial.println("pressure");
    }
}

void f_buzzer()
{
    if (buzzer_stop_timer == 120)
    {
        if (pressure_cmofH2O > set_pressure + c_band)
        {
            digitalWrite(buzzer, HIGH);
        }
        else if (pressure_cmofH2O < set_pressure - c_band)
        {
            digitalWrite(buzzer, HIGH);
        }
        else
        {
            digitalWrite(buzzer, LOW);
        }
    }
}

void setup()
{
    // put your setup code here, to run once:
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

    // Timer1.initialize(1000);
    // Timer1.attachInterrupt(f_sleep);

    Serial.begin(9600);
    if (!mysensor.begin()) // initialize and check the device
    {
        Serial.println("Device not responding.");
        while (true)
            delay(10);
    }

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
        // Show initial display buffer contents on the screen --
        // the library initializes this with an Adafruit splash screen.
        display.display();
        delay(100); // Pause for 2 seconds

        // Clear the buffer
        display.clearDisplay();
    }

    // // Draw a single pixel in white
    // display.drawPixel(10, 10, SSD1306_WHITE);

    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    // display.display();
    // delay(2000);
    // display.display() is NOT necessary after every single drawing command,
    // unless that's what you want...rather, you can batch up a bunch of
    // drawing operations and then update the screen all at once by calling
    // display.display(). These examples demonstrate both approaches...

    //   // Invert and restore display, pausing in-between
    // display.invertDisplay(true);
    // delay(1000);
    // display.invertDisplay(false);
    // delay(1000);
}

void loop()
{

    mysensor.readSensor(temperature, pressure);
    pressure_cmofH2O = pressure / 98.0665;

    gv_millis_new = millis();

    if (gv_millis_new - gv_millis_old > 1000)
    {
        gv_millis_old = gv_millis_new;
        f_set_display();
        f_print_serial();
        if (buzzer_stop_timer < 120)
        {
            buzzer_stop_timer++;
        }
        if (digitalRead(b_mute) == LOW)
        {
            press_mute_time++;
        }
        if (digitalRead(b_lock) == LOW)
        {
            press_lock_time++;
        }
    }

    f_get_button_state();
    f_buzzer();
    f_set_pressure();
    f_button_action();
    //
}
