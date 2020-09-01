/*
 *  Attribute.h
 *
 *  Created by Janin on 10/2019
 *  Copyright 2018 LaBRI. All rights reserved.
 *
 *  Module for a clean handling of attibutes values
 *
 */
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

typedef enum {INT, FLOAT} type;

struct ATTRIBUTE {
  char * name;
  int int_val;
  float float_val;
  type type_val;
  int reg_number;
  int nb_stars;

  /* other attribute's fields can goes here */

};

typedef struct ATTRIBUTE * attribute;

void print_attribute(attribute a);
char * type_to_string(int val);
int new_registre();
int new_label();

attribute new_attribute ();
/* returns the pointeur to a newly allocated (but uninitialized) attribute value structure */


attribute plus_attribute(attribute reg1, attribute reg2, FILE * header, FILE * body);
attribute mult_attribute(attribute reg1, attribute reg2, FILE * header, FILE * body);
attribute minus_attribute(attribute reg1, attribute reg2, FILE * header, FILE * body);
attribute div_attribute(attribute reg1, attribute reg2, FILE * header, FILE * body);
attribute neg_attribute(attribute x);
attribute condition(attribute reg1, attribute reg2, FILE * header, FILE * body, char * signe);

#endif
