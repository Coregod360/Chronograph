
int firstsens = A0;
//int secondsens = A1;

int val;
//int val2;

void setup()
{
Serial.begin(9600);
pinMode (firstsens, INPUT);
//pinMode (secondsens, INPUT);
}
void loop()
{
val = analogRead(firstsens);
//val2 = analogRead(secondsens);
//Serial.println("First Sensor");
Serial.println(val);
//Serial.println("Second Sensor");
//Serial.println(val2);
delay (1000);
}
