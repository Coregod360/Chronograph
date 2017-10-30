void chronoLoop() {

  // SENSOR UPDATE
  val1 = analogRead(firstsensor);
  val2 = analogRead(secondsensor);
  
  //DISPLAY PRE-LOAD
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println(fps);
  display.setCursor(70,10);
  display.println("fp/s");
  display.display();
  display.clearDisplay();

//script first sensor
while (val1 >= firstsensorThreshold){
  //Serial.println("Test");
  val1 = analogRead(firstsensor);
}

while (val1 < firstsensorThreshold);{
  Serial.println("Test1");
  time1 = micros();
  val1 = analogRead(firstsensor);
}

//Script second sensor
while(val2 > secondsensorThreshold){
  val2 = analogRead(secondsensor);  
}

while(val2 < secondsensorThreshold);{
  time2 = micros();
  val2 = analogRead(secondsensor);
  
  // DISPLAY UPDATE 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println(fps);
  display.setCursor(70,10);
  display.println("fp/s");
  display.display();
  display.clearDisplay();
}

elap = time2 - time1;
fps = 333333/elap;
Serial.println(fps );

}
