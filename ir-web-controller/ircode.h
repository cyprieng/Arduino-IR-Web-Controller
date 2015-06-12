#ifndef IRCODE
#define IRCODE

/*!
 * \file ircode.h
 * \brief Define and Send IR code
 * \author cyprieng
 * \version 0.1
 */
#include <Arduino.h>
#include <IRremote.h>
 
/**
 * \struct IR_Code
 * @brief Structure for a ircode
 *
 * code_type:
 *   NEC = 1,
 *   SONY = 2,
 *   RC5 = 3,
 *   RC6 = 4,
 *   DISH = 5,
 *   SHARP = 6,
 *   PANASONIC = 7,
 *   JVC = 8,
 *   SANYO = 9,
 *   MITSUBISHI = 10,
 *   SAMSUNG = 11,
 *   LG = 12,
 *   WHYNTER = 13
 */
typedef struct {
   char* remote_name; /*!< name of the remote */
   char* function_name; /*!< name of the action */
   int code_type; /*!< type of the IR code */
   int code_bits; /*!< length of the code */
   unsigned long code_value; /*!< value of the code */
} IR_Code;

extern int num_codes; /*!< Number of IR codes */
extern IR_Code ir_codes[]; /*!< Array of IR codes */

/*!
 *  \fn void sendIRCode(IR_Code code)
 *  \brief Send IR Code
 *
 *  Send an IR Code thought the LED in pin 3
 *
 *  \param code : code to send
 */
void sendIRCode(IR_Code code);

#endif
