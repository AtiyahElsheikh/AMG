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

/**
 * A data structure for a Matlab parameter's attributes.
 *
 */
struct argument
{ 
  char *name;     /**< The name of the parameter */
  int rank;       /**< its rank in the parameter list */

  /**
   * The name of the parameter of Identical size.
   *
   * Optionally set with the -size(<parameters_list>)=<input_parameter> & "-identical" flag \n
   * for an input parameters, it is for checking that size of both input parameters are identical \n
   * for an output parameters, it is for setting the size of an output parameter to the size of an input parameter
   */
  char* size;     
  
   int ndims;      /**< the number of dimensions, used by -size(*)={<explicit_setting>} flag */ 
  /**
   * The exact dimensions.
   *
   * Optionally set by the -size(*)={<explicit_setting>} flag 
   */
  char** dims;   

  /** 
   * The name of the parameter of Identical type.
   *
   * Optinally set with the "-type" flag\n
   * used in a similar way as the sie field
   */
  char* type;     

  /**
   * The exact type
   *
   * Optionally set by the -type(*)={<elementary_C_type>} flag 
   */
  char* explicit_type;

  /**
   * Boolean value representing whether the data field of the output parameter is explicitly allocated in "kernel" block.
   * 
   * Optionally enabeled by -explict(<outout_parameters>) flag
   */ 
  int explicit_allocate;
  
  /**
   * Boolean value representing whether the parameter is an active variable, ADIC-Context.
   *
   * Optionally enabelded by -active(<paramers-list>)
   */
  int isactive;

  /**
   * Boolean value representing whether the parameter is a derivative object, ADIC-Context.
   *
   * Optionally enabelded by -active(<paramers-list>)
   */
  int isderiv;
};

typedef struct argument argument;  

/**
 * Setting a default name for an input parameter, if not given
 */
void set_default_input_name(argument* p);

/**
 * Setting a default output name for an input parameter, if not given
 */
void set_default_output_name(argument* p);

/**
 * Setting a default type for the data field of an input parameter, double if not given
 */
void set_default_input_type(argument* p);

/**
 * Setting a default type for the data field of an output parameter, double if not given
 */
void set_default_output_type(argument* p);

/**
 * Setting a default type for the data field of an output parameter, nothing if not given
 */
void set_default_input_size(argument* p);

/**
 * Setting a default type for the data field of an output parameter, scalar if not given
 */
void set_default_output_size(argument* p);
