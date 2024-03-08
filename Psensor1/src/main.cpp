#include <Arduino.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A9);
  
   

  float voltage = sensorValue * (3.3 / 1024);
  int delayinput = 500;


  delay(delayinput);
  Serial.println(voltage);

}