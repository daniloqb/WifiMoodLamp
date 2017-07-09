
#ifndef DEVICE_H
#define DEVICE_H

#include "Arduino.h"
#include <MoodLamp.h>


#include <aJSON.h>

/*CONSTANTES DE ROTA*/
  const char ROUTE_ROOT[]           PROGMEM =  "/";
  const char ROUTE_DEVICE[]         PROGMEM =  "/rgb";
  const char ROUTE_COMMANDS[]       PROGMEM =  "/rgb/commands";
  const char ROUTE_COLOR_RED[]      PROGMEM =  "/rgb/red";
  const char ROUTE_COLOR_ORANGE[]   PROGMEM =  "/rgb/orange";
  const char ROUTE_COLOR_YELLOW[]   PROGMEM =  "/rgb/yellow";
  const char ROUTE_COLOR_LIME[]     PROGMEM =  "/rgb/lime";
  const char ROUTE_COLOR_GREEN[]    PROGMEM =  "/rgb/green";
  const char ROUTE_COLOR_AQUA[]     PROGMEM =  "/rgb/aqua";
  const char ROUTE_COLOR_CYAN[]     PROGMEM =  "/rgb/cyan";
  const char ROUTE_COLOR_OCEAN[]    PROGMEM =  "/rgb/ocean";
  const char ROUTE_COLOR_BLUE[]     PROGMEM =  "/rgb/blue";
  const char ROUTE_COLOR_PURPLE[]   PROGMEM =  "/rgb/purple";
  const char ROUTE_COLOR_VIOLET[]   PROGMEM =  "/rgb/violet";
  const char ROUTE_COLOR_MAGENTA[]  PROGMEM =  "/rgb/magenta";
  const char ROUTE_COLOR_PINK[]     PROGMEM =  "/rgb/pink";
  const char ROUTE_COLOR_WHITE[]    PROGMEM =  "/rgb/white";

  const char ROUTE_DEVICE_ON[]      PROGMEM =  "/rgb/on";
  const char ROUTE_DEVICE_OFF[]     PROGMEM =  "/rgb/off";

  const char ROUTE_COLOR_WHEEL[]    PROGMEM =  "/rgb/wheel";
  const char ROUTE_COLOR_FADE[]     PROGMEM =  "/rgb/fade";


  const char  DEVICE_NAME[] PROGMEM = "rgb";

  const char  COMMANDS[] PROGMEM = "{\"commands\": [{\"route\": \"/rgb\",\"label\": \"rgb\",\"params\": [{\"name\": \"color\",\"type\": \"int\",\"min\": 0,\"max\": 360 },{\"name\": \"brightness\",\"type\": \"int\",\"min\": 0,\"max\": 100 }]}]}\n";


  const char * DEVICE_PARAM_COLOR = "color";
  const char * DEVICE_PARAM_BRIGHTNESS = "brightness";
  const char * DEVICE_PARAM_SPEED = "speed";
  const char * DEVICE_PARAM_ACTIVE = "active";


class MoodLampDriver{

  
  private:
    MoodLamp * device;

  public:
    MoodLampDriver(MoodLamp *moodlamp);
    void begin();


    char * device_commands(char *msg);
    char * get_main_route();
    char * get_name();

    bool process_message(System sys, char * response);

  
};


MoodLampDriver::MoodLampDriver(MoodLamp * moodlamp){

  device = moodlamp;

}


char * MoodLampDriver::get_name(){

  static char response[5];

  strcpy_P(response,DEVICE_NAME);
  
  return response;
}




char * MoodLampDriver::get_main_route(){

  static char response[4];

  strcpy_P(response,ROUTE_DEVICE);
  
  return response;
}





char * MoodLampDriver::device_commands(char *msg){


 
  strcpy_P(msg,COMMANDS);


  

}




bool MoodLampDriver::process_message(System sys, char * msg){

 char * response = NULL;

 const char * uri = sys.get_uri();

  boolean change_color  = false;     // variavel que controla se a cor vai ser modificada.
  boolean valid_route = false;       // trabalha como change color, mas serve para se a rota somente necessita de informacao.
  int val_aux = 0;                   // variavel auxiliar que recebe o valor dos parametros.

  const char * param_color;                // recebe o valor da cor em formato string;
  const char * param_brightness;           // recebe o valor do brilho em formato string.
  const char * param_speed;           // recebe o valor do brilho em formato string.
  const char * param_active;

  if (strcmp_P(uri, ROUTE_DEVICE) == 0) {        // verifica se a rota eh a rota raiz do dispositivo

    valid_route = true;                               // valida a rota, mesmo que nao ocorra mudanca de cor. necessario para rotas que nao mudam a cor

    param_brightness =  sys.get_param(DEVICE_PARAM_BRIGHTNESS);      // recupera a string com o valor do brilho
    param_color =       sys.get_param(DEVICE_PARAM_COLOR);           // recupera a string com o valor da cor

 
    if (IsNumeric(param_color)) {                     // verifica se o valor eh numerico
      device->color(atoi(param_color));
      change_color = true;                          // caso esteja informa que a cor sera modificada
    
    }
    if (IsNumeric(param_brightness)) {                // faz o mesmo teste que foi feito com a cor
      device->brightness(atoi(param_brightness));
      change_color = true;      
    }
  }  
  else if (strcmp_P(uri, ROUTE_DEVICE_OFF) == 0) {

    device->brightness(0);
    change_color = true;
    device->wheel(0);
    device->fade(0);

  }

  // ROTA QUE LIGA A LAMPADA COM OS VALORES ANTERIORES AO DESLIGA
  else if (strcmp_P(uri, ROUTE_DEVICE_ON) == 0) {

    device->brightness(device->last_brightness());
    change_color = true;
  }
   // ABAIXO ESTAO AS ROTAS DAS CORES PRE-DEFINIDAS NO SISTEMA
  else if (strcmp_P(uri, ROUTE_COLOR_RED) == 0) {                 // RED

    device->color(COLOR_RED);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_GREEN) == 0) {               // GREEN

    device->color(COLOR_GREEN);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_BLUE) == 0) {                // BLUE

    device->color(COLOR_BLUE);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_YELLOW) == 0) {            // YELLOW

    device->color(COLOR_YELLOW);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_CYAN) == 0) {              // CYAN

    device->color(COLOR_CYAN);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_MAGENTA) == 0) {           // MAGENTA

    device->color(COLOR_MAGENTA);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_ORANGE) == 0) {             // ORANGE

    device->color(COLOR_ORANGE);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_VIOLET) == 0) {             // VIOLET

    device->color(COLOR_VIOLET);
    change_color = true;
  }

  else if (strcmp_P(uri, ROUTE_COLOR_PINK) == 0) {               // PINK

    device->color(COLOR_PINK);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_LIME) == 0) {             // LIME

    device->color(COLOR_LIME);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_AQUA) == 0) {              // AQUA

    device->color(COLOR_AQUA);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_OCEAN) == 0) {            // OCEAN

    device->color(COLOR_OCEAN);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_PURPLE) == 0) {           // PURPLE

    device->color(COLOR_PURPLE);
    change_color = true;
  }
  else if (strcmp_P(uri, ROUTE_COLOR_WHITE) == 0) {              // WHITE

    device->color(COLOR_WHITE);
    change_color = true;

  }
  
  else if (strcmp_P(uri, ROUTE_COLOR_WHEEL) == 0) {              // FUNCAO PARA TROCAR DE COR EM UM DETERMINADO TEMPO

    param_active =       sys.get_param(DEVICE_PARAM_ACTIVE);           // verifica o parametro para ativar ou desativar a funcao
    if (IsNumeric(param_active)) {                     // verifica se o valor eh numerico
      device->wheel(atoi(param_active));
      }
    
    param_speed =       sys.get_param(DEVICE_PARAM_SPEED);           // recupera o valor da velocidade da troca de cores
    if (IsNumeric(param_speed)) {                     // verifica se o valor eh numerico
      device->wheel_speed(atoi(param_speed));
    }
   valid_route = true;
  }

  else if (strcmp_P(uri, ROUTE_COLOR_FADE) == 0) {       //FUNCAO PARA DIMINUIR E AUMENTAR O BRILHO AUTOMATICAMENTE

    param_active =       sys.get_param(DEVICE_PARAM_ACTIVE);           // verifica o parametro para ativar ou desativar a funcao
    if (IsNumeric(param_active)) {                     // verifica se o valor eh numerico
      device->fade(atoi(param_active));
    }

    param_speed =       sys.get_param(DEVICE_PARAM_SPEED);           //  verifica o valor da velocidade da funcao
    if (IsNumeric(param_speed)) {                     // verifica se o valor eh numerico
      device->fade_speed(atoi(param_speed));
    }

    if (device->fade() == 1) {                             //se a funcao for ativada , guarda o ultimo valor de brightness
      device->last_brightness(device->brightness());
    } else {
      device->brightness(device->last_brightness());             // e se for desativada, pega o ultimo valor de brightness
      change_color = true;
    }

    valid_route = true;

  }else if (strcmp_P(uri, ROUTE_COMMANDS) == 0) {  

    device_commands(msg);
    return true;
    
  }


  

  if (change_color) {
    device->update_color();
  }


  // O JSON eh montado se a rota for valida ou se a cor for requisitada.

  if (valid_route || change_color) {


    StaticJsonBuffer<MAX_JSON> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["name"] = get_name();
    root[DEVICE_PARAM_COLOR] = device->color();
    root[DEVICE_PARAM_BRIGHTNESS] = device->brightness();
    root.printTo(msg,MAX_JSON);

    return true;
  }

 return false;

}










#endif
