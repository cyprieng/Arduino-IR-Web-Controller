#include "ircode.h"
#include <IRremote.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int code = Serial.read();
    sendIRCode(ir_codes[code-48]);
  } 
}
