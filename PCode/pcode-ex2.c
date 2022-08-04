/*************************************

Complation en PCode de:
 int main () {
   int x, y, z;
   x = 3;
   y = 7;
   z = x * y;
   return z;
 }

 *************************************/

#include "PCode.h"


int main(){

  print_stack();
  
  // int x, y, z;  
  LOADI(0);        // x déclaré et initialisé 0 à l'adresse mp + 0
  LOADI(0);        // y déclaré et initialisé 0 à l'adresse mp + 1
  LOADI(0);        // z déclaré et initialisé 0 à l'adresse mp + 2
  print_stack();
      // on calcul les offsets de x, y et z par rapport à mp
      // a la compilation, et on les stocke dans la table des symboles.
  
  // x = 3
  LOADI(3);
  STORE(mp + 0);
  print_stack();

  // y = 7
  LOADI(7);
  STORE(mp + 1);
  print_stack();

  // z = x * y
  LOAD(mp + 0);
  LOAD(mp + 1);  
  MULTI;
  STORE(mp + 2);

  print_stack();
  
  // return z
  LOAD(mp + 2);  
  STORE(mp);  // stocke le résultat à l'adresse "de retour" mp
  EXIT_MAIN;  // exit de la fonction main
  print_stack();

}
