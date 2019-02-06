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

#define  arg_1_par   arg[0]
#define  arg_2_par   arg[1]

#define  out_1_par   out[0]
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

  
	double*       arg_1 =  arg[0]->data;
	double*       arg_2 =  arg[1]->data;
	int* amg_itmp;

	out = (MatObj **) mxMalloc( sizeof(MatObj *) * nlhs);

	out[0] = (MatObj *) mxMalloc(sizeof(MatObj));
	double* out_1;
	amg_tmp = (int *) mxMalloc( sizeof(int) * 2) ;
	amg_tmp[0] = 1 ;
	amg_tmp[1] = 1 ;
	set_output_object(arg,-1,2,amg_tmp,-1,mxDOUBLE_CLASS,&out[0]);


	int i;
	if( numel(arg_1) > numel(arg_2)) {
		nrows(out_1) = nrows(arg_1);
		ncols(out_1) = ncols(arg_1);
		out_1 = (double *) mxMalloc(numel(arg_1) * sizeof(double));	
		for(i=0;i<numel(arg_1);i++)
			out_1[i] = arg_1[i];
        }
	else {
		nrows(out_1) = nrows(arg_2);
		ncols(out_1) = ncols(arg_2);
		out_1 = (double *) mxMalloc(numel(arg_2) * sizeof(double));	
		for(i=0;i<numel(arg_2);i++)
			out_1[i] = arg_2[i];
        }

	out[0]->data = out_1;
	create_explicit_array(out[0],&plhs[0]);


}
