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

#define  a_par   arg[0]
#define  arg_2_par   arg[1]
#define  c_par   arg[2]
#define  arg_4_par   arg[3]

int* amg_tmp;
void  mexFunction(int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[]) {

	MatObj** arg;
	MatObj** out;

	arg = (MatObj **) mxMalloc( sizeof(MatObj *) * nrhs) ;

	for(int i=0;i < nrhs;i++)
		arg[i] = (MatObj *) mxMalloc( sizeof(MatObj) );

	for(int i=0;i<nrhs;i++)
		extract_all(prhs[i],arg[i]);

  
	double*           a =  arg[0]->data;
	double*       arg_2 =  arg[1]->data;
	double*           c =  arg[2]->data;
	double*       arg_4 =  arg[3]->data;
	int* amg_itmp;
	if(!has_equal_dims(arg_4_par,a_par)) {
		printf("Error: arg_4 and a should have equal dimensions");
		exit(1);
	}

	if(!has_equal_type(arg_4_par,a_par)) {
		printf("Error: arg_4 and a should have equal dimenstions");
		exit(1);
	}
	out = (MatObj **) mxMalloc( sizeof(MatObj *) * nlhs);

	double* out_1;
	out_1 = create_identical_array_fast(a_par,&plhs[0]);

	double* out_2;
	out_2 = create_identical_array_size_fast(arg_4_par,&plhs[1],mxDOUBLE_CLASS);

	double* out_3;
	out_3 = create_identical_array_fast(c_par,&plhs[2]);



}
