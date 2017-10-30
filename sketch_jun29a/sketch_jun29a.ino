const int firstSens = A0;
int calibrationSample[199];
int val = 0;
int minimum = 0;
int lowest = 999;

void setup() {

  Serial.begin(9600);
  pinMode(firstSens, INPUT);



  for (int i = 0; i < 199; i++) {
      int val = analogRead(firstSens);
    calibrationSample[i] = val;
   Serial.println(calibrationSample[i]);
  }


  for (int i = 0; i < 199; i++) {
      if(calibrationSample[i] < lowest && calibrationSample[i] != lowest){
      lowest = calibrationSample[i];
    }
  }

  
  Serial.println("Lowest value found is");
  Serial.println(lowest); 
  Serial.println("Calibration finished!");

}


void loop() {

}

