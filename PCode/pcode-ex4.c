/*************************************

Complation en PCode de:
 int main () {
   int x, y;
   x = 1;
   y =  { int x;
          x = 2;
        }
  return x;
 }

 *************************************/

#include "PCode.h"


int main(){
  
  // int x, y;
  LOADI (0);        // x déclaré et initialisé 0 à l'adresse mp + 0
  LOADI (0);        // y déclaré et initialisé 0 à l'adresse mp + 1
  print_stack();

  // x = 1;
  LOADI (1);
  STORE (mp + 0);
  print_stack();
 Loop: 
  // (x < 5)
  LOAD (mp+0);
  LOADI (5);
  LT;
  print_stack();
  IFN (End);

  // WHILE BODY
  LOAD (mp+0);
  LOADI (1);
  ADDI;
  STORE (mp + 0);
  GOTO (Loop);

 End:
  LOAD (mp+0);
  STORE (mp);  
  EXIT_MAIN;
    
  print_stack();

}
