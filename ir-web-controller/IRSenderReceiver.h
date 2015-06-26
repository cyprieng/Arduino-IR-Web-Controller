#ifndef IRSENDERRECEIVER
#define IRSENDERRECEIVER

#include <Arduino.h>
#include <IRremote.h>
#include "IRCode.h"

/**
 * Class sending and receiving ir code
 * @author cyprieng
 * @see IRCode
 */
class IRSenderReceiver{
  public:
    /**
     * Constructor
     */
    IRSenderReceiver();

    /**
     * Send an ircode
     *
     * @param code the code to send
     * @param repeat 1 if it is a repetition of the code, 0 either
     * @see IRCode
     */
    void sendIRCode(const IRCode& code, int repeat);

    /**
     * Retrieve an IR code and store it in a given variable
     *
     * @param ircode variable where the code will be stored
     * @see IRCode
     */
    void getIRCode(IRCode *ircode);

    /**
     * Instance of IRrecv used to receive IR code
     * @see IRremote
     */
    static IRrecv m_irrecv;

  private:
    /**
     * Instance of IRsend used to send IR code
     * @see IRremote
     */
    IRsend m_irsend;

    /**
     * Store the toggle for each remote.
     * The index is the remote number
     */
    int toggle[100] = {0};
};

#endif
