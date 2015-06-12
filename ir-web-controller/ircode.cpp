/**
 * \file ircode.cpp
 * \brief Define and send IR codes
 * \author cyprieng
 * \version 0.1
 * \date 12/06/2015
 */
#include "ircode.h" 

IRsend irsend; /*!< Load IRsend from IRremote library */

// Define the list of IR codes
int num_codes = 4;
IR_Code ir_codes[4] = {
   { "Philipps", "key0", 4, 20, 0x0 },
   { "Philipps", "key1", 4, 20, 0x1 },
   { "Philipps", "key2", 4, 20, 0x2 },
   { "Philipps", "key3", 4, 20, 0x3 },
};

/*!
 *  \fn void sendIRCode(IR_Code code)
 *  \brief Send IR Code
 *
 *  Send an IR Code thought the LED in pin 3
 *
 *  \param code : code to send
 */
void sendIRCode(IR_Code code) {
  // Switch by the type of code
  switch (code.code_type) {
    case 1:    
      irsend.sendNEC(code.code_value, code.code_bits);
      break;
    case 2:    
      irsend.sendSony(code.code_value, code.code_bits);
      break;
    case 3:    
      irsend.sendRC5(code.code_value, code.code_bits);
      break;
    case 4:    
      irsend.sendRC6(code.code_value, code.code_bits);
      break;
    case 5:    
      irsend.sendDISH(code.code_value, code.code_bits);
      break;
    case 6:    
      irsend.sendSharp(code.code_value, code.code_bits);
      break;
    case 7:    
      irsend.sendPanasonic(code.code_value, code.code_bits);
      break;
    case 8:    
      irsend.sendJVC(code.code_value, code.code_bits, 0);
      break;
    case 9:
      // Not implemented yet in the library    
      //irsend.sendSanyo(code.code_value, code.code_bits);
      break;
    case 10:    
      // Not implemented yet in the library
      //irsend.sendMitsubishi(code.code_value, code.code_bits);
      break;
    case 11:    
      irsend.sendSAMSUNG(code.code_value, code.code_bits);
      break;
    case 12:    
      // Not implemented yet in the library
      //irsend.sendLG(code.code_value, code.code_bits);
      break;
    case 13:    
      irsend.sendWhynter(code.code_value, code.code_bits);
      break;
  } 
}
