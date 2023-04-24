#include "Arduino.h"
//IDE 2.0.4: Edit at line 401 in SoftwareSerial.h, C:\Users\Roshan Chamal\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\libraries\SoftwareSerial\src
//IDE 1.8.x version: Edit files (SoftwareSerial.h and SoftwareSerial.cpp) in the (ARDUINO) C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\SoftwareSerial\src
//IDE 1.8.x version: Edit files (SoftwareSerial.h and SoftwareSerial.cpp) in the (ESP8266) C:\Users\Roshan Chamal\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\3.1.2\libraries\SoftwareSerial\src
#define _SS_MAX_RX_BUFF 268 // RX buffer size
#include <SoftwareSerial.h>

#define RXPin        D1  // Serial Receive pin
#define TXPin        D2  // Serial Transmit pin

SoftwareSerial mySerial(RXPin, TXPin); // RX, TX

float chargingCurrent=0,batteryVoltage=0;
int batteryCapacity=0;

char dataCmd[] = {0x4E, 0x57, 0x00, 0x13 ,0x00 ,0x00, 0x00 ,0x00 ,0x06 ,0x03 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x68 ,0x00 ,0x00 ,0x01 ,0x29};

char buffData[268];
int byteCounter = 0;

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  mySerial.begin(115200);
  while (!mySerial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("JK-BMS ~ RS-485 TTL Monitor Starting...");
}

int reqCount = 0, validCount = 0;
void loop() {  

    Serial.println("Requesting ...");
    mySerial.write(dataCmd, sizeof(dataCmd));
    delayMicroseconds(2000);
    //read data
    byteCounter = 0;
    int inByte = 0;
    while(mySerial.available())
    {
      inByte = mySerial.read();
      buffData[byteCounter] = inByte;
      //Serial.print(byteCounter);Serial.print(':');Serial.print(inByte, HEX);Serial.println(' ');
      byteCounter++;
      delayMicroseconds(5);
    }
    //mySerial.flush();
    if(byteCounter > 0)
    {
      ProcessDataPacket();
    }
    reqCount++;
    Serial.print("Data available count:");Serial.print(byteCounter);
    Serial.print(", Request count:");Serial.print(reqCount);
    Serial.print(", Valid count:");Serial.println(validCount);

  delay(5000);
}

void ProcessDataPacket()
{
  //int pos = 11;
  //Serial.print(pos);Serial.print(':');Serial.print(buffData[pos], HEX);Serial.println(' ');

  if(buffData[0]==0x4E && buffData[1]==0x57 && buffData[11]==0x79)
  {    
    Serial.println("Valid.");
    validCount++;
    
    int pos = 12;
    int cellCount = buffData[pos++]/3;
    Serial.print("cellCount:");Serial.println(cellCount);

    for(int b=1; b <= cellCount; b++)
    {
      int cellNumber =buffData[pos++];
      int read_cellVolt1 = buffData[pos++];
      //Serial.print("pos:");Serial.print(pos);Serial.print(' ');Serial.print(buffData[pos],HEX);Serial.print(' ');Serial.print(read_cellVolt1,HEX);
      int read_cellVolt2 = buffData[pos++];
      //Serial.print("pos:");Serial.print(pos);Serial.print(' ');Serial.print(buffData[pos],HEX);Serial.print(' ');Serial.print(read_cellVolt2,HEX);
      float cellVolt = (read_cellVolt2 + read_cellVolt1*256) * 0.001;
      Serial.print("cell:");Serial.print(cellNumber);Serial.print(' ');Serial.println(cellVolt);
    }
    
    batteryCapacity = buffData[53];
    Serial.print("Capacity:");Serial.println(batteryCapacity);
    chargingCurrent = (buffData[51] + buffData[50]*256) * -0.01; 
    Serial.print("Current:");Serial.println(chargingCurrent);
    batteryVoltage = (buffData[48] + buffData[47]*256) * 0.01; 
    Serial.print("Voltage:");Serial.println(batteryVoltage);
    
    Serial.println();
  }
  else{
    Serial.println("Not a valid response.");
  }
}
