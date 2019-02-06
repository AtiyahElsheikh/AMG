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
  DERIV_TYPE*  x;
  DERIV_TYPE  sc;
  DERIV_TYPE*  y;
  int n=5;
  int i;

  ad_AD_Init(2);
  x = (DERIV_TYPE *) malloc( sizeof(DERIV_TYPE) * n);
  y = (DERIV_TYPE *) malloc( sizeof(DERIV_TYPE) * n);

  
  /** 
   * imagine that x is an intermidiate variable and 
   * there are two independent variables, say t1 and t2 
   */ 
  { 
    for(i=0;i<n;i++) 
      DERIV_val(x[i]) = 2.0/(i+1);
   
    /*
     * dx[i]/dt1 = (i+1)/3 
     * dx[i]/dt2 = (2*i+1)/3
     */
    for(i=0;i<n;i++) {   
      DERIV_grad(x[i])[0] = (i+1)/3.0;
      DERIV_grad(x[i])[1] = (2*i+1)/3.0;
      printf("x[%d] = %lf,g_x[%d](0) = %lf, g_x[%d](1) = %lf\n",i,
	     DERIV_val(x[i]),i,
	     DERIV_grad(x[i])[0],i,
	     DERIV_grad(x[i])[1]); 
    }
  }
 
  /*
   * Suppose that sc is just a scalar
   */
  {
    ad_grad_axpy_0(&(sc));
    DERIV_val(sc) = 3.333333333333333e-01;
  }
  
  ad_simple(y, sc, x, n);

  for(i=0;i<n;i++) {   
  
    printf("y[%d] = %lf,g_y[%d](0) = %lf, g_y[%d](1) = %lf\n",i,
	   DERIV_val(y[i]),i,
	   DERIV_grad(y[i])[0],i,
	   DERIV_grad(y[i])[1]); 
  }
  
  ad_AD_Final();
  
}
