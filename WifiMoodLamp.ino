/*
 * Este sketch representa o minimo para controlar um Host de dispositivos
 * Recebe um json no seguinte formato {"uri":"/route", "params":{"param1":value, "params2":value}}
 * 
 */



#include <ArduinoJson.h>
#include "helperfunctions.h"
#include "System.h"
#include "MoodLampDriver.h"


//Rota principal do Host
#define MAIN_ROUTE "/host"

//Variavel que contem a mensagem de resposta
char  msg[MAX_JSON];      


//Funcoes Auxiliares
bool processMessage();  // processa a mensagem que chegou
void checkSystem();     // enquanto nao ha mensagem esta funcao eh executada em cada loop
bool main_route();      // retorna dados referente a rota principal
void get_devices(char * response); // retorna os dados dos dispositivos conectados ao host. geralmente chamada pela funcao main_route()
void get_errorMessage();  // retorna uma mensagem de erro caso a requisicao nao seja atendida pelo host



/*
 * System eh uma classe de suporte que recebe e envia os dados
 * tambem faz o tratamento do json e retorna a uri e os parametros
 */
System sys;
MoodLampDriver driver;


void setup(){

  sys.begin();
  driver.begin();  
}


void loop(){

  
  if (sys.get_data()){                // verifica a existencia de novas requisicoes
     msg[0] = '\0';                   // caso haja novos dados, limpa a variavel de mensagem
    //DEBUG
    Serial.print("URL: ");  
    Serial.println(sys.get_json());

    
    processMessage();                 // realiza o processamento
    sys.send_response(msg);           // envia o resultado
    mem();
  } 
  else {
    checkSystem();                   // se nao existirem dados a serem processados o sistema sera verificado
  }
   
  
  }



// Aqui sera codificado todo o processamento dos dispositivos
void checkSystem(){
  
    driver.update();
  
  }



/*
   Esta funcao faz o processamento dos dados.
   Verifica se a URI que chegou corresponde
   a alguma URI do sistema.
   Caso combine, faz uma chamada a funcao correspondente
   a URI
*/
bool processMessage() {


  if (main_route()){
    get_devices(msg);
    return true;
  }


  if( driver.process_message(sys,msg)){
    return true;
  }
  


  
 get_errorMessage();

 return true;
  

}


bool main_route(){
   
  if (strcmp(sys.get_uri(), MAIN_ROUTE) == 0) {
    return true;

  }
  return false;
}



void get_devices(char * response) {
  
 StaticJsonBuffer<200> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
 JsonArray& devices = root.createNestedArray("devices");
 JsonObject& device_rgb = devices.createNestedObject();
 device_rgb["route"] = "/moodlamp";
 device_rgb["name"] = "moodlamp";                           


 root.printTo(response,MAX_JSON);
  
}

void get_errorMessage(){

 StaticJsonBuffer<200> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
 root["msg"] = "Invalid Request.";
 root.printTo(msg,MAX_JSON);
  
  }







  
