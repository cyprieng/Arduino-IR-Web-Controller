#include "IRSenderReceiver.h"

// Init IR receiver
IRrecv IRSenderReceiver::m_irrecv(11);

IRSenderReceiver::IRSenderReceiver(){

}

void IRSenderReceiver::getIRCode(IRCode *ircode){
  decode_results results;

  // Wait IR code
  while(!m_irrecv.decode(&results)) {
  }

  m_irrecv.resume(); // Restart ir receiver

  // Retrieve ir data and store it in ircode
  unsigned int rawCodes[RAWBUF];
  ircode->setCodeType(results.decode_type);
  ircode->setCodeLen(results.rawlen);
  if (ircode->getCodeType() == UNKNOWN) {
    ircode->setCodeLen(results.rawlen - 1);

    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    for (int i = 1; i <= ircode->getCodeLen(); i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results.rawbuf[i]*USECPERTICK - MARK_EXCESS;
      }
      else {
        // Space
        rawCodes[i - 1] = results.rawbuf[i]*USECPERTICK + MARK_EXCESS;
      }
      ircode->setRawCodes(rawCodes);
    }
  }
  else {
    if (ircode->getCodeType() == NEC) {
      if (results.value == REPEAT) {
        // Don't record a NEC repeat value as that's useless.
        return;
      }
    }

    ircode->setCodeValue(results.value);
    ircode->setCodeLen(results.bits);
  }
}

void IRSenderReceiver::sendIRCode(const IRCode& ircode, int repeat) {
 if (ircode.getCodeType() == NEC) {
    if (repeat) {
      m_irsend.sendNEC(REPEAT, ircode.getCodeLen());
    }
    else {
      m_irsend.sendNEC(ircode.getCodeValue(), ircode.getCodeLen());
    }
  }
  else if (ircode.getCodeType() == SONY) {
    m_irsend.sendSony(ircode.getCodeValue(), ircode.getCodeLen());
  }
  else if (ircode.getCodeType() == RC5 || ircode.getCodeType() == RC6) {
    if (!repeat) {
      // Flip the toggle bit for a new button press
      toggle[ircode.getRemoteNumber()] = 1 - toggle[ircode.getRemoteNumber()];
    }
    // Put the toggle bit into the code to send
    unsigned long codeValue = ircode.getCodeValue() & ~(1 << (ircode.getCodeLen() - 1));
    codeValue = codeValue | (toggle[ircode.getRemoteNumber()] << (ircode.getCodeLen() - 1));
    if (ircode.getCodeType() == RC5) {
      m_irsend.sendRC5(codeValue, ircode.getCodeLen());
    }
    else {
      m_irsend.sendRC6(codeValue, ircode.getCodeLen());
    }
  }
  else if (ircode.getCodeType() == UNKNOWN /* i.e. raw */) {
    // Assume 38 KHz
    m_irsend.sendRaw(ircode.getRawCodes(), ircode.getCodeLen(), 38);
  }
}
