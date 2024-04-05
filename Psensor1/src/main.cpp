#include <Arduino.h>
#include <SD.h>

// File object to store data
File dataFile; 

void setup() {
  // Set up code
  Serial.begin(9600);

  // SD initialization
  if (!SD.begin(10)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  // Data file initialization
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error opening data.csv!");
    return;
  }
  
}

void loop() {
  // Main code to run repeatedly

  
  int sensorValue = analogRead(A9);
  
  float voltage = sensorValue * (3.3 / 1024);
  int delayinput = 500;


  delay(delayinput);
  Serial.println(voltage);

  // Output instructions regarding CSV file
  if(dataFile) {

     dataFile.print(voltage);
     dataFile.flush();
     dataFile.close();
  }


}
