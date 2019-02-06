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

#include"lists.h"
#include "arguments_list.h"
#include "global_properties.h"

argument **input_arr;
argument **output_arr;

void init_array();
void display_outputs();
void display_inputs();
int search_input(char *s);
int search_output(char *s);
void set_active_size();

void set_default_name();
void set_default_type();
void set_default_size();

int set_identical_size(parameters_list *ind,int identical_index);  
int set_identical_type(parameters_list *ind,int identical_index);
int set_active_variables(parameters_list *ind);
int set_explicit_size(parameters_list *ind,dimensions_list *list);
int set_specific_type(parameters_list* ind,char* str);
int set_explicit_outputs(parameters_list* ind);

/**
 * For all identical variable names, thier sizes and types 
 * should be set to the size & type of the first input of 
 * the same size & type.
 */
void update_identical_parameters();

