/********************************************************************************** 
**                                                                               **
**   AMG , Automatic Mex-file Generator                                          **
**         ^         ^        ^                                                  **
**	                                                                             **
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

/* The maximum length of an argument name */
#define MAX_LEN 100

/* Whether adic is on*/ 
int adic_on;

// whether the info. of parameter should be printed after parsing
int info_param;

// whether the generated gateway should display the input arguments
int display_input;

// whether all arguments are of type double
int all_double   ;

// the name of the function (parser,generator)
char* fname;

// prefixes of input and output objects in the gateway routine
extern char* default_input_name;
extern char* default_output_name;

// The object and its data field
extern char* parpostfix;

// The buffer that stores the kernel code 
extern char *kernel_buffer ;

// The buffer that stores the header code
extern char *header_buffer;

