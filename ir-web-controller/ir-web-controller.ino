#include "IRCode.h"
#include "IRSenderReceiver.h"
#include <IRremote.h>

IRSenderReceiver sender = IRSenderReceiver();
int read = 0;
IRCode ircode;

void setup() {
  IRSenderReceiver::m_irrecv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0){
    read = Serial.read();

    if(read == '1'){ // Save code
      sender.getIRCode(&ircode);
      Serial.println("Saved\n");
    }

    if(read == '2'){ // Send code
      sender.sendIRCode(ircode, 0);
      Serial.println("Sent\n");
    }
  }
}
