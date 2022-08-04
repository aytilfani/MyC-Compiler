/*
 *  Table des symboles.c
 *
 *  Created by Janin on 12/10/10.
 *  Copyright 2010 LaBRI. All rights reserved.
 *
 */

#include "Table_des_symboles.h"
#include "Attribute.h"

#include <stdlib.h>
#include <stdio.h>
#define SIZE 100

/* The storage structure is implemented as a linked chain */

/* linked element def */

typedef struct elem {
	sid symbol_name;
	attribute symbol_value;
	struct elem * next;
} elem;

/* linked chain initial element */
static elem * storage[SIZE] = {NULL};

/* get the symbol value of symb_id from the symbol table */
attribute get_symbol_value(sid symb_id, int profondeur) {
	elem * tracker=storage[profondeur];

	/* look into the linked list for the symbol value */
	while (tracker) {
	  if (tracker -> symbol_name == symb_id) return tracker -> symbol_value;
	  tracker = tracker -> next;
	}
	//return NULL;
	
	/* if not found does cause an error */
	//fprintf(stderr,"Error : symbol %s is not a valid defined symbol\n",(char *) symb_id);
	//exit(-1);
	return NULL;
}

/* set the value of symbol symb_id to value */
attribute set_symbol_value(sid symb_id,attribute value, int profondeur) {

	elem * tracker;
	
	/* look for the presence of symb_id in storage */
	
	tracker = storage[profondeur];
	while (tracker) {
		if (tracker -> symbol_name == symb_id) {
			tracker -> symbol_value = value;
			return tracker -> symbol_value;
		}
		tracker = tracker -> next;
	}
	
	/* otherwise insert it at head of storage with proper value */
	
	tracker = malloc(sizeof(elem));
	tracker -> symbol_name = symb_id;
	tracker -> symbol_value = value;
	tracker -> next = storage[profondeur];
	storage[profondeur] = tracker;
	return storage[profondeur] -> symbol_value;
}

attribute get_symbol_proche(attribute id, int depth) {
  while(depth >= 0) {
    attribute att = get_symbol_value(id->name, depth);
    if (att != NULL)
      return att;
    depth--;
  }
  fprintf(stderr,"Error : symbol %s is not a valid defined symbol\n",id->name);
  exit(-1);
  return NULL;
}

/*
int get_symbol_offset(sid symb_id) {
	elem * tracker=storage;

	
	while (tracker) {
		if (tracker -> symbol_name == symb_id) return tracker -> symbol_value.offset; 
		tracker = tracker -> next;
	}

	return -1;
}
*/
