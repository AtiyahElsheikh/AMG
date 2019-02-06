/*************************************************************
 *    AMG version 0.0.3.1, Copyright (C) 2005 Atya El-Shekh ** 
 *                                                          **
 *    AMG is distributed under GNU General Public License   **
 ************************************************************/



	
#include <stdio.h>
#include <mex.h>
#include "amgmex.h"

/**
 * The input parameters. Given an input argument arg 
 * The fields of the input arguments can be accessed as follows :
 * size(arg)   : an array of integers representing the dimensions 
 * ndims(arg)  : the number of dimensions  
 * nrows(arg)  : the number of rows 
 * ncols(arg)  : the number of columns
 * numel(arg)  : the number of the elements 
 * class(arg)  : the type of the matrix object 
 *
 * for cell arrays, similar macros can be used to manipulate  	
 * the fields. 
 * celldata(arg) : a pointer to the data field of the cell array arg.
 * similarly:
 *  celldims, cellndims, cellnrows, cellncols, cellnelem, cellcalss 
 **/

#define  b_par   arg[0]
#define  c_par   arg[1]

int* amg_tmp;
void  mexFunction(int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[]) {

	MatObj** arg;
	void** out;

	arg = (MatObj **) mxMalloc( sizeof(MatObj *) * nrhs) ;

	for(int i=0;i < nrhs;i++)
		arg[i] = (MatObj *) mxMalloc( sizeof(MatObj) );

	for(int i=0;i<nrhs;i++)
		extract_all(prhs[i],arg[i]);

  
	double*           b =  arg[0]->data;
	double*           c =  arg[1]->data;
	int* amg_itmp;
	if(!has_equal_dims(b_par,c_par)) {
		printf("Error: b and c should have equal dimensions");
		exit(1);
	}

	out = (void **) mxMalloc( sizeof(void *) * nlhs);
	double* a;
	a = create_matrix_fast(&plhs[0],1,1,mxDOUBLE_CLASS,mxREAL);



}
