#include "Attribute.h"

#include <stdlib.h>
#include <stdio.h>

int num_registre = 0;
int num_label = 0;

void print_attribute(attribute a)
{
  printf(" name:%s int:%d float:%f type:%d reg:%d star:%d\n",a->name,a->int_val,a->float_val,a->type_val,a->reg_number,a->nb_stars);
}

char * type_to_string(int val)
{
  char * str = NULL;
  switch (val) {
    case 0:
      str = "int";
      break;
    case 1:
      str = "float";
      break;
    case 271:
      str = "void";
  }
  return str;
}


int new_registre()
{
  num_registre ++;
  return num_registre ;
}

int new_label()
{
  num_label ++;
  return num_label;
}


attribute new_attribute () {
  attribute r;
  r  = malloc (sizeof (struct ATTRIBUTE));
  return r;
};


attribute plus_attribute(attribute reg1, attribute reg2, FILE * header, FILE * body) {
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  if (reg1->type_val == INT && reg2->type_val == INT)
  {

    r->type_val = INT;
    r->int_val = reg1->int_val + reg2->int_val;
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d + r%d;\n",r->reg_number,reg1->reg_number,reg2->reg_number);
  }
  else if (reg1->type_val == FLOAT && reg2->type_val == INT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->float_val + reg2->int_val;
    int reg_temp_cast = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),reg_temp_cast);
    fprintf(body,"r%d = (%s) r%d;\n",reg_temp_cast,type_to_string(r->type_val),reg2->reg_number);
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d + r%d;\n",r->reg_number,reg1->reg_number,reg_temp_cast);
    printf("WARNING: casting d'un float en int !\n");
  }
  else if (reg1->type_val == INT && reg2->type_val == FLOAT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->int_val + reg2->float_val;
    int reg_temp_cast = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),reg_temp_cast);
    fprintf(body,"r%d = (%s) r%d;\n",reg_temp_cast,type_to_string(r->type_val),reg1->reg_number);
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d + r%d;\n",r->reg_number,reg_temp_cast,reg2->reg_number);
    printf("WARNING: casting d'un float en int !\n");
  }
  else if (reg1->type_val == FLOAT && reg2->type_val == FLOAT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->float_val + reg2->float_val;
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d + r%d;\n",r->reg_number,reg1->reg_number,reg2->reg_number);
  }

  return r;
};

attribute mult_attribute(attribute reg1, attribute reg2, FILE * header, FILE * body) {
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  if (reg1->type_val == INT && reg2->type_val == INT)
  {
    r->type_val = INT;
    r->int_val = reg1->int_val * reg2->int_val;
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d * r%d;\n",r->reg_number,reg1->reg_number,reg2->reg_number);
  }
  else if (reg1->type_val == FLOAT && reg2->type_val == INT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->float_val * reg2->int_val;
    int reg_temp_cast = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),reg_temp_cast);
    fprintf(body,"r%d = (%s) r%d;\n",reg_temp_cast,type_to_string(r->type_val),reg2->reg_number);
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d * r%d;\n",r->reg_number,reg1->reg_number,reg_temp_cast);
    printf("WARNING: casting d'un float en int !\n");
  }
  else if (reg1->type_val == INT && reg2->type_val == FLOAT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->int_val * reg2->float_val;
    int reg_temp_cast = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),reg_temp_cast);
    fprintf(body,"r%d = (%s) r%d;\n",reg_temp_cast,type_to_string(r->type_val),reg1->reg_number);
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d * r%d;\n",r->reg_number,reg_temp_cast,reg2->reg_number);
    printf("WARNING: casting d'un float en int !\n");
  }

  else if (reg1->type_val == FLOAT && reg2->type_val == FLOAT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->float_val * reg2->float_val;
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d * r%d;\n",r->reg_number,reg1->reg_number,reg2->reg_number);
  }
  return r;
};

attribute minus_attribute(attribute reg1, attribute reg2, FILE * header, FILE * body) {
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  if (reg1->type_val == INT && reg2->type_val == INT)
  {
    r->type_val = INT;
    r->int_val = reg1->int_val - reg2->int_val;
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d - r%d;\n",r->reg_number,reg1->reg_number,reg2->reg_number);
  }
  else if (reg1->type_val == FLOAT && reg2->type_val == INT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->float_val - reg2->int_val;
    int reg_temp_cast = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),reg_temp_cast);
    fprintf(body,"r%d = (%s) r%d;\n",reg_temp_cast,type_to_string(r->type_val),reg2->reg_number);
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d - r%d;\n",r->reg_number,reg1->reg_number,reg_temp_cast);
    printf("WARNING: casting d'un float en int !\n");
  }
  else if (reg1->type_val == INT && reg2->type_val == FLOAT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->int_val - reg2->float_val;
    int reg_temp_cast = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),reg_temp_cast);
    fprintf(body,"r%d = (%s) r%d;\n",reg_temp_cast,type_to_string(r->type_val),reg1->reg_number);
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d - r%d;\n",r->reg_number,reg_temp_cast,reg2->reg_number);
    printf("WARNING: casting d'un float en int !\n");
  }
  else if (reg1->type_val == FLOAT && reg2->type_val == FLOAT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->float_val - reg2->float_val;
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d - r%d;\n",r->reg_number,reg1->reg_number,reg2->reg_number);
  }
  return r;
};

attribute div_attribute(attribute reg1, attribute reg2, FILE * header, FILE * body) {
  attribute r = new_attribute();
  /* unconditionally adding integer values */
  if (reg1->type_val == INT && reg2->type_val == INT)
  {
    r->type_val = INT;
    r->int_val = reg1->int_val / reg2->int_val;
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d / r%d;\n",r->reg_number,reg1->reg_number,reg2->reg_number);
  }
  else if (reg1->type_val == FLOAT && reg2->type_val == INT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->float_val / reg2->int_val;
    int reg_temp_cast = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),reg_temp_cast);
    fprintf(body,"r%d = (%s) r%d;\n",reg_temp_cast,type_to_string(r->type_val),reg2->reg_number);
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d / r%d;\n",r->reg_number,reg1->reg_number,reg_temp_cast);
    printf("WARNING: casting d'un float en int !\n");
  }
  else if (reg1->type_val == INT && reg2->type_val == FLOAT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->int_val / reg2->float_val;
    int reg_temp_cast = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),reg_temp_cast);
    fprintf(body,"r%d = (%s) r%d;\n",reg_temp_cast,type_to_string(r->type_val),reg1->reg_number);
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d / r%d;\n",r->reg_number,reg_temp_cast,reg2->reg_number);
    printf("WARNING: casting d'un float en int !\n");
  }
  else if (reg1->type_val == FLOAT && reg2->type_val == FLOAT)
  {
    r->type_val = FLOAT;
    r->float_val = reg1->float_val / reg2->float_val;
    r->reg_number = new_registre();
    fprintf(header,"%s r%d;\n",type_to_string(r->type_val),r->reg_number);
    fprintf(body,"r%d = r%d / r%d;\n",r->reg_number,reg1->reg_number,reg2->reg_number);
  }
  return r;
};

attribute neg_attribute(attribute reg1){
  attribute r = new_attribute();
  r->type_val = reg1->type_val;
  /* unconditionally adding integer values */
  if (reg1->type_val == INT)
    r->int_val = -(reg1->int_val);
  else if (reg1->type_val == FLOAT);
    r->float_val = -(reg1->float_val);
  return r;
};

attribute condition(attribute reg1, attribute reg2, FILE * header, FILE * body, char * signe)
{
  attribute ret = new_attribute();
  int reg = new_registre();
  int label = new_label();
  ret->type_val = INT;
  if ((reg1->type_val == INT) && (reg2->type_val == INT))
  {
    if (strcmp(signe, "<") == 0)
    {
      ret->int_val = (reg1->int_val < reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d < r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, ">") == 0)
      {ret->int_val = (reg1->int_val > reg2->int_val);
        fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
        fprintf(body,"r%d = (r%d > r%d);\n",reg,reg1->reg_number,reg2->reg_number);}
    else if (strcmp(signe, "==") == 0)
    {
      ret->int_val = (reg1->int_val == reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d == r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, "!=") == 0)
    {
      ret->int_val = (reg1->int_val != reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d != r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

    else if (strcmp(signe, "&&") == 0)
    {
      ret->int_val = (reg1->int_val && reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d && r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

    else if (strcmp(signe, "||") == 0)
    {
      ret->int_val = (reg1->int_val || reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d || r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

    else if (strcmp(signe, "!") == 0)
    {
      ret->int_val = (!reg1->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (!r%d);\n",reg,reg1->reg_number);
    }

  }
  else if ((reg1->type_val == FLOAT) && (reg2->type_val == INT))
  {
    if (strcmp(signe, "<") == 0)
    {
      ret->int_val = (reg1->float_val < reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d < r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, ">") == 0)
      {ret->int_val = (reg1->float_val > reg2->int_val);
        fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
        fprintf(body,"r%d = (r%d > r%d);\n",reg,reg1->reg_number,reg2->reg_number);
      }
    else if (strcmp(signe, "==") == 0)
    {
      ret->int_val = (reg1->float_val == reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d == r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, "!=") == 0)
    {
      ret->int_val = (reg1->float_val != reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d != r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, "&&") == 0)
    {
      ret->int_val = (reg1->float_val && reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d && r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

    else if (strcmp(signe, "||") == 0)
    {
      ret->int_val = (reg1->float_val || reg2->int_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d || r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

    else if (strcmp(signe, "!") == 0)
    {
      ret->int_val = (!reg1->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (!r%d);\n",reg,reg1->reg_number);
    }
  }
  else if( (reg1->type_val == INT) && (reg2->type_val == FLOAT))
  {
    if (strcmp(signe, "<") == 0)
    {
      ret->int_val = (reg1->int_val < reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d < r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, ">") == 0)
      {ret->int_val = (reg1->int_val > reg2->float_val);
        fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
        fprintf(body,"r%d = (r%d > r%d);\n",reg,reg1->reg_number,reg2->reg_number);}
    else if (strcmp(signe, "==") == 0)
    {
      ret->int_val = (reg1->int_val == reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d == r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, "!=") == 0)
    {
      ret->int_val = (reg1->int_val != reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d != r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, "&&") == 0)
    {
      ret->int_val = (reg1->int_val && reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d && r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

    else if (strcmp(signe, "||") == 0)
    {
      ret->int_val = (reg1->int_val || reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d || r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

  }
  else if ((reg1->type_val == FLOAT) && (reg2->type_val == FLOAT))
  {
    if (strcmp(signe, "<") == 0)
    {
      ret->int_val = (reg1->float_val < reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d < r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, ">") == 0)
      {ret->int_val = (reg1->float_val > reg2->float_val);
        fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
        fprintf(body,"r%d = (r%d > r%d);\n",reg,reg1->reg_number,reg2->reg_number);}
    else if (strcmp(signe, "==") == 0)
    {
      ret->int_val = (reg1->float_val == reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d == r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, "!=") == 0)
    {
      ret->int_val = (reg1->float_val != reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d != r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }
    else if (strcmp(signe, "&&") == 0)
    {
      ret->int_val = (reg1->float_val && reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d && r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

    else if (strcmp(signe, "||") == 0)
    {
      ret->int_val = (reg1->float_val || reg2->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (r%d || r%d);\n",reg,reg1->reg_number,reg2->reg_number);
    }

    else if (strcmp(signe, "!") == 0)
    {
      ret->int_val = (!reg1->float_val);
      fprintf(header,"%s r%d;\n",type_to_string(ret->type_val),reg);
      fprintf(body,"r%d = (!r%d);\n",reg,reg1->reg_number);
    }
  }
  fprintf(body,"if (!r%d) goto label%d;\n",reg,label);

  ret->reg_number = reg;
  return ret;
}
