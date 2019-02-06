/************************** DISCLAIMER ********************************/
/*                                                                    */
/*   This file was generated on 07/04/05 09:25:45 by the version of   */
/*   ADIC compiled on  08/30/00 18:09:53                              */
/*                                                                    */
/*   ADIC was prepared as an account of work sponsored by an          */
/*   agency of the United States Government and the University of     */
/*   Chicago.  NEITHER THE AUTHOR(S), THE UNITED STATES GOVERNMENT    */
/*   NOR ANY AGENCY THEREOF, NOR THE UNIVERSITY OF CHICAGO, INCLUDING */
/*   ANY OF THEIR EMPLOYEES OR OFFICERS, MAKES ANY WARRANTY, EXPRESS  */
/*   OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR */
/*   THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY INFORMATION OR  */
/*   PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE */
/*   PRIVATELY OWNED RIGHTS.                                          */
/*                                                                    */
/**********************************************************************/
#include "ad_deriv.h"
#include <stdio.h>
int  main(char  *argv[]) {
DERIV_TYPE  x;
DERIV_TYPE  sc;
DERIV_TYPE  y;

 ad_AD_Init(2);

 /** 
  * imagine that x is an intermidiate variable and 
  * there are two independent variables, say t1 and t2 
  */ 
 {
   DERIV_val(x) = 2.0;
   /*
   * dx/dt1 = 1/3 , dx/dt2 = 2/3
   */
   DERIV_grad(x)[0] = 1.0/3;
   DERIV_grad(x)[1] = 2.0/3;
 }
 
 /*
  * Suppose that sc is just a scalar
  */
 {
   ad_grad_axpy_0(&(sc));
   DERIV_val(sc) = 3.333333333333333e-01;
 }

 printf("x       = %lf\n",DERIV_val(x));
 printf("g_x(0)  = %lf\n",DERIV_grad(x)[0]);
 printf("g_x(1)  = %lf\n",DERIV_grad(x)[1]);
 printf("sc      = %lf\n",DERIV_val(sc));
 printf("g_sc(0) = %lf\n",DERIV_grad(sc)[0]);
 printf("g_sc(1) = %lf\n",DERIV_grad(sc)[1]);
 
 ad_simple( &y, sc, x);
 printf("y = %lf\n", DERIV_val(y));
 printf("g_y[0] = %lf\n", DERIV_grad(y)[0]);
 printf("g_y[1] = %lf\n", DERIV_grad(y)[1]);

 ad_AD_Final();

}
