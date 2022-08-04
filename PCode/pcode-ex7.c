/*************************************

Complation en PCode de:
 int fact (int n) {
   if (n<=1) return 1;
   else return (n*fact(n-1));


 int main () {
   return (fact 3);
 }

 *************************************/

#include "PCode.h"
#include <stdio.h>

void fact_pcode (){

  // (n<=1)
  LOAD (mp -1 - 1);   // chargement de n (premier arguement de la fonction)
  LOADI (1);
  LEQ;
  print_stack();

  // Test
  IFN (Else);
  print_stack();

  // cas du if
  LOADI (1);          // chargement valeur de retour
  print_stack();
  
  return;   // on laisse le compilateur C gerer le pc (programme counter)
               // pour continuer l'execution après l'appel de fact_pcode()
       
  // cas du else
 Else:
  // chargement de n
  LOAD (mp -1 -1);
  
  // chargement des arguements de l'appel, i.e. n-1
  LOAD (mp -1 -1); // chargement de n
  LOADI (1);
  SUBI;

  // début de l'appel
  ENTER_BLOCK(1); // le nombre d'argument n'est pas utilisé ici, mais ça colle
                  // avec EXIT_BLOC(1)

  print_stack();

  // appel de fact(n-1)
  fact_pcode();

  // fin de l'appel
  EXIT_BLOCK (1); // on precise le nombre de paramètre pour bien positionner
                  // le résultat
  // calcul de n * fact(n-1)
  MULTI;

  print_stack();
  return;
}
  
int main(){
  
  // chargement de 3
  LOADI (5);
  print_stack();

  // début de l'appel
  ENTER_BLOCK(1);

  print_stack();
  // appel de fact(3)
  fact_pcode();

  print_stack();
  // fin de l'appel
  EXIT_BLOCK (1); // on precise le nombre de paramètre pour bien positionner
                  // le résultat
  
  print_stack();
}
