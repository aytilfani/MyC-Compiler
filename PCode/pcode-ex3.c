/*************************************

Complation en PCode de:
 int main () {
   int x, y;
   x = 22;
   if (x > 33) y = 44;
   else y = 66;
   return y;
 }

 *************************************/

#include "PCode.h"


int main(){
  
  // int x, y, z;  
  LOADI(0);        // x déclaré et initialisé 0 à l'adresse mp + 0
  LOADI(0);        // y déclaré et initialisé 0 à l'adresse mp + 1
  print_stack();

  // x = 22;
  LOADI(22);
  STORE(mp + 0);
  print_stack();
  
  // (x > 33)
  LOAD (mp+0);
  LOADI(33);
  GT;
  print_stack();

  IFN(Else);
  // THEN
  LOADI(44);
  STORE(mp + 1);
  GOTO (Fin);
  print_stack();

 Else:
  LOADI(66);
  STORE(mp + 1);
  print_stack();
  
 Fin:
  NOP;
  LOAD(mp + 1);
  STORE(mp);
  EXIT_MAIN;
    
  print_stack();

}
