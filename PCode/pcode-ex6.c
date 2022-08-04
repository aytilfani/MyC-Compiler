/*************************************

Complation en PCode de:
 int sum (int m, int n) {
   return (m+n);
}

 int main () {
   return (sum(14,7));
 }

 *************************************/

#include "PCode.h"
#include <stdio.h>

void sum_pcode (){

  // (m+n)
  LOAD (mp -1 - 2);   // chargement de m (premier argument de la fonction)
  LOAD (mp -1 - 1);   // chargement de n (second argument de la fonction)
  ADDI;
  print_stack();

  return;   // on laisse le compilateur C gerer le pc (programme counter)
            // pour continuer l'execution après l'appel de sum_pcode()
}
  
int main(){

  // chargement des arguments de l'appel
  LOADI (14);
  LOADI (7);
  
  print_stack();

  // début de l'appel
  ENTER_BLOCK(2);

  print_stack();
  // appel de sum(14,7)
  sum_pcode();
  // fin de l'appel
  EXIT_BLOCK (2); // on precise le nombre de paramètre pour bien positionner
                  // le résultat
  
  print_stack();
}
