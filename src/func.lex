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

%{
#include<stdio.h>
#include "func.tab.h"
#include "global_properties.h"

  char *reply = "=====>  ";
  int yywrap(void);
  int size_on;
  int equal_on;
  int nbrackets ; 
  int count_dim;
  int lineno;

%}

%x kernel
%x rank
%x kernel_rank
%x comment
%x explicit_size
%x header

ID  [a-zA-Z][a-zA-Z0-9_]*
RANK [1-9]|[1-9][0-9]
INT  [1-9][0-9]*
DIMS [^,}]*
SIZE -size
TYPE -type
VALID_TYPE double|float|long|int
KERNEL -kernel
IDENTICAL -identical
ADIC -adic
ACTIVE -active
EXPLICIT -explicit
HEADER_OPT -header
ANY  .  

%%

{VALID_TYPE} {
   printf("%s specifiying type %s\n",reply,yytext); 
   yylval = (int) yytext; 
   return VALID_TYPE; 
}

{ID}     { 
  printf("%s an ID               %s %s\n",reply,reply,yytext);        
  yylval = (int) yytext; 
  if(size_on && equal_on) { 
    size_on = 0;
    equal_on = 0;
  }
  return ID;
} 

<rank>{RANK}  { 
  printf("%s a rank              %s %d\n",reply,reply,atoi(yytext));  
  BEGIN(INITIAL);
  yylval = (int) yytext; 
  return RANK;
}
<rank>"\\n"|"\\t"|" " YY_FATAL_ERROR("A rank was expected\n");

{INT}    { 
  printf("%s an int              %s %d\n",reply,reply,atoi(yytext));  
  yylval = (int) yytext; 
  return INT;
}

{SIZE}   { 
  printf("%s setting size      ",reply);                     
  yylval = (int) yytext;
  size_on = 1;
  return SIZE; 
}

<explicit_size>{DIMS} { 
  count_dim++;
  printf("%s dim %d %s %s\n",reply,count_dim,reply,yytext);  
  yylval = (int) yytext;
  return DIMS; 
}

<explicit_size>"," { 
  yylval = (int) yytext;
  return ',';
}

<explicit_size>"}" {       
  printf("%s end   }      ",reply);
  yylval = (int) yytext;
  BEGIN(INITIAL);
  size_on = 0;
  equal_on = 0;
  count_dim = 0;
  return '}';
} 

{TYPE}   { 
  printf("%s setting type      ",reply);                     
  yylval = (int) yytext; 
  return TYPE; 
}

{IDENTICAL}  { 
  printf("%s setting size&type      ",reply);                     
  yylval = (int) yytext; 
  return IDENTICAL;
}

{EXPLICIT} {
  printf("%s setting explicit      ",reply);                     
  yylval = (int) yytext; 
  return EXPLICIT;
}

{ADIC} { 
  printf("%s aidc on       %s\n",reply,yytext); 
  yylval = (int) yytext;  
  return ADIC;
}

{ACTIVE} { 
  printf("%s aidc on       %s\n",reply,yytext); 
  yylval = (int) yytext;  
  return ACTIVE;
}

{KERNEL} { 
  printf("%s setting kernel %s\n",reply,yytext); 
  yylval = (int) yytext; 
  BEGIN(kernel); 
  return KERNEL;
}
{HEADER_OPT} { 
  printf("%s setting initial %s\n",reply,yytext); 
  yylval = (int) yytext; 
  BEGIN(header); 
  return HEADER_SEC;
}
"("      printf("%s argument list       %s ( \n",reply,reply);               yylval = (int) yytext; return '(';
")"      printf("%s argument list end   %s ) \n",reply,reply);               yylval = (int) yytext; return ')';
"["      printf("%s output list         %s [ \n",reply,reply);               yylval = (int) yytext; return '[';
"]"      printf("%s output list end     %s ] \n",reply,reply);               yylval = (int) yytext; return ']';
","      printf("%s another ID coming   %s , \n",reply,reply);               yylval = (int) yytext; return ',';
"="      { 
  printf("%s =                   ",reply);
  yylval = (int) yytext; 
  if(size_on)
    equal_on = 1;
  return '=';
}

"$"      { 
  printf("%s an input  rank      ",reply);                            
  BEGIN(rank);
  yylval = (int) yytext; 
  return '$';
}  
"@"      { 
  printf("%s an output rank      ",reply);                            
  BEGIN(rank);
  yylval = (int) yytext; 
  return '@';
}

"{" { 
  printf("%s start {      ",reply);
  yylval = (int) yytext; 
  if(size_on && equal_on)
    BEGIN(explicit_size);
  return '{';
}

"}" {       
  printf("%s end   }      ",reply);
  yylval = (int) yytext; 
  return '}';
}

"--display_input"  display_input = 1;
"--info_param"     info_param    = 1;
"--all_double"     all_double    = 1;

"\n"     ++lineno;
"\t"|" "
"%*"     BEGIN(comment);
<comment>[^*\n]* ;
<comment>"\n" ++lineno; 
<comment>"*"[^%*]* ;
<comment>"*"+"%"  BEGIN(INITIAL);
<kernel>"{" { 
  nbrackets++ ; 
  yylval = (int) yytext;
  if(nbrackets == 1)
    return '{';
  return ANY ;
}
<kernel>"}" {
  nbrackets-- ; 
  yylval = (int) yytext;
  if(nbrackets == 0) {
    BEGIN(INITIAL); 
    return '}';
  }
  else 
    return ANY;
} 
<kernel>"$"      yylval = (int) yytext; BEGIN(kernel_rank); return '$';
<kernel>"@"      yylval = (int) yytext; BEGIN(kernel_rank); return '@';
<kernel_rank>{RANK}     yylval = (int) yytext; BEGIN(kernel); return RANK;
<kernel_rank>"\n"|"\t"|" " YY_FATAL_ERROR("A rank was expected\n");
<kernel>" "|"\t" ;
<kernel>"\n"    ++lineno; yylval= (int) yytext; return ANY;
<kernel>[^{}$@\n]*   yylval = (int) yytext; return ANY;

<header>"{" { 
  nbrackets++ ; 
  yylval = (int) yytext;
  if(nbrackets == 1)
    return '{';
  return ANY ;
}
<header>"}" {
  nbrackets-- ; 
  yylval = (int) yytext;
  if(nbrackets == 0) {
    BEGIN(INITIAL); 
    return '}';
  }
  else 
    return ANY;
} 
<header>"\n"    ++lineno; yylval= (int) yytext; return ANY;
<header>" "|"\t" ;
<header>[^{}\n]*   yylval = (int) yytext; return ANY;

<<EOF>> printf("%s bye\n",reply);return 0;
.    if (yytext[0]==0) return 0; else printf("%s unmatched %s (ascii-code of first char: %d)\n",reply,yytext, yytext[0]);

%%

int yywrap(void) { 
  return 1;
}

/*
main(int argc, char* argv[]) { 
  //{WORD}   printf("%s a Word %s",reply,yytext);
  yylval = (int) yytext; return WORD; 
  ++argv,--argc ; 
  if(argc > 0)
    yyin = fopen(argv[0],"r");
  else
    yyin = stdin;
  
  yylex();
}
*/
