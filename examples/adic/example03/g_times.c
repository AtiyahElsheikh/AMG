/*************************************************************
 *	AMG version 0.0.2, Copyright (C) 2005 Atya El-Shekh ** 
 *                                                          **
 *	AMG is distributed under GNU General Public License **
 ************************************************************/



	
#include<stdio.h>
#include<mex.h>
#include"mymex-ad-double.h"

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


/**
 * Macros to handle derivative objects of Type DERIV_TYPE:
 *
 * 	deriv(X,Y) : set a DERIV_TYPE objects whose values are X
 *                   and gradients are Y 
 *                   DERIV_val(deriv(X,Y)) = X
 * 		     DERIV_grad(deriv(X,Y)) = Y 
 *	grad(X)    : refers to the corresponding DERIV_TYPE object
 *                   of the parameter X. 	
 *                   if X is an active variable then
 *                   grad(X) = deriv(X,Y) 
 * 
 * Some useful routines when dealing with adic:
 * 	DERIV_TYPE* set_deriv_type(MatObj x, MatObj g_x): 
 *         set the values and the derivative of a matrix objects.
 *      get_val(DERIV_TYPE* x,int nx, double *val): 
 *	   get the values of an array of DERIV_TYPE into an array 
 *         of double 
 *      get_grad(DERIV_TYPE* x,int nx, int ngrad, double *grad)
 *         get the gradients of an array of DERIV_TYPE and store 
 *	   them into an array (ADiMAT format)   
 *             
 **/

#define  g_c_par   arg[0]
#define  c_par   arg[1]
#define  g_x_par   arg[2]
#define  x_par   arg[3]

int amg_num_independents;
void  mexFunction(int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[]) {

	MatObj** arg;
	void** out;

	arg = (MatObj **) mxMalloc( sizeof(MatObj *) * nrhs) ;

	for(int i=0;i < nrhs;i++)
		arg[i] = (MatObj *) mxMalloc( sizeof(MatObj) );

	for(int i=0;i<nrhs;i++)
		extract_all(prhs[i],arg[i]);

  
	amg_num_independents = numel(g_c) / numel(c);

	double*         g_c =  arg[0]->data;
	double*           c =  arg[1]->data;
	double*         g_x =  arg[2]->data;
	double*           x =  arg[3]->data;
	int* amg_itmp;
	amg_itmp = (int *) malloc(sizeof(int) * 2);
	amg_itmp[0] = numel(c) * amg_num_independents;
	amg_itmp[1] = 1;
	if(!has_equal_size(g_c_par,amg_itmp,2))
		printf("??? Error: argument 1 is not of admissible size\n");
	amg_itmp = (int *) malloc(sizeof(int) * 2);
	amg_itmp[0] = numel(x) * amg_num_independents;
	amg_itmp[1] = 1;
	if(!has_equal_size(g_x_par,amg_itmp,2))
		printf("??? Error: argument 3 is not of admissible size\n");


	out = (void **) mxMalloc( sizeof(void *) * nlhs);
	double* g_y;
	g_y = create_matrix_fast(&plhs[0],1 * 1 * amg_num_independents,1);
	double* y;
	y = create_matrix_fast(&plhs[1],1,1);

	ad_AD_Init(amg_num_independents);

	DERIV_TYPE* grad(c) = deriv(c,g_c);
	DERIV_TYPE* grad(x) = deriv(x,g_x);

	DERIV_TYPE* grad(y) =
		 (DERIV_TYPE *) mxMalloc( sizeof(DERIV_TYPE) * 1 * 1);
 
	ad_simple(grad(y),*grad(c),*grad(x));

	get_value(grad(y),1 * 1,y);
	get_grad(grad(y),1 * 1,amg_num_independents,g_y);

	ad_AD_Final();


}
