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
    // Get request
    String req = "";
    char c;
    while(esp8266.available() && c != '\r'){
      c = esp8266.read(); // read the next character.
      req+=c;
    }

    if(req.indexOf("+IPD,") > -1 && req.indexOf("GET /receiver/") > -1){ // API URL for retrieving an IR code
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
      Content = "{\"type\":\""+ (String)ircode.getCodeType() +"\", \"value\":\""+ (String)ircode.getCodeValue() +"\", \"length\":\""+ (String)ircode.getCodeLen() +"\"}";

      // Set content length
      Header += "Content-Length: ";
      Header += (int)(Content.length());
      Header += "\r\n\r\n";

      // Send data
      int length = Header.length()+Content.length();
      sendData("AT+CIPSEND=0,"+(String)Header.length()+"\r\n",2000,DEBUG);
      sendData(Header,2000,DEBUG);
      sendData("AT+CIPSEND=0,"+(String)Content.length()+"\r\n",2000,DEBUG);
      sendData(Content,2000,DEBUG);
    }
    else if(req.indexOf("+IPD,") > -1 && req.indexOf("GET /send/") > -1){
      Serial.println("Sending...");

      // Get code
      int index_type = req.indexOf("?type=") + 6;
      int index_end_type = req.indexOf("&value=");
      String type = req.substring(index_type, index_end_type);

      int index_value = req.indexOf("&value=") + 7;
      int index_end_value = req.indexOf("&len=");
      String value = req.substring(index_value, index_end_value);

      int index_len = req.indexOf("&len=") + 5;
      int index_end_len = req.indexOf(" HTTP");
      String len = req.substring(index_len, index_end_len);
      
      ircode.setCodeType(atoi(type.c_str()));
      ircode.setCodeValue(atol(value.c_str()));
      ircode.setCodeLen(atoi(len.c_str()));

      // Send code
      sender.sendIRCode(ircode, 0);

      // Build header
      String Header;
      Header =  "HTTP/1.1 200 OK\r\n";
      Header += "Content-Type: application/json\r\n";
      Header += "Connection: close\r\n";
      Header += "Content-Length: 0";
      Header += "\r\n\r\n";

      // Send data
      sendData("AT+CIPSEND=0,"+(String)Header.length()+"\r\n",2000,DEBUG);
      sendData(Header,2000,DEBUG);
      
      Serial.println("Done");
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

