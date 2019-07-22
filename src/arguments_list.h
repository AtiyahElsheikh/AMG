/**********************************************************************************
**                                                                               **
**   AMG , Automatic Mex-file Generator                                          **
**         ^         ^        ^                                                  **
**                                                                               **
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

#include "argument.h"

/**
 * A data structure representing a list of arguments. Each argument has
 * diffent attributes @see argument.h
 * 
 */ 
struct arguments_list
{
  argument *arg;
  struct arguments_list *next;
};
typedef struct arguments_list arguments_list;

/** The list of input parameters */
arguments_list *inputs_list;
/** The list of output parameters */
arguments_list *outputs_list;

/** number of inputs */ 
int n_inputs;

/** number of outputs */
int n_outputs;

/** initialize the parameter lists */ 
void init_param();

/** 
 * add an output parameter to the outputs_list
 * @param name the name of the parameter
 */ 
void add_output(char* name);

/** 
 * add an input parameter to the inputs_list
 * @param name the name of the parameter
 */ 
void add_input(char* name);
