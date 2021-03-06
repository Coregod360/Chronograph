// INCLUDE OLED  
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
// END OLED INCLUDE


// DEFINE VARIABLES
const int firstsensor = A0;
const int secondsensor = A1;
unsigned long time1, time2;
float fps, elap;
int val1 = 0;
int val2 = 0;
int calibrationSample1[99];
int calibrationSample2[99];
int calibrateVal1 = 0;
int calibrateVal2 = 0;
int firstsensorThreshold = 999;
int secondsensorThreshold = 999;
int i1;
int i2;
// END VARIABLES



//DEFINE SPLASH SCREEN 
// 'pocket chrono splash screen'
static const unsigned char PROGMEM Logo[] = { 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xfe, 0x00, 0x0f, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x80, 0x38, 0x00, 0x00, 0x3e, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x00, 0xe0, 0x00, 0x00, 0x03, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xc0, 0x00, 0x00, 0x00, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0x00, 0x01, 0xff, 0x80, 0x30, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 
0xff, 0x00, 0x01, 0xff, 0xe0, 0x00, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 
0xfe, 0x00, 0x00, 0xfb, 0xf0, 0x00, 0x7d, 0x9c, 0x10, 0xfe, 0x7c, 0x07, 0xff, 0xff, 0xff, 0xff, 
0x0c, 0x00, 0x00, 0xfb, 0xf3, 0xfe, 0x20, 0x0c, 0x10, 0x70, 0x0c, 0x07, 0xff, 0xff, 0xff, 0xff, 
0x8c, 0x00, 0x00, 0xff, 0xe7, 0xdf, 0x01, 0x0c, 0x11, 0xe1, 0x86, 0x0f, 0xff, 0xff, 0xff, 0xff, 
0xfc, 0x00, 0x00, 0xff, 0x07, 0xcf, 0x83, 0xfc, 0x01, 0xe0, 0x06, 0x0f, 0xff, 0xff, 0xff, 0xff, 
0xfc, 0x00, 0x00, 0xf8, 0x07, 0xcf, 0x83, 0xbc, 0x01, 0xe1, 0xfe, 0x0f, 0xff, 0xff, 0xff, 0xff, 
0xfc, 0x00, 0x00, 0xf8, 0x07, 0xff, 0x21, 0x0c, 0x10, 0xf0, 0x86, 0x07, 0xff, 0xff, 0xff, 0xff, 
0xfe, 0x00, 0x01, 0xfe, 0x01, 0xfe, 0x70, 0x18, 0x18, 0x78, 0x0f, 0x07, 0xff, 0xff, 0xff, 0xff, 
0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xc6, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0x80, 0x40, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x02, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x83, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xc1, 0xc7, 0x00, 0x78, 0x07, 0xc0, 0xf0, 0x01, 0xfc, 0x0f, 
0x00, 0x02, 0x00, 0x00, 0x00, 0x7f, 0xc1, 0xff, 0x00, 0x38, 0x07, 0x00, 0x30, 0x00, 0xf0, 0x03, 
0xff, 0xff, 0xe0, 0x00, 0x07, 0xff, 0xc1, 0xff, 0x0c, 0x3c, 0x0e, 0x0c, 0x38, 0x30, 0xe0, 0xc3, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc1, 0xc7, 0x0c, 0x3c, 0x1e, 0x1c, 0x38, 0x30, 0xe1, 0xc3, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xc3, 0x0c, 0x3c, 0x1e, 0x0c, 0x38, 0x30, 0xe0, 0xc3, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x06, 0x04, 0x18, 0x0f, 0x00, 0x70, 0x10, 0x70, 0x07, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x1e, 0x04, 0x18, 0x0f, 0xc1, 0xf0, 0x10, 0x7c, 0x1f, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,};
// END SPLASH SCREEN DEFINE


void setup()   {
  Serial.begin(9600);

  // DEFINE PINS
    pinMode(firstsensor, INPUT);
    pinMode(secondsensor, INPUT);
  //END DEFINE PINS
                  
  // SETUP DISPLAY
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    display.clearDisplay();
  // DISPLAY CLEARED AND READY

  // CALL FUNCTION FOR SPLASH SCREEN
  splash(); 
  // DISPLAY CLEARED AND READY
  
  // CALL FUNCTION FOR CALIBRATION CHECK
  calibrate();
  // CALLIBRATION FINISHED
  
}

void loop (){
  //CALL MAIN LOOP
  chronoLoop();

}


