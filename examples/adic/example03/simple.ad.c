/************************** DISCLAIMER ********************************/
/*                                                                    */
/*   This file was generated on 08/01/05 13:16:48 by the version of   */
/*   ADIC compiled on  08/30/00 16:47:46                              */
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
void   ad_simple(DERIV_TYPE  *y,DERIV_TYPE  c,DERIV_TYPE  x) {
    double  ad_loc_0;
    {
        ad_loc_0 = DERIV_val(c) * DERIV_val(x);
        ad_grad_axpy_2(&(*y), DERIV_val(x), &(c), DERIV_val(c), &(x));
        DERIV_val(*y) = ad_loc_0;
    }
}
void   ad_AD_Init(int  arg0) {
    ad_AD_GradInit(arg0);

}
void   ad_AD_Final() {
    ad_AD_GradFinal();

}
