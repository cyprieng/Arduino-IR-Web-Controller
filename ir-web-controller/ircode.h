#ifndef IRCODE
#define IRCODE

#include <Arduino.h>
#include <IRremote.h>

/**
 * Class recording an IR code
 * @author cyprieng
 */
class IRCode{
  public:
    /**
     * Constructor without any initialization
     */
    IRCode();

    /**
     * Constructor whith init
     */
    IRCode(String remote_name, String function_name, int code_type, int code_len, unsigned long code_value);

    /**
     *
     * @return unique remote number
     */
    int getRemoteNumber() const;

    /**
     *
     * @return name of the remote
     */
    String getRemoteName() const;

    /**
     *
     * @return name of the ir code function
     */
    String getFunctionName() const;

    /**
     *
     * @return type of the code
     * @see IRremote.h
     */
    int getCodeType() const;

    /**
     *
     * @return length of the code
     */
    int getCodeLen() const;

    /**
     *
     * @return raw codes of an ircode with unknow type
     */
    unsigned int* getRawCodes() const;

    /**
     *
     * @return value of a code with a known code type
     */
    unsigned long getCodeValue() const;

    /**
     *
     * @param remote name of the remote
     */
    void setRemoteName(String remote);

    /**
     *
     * @param function name of the ir code function
     */
    void setFunctionName(String function);

    /**
     *
     * @param type type of the code
     * @see IRremote.h
     */
    void setCodeType(int type);

    /**
     *
     * @param len length of the code
     */
    void setCodeLen(int len);

    /**
     *
     * @param raw raw value of the code (for unknow code type)
     */
    void setRawCodes(unsigned int raw[RAWBUF]);

    /**
     *
     * @param value value of the code
     */
    void setCodeValue(unsigned long value);

  private:
    /**
     * Count the number of remote
     */
    static int m_remote_counter;

    /**
     * Name of the last remote addded
     */
    static String m_last_remote;

    /**
     * Number of the remote
     */
    int m_remote_number;

    /**
     * Name of the remote
     */
    String m_remote_name;

    /**
     * Name of the ir code function
     */
    String m_function_name; /*!< name of the action */

    /**
     * Type of the code
     * @see IRremote.h
     */
    int m_code_type;

    /**
     * Length of the code
     */
    int m_code_len;

    /**
     * If code type is unknow, this will contain the raw code
     */
    unsigned int m_raw_codes[RAWBUF];

    /**
     * Value of the code if the type is now unknow
     */
    unsigned long m_code_value;
};

#endif
