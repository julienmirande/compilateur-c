%code requires{

#include "Table_des_symboles.h"
#include "Attribute.h"

 }

%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
FILE* header = NULL;
FILE* body = NULL;


extern int yylex();
extern int yyparse();
extern int yylineno;
extern int num_registre;
extern int num_label;

void yyerror (char* s) {
  printf ("FAILURE: Erreur de %s à la ligne %d ...\n",s,yylineno);
  exit(0);
}

%}

%union {
	attribute val;
}
%token <val> NUMI NUMF
%token <val> TINT TFLOAT STRUCT
%token <val> ID
%token AO AF PO PF PV VIR
%token <val> RETURN VOID EQ
%token <val> IF ELSE WHILE

%token  <val> AND OR NOT DIFF EQUAL SUP INF
%token  <val> PLUS MOINS STAR DIV
%token DOT ARR

%type <val> exp did typename type vlist var_decl decl vir aff pointer bool_cond cond if

%left DIFF EQUAL SUP INF       // low priority on comparison
%left PLUS MOINS               // higher priority on + -
%left STAR DIV                 // higher priority on * /
%left OR                       // higher priority on ||
%left AND                      // higher priority on &&
%left DOT ARR                  // higher priority on . and ->
%nonassoc UNA                  // highest priority on unary operator

%start prog



%%

prog : block                   {//printf(" ")
                                ;} //PROG
;

block:
decl_list inst_list            {//printf(" ")
                                ;} //BLOCK
;

// I. Declarations

decl_list : decl decl_list     {//printf(" ")
                                ;} //LISTE_DECLARATION
|                              {}
;

decl: var_decl PV              {//fprintf(header,";\n")
                              ;} //DECLARATION
| struct_decl PV               {//printf("Fin declaration structure\n")
                                ;}
| fun_decl                     {}
;

// I.1. Variables
var_decl : type vlist          {//fprintf(header,"%s",$1->name);
                                //fprintf(header,"%s",$1->name)
                              ;} // DECLARATION_VARIABLE
;

// I.2. Structures
struct_decl : STRUCT ID struct {}
;

struct : AO attr AF            {}
;

attr : type ID                 {}
| type ID PV attr              {}

// I.3. Functions

fun_decl : type fun            {}
;

fun : fun_head fun_body        {}
;

fun_head : ID PO PF            {//printf(" ")
                                ;} //main () {\n
| ID PO params PF              {}
;

params: type ID vir params     {}
| type ID                      {}

vlist: did vir vlist            {$$=$1;//fprintf(header,"%s",$2->name)
                                ;}
| did                           {
                                ;}
;

did: ID                        {
                                $1->type_val = $<val>0->type_val;
                                $1->nb_stars = $<val>0->nb_stars;
                                set_symbol_value($1->name,$1);
                                if ($1->type_val != 271) //void type
                                {
                                  fprintf(header,"%s ",type_to_string($1->type_val));
                                  for (int i =0 ; i < $<val>0->nb_stars ; i++)
                                  {
                                    fprintf(header,"*");
                                  }
                                  fprintf(header," %s;\n",$1->name);
                                }
                                else
                                  yyerror("type");

                               ;}
;

vir : VIR                      {$$=$<val>-1;
                                ;}
;

fun_body : AO block AF         {//printf("\n}\n")
                                ;}
;

// I.4. Types
type
: typename pointer             {$$->type_val= $1->type_val;$$->nb_stars = $2->nb_stars
                                ;}

| typename                     {$$=$1; $$->nb_stars = 0
                                ;} //TYPE
;

typename
: TINT                          {$$ = new_attribute(); $$->type_val = INT;

                                ;}
| TFLOAT                        {$$ = new_attribute(); $$->type_val = FLOAT
                                ;}
| VOID                          {$$ = new_attribute(); $$->type_val = VOID
                                ;}
| STRUCT ID                     {}
;

pointer
: pointer STAR                 {$$->nb_stars = $$->nb_stars + 1;}
| STAR                         {$$ = new_attribute(); $$->nb_stars = 1;}
;


// II. Intructions

inst_list: inst PV inst_list   {}
| inst                         {} //INSTRUCTION
|                              {}
;

inst:
exp                           {}
| AO block AF                 {fprintf(body,"label%d:\n",num_label);
                                }
| aff                         {}
| ret                         {}
| cond                        {}
| loop                        {}
| PV                          {printf("Fin d'instruction\n");}
;


// II.1 Affectations
aff : ID EQ exp               {attribute id_attribut = get_symbol_value($1->name);
                               attribute retour = new_attribute();
                               retour->name = $1->name;
                              // casting obligatoire
                              if (id_attribut->type_val != $3->type_val)
                              {
                                  retour->type_val = id_attribut->type_val;
                                  retour->reg_number = new_registre();
                                  fprintf(header,"%s r%d;\n",type_to_string(retour->type_val),retour->reg_number);
                                  fprintf(body,"r%d = (%s) r%d;\n",retour->reg_number,type_to_string(retour->type_val),$3->reg_number);
                                  retour->int_val = (int) $3->float_val;
                                  retour->float_val = (float) $3->int_val;
                                  $$ = set_symbol_value($1->name,retour);
                                  fprintf(body,"%s = r%d;\n",$$->name,$$->reg_number);
                                  printf("WARNING: casting d'un float en int !\n");

                              }
                              else
                              {
                                if ($3->name == NULL)
                                  fprintf(body,"%s = r%d;\n",$1->name,$3->reg_number);
                                else
                                {
                                  fprintf(body,"%s = %s;\n",$1->name,$3->name);
                                }
                                retour->type_val = $3->type_val;
                                retour->int_val = $3->int_val;
                                retour->float_val = $3->float_val;
                                $$ = set_symbol_value($1->name,retour);
                                }

                            }
| STAR exp EQ exp           {}
;


// II.2 Return
ret : RETURN exp              {}
| RETURN PO PF                {}
;

// II.3. Conditionelles
cond :
if bool_cond inst             {
                                /*fprintf(body,"goto label%d;\n",num_label+1);
                                fprintf(body,"if (r%d) goto label%d;\n",$2->reg_number,num_label);
                                int label = new_label();
                                fprintf(body,"label%d: \n",label);*/
                                ;}
|  else inst                  {}
;


bool_cond : PO exp PF         {$$=$2;printf("AVANT");}
;

if : IF                       {$$->name = "if";}
;

else : ELSE                   {}
;

// II.4. Iterations

loop : while while_cond inst  {}
;

while_cond : PO exp PF        {}

while : WHILE                 {}
;


// II.3 Expressions
exp
// II.3.0 Exp. arithmetiques // bug quand l'operateur est a droite de l'opération
: MOINS exp %prec UNA         {$$ = neg_attribute($2);
                               $$->reg_number = new_registre();
                               fprintf(header,"%s r%d;\n",type_to_string($$->type_val),$$->reg_number);
                               fprintf(body,"r%d = -r%d;\n",$$->reg_number,$2->reg_number);
                               if ($$->type_val == INT)
                                 fprintf(body,"printf(\"%s\\n\",r%d);\n","%d",$$->reg_number);
                               else if ($$->type_val == FLOAT)
                                 fprintf(body,"printf(\"%s\\n\",r%d);\n","%f",$$->reg_number);
                              ;}
| exp PLUS exp                {$$ = plus_attribute($1,$3,header,body);
                              if ($$->type_val == INT)
                                fprintf(body,"printf(\"%s\\n\",r%d);\n","%d",$$->reg_number);
                              else if ($$->type_val == FLOAT)
                                fprintf(body,"printf(\"%s\\n\",r%d);\n","%f",$$->reg_number);
                              }
| exp MOINS exp               {int reg_number = new_registre();
                              $$ = minus_attribute($1,$3,header,body);
                                fprintf(header,"%s r%d;\n",type_to_string($$->type_val),$$->reg_number);
                                if ($$->type_val == INT)
                                  fprintf(body,"printf(\"%s\\n\",r%d);\n","%d",$$->reg_number);
                                else if ($$->type_val == FLOAT)
                                  fprintf(body,"printf(\"%s\\n\",r%d);\n","%f",$$->reg_number);
                              }
| exp STAR exp                {int reg_number = new_registre();
                              $$ = mult_attribute($1,$3,header,body);
                                fprintf(header,"%s r%d;\n",type_to_string($$->type_val),$$->reg_number);
                                if ($$->type_val == INT)
                                  fprintf(body,"printf(\"%s\\n\",r%d);\n","%d",$$->reg_number);
                                else if ($$->type_val == FLOAT)
                                  fprintf(body,"printf(\"%s\\n\",r%d);\n","%f",$$->reg_number);
                              }
| exp DIV exp                 {if ($3->int_val == 0 || $3->float_val == 0.0)
                                  printf("WARNING: division par 0");
                              int reg_number = new_registre();
                              $$ = div_attribute($1,$3,header,body);
                                fprintf(header,"%s r%d;\n",type_to_string($$->type_val),$$->reg_number);
                                if ($$->type_val == INT)
                                  fprintf(body,"printf(\"%s\\n\",r%d);\n","%d",$$->reg_number);
                                else if ($$->type_val == FLOAT)
                                  fprintf(body,"printf(\"%s\\n\",r%d);\n","%f",$$->reg_number);
                              }
| PO exp PF                   {$$=$2; }
| ID                          {
                                if (get_symbol_value($1->name) != NULL)
                                {
                                  $$=get_symbol_value($1->name);
                                  $$->reg_number = new_registre();
                                  fprintf(header,"%s r%d;\n",type_to_string($$->type_val),$$->reg_number);
                                  // for (int i =0 ; i < $$->nb_stars ; i++)
                                  // {
                                  //   fprintf(header,"*");
                                  // }
                                  fprintf(body,"r%d = %s;\n",$$->reg_number,$$->name);
                                }
                                else
                                yyerror("not declared");
                              }
| NUMI                        {$$->int_val=$1->int_val;$$->type_val = $1->type_val;
                              $$->reg_number = new_registre();
                              fprintf(header,"%s r%d;\n",type_to_string($$->type_val),$$->reg_number);
                              fprintf(body,"r%d = %d;\n",$$->reg_number,$$->int_val);
                              ;}
| NUMF                        {$$->float_val=$1->float_val;$$->type_val = $1->type_val;
                              $$->reg_number = new_registre();
                              fprintf(header,"%s r%d;\n",type_to_string($$->type_val),$$->reg_number);
                              fprintf(body,"r%d = %f;\n",$$->reg_number,$$->float_val);
                              ;}

// II.3.1 Déréférencement

| STAR exp %prec UNA          {}

// II.3.2. Booléens

| NOT exp %prec UNA           {$$ = condition($1,NULL,header,body,"!");}
| exp INF exp                 {$$ = condition($1,$3,header,body,"<");}
| exp SUP exp                 {$$ = condition($1,$3,header,body,">");}
| exp EQUAL exp               {$$ = condition($1,$3,header,body,"==");}
| exp DIFF exp                {$$ = condition($1,$3,header,body,"!=");}
| exp AND exp                 {$$ = condition($1,$3,header,body,"&&");}
| exp OR exp                  {$$ = condition($1,$3,header,body,"||");}

// II.3.3. Structures

| exp ARR ID                  {}
| exp DOT ID                  {}

| app                         {}
;

// II.4 Applications de fonctions

app : ID PO args PF;

args :  arglist               {}
|                             {}
;

arglist : exp VIR arglist     {}
| exp                         {}
;



%%
int error_opening(FILE * file)
{
  if (file == NULL)
  {
    printf("Impossible to open .h file");
    exit(0);
  }
  return 0;
}

int main () {
  // Create output.c //
  header = fopen("test/test.h", "w");
  if (header == NULL)
  {
    printf("Impossible to open .h file");
    exit(0);
  }

  fputs("#ifndef ATTRIBUTE_H \n#define ATTRIBUTE_H\n#include <stdio.h>\n", header);

  // Create output.h //
  body = fopen("test/test.c", "w");
  if (body == NULL)
  {
    printf("Impossible to open .h file");
    exit(0);
  }
  fputs("//test.c\n#include <stdio.h>\n#include \"test.h\"\nint main() {\n\n", body);

  // Start the parsing //
  yyparse ();

  fputs("}", body);

  // Addind the endif in .h
  fputs("\n#endif", header);
  fclose(header);
  fclose(body);

  // Debogging symbols //
  printf("\nSymbols:\n");
  afficher();
  printf("\n");
  return 0;
}
