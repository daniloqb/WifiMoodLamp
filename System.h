#ifndef SYSTEM_H
#define SYSTEM_H

#endif

#include "Arduino.h"

#include <ArduinoJson.h>
#include <SoftwareSerial.h>

//#define TESTING

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    
    #ifndef TESTING
      #define USESOFT
    #endif

#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    #ifndef TESTING
      #define USESERIAL
    #endif
#endif


/*************************
   VARIAVEIS DO SISTEMA
 *************************/

#define  BAUNDRATE 9600

const byte MAX_JSON = 200;  // Tamanho maximo da URL de entrada

const byte RX_PIN = 7;
const byte TX_PIN = 8;



class System {

  private:
    char _jsonString[MAX_JSON];

    SoftwareSerial * _my_serial;
    void _init_vars();
    boolean get_data_debug();
    boolean get_data_soft();
    boolean get_data_mega();
    void send_response_debug(char *msg);
    void send_response_soft(char *msg);
    void send_response_mega(char *msg);

  public:
    System();    
    void begin();
    boolean get_data();
    const char * get_param(const char * key);
    const char * get_json();
    const char * get_uri();
    void send_response(char *msg);


};


System::System() {

}


void System::begin() {

  Serial.begin(BAUNDRATE);

  #if defined(USESOFT)
    _my_serial = new SoftwareSerial(RX_PIN, TX_PIN);
    _my_serial->begin(BAUNDRATE);
  #endif

  #if defined(USEMEGA)
    Serial1.begin(BAUNDRATE);
  #endif
  
  _init_vars();


}

void System::_init_vars() {


  for (int i = 0; i < MAX_JSON; i++) {
     _jsonString[i] = '\0';
  }


}


boolean System::get_data() {

#if defined(TESTING)
  return get_data_debug();

#elif defined(USESOFT)
  return get_data_soft();

#elif defined(USEMEGA)
  return get_data_mega();

#endif


}


void System::send_response(char * msg) {


#if defined(TESTING)
  send_response_debug(msg);

#elif defined(USESOFT)
  send_response_soft(msg);

#elif defined(USEMEGA)
  send_response_mega(msg);
#endif

}



boolean System::get_data_debug() {

  //char buff[MAX_URL];
  int index = 0;
  char c;


  if (Serial.available() > 0) {

    for (int i = 0; i < MAX_JSON; i++) {
       _jsonString[i] = '\0';
    }

    while (Serial.available()) {
      c = Serial.read();

 
      delay(10);
      if ((c != '\r' && c != '\n') && index < MAX_JSON) {
         _jsonString[index++] = c;
      }


    }

    return true;

  }
  // se nao houver dados retorna null.
  return false;



}



void System::send_response_debug(char * msg) {


  //Verifica qual o tamando da mensagem.
  int size_msg = strlen(msg);

  // limpa o buffer da serial??? Sera que limpa mesmo?
  Serial.flush();


  for (int i = 0; i < size_msg; i++) {
    Serial.print(msg[i]);
    delay(1);
  }
  //Envia um caractere de nova linha, indicando o fim do envio.
  Serial.println();



  //free(msg);

}



boolean System::get_data_soft() {

    //char buff[MAX_URL];
  int index = 0;
  char c;


  if (_my_serial->available() > 0) {

    for (int i = 0; i < MAX_JSON; i++) {
       _jsonString[i] = '\0';
    }

    while (_my_serial->available()) {
      c = _my_serial->read();

 
      delay(1);
      if ((c != '\r' && c != '\n') && index < MAX_JSON) {
         _jsonString[index++] = c;
      }


    }

    return true;

  }
  // se nao houver dados retorna null.
  return false;


}



void System::send_response_soft(char * msg) {

  //Verifica qual o tamando da mensagem.
  int size_msg = strlen(msg);

  // limpa o buffer da serial??? Sera que limpa mesmo?
  _my_serial->flush();


  for (int i = 0; i < size_msg; i++) {
    _my_serial->print(msg[i]);
  //  delay(1);
  }
  //Envia um caractere de nova linha, indicando o fim do envio.
  _my_serial->println();

  Serial.println(msg);

}



boolean System::get_data_mega() {

  //char buff[MAX_URL];
  int index = 0;
  char c;

 #if defined(USEMEGA)
 
  if (Serial1.available() > 0) {

    for (int i = 0; i < MAX_JSON; i++) {
       _jsonString[i] = '\0';
    }

    while (Serial1.available()) {
      c = Serial1.read();

 
      delay(10);
      if ((c != '\r' && c != '\n') && index < MAX_JSON) {
         _jsonString[index++] = c;
      }


    }

    return true;

  }
  // se nao houver dados retorna null.
  return false;

#endif  

}



void System::send_response_mega(char * msg) {


  #if defined(USEMEGA)
   //Verifica qual o tamando da mensagem.
  int size_msg = strlen(msg);

  // limpa o buffer da serial??? Sera que limpa mesmo?
  Serial1.flush();


  for (int i = 0; i < size_msg; i++) {
    Serial1.print(msg[i]);
    delay(1);
  }
  //Envia um caractere de nova linha, indicando o fim do envio.
  Serial1.println();

#endif

}




const char * System::get_json(){

  return _jsonString;
  
}

const char * System::get_uri(){

   String str_to_parse(_jsonString);
   
   StaticJsonBuffer<MAX_JSON> jsonBuffer;
   JsonObject& root = jsonBuffer.parseObject(str_to_parse);
   if (!root.success()) {
     return NULL;
   }

   return root["uri"].as<char*>();
  }


const char * System::get_param(const char* key){

  String str_to_parse(_jsonString);
  
  StaticJsonBuffer<MAX_JSON> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(str_to_parse);
  JsonObject& params = root["params"];

  return params[key].as<char*>();
  
  }




