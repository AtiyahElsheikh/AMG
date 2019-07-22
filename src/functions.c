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

#include <stdio.h>
#include "functions.h"

/**
 * Set variables to be active -actice($n,@m,...)
 *
 * @return 1 failure, 0 success.
 */
int set_active_variables(parameters_list *ind) { 

  parameters_list *ptr;
  int tmp;
  char *str;
  ptr = ind; 

  while(ptr != (parameters_list *) 0) {
    
    //printf("%d\n",ptr->index);
    if(ptr->index >= 0) { 
      // this variable is active 
      input_arr[ptr->index]->isactive = 1;
      
      // the previous variable represents the derivative
      input_arr[ptr->index-1]->isderiv  = 1;

      if(input_arr[ptr->index]->isderiv) { 
	printf("$%d cann't be active and deriv in the same time\n",
	       ptr->index+1);
	return 1;
      }
      
      if(input_arr[ptr->index-1]->isactive) { 
	printf("$%d cann't be active and deriv in the same time\n",
	       ptr->index);
	return 1;
      }
    }
    else { 
      tmp = ptr->index + n_outputs ;
      //printf("%d %s\n",tmp,output_arr[tmp]->size);
      output_arr[tmp]->isactive = 1;
      output_arr[tmp-1]->isderiv = 1;

      if(output_arr[tmp]->isderiv) { 
	printf("@%d cann't be active and deriv in the same time\n",
	       tmp+1);
	return 1;
      }
      
      if(output_arr[tmp-1]->isactive) { 
	printf("@%d cann't be active and deriv in the same time\n",
	       tmp);
	return 1;
      }
      
    }
    ptr = ptr->next ;
    
  }

  return 0;
}



/*
 * Set size of parameters from the macro -size($x,@y,...)=$z
 *
 * @return 1 failure, 0 success.
 */
int set_identical_size(parameters_list *ind, 
			int identical_index) { 

  parameters_list *ptr;
  int len;

  /* 
   * Set the size  of all parameters whose indeces are allready 
   * in ind to the target size  
   */ 
  ptr = ind;
  len = strlen(input_arr[identical_index]->name)+1;
  while(ptr != (parameters_list *) 0) { 
   
    /* if the parameter to be changed is an input */
    if(ptr->index >= 0) { 
      
      /* ensure that we don't set the size of a parameter to it self */
      if(ptr->index == identical_index) { 
	printf("Conflict : setting size $%d to it self\n", ptr->index); 
	yyerror("\n"); 
	return 1;
      }

      /* ensure that its size  has not been set before */
      if(input_arr[ptr->index]->size == (char *) 0)
	input_arr[ptr->index]->size = (char *) malloc(sizeof(char)*len); //strlen(input_arr[identical_index]->name);
      else { 
	printf("$%d size set twice ", ptr->index+1); 
	yyerror("\n"); 
	return 1;
      } 
      
      /*set its size to the target size */
      input_arr[ptr->index]->size = 
	strcpy(input_arr[ptr->index]->size,input_arr[identical_index]->name);

    }
    /* if the parameter to be changed is an output parameter*/
    else { 
      /* update to the real index */ 
      ptr->index = ptr->index + n_outputs ;
       /* ensures that it has not been set before */
      if(output_arr[ptr->index]->size == (char *)0 )
	output_arr[ptr->index]->size = (char *) malloc(sizeof(char)*len);
      else { 
	printf("@%d size set twice ", ptr->index+1); 
	yyerror("\n"); 
	return 1;
      }

      output_arr[ptr->index]->size = 
	strcpy(output_arr[ptr->index]->size,input_arr[identical_index]->name);
      
      // update it to the original index
      ptr->index = ptr->index - n_outputs ;

    }
    ptr = ptr -> next; // repeat with the next target index
  }

  return 0;
}

/*
 * Set type of parameters from the macro -type($x,@y,...)=$z
 *
 * @return 1 failure, 0 success.
 */
int set_identical_type(parameters_list *ind, 
			int identical_index) { 

  parameters_list *ptr;
  int len;

  /* 
   * Set the type  of all parameters whose indeces are allready 
   * in ind to the target type  
   */ 
  ptr = ind;
  
  len = strlen(input_arr[identical_index]->name)+1;
  while(ptr != (parameters_list *) 0) { 
   
    /* if the parameter to be changed is an input */
    if(ptr->index >= 0) { 
      
      /* ensure that we don't set the type of a parameter to it self */
      if(ptr->index == identical_index) { 
	printf("Conflict : setting type $%d to it self\n", ptr->index+1); 
	yyerror("\n"); 
	return 1;
      }

      /* ensure that its type  has not been set before */
      if(input_arr[ptr->index]->type == (char *) 0)
	input_arr[ptr->index]->type = (char *) malloc(sizeof(char)*len); //strlen(input_arr[identical_index]->name);
      else { 
	printf("$%d type set twice ", ptr->index+1); 
	yyerror("\n"); 
	return 1;
      } 
      
      /*set its type to the target type */
      input_arr[ptr->index]->type = 
	strcpy(input_arr[ptr->index]->type,input_arr[identical_index]->name);

    }
    /* if the parameter to be changed is an output parameter*/
    else { 
      /* update to the real index */ 
      ptr->index = ptr->index + n_outputs ;
       /* ensures that it has not been set before */
      if(output_arr[ptr->index]->type == (char *)0 )
	output_arr[ptr->index]->type = (char *) malloc(sizeof(char)*len);
      else { 
	printf("@%d type set twice ", ptr->index+1); 
	yyerror("\n"); 
	return 1;
      }

      output_arr[ptr->index]->type = 
	strcpy(output_arr[ptr->index]->type,input_arr[identical_index]->name);
      
      // update it to the original index
      ptr->index = ptr->index - n_outputs ; 
      
    }
    ptr = ptr -> next; // repeat with the next target index
  }

  return 0;
}

/*
 * 
 */
int set_specific_type(parameters_list* ind,char* str) { 
  char *tmp;
  int i;
  parameters_list* ptr;

  ptr = ind;

  while(ptr != (parameters_list *)0) { 
    
    if(ptr->index >= 0) { 
      tmp = (char *) malloc(sizeof(char)*(strlen(str)+1));
      tmp = strcpy(tmp,str);
      input_arr[ptr->index]->explicit_type = tmp;
    }
    else { 
      i = ptr->index + n_outputs;
      tmp = (char *) malloc(sizeof(char)*(strlen(str)+1));
      tmp = strcpy(tmp,str);
      output_arr[i]->explicit_type = tmp;
    }

    ptr = ptr->next;
  }

  return 0;
}

int set_explicit_size(parameters_list *ind,dimensions_list *list) { 
  parameters_list*     ptr;
  dimensions_list*  dim;
  char *tmp;
  int n,i,count;

  ptr   = ind;
  dim   = list;
  n = dimensions_list_size(list);
  
  while(ptr != (parameters_list *)0) { 
    
    if(ptr->index >= 0) { 
      input_arr[ptr->index]->ndims = n;
      input_arr[ptr->index]->dims = (char **) malloc( sizeof(char *) * n);
      count = n-1;
      while(dim != (dimensions_list *) 0) { 
        tmp = (char *) malloc((strlen(dim->str)+1)*sizeof(char));
	tmp = strcpy(tmp,dim->str);
	input_arr[ptr->index]->dims[count--] = tmp;
	dim = dim->next;
      }
    }
    else {
      i = ptr->index + n_outputs;
      output_arr[i]->ndims = n;
      output_arr[i]->dims = (char **) malloc( sizeof(char *) * n);
      count = n-1;
      while(dim != (dimensions_list *) 0) { 
	 tmp = (char *) malloc(sizeof(char)*(strlen(dim->str)+1));
	 tmp = strcpy(tmp,dim->str);
	 output_arr[i]->dims[count--] = tmp;
	 dim = dim->next;
       }
    }
    dim = list;
    ptr = ptr->next;
  }

  return 0;
}

/**
 * Set the corresponging (output) parameters, whose data field to be explicitly allocated
 * by the user, in the kernel buffer
 * work only for output parameters
 * @param ind: output parameter list
 * @ret 0 for succesful, 1 for Error
 */  
int set_explicit_outputs(parameters_list* ind) { 
  parameters_list*     ptr;
  
  ptr = ind;
  while(ptr != (parameters_list *)0) { 
    output_arr[ptr->index]->explicit_allocate = 1;
    ptr = ptr->next;
  }
  return 0;
}


void set_default_type() { 
  int i,k;
  char *tmp;
  argument *ptr;

  for(i=0; i < n_inputs; i++) 
    if( (input_arr[i]->type == (char *) 0) && 
	(input_arr[i]->explicit_type == (char *) 0)) 
      { 
	tmp = (char *) malloc( sizeof(char) * 10);
	tmp = strcpy(tmp,"double");
	input_arr[i]->explicit_type = tmp;
      }

  for(i=0; i < n_outputs; i++) 
    if ( (output_arr[i]->type == (char *) 0) && 
	 (output_arr[i]->explicit_type == (char *) 0))
      { 
	tmp = (char *) malloc( sizeof(char) * 10);
	tmp = strcpy(tmp,"double");
	output_arr[i]->explicit_type = tmp;
      }

  for(i=0;i<n_inputs;i++) {  
    ptr = input_arr[i]; 
    tmp = ptr->explicit_type;
    
    while(tmp == (char *) 0) {
      if(ptr->explicit_type != (char *) 0) { 
	tmp = (char *) malloc( sizeof(char) * 100);
	tmp = strcpy(tmp,ptr->explicit_type);
	input_arr[i]->explicit_type = tmp;
      }
      else { 
	k = search_input(ptr->type);
	if(k >= 0)
	  ptr = input_arr[k];
	else { 
	  printf("confilict with explicit type and type\n");
	  exit(1);
	}
      }
    }
  }

  for(i=0;i<n_outputs;i++) {  
    ptr = output_arr[i]; 
    tmp = ptr->explicit_type;
    
    while(tmp == (char *) 0) {
      if(ptr->explicit_type != (char *) 0) { 
	tmp = (char *) malloc( sizeof(char) * 100);
	tmp = strcpy(tmp,ptr->explicit_type);
	output_arr[i]->explicit_type = tmp;
      }
      else { 
	k = search_input(ptr->type);
	if(k >= 0)
	  ptr = input_arr[k];
	else { 
	  printf("confilict with explicit type and type\n");
	  exit(1);
	}
      }
    }
  }

}

void set_default_size() { 
  int i;
  char* str;
 
  for(i=0;i<n_outputs;i++)
    if( (output_arr[i]->size == (char *)0) && 
	(output_arr[i]->ndims == 0) && 
	(!output_arr[i]->isderiv)) 
      { 
	output_arr[i]->ndims = 2;
	output_arr[i]->dims = (char **) malloc(sizeof(char *) * 2);
	
	str = (char *) malloc(sizeof(char)* 3);
	str = strcpy(str,"1");	
	output_arr[i]->dims[0] = str;
      
	str = (char *) malloc(sizeof(char)* 3);
	str = strcpy(str,"1");	
	output_arr[i]->dims[1] = str;
      }
  
}

/**
 * For all identical variable names, thier sizes and types 
 * should be set to the size & type of the first input of 
 * the same size & type.
 */
void update_identical_parameters() { 
  int i,j,len;
  
/* set the size & type of arguments having identical names */
  for(i=0; i<n_inputs; i++) { 

    /*if the input argument is not named */
    if(!strcmp(input_arr[i]->name,"")) { 
      set_default_input_name(input_arr[i]);
      // default type is always double 
      continue ;
    }
    len = strlen(input_arr[i]->name)+1;
    
    /* update the size & type & names of inputs of similar names  */ 
    for(j = i+1;j<n_inputs;j++) { 
      /*if  argument i & j have identical name */
      if(!strcmp(input_arr[i]->name,input_arr[j]->name)) { 
	/*set the size & type of argument j*/

	input_arr[j]->size = (char *) malloc(sizeof(char)*len);
	input_arr[j]->type = (char *) malloc(sizeof(char)*len);
	input_arr[j]->size =  strcpy(input_arr[j]->size,
				     input_arr[i]->name);
	input_arr[j]->type =  strcpy(input_arr[j]->type,
				     input_arr[i]->name);

	/* change the name of argument j*/
	set_default_input_name(input_arr[j]);
	
      }
    } // for j inputs 
     
    for(j=0; j<n_outputs; j++) { 
     
      if(!strcmp(input_arr[i]->name,output_arr[j]->name)) {
	/*update the size & type of argument j*/
	output_arr[j]->size = (char *) malloc(sizeof(char)*len);
	output_arr[j]->type = (char *) malloc(sizeof(char)*len);
	output_arr[j]->size =  strcpy(output_arr[j]->size,
				      input_arr[i]->name);
	output_arr[j]->type =  strcpy(output_arr[j]->type,
				     input_arr[i]->name);
	/*update the type of the argument j*/

	/* change the name of argument j*/
	set_default_output_name(output_arr[j]);
      }
    } // for j outputs 
  
  } // for i 

}

