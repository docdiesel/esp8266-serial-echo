/*
 * ==== 8266_softwareserial-echo.ino ====
 * 
 * (en) This is just a small sketch for ESP 8266 that's echoing data which is coming
 *      in via serial line. Useful as counter part when working on a serial client,
 *      e.g. for simulating a device with rs232 interface.
 *      
 * (de) Dieser kleine EPS8266-Sketch lauscht an einer seriellen Schnittstelle und 
 *      sendet die empfangenen Daten zurück ("Echo"). Kann als Gegenstück bei Testen
 *      einer seriellen Kommunikation nützlich sein, z.B. zum Simulieren eines Gerätes
 *      mit RS232-Schnittstelle.
 *
 */

#include <SoftwareSerial.h>

#define BAUD1 115200  // for USB debugging
#define BAUD2 9600    // for the 'echo' serial line
#define RXPIN 13      // RX/TX pins for the 'echo' serial line
#define TXPIN 15
#define SIMULATED_RCT_TIME  100 // reaction time of a simulated device

#define BUFLEN  1024
char    BUFFER[BUFLEN];

// define soft serial object
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
  if (num_bytes>0) {
    delay(SIMULATED_RCT_TIME);  // simulate device reaction time
    WriteToSoftSerial(num_bytes);
  }
}

//-- read from SoftwareSerial
int ReadFromSoftSerial(){
  int i=0;
  while ( softSerial.available()>0 && i<BUFLEN-1) {
    //-- read from serial (RX)
    BUFFER[i] = softSerial.read();   // read
    if (int(BUFFER[i])>0) {          // sometimes softwareserial delivers empty/non-existent byte
      Serial.print(".");             // show on Serial what's going on
      Serial.print(BUFFER[i]);
      i++;
    }
  }
  if ( i>0 ) Serial.println(" < received bytes = " + String(i) );
  return i;  // return number of bytes read
}

//-- write to SoftwareSerial
void WriteToSoftSerial(int numbytes){
  for(int i=0; i<numbytes; i++) {
    //-- write to serial (TX)
    softSerial.write(BUFFER[i]);
  }
}
