/*
 * ==== 8266_softwareserial-echo.ino ====
 * 
 * (en) This is just a small sketch for ESP 8266 that's echoing data which is coming
 *      in via serial line. Useful as counter part when working on a serial client.
 *      
 * (de) Dieser kleine EPS8266-Sketch lauscht an einer seriellen Schnittstelle und 
 *      sendet die empfangenen Daten zurück ("Echo"). Kann als Gegenstück bei Testen
 *      einer seriellen Kommunikation nützlich sein. 
 *
 */

#include <SoftwareSerial.h>

#define SLEEP 500     // ms to wait between read tries
#define BAUD1 115200  // for USB debugging
#define BAUD2 9600    // for the 'echo' serial line
#define RXPIN 13      // RX/TX pins for the 'echo' serial line
#define TXPIN 15

#define BUFLEN  1024
char BUFFER[BUFLEN];

// define soft serial object; RX = GPIO13, TX = GPIO15
SoftwareSerial softSerial(RXPIN, TXPIN, false, BUFLEN);

//== fire up your ESP
void setup() {
  Serial.begin(BAUD1);     // standard serial/USB
  softSerial.begin(BAUD2); // default is 8N1
  Serial.println("\n\n******** Software Serial Echo starting; RXPIN=" + String(RXPIN) + ",TXPIN=" +  String(TXPIN) + " ********\n");
}

//== listen to RX, echo on TX
void loop() {
  int num_bytes = ReadFromSoftSerial();
  if (num_bytes > 0) {
    delay(100);
    WriteToSoftSerial(num_bytes);
    Serial.println("Echoed " + String(num_bytes) + " bytes");
  }
  else
  {
    Serial.println("nothing to echo");
  }
  delay(SLEEP);            // waiting for Godot
}

int ReadFromSoftSerial(){
  int i=0;
  while(softSerial.available() > 0 && i < BUFLEN) {
    //-- read from serial (RX)
    BUFFER[i] = softSerial.read();
    i++;
  }
  return i;
}

void WriteToSoftSerial(int numbytes){
  for(int i=0; i<numbytes; i++) {
    //-- write to serial (TX)
    softSerial.write(BUFFER[i]);
    i++;
  }
}
