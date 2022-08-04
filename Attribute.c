#include "Attribute.h"

#include <stdlib.h>

int label = 0;

attribute new_attribute () {
  attribute r;
  r  = malloc (sizeof (struct ATTRIBUTE));
  return r;
};

int make_label() {
  return label++;
}
