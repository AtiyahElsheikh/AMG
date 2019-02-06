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

#include "lists.h"

/**
 * specify the next dimension size of a certain parameter
 *
 * @param list the list of dimensions size of a parameter
 * @param str the fixed size of dimension d, where d = size(list)+1;
 */
void add_dimension(dimensions_list** list,char* str) { 
  dimensions_list* ptr;
  char *tmp;

  ptr = (dimensions_list *) malloc(sizeof(dimensions_list));
  tmp = (char *) malloc(1000);
  tmp = strcpy(tmp,str);
  ptr->str = tmp;
  ptr->next = *list;
  *list = ptr;
    
}

/**
 * The size of a dimension list.
 *
 * @param list the list to be quieried
 */
int dimensions_list_size(dimensions_list* list) { 
  dimensions_list* ptr;
  int ans = 0;
  ptr = list;

  while(ptr != (dimensions_list *) 0) { 
    ans++;
    ptr = ptr->next;
  }

  return ans;
}

/**
 * Deallocate the list.
 *
 * @param list a not need any more list
 */  
void free_dimensions_list(dimensions_list** list) { 
  dimensions_list* ptr;

  ptr = *list;
  while(ptr != (dimensions_list *) 0) { 
    ptr = ptr->next;
    free((*list)->str);
    free(*list);
    *list = ptr;
  }

  *list = (dimensions_list *) 0;
}

/**
 * Deallocate the list.
 *
 * @param list a not need any more list
 */
void free_parameters_list(parameters_list **ind) { 

  parameters_list *ptr;

  ptr=*ind; 
  while(ptr != (parameters_list *) 0) { 
    ptr = ptr->next ;
    free(*ind);
    *ind = ptr;
  }
  *ind = (parameters_list *) 0;

}
