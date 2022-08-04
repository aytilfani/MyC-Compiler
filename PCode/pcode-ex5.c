/*************************************

Complation en PCode de:
 int main () {
   int x, y;
   x = 1;
   { int x;
     x = 5;
     y = 6; 
    }
   return y;
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

  // entrée dans le bloc
  ENTER_BLOCK(0);
  // int x
  LOADI (0);        // x (local) déclaré et initialisé 0 à l'adresse mp + 0
  print_stack();

  // x = 5;
  LOADI (5);
  STORE (mp + 0);  // modification de la variable LOCALE x

  // y = 6;
  LOADI (6);
  STORE (stack[mp-1]+1);
             // modification de y dans le bloc englobant
             // on sort du code 3@ avec cet adressage indirecte indexé...
             // Comment gerer ça mieux ? Le nombre d'indirection est
             // connu à la compilation
  
  print_stack();
  // sortie du bloc
  EXIT_BLOCK(0);

  print_stack();

  // return y
  LOAD (mp+1);
  STORE (mp);  // valeur de retour à l'adresse mp

  EXIT_MAIN;

  print_stack();
  

}
