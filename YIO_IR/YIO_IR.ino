#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>            //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>     //https://github.com/esp8266/Arduino
#include <IRremoteESP8266.h>      //https://github.com/markszabo/IRremoteESP8266
#include <ProntoHex.h>            //https://github.com/probonopd/ProntoHex
#include "WiFiManager.h"          //https://github.com/tzapu/WiFiManager
#include <ESP8266mDNS.h>          //MDNS
#include <ArduinoJson.h>          //Standard Module V6


//////////////////////////////
// Configuration
//////////////////////////////

//Pin used for the IR LED(S)
IRsend irsend(D3); // Configure Ditigal PIN, D3 is used with the wemos IR shield.

//Pin used for receiving IR signals.
IRrecv irrecv(D4);

//Reset wireless settings at boot. (for recovery and testing purposes)
boolean resetWifiAtBoot = false;





//////////////////////////////
// Global Declerations
//////////////////////////////
char hostString[16] = {0};
ProntoHex ph = ProntoHex();                //Prontohex.
ESP8266WebServer serverHttp(80);          //HTTP service.
WiFiServer serverTcp(23);                 //TCP service.
boolean recordIrLoop = false;              //enable to recordIr
unsigned long serviceIrCapturedCodes[10]; //cache of ir codes to filter out noise
unsigned long serviceIrCapturedCode = 0;  //Found Ir code.
int serviceIrCapturedCodesI = 0;          //Counter to count form 0 to max cache size.

// Storage for the recorded code
int codeType = -1; // The type of code
unsigned long codeValue; // The code value if not raw
unsigned int rawCodes[RAWBUF]; // The durations if raw
int codeLen; // The length of the code
int toggle = 0; // The RC5/6 toggle state

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println(F("Entered config mode"));
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}


//////////////////////////////
// Setup
//////////////////////////////

void setup() {
Serial.begin(115200);

  setupWifi();
  setupHttp();
  setupTcp();
  setupMdns();
  irrecv.enableIRIn();  // Start the receiver
}



//////////////////////////////
// Loop
//////////////////////////////

void loop() {
  serverHttp.handleClient();
  handleTcpPronto();
  MDNS.update();
  if (recordIrLoop){
    recordIr();    
  }
}
