/*************************************

 Compilation en PCode de:
 int main () {
   return (1+2)*(3+4);
 }

 *************************************/

#include "PCode.h"


int main(){
  print_stack();
  // 1+2
  LOADI(1);
  LOADI(2);
  print_stack();
  ADDI;
  //3+4
  LOADI(3);
  LOADI(4);
  print_stack();
  ADDI;
  // multiplication des deux ci-dessus
  print_stack();
  MULTI;
  print_stack();
  EXIT_MAIN;
  print_stack();
}
