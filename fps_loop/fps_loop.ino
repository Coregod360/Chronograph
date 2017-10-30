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


int firstsensor = A0;
int secondsensor = A1;
unsigned long time1, time2;
float fps, elap;
int val1;
int val2;

void setup() {
  Serial.begin(9600);
  pinMode (firstsensor, INPUT);
  pinMode (secondsensor, INPUT);
}

void loop() {
  val1 = analogRead(firstsensor);
  val2 = analogRead(secondsensor);


//script first sensor
while (val1 > 145){
  val1 = analogRead(firstsensor);
}

while (val1 < 145){
  time1 = micros();
  val1 = analogRead(firstsensor);
}

//Script second sensor
while(val2 > 154){
  val2 = analogRead(secondsensor);
}

while(val2 < 154){
  time2 = micros();
  val2 = analogRead(secondsensor);
}

  elap = time2 - time1;
  fps = 333333/elap;
  Serial.println(fps );
  
  
}



