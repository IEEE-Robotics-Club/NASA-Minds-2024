#include <SD.h>
#include <SPI.h>
#include <string.h>

const int chipSelect = BUILTIN_SDCARD;
const int analogPin = 9;
String logFileName; 

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect.
  }

  Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1) {
      // No SD card, so don't do anything more - stay stuck here
    }
  }
  Serial.println("card initialized.");
  logFileName = createFileName();

  //Debug Printng
  //printDirectory(root, 0);
}

void loop()
{
  // make a string for assembling the data to log:
  String dataString = "";
  int sensor = analogRead(analogPin);
  dataString += String(sensor);
  dataString += ",";

  // open the file.
  File dataFile = SD.open(logFileName.c_str(), FILE_WRITE);
  Serial.println(logFileName);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  } else {
    // if the file isn't open, pop up an error:
    Serial.println("error opening file");
  }
  delay(1000); // run at a reasonable not-too-fast speed
}

String createFileName() {
  int counter = 0;
  String fileString = "datalog-0.csv";

  while(SD.exists(fileString.c_str())){
    counter++;
    fileString = "datalog-" + (String)counter + ".csv";
  }
  return fileString;
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }


    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());

    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

