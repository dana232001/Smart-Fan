#include <SPI.h>
#include <SD.h>
#include <SimpleDHT.h>

int pinDHT11 = 2;
SimpleDHT11 dht11;
int m=3;
int pir=4;
#define CS_PIN 10
  
File dataLoggerFile;

int hasMoved;
String dataLoggerFileName = "logger.txt";

void setup() 
{
  Serial.begin(9600);

  // SD Card initialization
  pinMode(CS_PIN, OUTPUT);
  if (SD.begin()) {
    Serial.println("SD Card is ready to use.");
  } else {
    Serial.println("SD Card initialization failed");
    return;
  }
  pinMode(pir, INPUT);
  pinMode(m,OUTPUT);
  delay(500);
}

void loop() 
{
  hasMoved = digitalRead(pir);
  Serial.println(hasMoved);
  byte temp = 0;
  byte humidity = 0;
  byte data[40] = {0}; 

  if (dht11.read(pinDHT11, &temp, &humidity, data)) 
  {
    Serial.print("Read DHT11 failed");
    return;
  }
  Serial.print((float)temp); 
  Serial.print(" *C, ");
 
dataLoggerFile = SD.open("logger.txt", FILE_WRITE);
  if (dataLoggerFile) {
    dataLoggerFile.print((float)temp);
    dataLoggerFile.print("-");
    dataLoggerFile.println(hasMoved);
    Serial.println("Done");
    
  }
  else {
    Serial.println("error opening data logger file");
  }  
  dataLoggerFile.close();
  
  if((float)temp>=20)
    digitalWrite(m,HIGH);
  else
    digitalWrite(m,LOW);
 delay(1000);
}
