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
 * A data structur representing a list of dimensions size of a 
 * certain parameter, set by the user using -size(*)={a,..,z}
 * where a,z are specific dimensions size e.g. nrows(x) or 5 
 */
struct dimensions_list { 
  /** The explicit size of a certain dimension*/
  char* str;
  /** The next dimension's size */
  struct dimensions_list *next;
};
typedef struct dimensions_list dimensions_list;

/**
 * specify the next dimension size of a certain parameter
 *
 * @param list the list of dimensions size of a parameter
 * @param str the fixed size of dimension d, where d = size(list)+1;
 */
void add_dimension(dimensions_list** list,char* str);

/**
 * The size of a dimension list.
 *
 * @param list the list to be quieried
 */
int  dimensions_list_size(dimensions_list* list);

/**
 * Deallocate the list.
 *
 * @param list a not need any more list
 */
void free_dimensions_list(dimensions_list** list);


/** the input parameter index to which the size of other variables will be set*/ 
int identical_index ;

/** the a list of parameter indeces, whose sizes are going to be set to be 
 * identical to the size of another list
 */
struct parameters_list { 
  int index;
  struct parameters_list *next; 
};
typedef struct parameters_list parameters_list;

/**
 * Deallocate the list.
 *
 * @param list a not need any more list
 */
void free_parameters_list(parameters_list **ind);
