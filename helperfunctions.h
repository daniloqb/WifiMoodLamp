#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include "Arduino.h"


/*
   FUNCOES DE SISTEMA
   Estas funcoes sao necessarias para debug. Depois do codigo consolidado
   elas serao descartadas.
   Sao utilizadas para saber a quantidade de memoria disponivel.
   Estamos com problemas de falta de memoria devido a geracao de json de
   resposta.
*/

int get_free_memory();
void mem(void);
boolean IsNumeric(String str);


/*
   FUNCAO retirada do site: http://tripsintech.com/arduino-isnumeric-function/
   MODIFICADA: Acrescentei um teste para verificar se a string passada nao esta vazia
   se estiver retorna false.
*/

boolean IsNumeric(String str) {

  if (str.length()) {

    for (char i = 0; i < str.length(); i++) {
      if ( !(isDigit(str.charAt(i)) || str.charAt(i) == '.' )) {
        return false;
      }
    }
    return true;
  }
  else {
    return false;
  }
}


/*
   MEMORY FUNCTIONS

   Funcoes auxiliares que mostram a quantidade de memoria livre do sistema.
*/


extern unsigned int __bss_end;
extern void *__brkval;

int get_free_memory()
{
  int free_memory;

  if ((int)__brkval == 0)
    free_memory = ((int)&free_memory) - ((int)&__bss_end);
  else
    free_memory = ((int)&free_memory) - ((int)__brkval);

  return free_memory;
}

void mem(void)
{
  Serial.print("free_memory():");
  Serial.println( get_free_memory() );
  delay(10);
}






#endif

