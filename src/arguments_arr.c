/********************************************************************************** 
**                                                                               **
**   AMG , Automatic Mex-file Generator                                          **
**         ^         ^        ^                                                  **
**	                                                                         **
**   CopyRight (C) 2005 Atya El-Shekh                                            **
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

#include "functions.h"

void init_array(){
  arguments_list *ptr;
  int n;

  input_arr  = (argument **) malloc(sizeof(argument *) * n_inputs);
  ptr = inputs_list;
  n = n_inputs;

  while( n-- > 0) {
    input_arr[n] = ptr->arg;
    ptr=ptr->next;
  }

  output_arr  = (argument **) malloc(sizeof(argument *) * n_outputs);
  ptr = outputs_list;
  n = n_outputs;

  while( n-- > 0) {
    output_arr[n] = ptr->arg;
    ptr=ptr->next;
  }
}

/** initialize the parameter lists, inputs_list and outputs_list */ 
void init_param() {
  inputs_list = (arguments_list *) 0; 
  outputs_list = (arguments_list *) 0;
  n_inputs = 0;
  n_outputs = 0;
}

void display_outputs() {
  int i,j;
  
  printf("the outputs are:\n");
  
  for(i=0; i<n_outputs; i++) {
    printf("@%d:\n",i+1);
    printf("\t name: %s\n",output_arr[i]->name);
    printf("\t rank: %d\n",output_arr[i]->rank);
    if(output_arr[i]->size != (char *)0)
      printf("\t size: %s\n",output_arr[i]->size);
    if(output_arr[i]->ndims != 0) { 
      printf("\t explicit size: \n\t\t");
      for(j=0;j<output_arr[i]->ndims;j++)
	printf("%s  ",output_arr[i]->dims[j]);
      printf("\n");
    }
    if(output_arr[i]->type != (char *)0)
      printf("\t type: %s\n",output_arr[i]->type);
    if(output_arr[i]->explicit_type != (char *)0)
      printf("\t explicit type: %s\n",output_arr[i]->explicit_type);
    if(output_arr[i]->explicit_allocate)
      printf("\t data field memory should be explicitly allocated");
    if(adic_on) { 
      printf("\t isactive: %d\n",output_arr[i]->isactive);
      printf("\t isderiv : %d\n",output_arr[i]->isderiv);
    }
  }
  printf("\n");
}

void display_inputs() {
  int i,j;

  printf("the inputs are:\n");
  
  for(i=0; i<n_inputs; i++) {
    printf("$%d:\n",i+1);
    printf("\t name: %s\n",input_arr[i]->name);
    printf("\t rank: %d\n",input_arr[i]->rank);
    if(input_arr[i]->size != (char *)0)
      printf("\t size: %s\n",input_arr[i]->size);
    if(input_arr[i]->ndims != 0) { 
      printf("\t explicit size: \n\t\t");
      for(j=0;j<input_arr[i]->ndims;j++)
	printf("%s  ",input_arr[i]->dims[j]);
      printf("\n");
    }
    if(input_arr[i]->type != (char *)0)
      printf("\t type: %s\n",input_arr[i]->type);
    if(input_arr[i]->explicit_type != (char *)0)
      printf("\t explicit type: %s\n",input_arr[i]->explicit_type);
    if(adic_on) { 
      printf("\t isactive: %d\n",input_arr[i]->isactive);
      printf("\t isderiv : %d\n",input_arr[i]->isderiv);
    }
  }
  
  printf("\n");
}

int search_input(char *s) { 
  int i;

  for(i=0;i< n_inputs; i++)  
    if( strcmp(input_arr[i]->name,s) == 0)
      return i;

  return -1;
}

int search_output(char *s) { 
  int i;
  
  for(i=0;i< n_outputs; i++)  
    if( strcmp(output_arr[i]->name,s) == 0)
      return i;

  return -1;
}

/** 
 * add an output parameter to outputs_list
 * @param s the name of the parameter
 */ 

void add_output(char *s) {

  argument *ptr ;
  arguments_list *tmp;
  
  ptr = (argument *) malloc(sizeof(argument));
  tmp = (arguments_list *) malloc(sizeof(arguments_list));

  ptr->name = (char *) malloc(sizeof(char)*(strlen(s)+1)); // The nullbyte needs space, too!
  strcpy(ptr->name,s);

  tmp->arg = ptr;
  tmp->next = outputs_list;
  outputs_list = tmp ;

  ptr->rank = n_outputs;
  ptr->size = (char *) 0;
  ptr->ndims = 0;
  ptr->dims = (char **) 0;
  ptr->type = (char *) 0;
  ptr->explicit_type = (char *) 0;
  ptr->explicit_allocate = 0;
  ptr->isactive = 0;
  ptr->isderiv  = 0;

  
}

/** 
 * add an input parameter to inputs_list
 * @param name the name of the variable
 */ 
void add_input(char *s) {

  argument *ptr ;
  arguments_list *tmp;

  ptr = (argument *) malloc(sizeof(argument));
  tmp = (arguments_list *) malloc(sizeof(arguments_list));

  ptr->name = (char *) malloc(sizeof(char)*(strlen(s)+1)); // The nullbyte needs space, too!
  strcpy(ptr->name,s);

  tmp->arg = ptr;
  tmp->next = inputs_list;
  inputs_list = tmp ;
  
  ptr->rank = n_inputs;
  ptr->size = (char *) 0;
  ptr->ndims = 0;
  ptr->dims = (char **) 0;
  ptr->type = (char *) 0;
  ptr->explicit_allocate = 0;
  ptr->explicit_type = (char *) 0;
  ptr->isactive = 0;
  ptr->isderiv  = 0;
 
}

void set_default_name(argument *p, const char *defname) {
  int k=0,j;
  char *tmp;

  free(p->name); 

  j = p->rank;
  tmp = (char *) malloc(sizeof(char)*3); 
  if( j < 10 )
    tmp[k++] = '0' + j ; 
  else {  
    tmp[k++] = '0' + j/10;
    tmp[k++] = '0' + j%10;
  }
  tmp[k] = '\0'; 

  p->name = (char *) malloc(sizeof(char)*(strlen(defname)+strlen(tmp)+1)); 
  p->name = strcpy(p->name,defname);
  p->name = strcat(p->name,tmp);

  free(tmp);
}

void set_default_input_name(argument *p) { 
  set_default_name(p, default_input_name);
/*  int k=0,j;
  char *tmp;

  free(p->name); 

  j = p->rank;
  tmp = (char *) malloc(sizeof(char)*3); 
  if( j < 10 )
    tmp[k++] = '0' + j ; 
  else {  
    tmp[k++] = '0' + j/10;
    tmp[k++] = '0' + j%10;
  }
  tmp[k] = '\0'; 

  p->name = (char *) malloc(sizeof(char)*(strlen(default_input_name)+strlen(tmp)+1)); 
  p->name = strcat(p->name,default_input_name);
  p->name = strcat(p->name,tmp);

  free(tmp);
*/	
}

void set_default_output_name(argument *p) { 
  set_default_name(p, default_output_name);
  /*
  int k=0,j;
  char *tmp;

  free(p->name); 

  j = p->rank;
  tmp = (char *) malloc(sizeof(char)*3); 
  if( j < 10 )
    tmp[k++] = '0' + j ; 
  else {  
    tmp[k++] = '0' + j/10;
    tmp[k++] = '0' + j%10;
  }
  tmp[k] = '\0'; 

  p->name = (char *) malloc(sizeof(char)*(strlen(default_output_name)+5); 
  p->name = strcat(p->name,default_output_name);
  p->name = strcat(p->name,tmp);

  free(tmp);
*/	
}

void set_active_size() { 
  int i,j;
  char *str;

  // the size of the derivative variables = 
  //   numel($this) * num_independents
  for(i=0;i<n_inputs;i++)  
    if(input_arr[i]->isactive) { 
      input_arr[i-1]->ndims = 2;
      input_arr[i-1]->dims = (char **) malloc(sizeof(char *) * 2);
      
      str = (char *) malloc(sizeof(char)*(strlen(input_arr[i]->name)+36));
      str = strcpy(str,"numel(");
      str = strcat(str,input_arr[i]->name);
      str = strcat(str,") * amg_num_independents");
      input_arr[i-1]->dims[0] = str;

      str = (char *) malloc(sizeof(char)*2);
      str[0] = '1'; str[1]='\0'; // strcpy(str,"1");	
      input_arr[i-1]->dims[1] = str;
    } 

  for(i=0;i<n_outputs;i++)  
    if(output_arr[i]->isactive) { 
      output_arr[i-1]->ndims = 2;
      output_arr[i-1]->dims = (char **) malloc(sizeof(char *) * 2);

      if(output_arr[i]->size != (char *)0) { 
	 str = (char *) malloc(sizeof(char)*(strlen(output_arr[i]->size)+36));
	 str = strcpy(str,"numel(");
	 str = strcat(str,output_arr[i]->size);
	 str = strcat(str,") * amg_num_independents");
      }
      else { 
	 str = (char *) malloc(sizeof(char)*1000);
	 for(j=0;j<output_arr[i]->ndims;j++) { 
	   str = strcat(str,output_arr[i]->dims[j]);
	   str = strcat(str," * ");
	 }
	 str = strcat(str,"amg_num_independents");
      }
      output_arr[i-1]->dims[0] = str;

      str = (char *) malloc(sizeof(char)*2);
      str[0]='1'; str[1]= '\0'; // = strcpy(str,"1");	
      output_arr[i-1]->dims[1] = str;
    }

}

