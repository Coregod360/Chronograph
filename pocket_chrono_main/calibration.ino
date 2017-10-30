void calibrate() {
  
  for (int i1 = 0; i1 < 99; i1++) {
      int calibrateVal1 = analogRead(firstsensor); 
    calibrationSample1[i1] = calibrateVal1;
    Serial.println(calibrationSample1[i1]);
      
     // LOADER TEXT
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(30,0);
        display.println("Calibrating");
        display.setCursor(30,10);
        display.println("Please wait");
        display.display();
     
      //LOADER   
          display.fillRect( 5, 20, i1+21, 10, WHITE);
          display.display();
          
      // END LOADER
  }

  for (int i2 = 0; i2 < 99; i2++) {
      int calibrateVal2 = analogRead(secondsensor);
    calibrationSample2[i2] = calibrateVal2;  
   Serial.println(calibrationSample2[i2]);
  }

  for (int i1 = 0; i1 < 99; i1++) {
      if(calibrationSample1[i1] < firstsensorThreshold && calibrationSample1[i1] != firstsensorThreshold){
      firstsensorThreshold = calibrationSample1[i1] - 50;
    }
  }


  for (int i2 = 0; i2 < 99; i2++) {
      if(calibrationSample2[i2] < secondsensorThreshold && calibrationSample2[i2] != secondsensorThreshold){
      secondsensorThreshold = calibrationSample2[i2] - 50;
    }
  }

  //LOADER CLEAR
  display.clearDisplay();

  Serial.println("Lowest value for first sensor is");
  Serial.println(firstsensorThreshold); 
  Serial.println("Lowest value for second sensor is");
  Serial.println(secondsensorThreshold); 
  Serial.println("Calibration finished!");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("Calibration");
  display.setCursor(35,10);
  display.println("finished!");
  display.display();
  delay(1000);
  display.clearDisplay();

}
