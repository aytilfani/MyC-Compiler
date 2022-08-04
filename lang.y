%{

#include "Table_des_symboles.h"
#include "Attribute.h"

#include <stdio.h>
  
extern int yylex();
extern int yyparse();

static int prof = 0;
void dec_prof() {
  prof--;
}

void inc_prof() {
  prof++;
}

int get_prof() {
  return prof;
}

int compt = 0;
int pos[10] = {0};
int nb_param = 0;
int compt1 = 0;
int compt_blocks = 0;
FILE* filec;



void make_store(int var_prof, int var_offset) {
  int a, b;
  fprintf(filec,"  STORE(");
  for ( a = 0; a < get_prof()-var_prof; a++) {
    fprintf(filec,"stack[");
  }
  fprintf(filec,"mp");
  for ( b = 0; b < get_prof()-var_prof; b++) {
    fprintf(filec,"-1]");
  }
  fprintf(filec,"+%d);\n",var_offset);
}

void yyerror (char* s) {
  printf ("%s\n",s);
  }
		

%}

%union { 
	struct ATTRIBUTE * att;
}

%token <att> NUM
%token TINT
%token <att> ID
%token AO AF PO PF PV VIR
%token RETURN VOID EQ
%token <att> IF ELSE WHILE

%token <att> AND OR NOT DIFF EQUAL SUP INF
%token PLUS MOINS STAR DIV
%token DOT ARR

%left OR                       // higher priority on ||
%left AND                      // higher priority on &&
%left DIFF EQUAL SUP INF       // higher priority on comparison
%left PLUS MOINS               // higher priority on + - 
%left STAR DIV                 // higher priority on * /
%left DOT ARR                  // higher priority on . and -> 
%nonassoc UNA                  // highest priority on unary operator
%nonassoc ELSE


%start prog  

// liste de tous les non terminaux dont vous voulez manipuler l'attribut
%type <att> exp  typename while if inst_cond else cond
         

%%

prog : func_list               {}
;

func_list : func_list fun      {}
| fun                          {}
;


// I. Functions

fun : type fun_head fun_body        {}
;

fun_head : ID PO PF            {if(!strcmp($1->name, "main")) fprintf(filec, "int %s() {\n", $1->name);
   else  fprintf(filec,"void %s_pcode(){\n", $1->name); } // erreur si profondeur diff zero
| ID PO params PF              {$1->offset = nb_param;set_symbol_value($1->name,$1,get_prof());
   if (!strcmp($1->name,"main")) fprintf(filec,"int %s(){\n", $1->name);
 else fprintf(filec, "void %s_pcode(){\n", $1->name);}
;

 params: TINT ID vir params     {$2->arg_numb = ++nb_param;set_symbol_value($2->name,$2,get_prof());}
   | TINT ID                      {$2->arg_numb = ++nb_param;set_symbol_value($2->name,$2,get_prof());}

vlist: vlist vir ID            {fprintf(filec,"  LOADI(0);\n");attribute a = new_attribute();a->profondeur = get_prof();a->offset = pos[prof]++;set_symbol_value($3->name,a,get_prof());}
| ID                           {fprintf(filec,"  LOADI(0);\n");attribute a = new_attribute();a->profondeur = get_prof();a->offset = pos[prof]++;set_symbol_value($1->name,a,get_prof());}
;

vir : VIR                      {}
;

fun_body : AO block AF         {}
;

// Block
block:
decl_list inst_list            {}
;

// I. Declarations

decl_list : decl_list decl     {}
|                              {}
;

 decl: var_decl PV              {}
;

var_decl : type vlist          {}
;

type
: typename                     {}
;

typename
: TINT                          {}
| VOID                          {}
;

// II. Intructions

inst_list: inst inst_list   {}
| inst                      {}
;

pv : PV                       {}
;
 
inst:
exp pv                        {}
| ao block af                 {}
| aff pv                      {}
| ret pv                      {}
| cond                        {}
| loop                        {}
| pv                          {}
;

// Accolades pour gerer l'entrée et la sortie d'un sous-bloc

ao : AO                       {inc_prof();fprintf(filec, "  ENTER_BLOCK(0);\n");}
;

af : AF                       {dec_prof();fprintf(filec, "  EXIT_BLOCK(0);\n");}
;


// II.1 Affectations

aff : ID EQ exp               {attribute att = get_symbol_proche($1, get_prof());make_store(att->profondeur,att->offset);}
;


// II.2 Return
ret : RETURN exp              {if(!strcmp($2->name, "main")) fprintf(filec, "  EXIT_MAIN;\n}\n");
   else  fprintf(filec,"  return;\n}\n");}
| RETURN PO PF                {}
;

// II.3. Conditionelles
//           N.B. ces rêgles génèrent un conflit déclage reduction
//           qui est résolu comme on le souhaite par un décalage (shift)
//           avec ELSE en entrée (voir y.output)

cond :
if bool_cond inst_cond elsop       {$$=$<att>1; fprintf(filec, "Fin%d:\n  NOP;\n", $$->int_val);}
;

// la regle avec else vient avant celle avec vide pour induire une resolution
// adequate du conflit shift / reduce avec ELSE en entrée

elsop : else inst             {}
  |                             {}
;

inst_cond: inst    {fprintf(filec,"  GOTO(Fin%d);\n",$<att>-1->int_val,$<att>-1->int_val);}
;
bool_cond : PO exp PF         {fprintf(filec,"  IFN(Else%d);\n", $<att>0->int_val);}
;

if : IF                       {$$ = new_attribute();
$$->int_val = compt1++;}
;

 else : ELSE                   {$$=$<att>-2; fprintf(filec, "Else%d:\n",$$->int_val);}
;

// II.4. Iterations

loop : while while_cond inst  {fprintf(filec,"  GOTO(Loop%d);\nEnd%d:\n",$<att>1->int_val,$<att>1->int_val);}
;

while_cond : PO exp PF        {fprintf(filec,"  IFN(End%d);\n",$<att>0->int_val);}
while : WHILE                 {$$ = new_attribute();$$->int_val = compt++;fprintf(filec,"Loop%d:\n",$$->int_val);}
;


// II.3 Expressions
exp
// II.3.1 Exp. arithmetiques
: MOINS exp %prec UNA         {fprintf(filec,"  MINUS;\n");}
         // -x + y lue comme (- x) + y  et pas - (x + y)
| exp PLUS exp                {fprintf(filec,"  ADDI;\n");}
| exp MOINS exp               {fprintf(filec,"  SUBI;\n");}
| exp STAR exp                {fprintf(filec,"  MULTI;\n");}
| exp DIV exp                 {fprintf(filec,"  DIVI;\n");}
| PO exp PF                   {}
| ID                          {attribute att = get_symbol_value($1->name, $1->profondeur);
  if(nb_param != 0) fprintf(filec, "  LOAD(mp - 1 - %d);\n", att->arg_numb);
  else fprintf(filec,"  LOAD(mp+%d)\n",att->offset);}
| app                         {}
| NUM                         {$$ =new_attribute();$$->int_val = $1->int_val;fprintf(filec,"  LOADI(%i);\n",$1->int_val);}


// II.3.2. Booléens

| NOT exp %prec UNA           {}
| exp INF exp                 {fprintf(filec,"  LT;\n");}
| exp SUP exp                 {fprintf(filec,"  GT;\n");}
| exp EQUAL exp               {}
| exp DIFF exp                {}
| exp AND exp                 {}
| exp OR exp                  {}

;

// II.4 Applications de fonctions

 app : ID PO args PF           {attribute att = get_symbol_value($1->name,$1->profondeur);
  fprintf(filec, "  %s_pcode();\n  EXIT_BLOCK(%i);\n", att->name,att->offset);}
;

args :  arglist               {fprintf(filec, "  ENTER_BLOCK(%i);\n",get_symbol_value($<att>-1->name,get_prof())->offset);}
|                             {fprintf(filec, "  ENTER_BLOCK(%i);\n",get_symbol_value($<att>-1->name,get_prof())->offset);}
;
 arglist : exp VIR arglist     {}
| exp                         {}
;



%% 
int main (int argc, char *argv[]) {

  /* Ici on peut ouvrir le fichier source, avec les messages 
     d'erreur usuel si besoin, et rediriger l'entrée standard 
     sur ce fichier pour lancer dessus la compilation.
   */
filec = fopen("out.c", "w");
fprintf(filec, "#include \"PCode/PCode.h\"\n");
fprintf(filec, "int stack[SIZE];\nint sp = 0;\nint mp = 0;\n");

//fprintf(filec, "int  main() {\n");
//printf ("Compiling MyC source code into PCode (Version 2021) !\n\n");
yyparse ();
//fprintf(filec, "\n}\n");
return 0;
 
} 

