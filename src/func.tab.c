/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     RANK = 259,
     INT = 260,
     SIZE = 261,
     TYPE = 262,
     VALID_TYPE = 263,
     IDENTICAL = 264,
     EXPLICIT = 265,
     ADIC = 266,
     ACTIVE = 267,
     KERNEL = 268,
     DIMS = 269,
     ANY = 270,
     HEADER_SEC = 271
   };
#endif
#define ID 258
#define RANK 259
#define INT 260
#define SIZE 261
#define TYPE 262
#define VALID_TYPE 263
#define IDENTICAL 264
#define EXPLICIT 265
#define ADIC 266
#define ACTIVE 267
#define KERNEL 268
#define DIMS 269
#define ANY 270
#define HEADER_SEC 271




/* Copy the first part of user declarations.  */
#line 30 "func.y"

  #include <stdio.h>
  #include <string.h>
  #include "functions.h"
  #define YYSTYPE char* 
  
  int yylex(void);
  void yyerror(char const *s);

  void generate_mex(void);
  extern int lineno;
  extern int nbrackets;
  
  /* temporary char for setting name for vars*/
  char* tmp;
  char* type;
  
  /* the input argument index to which the size of other variables will be set*/ 
  int identical_index ;

  // initial buffer size, is increased when needed
  int buffer_size=1000;
  // The buffer that stores the kernel code 
  char *kernel_buffer ;

  // One nullbyte is required.
  int header_size=0;
  int header_cap= 1;
  // The buffer that stores the initial code
  char *header_buffer;
  
  parameters_list *ind;
  parameters_list *ptr;

  dimensions_list *dimensions;

  // loop indeces 
  int i,j;
  int len;
  


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 161 "func.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   96

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  36
/* YYNRULES -- Number of rules. */
#define YYNRULES  66
/* YYNRULES -- Number of states. */
#define YYNSTATES  119

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   271

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,    24,     2,     2,     2,
      18,    19,     2,     2,    22,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    17,     2,     2,    23,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    20,     2,    21,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     7,     8,    11,    13,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    37,    39,    41,    45,
      47,    49,    53,    57,    59,    61,    63,    67,    71,    74,
      77,    79,    84,    86,    88,    97,   101,   103,   105,   112,
     114,   116,   125,   127,   134,   141,   145,   147,   149,   152,
     155,   157,   160,   165,   169,   171,   173,   176,   181,   184,
     186,   189,   192,   194,   199,   202,   204
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      28,     0,    -1,    29,    32,    30,    -1,    -1,    30,    31,
      -1,    31,    -1,    -1,    41,    -1,    50,    -1,    46,    -1,
      54,    -1,    39,    -1,    40,    -1,    60,    -1,    57,    -1,
      33,    17,    35,    18,    36,    19,    -1,     3,    -1,    37,
      -1,    20,    34,    21,    -1,     3,    -1,    37,    -1,    34,
      22,     3,    -1,    34,    22,    37,    -1,     3,    -1,     3,
      -1,    38,    -1,    36,    22,     3,    -1,    36,    22,    38,
      -1,    23,     4,    -1,    24,     4,    -1,    11,    -1,    12,
      18,    51,    19,    -1,    42,    -1,    45,    -1,     6,    18,
      51,    19,    17,    25,    43,    26,    -1,    43,    22,    44,
      -1,    44,    -1,    14,    -1,     6,    18,    51,    19,    17,
      53,    -1,    47,    -1,    49,    -1,     7,    18,    51,    19,
      17,    25,    48,    26,    -1,     8,    -1,     7,    18,    51,
      19,    17,    53,    -1,     9,    18,    51,    19,    17,    53,
      -1,    51,    22,    52,    -1,    52,    -1,     3,    -1,    24,
       4,    -1,    23,     4,    -1,     3,    -1,    24,     4,    -1,
      10,    18,    55,    19,    -1,    55,    22,    56,    -1,    56,
      -1,     3,    -1,    23,     4,    -1,    13,    25,    58,    26,
      -1,    58,    59,    -1,    59,    -1,    24,     4,    -1,    23,
       4,    -1,    15,    -1,    16,    25,    61,    26,    -1,    61,
      62,    -1,    62,    -1,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   100,   100,   104,   115,   116,   117,   121,   122,   123,
     124,   125,   126,   127,   128,   132,   153,   157,   158,   162,
     163,   164,   165,   168,   176,   177,   178,   179,   183,   193,
     204,   214,   224,   224,   228,   238,   238,   242,   248,   258,
     258,   262,   272,   279,   289,   302,   302,   306,   325,   335,
     348,   354,   363,   370,   370,   374,   386,   400,   405,   405,
     409,   416,   423,   434,   439,   439,   443
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "RANK", "INT", "SIZE", "TYPE",
  "VALID_TYPE", "IDENTICAL", "EXPLICIT", "ADIC", "ACTIVE", "KERNEL",
  "DIMS", "ANY", "HEADER_SEC", "'='", "'('", "')'", "'['", "']'", "','",
  "'@'", "'$'", "'{'", "'}'", "$accept", "line", "init", "amg_arguments",
  "amg_argument", "function_call", "output_list", "outputs", "func_ID",
  "inputs", "output_rank", "input_rank", "adic_argument",
  "active_argument", "size_argument", "explicit_size_argument",
  "dimensions_list", "dimension_arg", "implicit_size_argument",
  "type_argument", "specific_type", "valid_type", "generic_type",
  "identical_argument", "arguments", "argument", "input_argument",
  "explicit_argument", "out_arguments", "output_argument",
  "kernel_argument", "stmts", "stm", "header_argument", "init_stmts",
  "init_stm", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,    61,    40,    41,
      91,    93,    44,    64,    36,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    27,    28,    29,    30,    30,    30,    31,    31,    31,
      31,    31,    31,    31,    31,    32,    33,    33,    33,    34,
      34,    34,    34,    35,    36,    36,    36,    36,    37,    38,
      39,    40,    41,    41,    42,    43,    43,    44,    45,    46,
      46,    47,    48,    49,    50,    51,    51,    52,    52,    52,
      53,    53,    54,    55,    55,    56,    56,    57,    58,    58,
      59,    59,    59,    60,    61,    61,    62
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     3,     0,     2,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     6,     1,     1,     3,     1,
       1,     3,     3,     1,     1,     1,     3,     3,     2,     2,
       1,     4,     1,     1,     8,     3,     1,     1,     6,     1,
       1,     8,     1,     6,     6,     3,     1,     1,     2,     2,
       1,     2,     4,     3,     1,     1,     2,     4,     2,     1,
       2,     2,     1,     4,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       3,     0,     0,     1,    16,     0,     0,     6,     0,    17,
      19,     0,    20,    28,     0,     0,     0,     0,    30,     0,
       0,     0,     2,     5,    11,    12,     7,    32,    33,     9,
      39,    40,     8,    10,    14,    13,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     4,    23,     0,    21,
      22,    47,     0,     0,     0,    46,     0,     0,    55,     0,
       0,    54,     0,    62,     0,     0,     0,    59,    66,     0,
      65,     0,    49,    48,     0,     0,     0,     0,    56,    52,
       0,    31,    61,    60,    57,    58,    63,    64,    24,     0,
       0,    25,     0,    45,     0,     0,    53,    29,    15,     0,
      50,     0,     0,    38,     0,    43,    44,    26,    27,    51,
      37,     0,    36,    42,     0,     0,    34,    41,    35
};

/* YYDEFGOTO[NTERM-NUM]. */
static const yysigned_char yydefgoto[] =
{
      -1,     1,     2,    22,    23,     7,     8,    11,    48,    90,
       9,    91,    24,    25,    26,    27,   111,   112,    28,    29,
      30,   114,    31,    32,    54,    55,   103,    33,    60,    61,
      34,    66,    67,    35,    69,    70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -44
static const yysigned_char yypact[] =
{
     -44,    21,    11,   -44,   -44,     9,    15,    33,    36,   -44,
     -44,   -17,   -44,   -44,    47,    50,    51,    52,   -44,    53,
      48,    49,    33,   -44,   -44,   -44,   -44,   -44,   -44,   -44,
     -44,   -44,   -44,   -44,   -44,   -44,    69,   -44,    12,     3,
       3,     3,    13,     3,    32,    60,   -44,   -44,    58,   -44,
     -44,   -44,    73,    74,    19,   -44,    38,    39,   -44,    75,
      40,   -44,    44,   -44,    76,    77,   -13,   -44,   -44,    22,
     -44,     4,   -44,   -44,    65,     3,    66,    67,   -44,   -44,
      13,   -44,   -44,   -44,   -44,   -44,   -44,   -44,   -44,    81,
      45,   -44,    -2,   -44,     0,     5,   -44,   -44,   -44,     6,
     -44,    82,    78,   -44,    79,   -44,   -44,   -44,   -44,   -44,
     -44,    28,   -44,   -44,    62,    78,   -44,   -44,   -44
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -44,   -44,   -44,   -44,    68,   -44,   -44,   -44,   -44,   -44,
      -5,   -10,   -44,   -44,   -44,   -44,   -44,   -24,   -44,   -44,
     -44,   -44,   -44,   -44,   -23,    18,   -43,   -44,   -44,    14,
     -44,   -44,    29,   -44,   -44,    27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      12,   100,    63,   100,    37,    38,    51,    88,   100,   107,
      64,    65,    10,    84,     4,    49,    58,    56,    57,    13,
      62,     3,   101,   102,   101,   104,    52,    53,    89,   101,
      89,     5,     6,    50,     6,     6,    59,    68,    74,    14,
      15,    75,    16,    17,    18,    19,    20,    63,    86,    21,
     115,   105,   106,    36,   116,    64,    65,    76,    77,    79,
      75,    75,    80,    81,    98,    39,    75,    99,    40,    41,
      42,    43,    47,    44,    45,    68,    71,    72,    73,    78,
      82,    83,    92,    94,    95,    97,   109,   113,   117,   108,
      46,   118,   110,    93,    96,    85,    87
};

static const unsigned char yycheck[] =
{
       5,     3,    15,     3,    21,    22,     3,     3,     3,     3,
      23,    24,     3,    26,     3,     3,     3,    40,    41,     4,
      43,     0,    24,    25,    24,    25,    23,    24,    24,    24,
      24,    20,    23,    38,    23,    23,    23,    15,    19,     6,
       7,    22,     9,    10,    11,    12,    13,    15,    26,    16,
      22,    94,    95,    17,    26,    23,    24,    19,    19,    19,
      22,    22,    22,    19,    19,    18,    22,    22,    18,    18,
      18,    18,     3,    25,    25,    15,    18,     4,     4,     4,
       4,     4,    17,    17,    17,     4,     4,     8,    26,    99,
      22,   115,    14,    75,    80,    66,    69
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    28,    29,     0,     3,    20,    23,    32,    33,    37,
       3,    34,    37,     4,     6,     7,     9,    10,    11,    12,
      13,    16,    30,    31,    39,    40,    41,    42,    45,    46,
      47,    49,    50,    54,    57,    60,    17,    21,    22,    18,
      18,    18,    18,    18,    25,    25,    31,     3,    35,     3,
      37,     3,    23,    24,    51,    52,    51,    51,     3,    23,
      55,    56,    51,    15,    23,    24,    58,    59,    15,    61,
      62,    18,     4,     4,    19,    22,    19,    19,     4,    19,
      22,    19,     4,     4,    26,    59,    26,    62,     3,    24,
      36,    38,    17,    52,    17,    17,    56,     4,    19,    22,
       3,    24,    25,    53,    25,    53,    53,     3,    38,     4,
      14,    43,    44,     8,    48,    22,    26,    26,    44
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;


  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 104 "func.y"
    {
  printf("\n\n\tparsing a matlab function prototype\n");
  printf("\t===================================\n\n");
  nbrackets= 0;
  kernel_buffer = (char *) malloc(sizeof(char)*buffer_size); 
  kernel_buffer[0] = '\0'; // Identical to:  kernel_buffer = strcpy(kernel_buffer,""); , but faster!
  header_buffer = (char *) malloc(sizeof(char)*header_cap); 
  header_buffer[0] = '\0'; 
;}
    break;

  case 15:
#line 132 "func.y"
    { 
  
  /* restore input and output arguments into seperates arrays 
   * (to ease accessing) input_arr & output_arr will be constructed 
   */
  init_array();
  
  update_identical_parameters();

  // setting default names for unnamed output arguments
  for(j=0; j<n_outputs; j++) 
    if(!strcmp(output_arr[j]->name,""))
      set_default_output_name(output_arr[j]);
  // default outputs type are double 
    
  ind = (parameters_list *) 0; 
  dimensions = (dimensions_list *) 0;  
;}
    break;

  case 16:
#line 153 "func.y"
    { 
  n_outputs++; 
  add_output(yyvsp[0]); // add the ID to the output_list
;}
    break;

  case 19:
#line 162 "func.y"
    { n_outputs++; add_output(yyvsp[0]);;}
    break;

  case 21:
#line 164 "func.y"
    { n_outputs++; add_output(yyvsp[0]);;}
    break;

  case 23:
#line 168 "func.y"
    { 
  /* store the name of the function into fname */ 
  fname = (char *) malloc(strlen(yyvsp[0])+1); 
  strcpy(fname,yyvsp[0]); 
;}
    break;

  case 24:
#line 176 "func.y"
    { n_inputs++ ; add_input(yyvsp[0]);;}
    break;

  case 26:
#line 178 "func.y"
    { n_inputs++ ; add_input(yyvsp[0]); ;}
    break;

  case 28:
#line 183 "func.y"
    { 
  n_outputs++; 
  /* ensures that the rank is correct */
  if(n_outputs != atoi(yyvsp[0])) 
    { yyerror("wrong output rank\n"); exit(1); }
  add_output("");
 ;}
    break;

  case 29:
#line 194 "func.y"
    { 
  n_inputs++; 
  /* ensures that the rank of the input parameter is correct */ 
  if(n_inputs != atoi(yyvsp[0])) 
    { yyerror("wrong input rank\n"); exit(1); }
  add_input("");
;}
    break;

  case 30:
#line 204 "func.y"
    { 
  if(adic_on) { 
    yyerror("adic argument set twice\n");
    exit(1);
  }
  adic_on = 1;
;}
    break;

  case 31:
#line 214 "func.y"
    { 
  
  if( set_active_variables(ind))
    YYABORT;
  
  free_parameters_list(&ind);
;}
    break;

  case 34:
#line 228 "func.y"
    {
  if(set_explicit_size(ind,dimensions))
    YYABORT;

  free_parameters_list(&ind);
  free_dimensions_list(&dimensions);  
;}
    break;

  case 37:
#line 242 "func.y"
    { 
  add_dimension(&dimensions,yyvsp[0]);
;}
    break;

  case 38:
#line 248 "func.y"
    { 

  if (set_identical_size(ind,identical_index))
    YYABORT;

  free_parameters_list(&ind);
;}
    break;

  case 41:
#line 262 "func.y"
    { 
  printf("type = %s\n",type);
  if(set_specific_type(ind,type))
    YYABORT;

  free_parameters_list(&ind);
;}
    break;

  case 42:
#line 272 "func.y"
    { 
  type = (char *) malloc(strlen(yyvsp[0])+1);
  type = strcpy(type,yyvsp[0]);
;}
    break;

  case 43:
#line 279 "func.y"
    { 

  if (set_identical_type(ind,identical_index))
    YYABORT;

  free_parameters_list(&ind);
;}
    break;

  case 44:
#line 289 "func.y"
    { 
 
  if (set_identical_type(ind,identical_index))
    YYABORT;
  
  if (set_identical_size(ind,identical_index))
    YYABORT;

  free_parameters_list(&ind);
;}
    break;

  case 47:
#line 306 "func.y"
    { 
  ptr = (parameters_list *) malloc(sizeof(parameters_list)); 

  /* ensure that it is really an input or output parameter */
  ptr->index = search_input(yyvsp[0]);
  if(ptr->index < 0) { // if it is not an input parameter
    ptr->index = search_output(yyvsp[0]); // it should be an output parameter then
    if(ptr->index < 0)
      { printf("unknown argument : %s ", yyvsp[0]); yyerror("\n"); YYABORT;}
    /*  output parameter indeces should be distinguished from the input one*/
    ptr->index = ptr->index - n_outputs;
  }
  else 
    if(search_output(yyvsp[0]) >= 0) // what if both are input and output parameter
      {  printf("Conflict: argument is both input and output : %s ", yyvsp[0]); }//yyerror("\n"); exit(1);}
  
  ptr->next = ind;
  ind = ptr;
;}
    break;

  case 48:
#line 325 "func.y"
    { 
  // ensure that the rank inside the addmissible range
   ptr = (parameters_list *) malloc(sizeof(parameters_list)); 
   ptr->index = atoi(yyvsp[0]) - 1;
   if( (ptr->index < 0) || (ptr->index  > n_inputs)) 
     { printf("illagal rank : @%d ", ptr->index); yyerror("\n"); YYABORT;}
   ptr->next = ind;
   ind = ptr;
     
;}
    break;

  case 49:
#line 335 "func.y"
    { 
  // ensure that the rank inside the addmissible range
   ptr = (parameters_list *) malloc(sizeof(parameters_list)); 
   ptr->index = atoi(yyvsp[0]) - 1;
   if( (ptr->index < 0) || (ptr->index  > n_outputs-1))
     { printf("illagal rank : @%d ", ptr->index + 1); yyerror("\n"); YYABORT;}
   ptr->index -= n_outputs;
   ptr->next = ind;
   ind = ptr;
;}
    break;

  case 50:
#line 348 "func.y"
    { 
  // ensures that the given parameter name exists 
  identical_index = search_input(yyvsp[0]);
  if( identical_index < 0)
     { printf("unknown size argument : %s ",yyvsp[0]); yyerror("\n"); exit(1); }
;}
    break;

  case 51:
#line 354 "func.y"
    { 
  // ensure that the rank is inside the addmissible range
  identical_index = atoi(yyvsp[0])-1;
  if( (identical_index < 0) || (ptr->index  > n_inputs-1)) { 
    printf("non admissible input rank : $%d",identical_index + 1); yyerror("\n"); exit(1); 
  }
;}
    break;

  case 52:
#line 363 "func.y"
    { 
  if( set_explicit_outputs(ind))
    YYABORT;
  free_parameters_list(&ind);
;}
    break;

  case 55:
#line 374 "func.y"
    { 
  ptr = (parameters_list *) malloc(sizeof(parameters_list)); 

  // ensures that the given parameter name exists 
  ptr->index = search_output(yyvsp[0]);
  if(ptr->index < 0) { 
    printf("unknown explicit argument : %s ",yyvsp[0]); yyerror("\n"); exit(1); 
  }
  
  ptr->next = ind;
  ind = ptr;
;}
    break;

  case 56:
#line 386 "func.y"
    { 
  ptr = (parameters_list *) malloc(sizeof(parameters_list)); 

  // ensure that the rank is inside the addmissible range
  ptr->index = atoi(yyvsp[0])-1;
  if( (ptr->index < 0) || (ptr->index  > n_outputs-1) ) { 
    printf("non admissible output rank : @%d ",identical_index); yyerror("\n"); exit(1); 
  }
  
  ptr->next = ind;
  ind = ptr;
;}
    break;

  case 57:
#line 400 "func.y"
    { 
  printf("kernel : \n%s\n",kernel_buffer);  
;}
    break;

  case 60:
#line 409 "func.y"
    { 
  if( strlen(kernel_buffer) > buffer_size-3) {
    buffer_size += 1000;
    kernel_buffer= (char *) realloc(kernel_buffer, sizeof(char)*buffer_size);
  }
  kernel_buffer = strcat(kernel_buffer,input_arr[atoi(yyvsp[0])-1]->name); 
;}
    break;

  case 61:
#line 416 "func.y"
    { 
  if( strlen(kernel_buffer) > buffer_size-3) {
    buffer_size += 1000;
    kernel_buffer= (char *)realloc(kernel_buffer,sizeof(char)*buffer_size);
  }
  kernel_buffer = strcat(kernel_buffer,output_arr[atoi(yyvsp[0])-1]->name); 
;}
    break;

  case 62:
#line 423 "func.y"
    { 
  //printf("=>%s\n",$1);
  if(strlen(yyvsp[0]) + strlen(kernel_buffer) > buffer_size-3) {
    buffer_size += 1000;
    kernel_buffer= (char *)realloc(kernel_buffer, sizeof(char)*buffer_size);
  }
  kernel_buffer = strcat(kernel_buffer,yyvsp[0]);
;}
    break;

  case 63:
#line 434 "func.y"
    {
  printf("header : %s",  header_buffer);
  
;}
    break;

  case 66:
#line 443 "func.y"
    { 
  //printf("=>%s\n",$1);
  int len= strlen(yyvsp[0]);
  if(len + header_size > header_cap-3) {
    header_cap += 1000;
    header_buffer= (char *)realloc(header_buffer, sizeof(char)*header_cap);
  }
  header_size+= len;
  header_buffer = strcat(header_buffer,yyvsp[0]);
;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1511 "func.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 455 "func.y"



void yyerror (char const *s) { 
  fprintf(stderr, "in line %d: %s\n", lineno, s);
  exit(1);
}

int main(int argc, char **argv) {
  lineno=0;
  init_param();
  int r = yyparse();
  set_default_type();
  set_default_size();
  set_active_size();
  
  if(info_param) {
    display_inputs();
    display_outputs();
  }
  generate_mex();

  return 0;
}

