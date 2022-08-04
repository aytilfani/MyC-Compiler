/*
 *  Attribute.h
 *
 *  Created by Janin on 10/2019
 *  Copyright 2018 LaBRI. All rights reserved.
 *
 *  Module for a clean handling of attibutes values
 *
 */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

typedef enum {INT, FLOAT} type;

struct ATTRIBUTE {
  char * name;
  int int_val;           // utilise' pour NUM et uniquement pour NUM
  type type_val;
  int offset;
  //int num_label;
  int profondeur;
  int arg_numb;
  /* les autres attributs dont vous pourriez avoir besoin sont déclarés ici */
  
};

typedef struct ATTRIBUTE * attribute;

attribute new_attribute ();
/* returns the pointeur to a newly allocated (but uninitialized) attribute value structure */
int make_label();

#endif

