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

#include<stdio.h>
#include "functions.h"

const char* mexpostfix = ".c"; 
char* default_input_name = "arg_";
char* default_output_name = "out_";
char* parpostfix = "_par";
extern const char* doc_tmp;
extern const char* doc_ad_tmp;
extern const char* copyright_tmp;
extern const char* input_tmp;
extern const char* output_tmp;

char* mx_class(argument *ptr);
void  create_outputs();
FILE *mex; //,*in,*out ; 

void generate_mex() {

  char* mexname;
  char* tmp;
  char* class;
  int c,i,j,k;

  //printf("Allocating %d byte for '%s.c'.\n", sizeof(char)* (strlen(fname) + strlen(mexpostfix)+1), fname); 
  mexname = (char *) malloc( sizeof(char)* (strlen(fname) + strlen(mexpostfix)+1));
  strcpy(mexname,fname);
  strcat(mexname,mexpostfix);
  printf("generate %s\n",mexname);

  mex = fopen(mexname,"w");
  
  fputs(copyright_tmp, mex);

/*in  = fopen("copyright.tmp","r");
  while( (c=getc(in)) != EOF)
    putc(c,mex) ;
  fclose(in);*/

  fprintf(mex,"#include <stdio.h>\n");
  fprintf(mex,"#include <mex.h>\n");

  if(!adic_on) { 
    if(!all_double)
      fprintf(mex,"#include \"amgmex.h\"\n");
    else
      fprintf(mex,"#include \"amgmex-double.h\"\n");
  }
  else {  
    if(!all_double)
      fprintf(mex,"#include \"amgmex-ad.h\"\n");
    else
      fprintf(mex,"#include \"amgmex-ad-double.h\"\n");
  }

  fputs(doc_tmp, mex);

  if (header_buffer[0] != 0) 
    fputs(header_buffer, mex);

  
/* These files are now compiled into mexgen.
   in  = fopen("doc.tmp","r");
  while( (c=getc(in)) != EOF)
    putc(c,mex) ;
  fclose(in);*/

  if(adic_on) { 
    fputs(doc_ad_tmp, mex);
/*    in  = fopen("doc-ad.tmp","r");
    while( (c=getc(in)) != EOF)
      putc(c,mex) ;
    fclose(in);*/
  }

  for(i=0;i<n_inputs;i++)  
    fprintf(mex,"#define  %s%s   arg[%d]\n",
	    input_arr[i]->name,
	    parpostfix,
	    input_arr[i]->rank-1); 
  fprintf(mex,"\n"); 

  for(i=0;i<n_outputs;i++)
    if(output_arr[i]->explicit_allocate)
       fprintf(mex,"#define  %s%s   out[%d]\n",
	       output_arr[i]->name,
	       parpostfix,
	       output_arr[i]->rank-1); 

  fprintf(mex,"int* amg_tmp;\n");

  if(adic_on)
    fprintf(mex,"int amg_num_independents;\n");

  fputs(input_tmp, mex);
  /*  in  = fopen("input.tmp","r");
      while( (c=getc(in)) != EOF)
      putc(c,mex); */
  if(adic_on) { 
    i=0;
    while( (i<n_inputs) && !input_arr[i]->isactive ) i++;
    if( i == n_inputs) { 
      printf("ERROR: no input active variables?\nsome input variables should be set with -active\n");
      exit(1); 
    }
    fprintf(mex,"\tamg_num_independents = numel(%s) / numel(%s);\n\n", 
	    input_arr[i-1]->name,
	    input_arr[i]->name);    
  }
  for(i=0;i<n_inputs;i++)
    fprintf(mex,"\t%s*  %10s =  arg[%d]->data;\n",
	    input_arr[i]->explicit_type,
	    input_arr[i]->name,
	    input_arr[i]->rank-1); 
    
  if(display_input)
    fprintf(mex,"\tdisplay(arg,nrhs);\n");

  // TO DO:
  //     use mxErrMsgTxt..
  fprintf(mex,"\tint* amg_itmp;\n");
  for(i=0;i<n_inputs;i++) { 
    
    if(input_arr[i]->size != (char *) 0) { 
      fprintf(mex,"\tif(!has_equal_dims(%s%s,%s%s)) {\n",
	      input_arr[i]->name,parpostfix,
	      input_arr[i]->size,parpostfix); 
      fprintf(mex,"\t\tprintf(\"Error: %s and %s should have equal dimensions\");\n\t\texit(1);\n\t}\n",
	      input_arr[i]->name,input_arr[i]->size);
    }
    else if(input_arr[i]->ndims != 0) { 
      fprintf(mex,"\tamg_itmp = (int *) malloc(sizeof(int) * %d);\n",
	      input_arr[i]->ndims);
      for(j=0;j<input_arr[i]->ndims;j++)
	fprintf(mex,"\tamg_itmp[%d] = %s;\n",j,
		input_arr[i]->dims[j]);
      fprintf(mex,"\tif(!has_equal_size(%s%s,amg_itmp,%d))\n",
	      input_arr[i]->name,parpostfix,
	      input_arr[i]->ndims);	
      fprintf(mex,"\t\tprintf(\"??? Error: argument %d is not of admissible size\\n\");\n",i+1);
    }      
  }
      
  fprintf(mex,"\n");

  for(i=0;i<n_inputs;i++) 
    if(input_arr[i]->type != (char *) 0) { 
      fprintf(mex,"\tif(!has_equal_type(%s%s,%s%s)) {\n",
	      input_arr[i]->name,parpostfix,
	      input_arr[i]->type,parpostfix); 
      fprintf(mex,"\t\tprintf(\"Error: %s and %s should have equal dimenstions\");\n\t\texit(1);\n\t}\n",
	      input_arr[i]->name,input_arr[i]->type);
    }

  fputs(output_tmp, mex);
/*  out = fopen("output.tmp","r");
  while( (c=getc(out)) != EOF)
    putc(c,mex) ; */

  create_outputs();

  if(adic_on) { 
    
    //fprintf(mex,"\n\tad_AD_Init(%d);\n\n",num_independent_variables);
    fprintf(mex,"\n\tad_AD_Init(amg_num_independents);\n\n");

    for(i=0;i<n_inputs;i++) 
      if(input_arr[i]->isactive) 
	fprintf(mex,"\tDERIV_TYPE* grad(%s) = deriv(%s,%s);\n",
		input_arr[i]->name,
		input_arr[i]->name,
		input_arr[i-1]->name);

    fprintf(mex,"\n");
    for(i=0;i<n_outputs;i++) 
      if(output_arr[i]->isactive) { 
	if(output_arr[i]->size != (char *) 0)
	  fprintf(mex,"\tDERIV_TYPE* grad(%s) =\n\t\t (DERIV_TYPE *) mxMalloc( sizeof(DERIV_TYPE) * numel(%s));\n",
		  output_arr[i]->name,
		  output_arr[i]->size);
	else { 
	  fprintf(mex,"\tDERIV_TYPE* grad(%s) =\n\t\t (DERIV_TYPE *) mxMalloc( sizeof(DERIV_TYPE)",
		  output_arr[i]->name);
	  for(j=0;j<output_arr[i]->ndims;j++)
	    fprintf(mex," * %s",output_arr[i]->dims[j]);
	  fprintf(mex,");\n");
	}
      }
	    
    fprintf(mex,kernel_buffer);

    fprintf(mex,"\n");
    for(i=0;i<n_outputs;i++) 
      if(output_arr[i]->isderiv) { 
	if(output_arr[i+1]->size != (char *) 0) { 
	  fprintf(mex,"\tget_value(grad(%s),numel(%s),%s);\n",
		  output_arr[i+1]->name,
		  output_arr[i+1]->size,
		  output_arr[i+1]->name);
	  fprintf(mex,"\tget_grad(grad(%s),numel(%s),amg_num_independents,%s);\n",
		  output_arr[i+1]->name,
		  output_arr[i+1]->size,
		  output_arr[i]->name);
	}
	else { 

	  tmp = (char *) malloc( 1000 );
	  tmp = strcpy(tmp,output_arr[i+1]->dims[0]);
	  for(j=1;j<output_arr[i+1]->ndims;j++) { 
	    tmp = strcat(tmp," * ");
	    tmp = strcat(tmp,output_arr[i+1]->dims[j]);
	  }

	  fprintf(mex,"\tget_value(grad(%s),%s,%s);\n",
		  output_arr[i+1]->name,
		  tmp,
		  output_arr[i+1]->name);
	  fprintf(mex,"\tget_grad(grad(%s),%s,amg_num_independents,%s);\n",
		  output_arr[i+1]->name,
		  tmp,
		  output_arr[i]->name);
	  
	}
      }      
  
    fprintf(mex,"\n\tad_AD_Final();\n\n");
  }
  else { 
    fprintf(mex,kernel_buffer);
    fprintf(mex,"\n");
    for(i=0;i<n_outputs;i++) { 
      if(output_arr[i]->explicit_allocate) {
	fprintf(mex,"\tout[%d]->data = out_%d;\n",i,i+1);
	fprintf(mex,"\tcreate_explicit_array(out[%d],&plhs[%d]);\n\n",i,i);
      }
    }
  }

  fprintf(mex,"\n}\n");  

  fclose(mex);
}

char* mx_class(argument *ptr) { 
  char *tmp;

  tmp = (char *) malloc(sizeof(char) * 20);
 
  if(!strcmp(ptr->explicit_type,"double") )
    strcpy(tmp,"mxDOUBLE_CLASS");
  else  if(!strcmp(ptr->explicit_type,"float") )
    strcpy(tmp,"mxSINGLE_CLASS");
  else  if(!strcmp(ptr->explicit_type,"long") )
    strcpy(tmp,"mxINT64_CLASS");
  else  if(!strcmp(ptr->explicit_type,"int") )
    strcpy(tmp,"mxINT32_CLASS");
  else { 
    printf("Error: %s is unsupported type\n",ptr->explicit_type);
    exit(0);
  }
  
  return tmp;
}

void create_outputs() { 
  int i,j;
  char* class;
  
  int identical_size;
  int identical_type;
  
  // if(!all_double) 
    for(i=0;i<n_outputs;i++) {

      class = mx_class(output_arr[i]);

      // If data field of output objects are not going to be explicitly created
      if(!output_arr[i]->explicit_allocate) { 
	fprintf(mex,"\t%s* %s;\n",
		output_arr[i]->explicit_type,
		output_arr[i]->name);
      
	if(output_arr[i]->size == (char *)0) {
	  if(output_arr[i]->ndims == 2)
	    fprintf(mex,"\t%s = create_matrix_fast(&plhs[%d],%s,%s,%s,mxREAL);\n",
		    output_arr[i]->name,
		    output_arr[i]->rank-1,
		    output_arr[i]->dims[0],
		    output_arr[i]->dims[1],
		    class);
	  else { 
	    fprintf(mex,"\tamg_tmp = (int *) mxMalloc( sizeof(int) * %d) ;\n", 
		    output_arr[i]->ndims);
	    for(j=0;j<output_arr[i]->ndims;j++)
	      fprintf(mex,"\tamg_tmp[%d] = %s ;\n",j,output_arr[i]->dims[j]);
	    fprintf(mex,"\t%s = create_array_fast(&plhs[%d],%d,amg_tmp,%s,mxREAL);\n",
		    output_arr[i]->name,
		    output_arr[i]->rank-1,
		    output_arr[i]->ndims,
		    class);
	  }
	}
	else if(output_arr[i]->type == (char *) 0) 
	  fprintf(mex,"\t%s = create_identical_array_size_fast(%s%s,&plhs[%d],%s);\n",
		  output_arr[i]->name,
		  output_arr[i]->size,parpostfix,
		  output_arr[i]->rank-1,
		  class);
	else if(strcmp(output_arr[i]->size,output_arr[i]->type))
	  fprintf(mex,"\t%s = create_identical_array_size_fast(%s%s,&plhs[%d],%s);\n",
		  output_arr[i]->name,
		  output_arr[i]->size,parpostfix,
		  output_arr[i]->rank-1,
		  class);
	else
	  fprintf(mex,"\t%s = create_identical_array_fast(%s%s,&plhs[%d]);\n",
		  output_arr[i]->name,
		  output_arr[i]->size,parpostfix,
		  output_arr[i]->rank-1);
      }
      
      else {
	fprintf(mex,"\tout[%d] = (MatObj *) mxMalloc(sizeof(MatObj));\n",i);
	fprintf(mex,"\t%s* out_%d;\n",output_arr[i]->explicit_type,i+1);

	identical_size = output_arr[i]->size != (char *)0 ? search_input(output_arr[i]->size) : -1;
	identical_type = output_arr[i]->type != (char *)0 ? search_input(output_arr[i]->type) : -1;

	if(output_arr[i]->size == (char *) 0) {
	  fprintf(mex,"\tamg_tmp = (int *) mxMalloc( sizeof(int) * %d) ;\n", 
		  output_arr[i]->ndims);
	  for(j=0;j<output_arr[i]->ndims;j++)
	    fprintf(mex,"\tamg_tmp[%d] = %s ;\n",j,output_arr[i]->dims[j]);
	}

	fprintf(mex,"\tset_output_object(arg,%d,%d,amg_tmp,%d,%s,&out[%d]);\n",
		identical_size,
		output_arr[i]->ndims,
		identical_type,
		class,   
		i,
		i+1);
	
      }
      fprintf(mex,"\n");    
    }
     
      /*else
	for(i=0;i<n_outputs;i++) {
	
	if(strcmp(output_arr[i]->explicit_type,"double")) { 
	printf("Error: all types are supposed to be double\n");
	exit(1);
	}

	fprintf(mex,"\tdouble* %s;\n",output_arr[i]->name);

	if(output_arr[i]->size == (char *)0) {
	if(output_arr[i]->ndims == 2)
	fprintf(mex,"\t%s = create_matrix_fast(&plhs[%d],%s,%s);\n",
	output_arr[i]->name,
	output_arr[i]->rank-1,
		 output_arr[i]->dims[0],
		 output_arr[i]->dims[1]);
       else { 
	 fprintf(mex,"\t amg_tmp = (int *) * mxMalloc( sizeof(int) * %d) ;\n", 
		 output_arr[i]->ndims);
	 for(j=0;j<output_arr[i]->ndims;j++)
	   fprintf(mex,"\tamg_tmp[%d] = %s ;\n",j,output_arr[i]->dims[j]);
	 fprintf(mex,"\t%s = create_array_fast(&plhs[%d],%d,tmp);\n",
		 output_arr[i]->name,
		 output_arr[i]->rank-1,
		 output_arr[i]->ndims);
       }
     }
     else
       fprintf(mex,"\t%s = create_identical_array_fast(%s%s,&plhs[%d]);\n",
	       output_arr[i]->name,
	       output_arr[i]->size,parpostfix,
	       output_arr[i]->rank-1);
	       } */
}
