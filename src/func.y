/********************************************************************************** 
**                                                                               **
**   AMG , Automatic Mex-file Generator                                          **
**         ^         ^        ^                                                  **
**	                                                                             **
**   CopyRight (C) 2005 Atiyah Elsheikh  / 2019 Mathemodica.com                  **
**                                                                               **
**   This file is part of AMG.                                                   **
**                                                                               **
**   AMG is a free software; you can redistribute it and/or modify               **
**   it under the terms of the GNU General Public License as published by        **
**   the Free Software Foundation; Version 2                                     **
**                                                                               **
**   AMG is distributed in the hope that it will be useful,                      **
**   but WITHOUT ANY WARRANTY; without even the implied warranty of              **
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               **
**   GNU General Public License for more details.                                **
**                                                                               **
**   You should have received a copy of the GNU General Public License           **
**   along with AMG; if not, write to the Free Software                          **
**   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA  **
**                                                                               **
**   Contact:  elshekh@rz.rwth-aachen.de                                         ** 
**   =======   =========================                                         **
**                                                                               **
**********************************************************************************/

/* matlab functions prototype */

%{
  #include <stdio.h>
  #include <string.h>
  #include "functions.h"
  #define YYSTYPE char* 
  
  int yylex(void);
  void yyerror(char const *s);

  void generate_mex(void);
  extern int lineno;
  extern int nbrackets;
  
  /* temporary char for setting name for vars*/
  char* tmp;
  char* type;
  
  /* the input argument index to which the size of other variables will be set*/ 
  int identical_index ;

  // initial buffer size, is increased when needed
  int buffer_size=1000;
  // The buffer that stores the kernel code 
  char *kernel_buffer ;

  // One nullbyte is required.
  int header_size=0;
  int header_cap= 1;
  // The buffer that stores the initial code
  char *header_buffer;
  
  parameters_list *ind;
  parameters_list *ptr;

  dimensions_list *dimensions;

  // loop indeces 
  int i,j;
  int len;
  
%}

%token ID
%token RANK
%token INT
%token SIZE
%token TYPE
%token VALID_TYPE
%token IDENTICAL
%token EXPLICIT
%token ADIC
%token ACTIVE
%token KERNEL
%token DIMS
%token ANY
%token HEADER_SEC

/* initial-action is not portable. Rewritten for better protability. 
%initial-action
{
  printf("\n\n\tparsing a matlab function prototype\n");
  printf("\t===================================\n\n");
  kernel_buffer = (char *) malloc(buffer_size); 
  kernel_buffer = strcpy(kernel_buffer,"");
}
*/

%%

line:
init function_call amg_arguments
;

init: 
{
  printf("\n\n\tparsing a matlab function prototype\n");
  printf("\t===================================\n\n");
  nbrackets= 0;
  kernel_buffer = (char *) malloc(sizeof(char)*buffer_size); 
  kernel_buffer[0] = '\0'; // Identical to:  kernel_buffer = strcpy(kernel_buffer,""); , but faster!
  header_buffer = (char *) malloc(sizeof(char)*header_cap); 
  header_buffer[0] = '\0'; 
}

amg_arguments:
  amg_arguments amg_argument
| amg_argument
|
;

amg_argument:
  size_argument
| identical_argument
| type_argument
| explicit_argument
| adic_argument
| active_argument
| header_argument
| kernel_argument
;

function_call:   
output_list '=' func_ID '(' inputs ')' { 
  
  /* restore input and output arguments into seperates arrays 
   * (to ease accessing) input_arr & output_arr will be constructed 
   */
  init_array();
  
  update_identical_parameters();

  // setting default names for unnamed output arguments
  for(j=0; j<n_outputs; j++) 
    if(!strcmp(output_arr[j]->name,""))
      set_default_output_name(output_arr[j]);
  // default outputs type are double 
    
  ind = (parameters_list *) 0; 
  dimensions = (dimensions_list *) 0;  
}
;

output_list:  
ID { 
  n_outputs++; 
  add_output($1); // add the ID to the output_list
} 
| output_rank 
| '[' outputs ']'
;

outputs:   
ID { n_outputs++; add_output($1);}
| output_rank
| outputs ',' ID { n_outputs++; add_output($3);}
| outputs ',' output_rank
;

func_ID: ID  { 
  /* store the name of the function into fname */ 
  fname = (char *) malloc(strlen($1)+1); 
  strcpy(fname,$1); 
}
;

inputs: 
ID { n_inputs++ ; add_input($1);}
| input_rank 
| inputs ',' ID { n_inputs++ ; add_input($3); }
| inputs ',' input_rank
;

output_rank:
'@' RANK { 
  n_outputs++; 
  /* ensures that the rank is correct */
  if(n_outputs != atoi($2)) 
    { yyerror("wrong output rank\n"); exit(1); }
  add_output("");
 }
;

input_rank:
'$' RANK 
{ 
  n_inputs++; 
  /* ensures that the rank of the input parameter is correct */ 
  if(n_inputs != atoi($2)) 
    { yyerror("wrong input rank\n"); exit(1); }
  add_input("");
}
;

adic_argument: 
ADIC  { 
  if(adic_on) { 
    yyerror("adic argument set twice\n");
    exit(1);
  }
  adic_on = 1;
}
;

active_argument:
ACTIVE '(' arguments ')' { 
  
  if( set_active_variables(ind))
    YYABORT;
  
  free_parameters_list(&ind);
}
;

size_argument : 
explicit_size_argument | implicit_size_argument
;

explicit_size_argument:
SIZE '(' arguments ')' '=' '{' dimensions_list '}' {
  if(set_explicit_size(ind,dimensions))
    YYABORT;

  free_parameters_list(&ind);
  free_dimensions_list(&dimensions);  
}
;

dimensions_list:
dimensions_list ',' dimension_arg | dimension_arg
;

dimension_arg:
DIMS { 
  add_dimension(&dimensions,$1);
}
;

implicit_size_argument:
SIZE '(' arguments ')' '=' input_argument { 

  if (set_identical_size(ind,identical_index))
    YYABORT;

  free_parameters_list(&ind);
}
;

type_argument :
specific_type | generic_type
;

specific_type:
TYPE '(' arguments ')' '=' '{' valid_type '}' { 
  printf("type = %s\n",type);
  if(set_specific_type(ind,type))
    YYABORT;

  free_parameters_list(&ind);
}
;

valid_type: 
VALID_TYPE { 
  type = (char *) malloc(strlen($1)+1);
  type = strcpy(type,$1);
}
;

generic_type:
TYPE '(' arguments ')' '=' input_argument { 

  if (set_identical_type(ind,identical_index))
    YYABORT;

  free_parameters_list(&ind);
}
;

identical_argument :
IDENTICAL '(' arguments ')' '=' input_argument { 
 
  if (set_identical_type(ind,identical_index))
    YYABORT;
  
  if (set_identical_size(ind,identical_index))
    YYABORT;

  free_parameters_list(&ind);
}
;

arguments :
arguments ','  argument | argument    
;

argument:
ID { 
  ptr = (parameters_list *) malloc(sizeof(parameters_list)); 

  /* ensure that it is really an input or output parameter */
  ptr->index = search_input($1);
  if(ptr->index < 0) { // if it is not an input parameter
    ptr->index = search_output($1); // it should be an output parameter then
    if(ptr->index < 0)
      { printf("unknown argument : %s ", $1); yyerror("\n"); YYABORT;}
    /*  output parameter indeces should be distinguished from the input one*/
    ptr->index = ptr->index - n_outputs;
  }
  else 
    if(search_output($1) >= 0) // what if both are input and output parameter
      {  printf("Conflict: argument is both input and output : %s ", $1); }//yyerror("\n"); exit(1);}
  
  ptr->next = ind;
  ind = ptr;
} |
'$' RANK { 
  // ensure that the rank inside the addmissible range
   ptr = (parameters_list *) malloc(sizeof(parameters_list)); 
   ptr->index = atoi($2) - 1;
   if( (ptr->index < 0) || (ptr->index  > n_inputs)) 
     { printf("illagal rank : @%d ", ptr->index); yyerror("\n"); YYABORT;}
   ptr->next = ind;
   ind = ptr;
     
} 
| '@' RANK { 
  // ensure that the rank inside the addmissible range
   ptr = (parameters_list *) malloc(sizeof(parameters_list)); 
   ptr->index = atoi($2) - 1;
   if( (ptr->index < 0) || (ptr->index  > n_outputs-1))
     { printf("illagal rank : @%d ", ptr->index + 1); yyerror("\n"); YYABORT;}
   ptr->index -= n_outputs;
   ptr->next = ind;
   ind = ptr;
}
;

input_argument:
ID { 
  // ensures that the given parameter name exists 
  identical_index = search_input($1);
  if( identical_index < 0)
     { printf("unknown size argument : %s ",$1); yyerror("\n"); exit(1); }
} 
| '$' RANK { 
  // ensure that the rank is inside the addmissible range
  identical_index = atoi($2)-1;
  if( (identical_index < 0) || (ptr->index  > n_inputs-1)) { 
    printf("non admissible input rank : $%d",identical_index + 1); yyerror("\n"); exit(1); 
  }
}

explicit_argument:
EXPLICIT '(' out_arguments ')' { 
  if( set_explicit_outputs(ind))
    YYABORT;
  free_parameters_list(&ind);
}

out_arguments :
out_arguments ','  output_argument | output_argument    
;

output_argument:
ID { 
  ptr = (parameters_list *) malloc(sizeof(parameters_list)); 

  // ensures that the given parameter name exists 
  ptr->index = search_output($1);
  if(ptr->index < 0) { 
    printf("unknown explicit argument : %s ",$1); yyerror("\n"); exit(1); 
  }
  
  ptr->next = ind;
  ind = ptr;
} 
| '@' RANK { 
  ptr = (parameters_list *) malloc(sizeof(parameters_list)); 

  // ensure that the rank is inside the addmissible range
  ptr->index = atoi($2)-1;
  if( (ptr->index < 0) || (ptr->index  > n_outputs-1) ) { 
    printf("non admissible output rank : @%d ",identical_index); yyerror("\n"); exit(1); 
  }
  
  ptr->next = ind;
  ind = ptr;
}

kernel_argument: 
KERNEL '{' stmts '}' { 
  printf("kernel : \n%s\n",kernel_buffer);  
}
;

stmts :  stmts stm | stm  
;

stm: 
'$' RANK { 
  if( strlen(kernel_buffer) > buffer_size-3) {
    buffer_size += 1000;
    kernel_buffer= (char *) realloc(kernel_buffer, sizeof(char)*buffer_size);
  }
  kernel_buffer = strcat(kernel_buffer,input_arr[atoi($2)-1]->name); 
}
| '@' RANK { 
  if( strlen(kernel_buffer) > buffer_size-3) {
    buffer_size += 1000;
    kernel_buffer= (char *)realloc(kernel_buffer,sizeof(char)*buffer_size);
  }
  kernel_buffer = strcat(kernel_buffer,output_arr[atoi($2)-1]->name); 
}
| ANY { 
  //printf("=>%s\n",$1);
  if(strlen($1) + strlen(kernel_buffer) > buffer_size-3) {
    buffer_size += 1000;
    kernel_buffer= (char *)realloc(kernel_buffer, sizeof(char)*buffer_size);
  }
  kernel_buffer = strcat(kernel_buffer,$1);
}
;

header_argument:
HEADER_SEC '{' init_stmts '}' {
  printf("header : %s",  header_buffer);
  
};

init_stmts :  init_stmts init_stm | init_stm  
;

init_stm:
ANY { 
  //printf("=>%s\n",$1);
  int len= strlen($1);
  if(len + header_size > header_cap-3) {
    header_cap += 1000;
    header_buffer= (char *)realloc(header_buffer, sizeof(char)*header_cap);
  }
  header_size+= len;
  header_buffer = strcat(header_buffer,$1);
}
;

%%


void yyerror (char const *s) { 
  fprintf(stderr, "in line %d: %s\n", lineno, s);
  exit(1);
}

int main(int argc, char **argv) {
  lineno=0;
  init_param();
  int r = yyparse();
  set_default_type();
  set_default_size();
  set_active_size();
  
  if(info_param) {
    display_inputs();
    display_outputs();
  }
  generate_mex();

  return 0;
}
