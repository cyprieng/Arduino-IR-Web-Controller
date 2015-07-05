#include "IRCode.h"
#include "IRSenderReceiver.h"
#include <IRremote.h>
#include <SoftwareSerial.h>
#define DEBUG true

IRSenderReceiver sender = IRSenderReceiver();
IRCode ircode;
 
String SSID = "TECOM-AH4222-7B2F41";
String password = "a220b9d7af3fcbd6bcc98df8d6";

SoftwareSerial esp8266(9,10);

void setup(){
  Serial.begin(9600);
  IRSenderReceiver::m_irrecv.enableIRIn();
  esp8266.begin(9600);

  // Configure WiFi module
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CWJAP=\""+ SSID + "\",\"" + password +"\"\r\n",10000,DEBUG); // connect to network
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop(){
  if(esp8266.available()){ // check if the esp is sending a message
 
    if(esp8266.find("+IPD,") && esp8266.find("GET /receiver/")){ // API URL for retrieving an IR code
      // Get IR code
      Serial.println("Getting IR code...");
      sender.getIRCode(&ircode);

      // Send JSON
      Serial.println("Sending IR code...");
      
      // Build header
      String Header;
      Header =  "HTTP/1.1 200 OK\r\n";
      Header += "Content-Type: application/json\r\n";
      Header += "Connection: close\r\n";

      // Build content
      String Content;
      Content = "{\"type\":\""+ (String)ircode.getCodeType() +"\", \"value\":\""+ (String)ircode.getCodeValue() +"\"}";

      // Set content length
      Header += "Content-Length: ";
      Header += (int)(Content.length());
      Header += "\r\n\r\n";

      // Send data
      int length = Header.length()+Content.length();
      sendData("AT+CIPSEND=0,"+(String)length+"\r\n",2000,DEBUG);
      delay(10);
      sendData(Header+Content,2000,DEBUG);
      delay(10);
    }
  }
}
 
 
String sendData(String command, const int timeout, boolean debug){
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis()){
      while(esp8266.available()){
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug){
      Serial.print(response);
    }
    
    return response;
}

