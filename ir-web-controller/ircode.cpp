#include "IRCode.h"

using namespace std;

// Init remote counter and last remote name
int IRCode::m_remote_counter = 0;
String IRCode::m_last_remote = "";

IRCode::IRCode(){
  // Set default remote and function name
  m_remote_name = "Default";
  m_function_name = "";

  if(m_remote_name != m_last_remote){ // New remote
    // Increase counter
    m_remote_counter++;
    m_remote_number = m_remote_counter;
  }
  else{
    m_remote_number = m_remote_counter;
  }

  m_last_remote = m_remote_name; // Store remote name
}

IRCode::IRCode(String remote_name, String function_name,
                int code_type, int code_len, unsigned long code_value) :
                m_remote_name(remote_name), m_function_name(function_name),
                m_code_type(code_type), m_code_len(code_len), m_code_value(code_value) {
  if(remote_name != m_last_remote){ // New remote
    // Increase counter
    m_remote_counter++;
    m_remote_number = m_remote_counter;
  }
  else{
    m_remote_number = m_remote_counter;
  }

  m_last_remote = remote_name; // Store remote name
}

int IRCode::getRemoteNumber() const{
  return m_remote_number;
}

String IRCode::getRemoteName() const{
  return m_remote_name;
}

String IRCode::getFunctionName() const{
  return m_function_name;
}

int IRCode::getCodeType() const{
  return m_code_type;
}

int IRCode::getCodeLen() const{
  return m_code_len;
}

unsigned int* IRCode::getRawCodes() const{
  return const_cast<unsigned int*>(m_raw_codes);
}

unsigned long IRCode::getCodeValue() const{
  return m_code_value;
}

void IRCode::setRemoteName(String remote){
  m_remote_name = remote;
}

void IRCode::setFunctionName(String function){
  m_function_name = function;
}

void IRCode::setCodeType(int type){
  m_code_type = type;
}

void IRCode::setCodeLen(int len){
  m_code_len = len;
}

void IRCode::setRawCodes(unsigned int raw[RAWBUF]){
  memcpy(m_raw_codes, raw, RAWBUF);
}

void IRCode::setCodeValue(unsigned long value){
  m_code_value = value;
}
