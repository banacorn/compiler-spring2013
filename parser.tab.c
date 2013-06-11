/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

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
     CONST = 259,
     VOID = 260,
     INT = 261,
     FLOAT = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     FOR = 266,
     TYPEDEF = 267,
     OP_ASSIGN = 268,
     OP_OR = 269,
     OP_AND = 270,
     OP_NOT = 271,
     OP_EQ = 272,
     OP_NE = 273,
     OP_GT = 274,
     OP_LT = 275,
     OP_GE = 276,
     OP_LE = 277,
     OP_PLUS = 278,
     OP_MINUS = 279,
     OP_TIMES = 280,
     OP_DIVIDE = 281,
     MK_LB = 282,
     MK_RB = 283,
     MK_LPAREN = 284,
     MK_RPAREN = 285,
     MK_LBRACE = 286,
     MK_RBRACE = 287,
     MK_COMMA = 288,
     MK_SEMICOLON = 289,
     MK_DOT = 290,
     ERROR = 291,
     RETURN = 292
   };
#endif
/* Tokens.  */
#define ID 258
#define CONST 259
#define VOID 260
#define INT 261
#define FLOAT 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define FOR 266
#define TYPEDEF 267
#define OP_ASSIGN 268
#define OP_OR 269
#define OP_AND 270
#define OP_NOT 271
#define OP_EQ 272
#define OP_NE 273
#define OP_GT 274
#define OP_LT 275
#define OP_GE 276
#define OP_LE 277
#define OP_PLUS 278
#define OP_MINUS 279
#define OP_TIMES 280
#define OP_DIVIDE 281
#define MK_LB 282
#define MK_RB 283
#define MK_LPAREN 284
#define MK_RPAREN 285
#define MK_LBRACE 286
#define MK_RBRACE 287
#define MK_COMMA 288
#define MK_SEMICOLON 289
#define MK_DOT 290
#define ERROR 291
#define RETURN 292




/* Copy the first part of user declarations.  */
#line 3 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
int linenumber = 1;
AST_NODE *prog;
int STRUCT_DEC = 0;

static inline void  makesibling(AST_NODE *a,AST_NODE *b){ a->sibling=b; b->parent=a->parent;}
static inline void  makechild(AST_NODE *a,AST_NODE *b){ a->child=b; b->parent=a;}
static inline void  makefirstborn(AST_NODE *a,AST_NODE *b){ a->firstborn=b->firstborn;}


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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "parser.y"
{
	char *lexeme;
	CON_Type  *const1;
	AST_NODE  *node;
}
/* Line 193 of yacc.c.  */
#line 190 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 203 "parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
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
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNRULES -- Number of states.  */
#define YYNSTATES  214

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    14,    16,    25,
      34,    42,    50,    54,    56,    59,    63,    68,    73,    74,
      76,    77,    80,    82,    84,    85,    88,    90,    92,    94,
      99,   104,   108,   112,   114,   116,   118,   122,   127,   130,
     134,   139,   143,   147,   149,   153,   157,   159,   161,   165,
     167,   171,   173,   176,   180,   183,   185,   189,   195,   205,
     210,   216,   224,   230,   232,   235,   239,   241,   242,   246,
     248,   250,   254,   256,   258,   262,   264,   268,   270,   274,
     276,   278,   280,   282,   284,   286,   288,   289,   293,   295,
     299,   301,   303,   305,   309,   311,   313,   315,   319,   324,
     329,   331,   334,   337,   342,   348,   354,   356,   359,   362,
     364,   367
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    -1,    40,    41,    -1,    41,
      -1,    49,    42,    -1,    42,    -1,    53,     3,    29,    43,
      30,    31,    48,    32,    -1,     5,     3,    29,    43,    30,
      31,    48,    32,    -1,    53,     3,    29,    30,    31,    48,
      32,    -1,     5,     3,    29,    30,    31,    48,    32,    -1,
      43,    33,    44,    -1,    44,    -1,    53,     3,    -1,    53,
       3,    45,    -1,    27,    47,    28,    46,    -1,    27,    73,
      28,    46,    -1,    -1,    73,    -1,    -1,    49,    61,    -1,
      61,    -1,    49,    -1,    -1,    49,    50,    -1,    50,    -1,
      51,    -1,    52,    -1,    12,    53,    54,    34,    -1,    12,
       5,    54,    34,    -1,    53,    59,    34,    -1,     3,    54,
      34,    -1,     6,    -1,     7,    -1,     3,    -1,    54,    33,
       3,    -1,    54,    33,     3,    55,    -1,     3,    55,    -1,
      27,    56,    28,    -1,    55,    27,    56,    28,    -1,    56,
      23,    57,    -1,    56,    24,    57,    -1,    57,    -1,    57,
      25,    58,    -1,    57,    26,    58,    -1,    58,    -1,     4,
      -1,    29,    56,    30,    -1,    60,    -1,    59,    33,    60,
      -1,     3,    -1,     3,    55,    -1,     3,    13,    67,    -1,
      61,    62,    -1,    62,    -1,    31,    48,    32,    -1,    10,
      29,    65,    30,    62,    -1,    11,    29,    63,    34,    71,
      34,    63,    30,    62,    -1,    78,    13,    67,    34,    -1,
       8,    29,    65,    30,    62,    -1,     8,    29,    65,    30,
      62,     9,    62,    -1,     3,    29,    71,    30,    34,    -1,
      34,    -1,    37,    34,    -1,    37,    67,    34,    -1,    64,
      -1,    -1,    64,    33,    66,    -1,    66,    -1,    66,    -1,
       3,    13,    67,    -1,    67,    -1,    68,    -1,    67,    14,
      68,    -1,    69,    -1,    68,    15,    69,    -1,    73,    -1,
      73,    70,    73,    -1,    17,    -1,    21,    -1,    22,    -1,
      18,    -1,    19,    -1,    20,    -1,    72,    -1,    -1,    72,
      33,    67,    -1,    67,    -1,    73,    74,    75,    -1,    75,
      -1,    23,    -1,    24,    -1,    75,    76,    77,    -1,    77,
      -1,    25,    -1,    26,    -1,    29,    67,    30,    -1,    24,
      29,    67,    30,    -1,    16,    29,    67,    30,    -1,     4,
      -1,    24,     4,    -1,    16,     4,    -1,     3,    29,    71,
      30,    -1,    24,     3,    29,    71,    30,    -1,    16,     3,
      29,    71,    30,    -1,    78,    -1,    24,    78,    -1,    16,
      78,    -1,     3,    -1,    78,    79,    -1,    27,    73,    28,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    73,    73,    74,    77,    78,    81,    82,    85,    86,
      87,    88,    91,    92,    95,    96,    98,   101,   102,   104,
     105,   108,   109,   110,   111,   114,   115,   118,   119,   122,
     123,   126,   127,   130,   131,   134,   135,   136,   137,   139,
     140,   142,   143,   144,   146,   147,   148,   150,   151,   154,
     155,   158,   159,   160,   163,   164,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   181,   182,   185,   186,
     189,   192,   193,   196,   197,   200,   201,   204,   205,   208,
     209,   210,   211,   212,   213,   223,   224,   227,   228,   231,
     232,   235,   236,   239,   240,   243,   244,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   261,
     262,   266
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "CONST", "VOID", "INT", "FLOAT",
  "IF", "ELSE", "WHILE", "FOR", "TYPEDEF", "OP_ASSIGN", "OP_OR", "OP_AND",
  "OP_NOT", "OP_EQ", "OP_NE", "OP_GT", "OP_LT", "OP_GE", "OP_LE",
  "OP_PLUS", "OP_MINUS", "OP_TIMES", "OP_DIVIDE", "MK_LB", "MK_RB",
  "MK_LPAREN", "MK_RPAREN", "MK_LBRACE", "MK_RBRACE", "MK_COMMA",
  "MK_SEMICOLON", "MK_DOT", "ERROR", "RETURN", "$accept", "program",
  "global_decl_list", "global_decl", "function_decl", "param_list",
  "param", "dim_fn", "dimfn1", "expr_null", "block", "decl_list", "decl",
  "type_decl", "var_decl", "type", "id_list", "dim_decl", "cexpr",
  "mcexpr", "cfactor", "init_id_list", "init_id", "stmt_list", "stmt",
  "assign_expr_list", "nonempty_assign_expr_list", "test", "assign_expr",
  "relop_expr", "relop_term", "relop_factor", "rel_op", "relop_expr_list",
  "nonempty_relop_expr_list", "expr", "add_op", "term", "mul_op", "factor",
  "var_ref", "dim", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    42,
      42,    42,    43,    43,    44,    44,    45,    46,    46,    47,
      47,    48,    48,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    54,    54,    54,    55,
      55,    56,    56,    56,    57,    57,    57,    58,    58,    59,
      59,    60,    60,    60,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    70,
      70,    70,    70,    70,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    75,    76,    76,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    78,
      78,    79
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     8,     8,
       7,     7,     3,     1,     2,     3,     4,     4,     0,     1,
       0,     2,     1,     1,     0,     2,     1,     1,     1,     4,
       4,     3,     3,     1,     1,     1,     3,     4,     2,     3,
       4,     3,     3,     1,     3,     3,     1,     1,     3,     1,
       3,     1,     2,     3,     2,     1,     3,     5,     9,     4,
       5,     7,     5,     1,     2,     3,     1,     0,     3,     1,
       1,     3,     1,     1,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     3,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     4,     4,
       1,     2,     2,     4,     5,     5,     1,     2,     2,     1,
       2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,    33,    34,     0,     0,     2,     5,     7,
       0,    26,    27,    28,     0,    35,     0,     0,     0,     0,
       1,     4,     6,    25,    51,     0,    49,     0,    38,     0,
      32,     0,     0,     0,     0,     0,    52,     0,    31,    47,
       0,     0,    43,    46,     0,    36,     0,     0,    13,     0,
      30,    29,   109,   100,     0,     0,     0,    53,    73,    75,
      77,    90,    94,   106,     0,     0,    51,    50,     0,     0,
       0,    39,     0,     0,     0,    37,    24,     0,     0,    14,
      86,   109,   102,     0,   108,   109,   101,     0,   107,     0,
       0,     0,    79,    82,    83,    84,    80,    81,    91,    92,
       0,     0,    95,    96,     0,     0,   110,    24,     0,    48,
      41,    42,    44,    45,    40,   109,     0,     0,     0,    24,
      63,     0,     0,    23,     0,    22,    55,     0,    24,    12,
      20,    15,    88,     0,    85,    86,     0,    86,     0,    97,
      74,    76,    78,    89,    93,     0,     0,    24,    86,     0,
       0,    67,     0,    64,     0,    11,    21,   109,    54,     0,
       0,     0,    19,   103,     0,     0,    99,     0,    98,   111,
      10,     0,     0,   109,     0,    70,    72,     0,     0,    66,
      69,    56,    65,     0,     9,    18,    87,   105,   104,     8,
       0,     0,     0,     0,    86,     0,    59,     0,    16,    62,
      71,    60,    57,     0,    68,     0,     0,    67,    18,    61,
       0,    17,     0,    58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    47,    48,   131,   198,   161,
     122,   123,    11,    12,    13,   124,    16,    36,    41,    42,
      43,    25,    26,   125,   126,   178,   179,   174,   175,   132,
      58,    59,   100,   133,   134,    60,   101,    61,   104,    62,
      63,   106
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -148
static const yytype_int16 yypact[] =
{
     138,     7,    26,  -148,  -148,   179,    44,   138,  -148,  -148,
     138,  -148,  -148,  -148,    35,    40,   121,    23,     7,     7,
    -148,  -148,  -148,  -148,    85,   154,  -148,    22,    82,   101,
    -148,    62,   156,   158,   104,    67,    82,   120,  -148,  -148,
      22,   128,   168,  -148,    22,    40,    88,    94,  -148,   132,
    -148,  -148,   119,  -148,    14,    17,   104,   123,   143,  -148,
     145,   170,  -148,   180,   141,   116,    29,  -148,   108,    22,
      22,  -148,    22,    22,   147,    82,    24,   149,   191,   181,
     104,   131,  -148,   104,   180,   182,  -148,   104,   180,    65,
     104,   104,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
     104,   104,  -148,  -148,   104,   104,  -148,    24,   151,  -148,
     168,   168,  -148,  -148,  -148,    21,   184,   185,   186,    24,
    -148,    77,   142,    24,   120,    54,  -148,    86,    24,  -148,
     104,  -148,   123,   187,   177,   104,    72,   104,    75,  -148,
     143,  -148,   176,   170,  -148,   153,   188,    24,   104,   118,
     118,   118,   189,  -148,    25,  -148,    54,   190,  -148,   104,
     192,   194,   176,  -148,   104,   193,  -148,   195,  -148,  -148,
    -148,   196,   197,    97,   199,  -148,   123,   200,   175,   198,
    -148,  -148,  -148,    49,  -148,   205,   123,  -148,  -148,  -148,
     178,   104,    54,    54,   104,   118,  -148,   104,  -148,  -148,
     123,   207,  -148,   201,  -148,   155,    54,   118,   205,  -148,
     203,  -148,    54,  -148
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -148,  -148,  -148,   211,   216,   202,   160,  -148,    28,  -148,
    -100,   129,    -5,  -148,  -148,     6,   183,     0,    38,   134,
     133,  -148,   204,   111,  -116,    32,  -148,    90,  -147,   -34,
     152,   157,  -148,  -123,  -148,   -97,  -148,   144,  -148,   139,
     -53,  -148
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      57,    84,    88,   142,   180,    23,    14,   146,   145,   158,
      15,    19,   165,    14,   167,    28,    14,    81,    82,   152,
      85,    86,    89,   127,    15,   172,    39,   115,   160,    17,
       3,     4,   116,   162,   117,   118,     5,    49,    24,    90,
     158,    49,    34,    83,    20,    75,    87,   171,   204,   136,
     148,    40,    31,   138,   127,   119,    27,   157,   120,   182,
     180,   121,   116,    90,   117,   118,   127,    27,     3,     4,
     127,   203,   127,     3,     4,   127,   201,   202,    68,    90,
      52,    53,    74,   196,    49,   119,    90,   154,   120,    90,
     209,   121,    46,    54,   127,   139,   213,    64,    34,   159,
     205,    55,   166,   127,    45,   168,    56,    52,    53,    44,
     191,   153,    27,   105,    35,   176,   176,   176,    23,    76,
      54,   173,    53,    66,    77,   183,    80,    78,    55,    10,
     186,    69,    70,    56,    54,    79,    10,    90,   109,   127,
     127,     1,    55,     2,     3,     4,   108,    56,    80,    78,
       5,    69,    70,   127,    29,    30,    71,   200,    91,   127,
     135,   176,    92,    93,    94,    95,    96,    97,    98,    99,
      69,    70,   107,   176,   155,   114,    98,    99,    98,    99,
     128,   169,   147,   208,    18,     3,     4,    37,    38,    29,
      50,    29,    51,    72,    73,   102,   103,     3,     4,    98,
      99,    32,    33,   110,   111,   112,   113,   105,   130,   194,
     164,   137,   199,   149,   150,   151,   206,   163,    21,   148,
     170,   181,   185,   187,   184,   188,    22,   190,   189,   192,
     193,   195,   197,   212,   156,   207,   211,    65,   129,   210,
     177,    67,   140,   144,     0,   143,     0,     0,   141
};

static const yytype_int16 yycheck[] =
{
      34,    54,    55,   100,   151,    10,     0,   107,   105,   125,
       3,     5,   135,     7,   137,    15,    10,     3,     4,   119,
       3,     4,    56,    76,     3,   148,     4,     3,   128,     3,
       6,     7,     8,   130,    10,    11,    12,    31,     3,    14,
     156,    35,    13,    29,     0,    45,    29,   147,   195,    83,
      29,    29,    29,    87,   107,    31,    27,     3,    34,    34,
     207,    37,     8,    14,    10,    11,   119,    27,     6,     7,
     123,   194,   125,     6,     7,   128,   192,   193,    40,    14,
       3,     4,    44,    34,    78,    31,    14,   121,    34,    14,
     206,    37,    30,    16,   147,    30,   212,    30,    13,    13,
     197,    24,    30,   156,     3,    30,    29,     3,     4,    27,
      13,    34,    27,    27,    29,   149,   150,   151,   123,    31,
      16,     3,     4,     3,    30,   159,    29,    33,    24,     0,
     164,    23,    24,    29,    16,     3,     7,    14,    30,   192,
     193,     3,    24,     5,     6,     7,    30,    29,    29,    33,
      12,    23,    24,   206,    33,    34,    28,   191,    15,   212,
      29,   195,    17,    18,    19,    20,    21,    22,    23,    24,
      23,    24,    31,   207,    32,    28,    23,    24,    23,    24,
      31,    28,    31,    28,     5,     6,     7,    33,    34,    33,
      34,    33,    34,    25,    26,    25,    26,     6,     7,    23,
      24,    18,    19,    69,    70,    72,    73,    27,    27,    34,
      33,    29,    34,    29,    29,    29,     9,    30,     7,    29,
      32,    32,    28,    30,    32,    30,    10,    30,    32,    30,
      30,    33,    27,    30,   123,    34,   208,    35,    78,   207,
     150,    37,    90,   104,    -1,   101,    -1,    -1,    91
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,    12,    39,    40,    41,    42,
      49,    50,    51,    52,    53,     3,    54,     3,     5,    53,
       0,    41,    42,    50,     3,    59,    60,    27,    55,    33,
      34,    29,    54,    54,    13,    29,    55,    33,    34,     4,
      29,    56,    57,    58,    27,     3,    30,    43,    44,    53,
      34,    34,     3,     4,    16,    24,    29,    67,    68,    69,
      73,    75,    77,    78,    30,    43,     3,    60,    56,    23,
      24,    28,    25,    26,    56,    55,    31,    30,    33,     3,
      29,     3,     4,    29,    78,     3,     4,    29,    78,    67,
      14,    15,    17,    18,    19,    20,    21,    22,    23,    24,
      70,    74,    25,    26,    76,    27,    79,    31,    30,    30,
      57,    57,    58,    58,    28,     3,     8,    10,    11,    31,
      34,    37,    48,    49,    53,    61,    62,    78,    31,    44,
      27,    45,    67,    71,    72,    29,    67,    29,    67,    30,
      68,    69,    73,    75,    77,    73,    48,    31,    29,    29,
      29,    29,    48,    34,    67,    32,    61,     3,    62,    13,
      48,    47,    73,    30,    33,    71,    30,    71,    30,    28,
      32,    48,    71,     3,    65,    66,    67,    65,    63,    64,
      66,    32,    34,    67,    32,    28,    67,    30,    30,    32,
      30,    13,    30,    30,    34,    33,    34,    27,    46,    34,
      67,    62,    62,    71,    66,    73,     9,    34,    28,    62,
      63,    46,    30,    62
};

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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
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

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
        case 2:
#line 73 "parser.y"
    { (yyval.node)=Allocate(PROGRAM);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); prog=(yyval.node);;}
    break;

  case 3:
#line 74 "parser.y"
    { (yyval.node)=Allocate(PROGRAM); prog=(yyval.node);;}
    break;

  case 4:
#line 77 "parser.y"
    {(yyval.node)=Allocate(GLOBAL_DECL_LIST); makechild((yyval.node),(yyvsp[(2) - (2)].node));makesibling((yyvsp[(1) - (2)].node), (yyval.node));makefirstborn((yyval.node),(yyvsp[(1) - (2)].node));;}
    break;

  case 5:
#line 78 "parser.y"
    {(yyval.node)=Allocate(GLOBAL_DECL_LIST);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->firstborn=(yyval.node);;}
    break;

  case 6:
#line 81 "parser.y"
    {(yyval.node)=Allocate(GLOBAL_DECL); makechild((yyval.node),(yyvsp[(1) - (2)].node)); makesibling((yyval.node)->child,(yyvsp[(2) - (2)].node));;}
    break;

  case 7:
#line 82 "parser.y"
    {(yyval.node)=Allocate(GLOBAL_DECL); makechild((yyval.node),(yyvsp[(1) - (1)].node));;}
    break;

  case 8:
#line 85 "parser.y"
    {(yyval.node)=Allocate(FUNCTION_DECL);  makechild((yyval.node),(yyvsp[(1) - (8)].node)); makesibling((yyvsp[(1) - (8)].node),Allocate(ID_value)); (yyvsp[(1) - (8)].node)->sibling->semantic_value.lexeme=(yyvsp[(2) - (8)].lexeme); makesibling((yyvsp[(1) - (8)].node)->sibling,(yyvsp[(4) - (8)].node)); makesibling((yyvsp[(4) - (8)].node),(yyvsp[(7) - (8)].node)); (yyval.node)->semantic_value.func_decl=FD_TYPE_PARAM;;}
    break;

  case 9:
#line 86 "parser.y"
    {(yyval.node)=Allocate(FUNCTION_DECL);  makechild((yyval.node),Allocate(ID_value)); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(2) - (8)].lexeme); makesibling((yyval.node)->child,(yyvsp[(4) - (8)].node));  makesibling((yyvsp[(4) - (8)].node),(yyvsp[(7) - (8)].node)); (yyval.node)->semantic_value.func_decl=FD_VOID_PARAM;;}
    break;

  case 10:
#line 87 "parser.y"
    {(yyval.node)=Allocate(FUNCTION_DECL);  makechild((yyval.node),(yyvsp[(1) - (7)].node)); makesibling((yyval.node)->child,Allocate(ID_value)); (yyval.node)->child->sibling->semantic_value.lexeme=(yyvsp[(2) - (7)].lexeme); makesibling((yyval.node)->child->sibling,(yyvsp[(6) - (7)].node)); (yyval.node)->semantic_value.func_decl=FD_TYPE_NONE;;}
    break;

  case 11:
#line 88 "parser.y"
    {(yyval.node)=Allocate(FUNCTION_DECL);  makechild((yyval.node),Allocate(ID_value)); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(2) - (7)].lexeme); makesibling((yyval.node)->child,(yyvsp[(6) - (7)].node)); (yyval.node)->semantic_value.func_decl=FD_VOID_NONE;;}
    break;

  case 12:
#line 91 "parser.y"
    {(yyval.node)=Allocate(PARAM_LIST);  makesibling((yyvsp[(1) - (3)].node),(yyval.node)); makefirstborn((yyval.node),(yyvsp[(1) - (3)].node)); makechild((yyval.node),(yyvsp[(3) - (3)].node));;}
    break;

  case 13:
#line 92 "parser.y"
    {(yyval.node)=Allocate(PARAM_LIST);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->firstborn=(yyval.node);;}
    break;

  case 14:
#line 95 "parser.y"
    {(yyval.node)=Allocate(PARAM);  makechild((yyval.node),(yyvsp[(1) - (2)].node)); makesibling((yyvsp[(1) - (2)].node),Allocate(ID_value)); (yyvsp[(1) - (2)].node)->sibling->semantic_value.lexeme=(yyvsp[(2) - (2)].lexeme); (yyval.node)->semantic_value.param=P_TYPE_NONE;;}
    break;

  case 15:
#line 96 "parser.y"
    {(yyval.node)=Allocate(PARAM);  makechild((yyval.node),(yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node),Allocate(ID_value)); (yyvsp[(1) - (3)].node)->sibling->semantic_value.lexeme=(yyvsp[(2) - (3)].lexeme); makesibling((yyvsp[(1) - (3)].node)->sibling,(yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.param=P_TYPE_ARR;;}
    break;

  case 16:
#line 98 "parser.y"
    {(yyval.node)=Allocate(DIM_FN);  makechild((yyval.node),(yyvsp[(2) - (4)].node)); makesibling((yyvsp[(2) - (4)].node),(yyvsp[(4) - (4)].node));;}
    break;

  case 17:
#line 101 "parser.y"
    {(yyval.node)=Allocate(DIMFN1);  makechild((yyval.node),(yyvsp[(2) - (4)].node)); makesibling((yyvsp[(2) - (4)].node),(yyvsp[(4) - (4)].node));;}
    break;

  case 18:
#line 102 "parser.y"
    { (yyval.node)=Allocate(DIMFN1);;}
    break;

  case 19:
#line 104 "parser.y"
    {(yyval.node)=Allocate(EXPR_NULL);  makechild((yyval.node),(yyvsp[(1) - (1)].node));;}
    break;

  case 20:
#line 105 "parser.y"
    { (yyval.node)=Allocate(EXPR_NULL); ;}
    break;

  case 21:
#line 108 "parser.y"
    {(yyval.node)=Allocate(BLOCK);  makechild((yyval.node),(yyvsp[(1) - (2)].node)); makesibling((yyval.node)->child,(yyvsp[(2) - (2)].node)); (yyval.node)->semantic_value.block=B_DECL_STMT;;}
    break;

  case 22:
#line 109 "parser.y"
    {(yyval.node)=Allocate(BLOCK);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.block=B_STMT;;}
    break;

  case 23:
#line 110 "parser.y"
    {(yyval.node)=Allocate(BLOCK);   makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.block=B_DECL;;}
    break;

  case 24:
#line 111 "parser.y"
    {(yyval.node)=Allocate(BLOCK); (yyval.node)->semantic_value.block=B_NULL;;}
    break;

  case 25:
#line 114 "parser.y"
    { (yyval.node)=Allocate(DECL_LIST);  makesibling((yyvsp[(1) - (2)].node),(yyval.node)); makefirstborn((yyval.node),(yyvsp[(1) - (2)].node)); makechild((yyval.node),(yyvsp[(2) - (2)].node));;}
    break;

  case 26:
#line 115 "parser.y"
    {(yyval.node)=Allocate(DECL_LIST);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->firstborn=(yyval.node);;}
    break;

  case 27:
#line 118 "parser.y"
    { (yyval.node)=Allocate(DECL);  makechild((yyval.node),(yyvsp[(1) - (1)].node));;}
    break;

  case 28:
#line 119 "parser.y"
    {(yyval.node)=Allocate(DECL);   makechild((yyval.node),(yyvsp[(1) - (1)].node));;}
    break;

  case 29:
#line 122 "parser.y"
    {(yyval.node)=Allocate(TYPE_DECL);  makechild((yyval.node),(yyvsp[(2) - (4)].node));  makesibling((yyvsp[(2) - (4)].node),(yyvsp[(3) - (4)].node)); (yyval.node)->semantic_value.type_decl=TD_TYPE_ID;;}
    break;

  case 30:
#line 123 "parser.y"
    {(yyval.node)=Allocate(TYPE_DECL);  makechild((yyval.node),(yyvsp[(3) - (4)].node)); (yyval.node)->semantic_value.type_decl=TD_VOID_ID;;}
    break;

  case 31:
#line 126 "parser.y"
    {(yyval.node)=Allocate(VAR_DECL);  makechild((yyval.node),(yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node)); (yyval.node)->semantic_value.var_decl=VD_TYPE;;}
    break;

  case 32:
#line 127 "parser.y"
    {(yyval.node)=Allocate(VAR_DECL);  (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (3)].lexeme); makesibling((yyval.node)->child,(yyvsp[(2) - (3)].node)); (yyval.node)->semantic_value.var_decl=VD_ID;;}
    break;

  case 33:
#line 130 "parser.y"
    {(yyval.node)=Allocate(TYPE);  (yyval.node)->semantic_value.type=INT_;;}
    break;

  case 34:
#line 131 "parser.y"
    {(yyval.node)=Allocate(TYPE);  (yyval.node)->semantic_value.type=FLOAT_;;}
    break;

  case 35:
#line 134 "parser.y"
    {(yyval.node)=Allocate(ID_LIST);  (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (1)].lexeme); (yyval.node)->semantic_value.type=STR_VAR_; (yyval.node)->firstborn=(yyval.node);;}
    break;

  case 36:
#line 135 "parser.y"
    {(yyval.node)=Allocate(ID_LIST);  makesibling((yyvsp[(1) - (3)].node),(yyval.node)); makefirstborn((yyval.node),(yyvsp[(1) - (3)].node)); (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(3) - (3)].lexeme); (yyval.node)->semantic_value.type=STR_VAR_;;}
    break;

  case 37:
#line 136 "parser.y"
    {(yyval.node)=Allocate(ID_LIST);  makesibling((yyvsp[(1) - (4)].node),(yyval.node)); makefirstborn((yyval.node),(yyvsp[(1) - (4)].node)); (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(3) - (4)].lexeme); makesibling((yyval.node)->child,(yyvsp[(4) - (4)].node)); (yyval.node)->semantic_value.type=ARR_;;}
    break;

  case 38:
#line 137 "parser.y"
    {(yyval.node)=Allocate(ID_LIST);  (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (2)].lexeme); makesibling((yyval.node)->child,(yyvsp[(2) - (2)].node)); (yyval.node)->semantic_value.type=ARR_; (yyval.node)->firstborn=(yyval.node);;}
    break;

  case 39:
#line 139 "parser.y"
    {(yyval.node)=Allocate(DIM_DECL);  makechild((yyval.node),(yyvsp[(2) - (3)].node)); (yyval.node)->firstborn=(yyval.node);;}
    break;

  case 40:
#line 140 "parser.y"
    {(yyval.node)=Allocate(DIM_DECL);  makesibling((yyvsp[(1) - (4)].node),(yyval.node)); makefirstborn((yyval.node),(yyvsp[(1) - (4)].node)); makechild((yyval.node),(yyvsp[(3) - (4)].node));;}
    break;

  case 41:
#line 142 "parser.y"
    {(yyval.node)=Allocate(CEXPR);  makechild((yyval.node),(yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_ADD; ;}
    break;

  case 42:
#line 143 "parser.y"
    {(yyval.node)=Allocate(CEXPR); makechild((yyval.node),(yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_SUB;;}
    break;

  case 43:
#line 144 "parser.y"
    {(yyval.node)=Allocate(CEXPR);   makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.op_type=OPT_NONE;;}
    break;

  case 44:
#line 146 "parser.y"
    {(yyval.node)=Allocate(MCEXPR);   makechild((yyval.node),(yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_MUL;;}
    break;

  case 45:
#line 147 "parser.y"
    {(yyval.node)=Allocate(MCEXPR);   makechild((yyval.node),(yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_DIV;;}
    break;

  case 46:
#line 148 "parser.y"
    {(yyval.node)=Allocate(MCEXPR);   makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.op_type=OPT_NONE; ;}
    break;

  case 47:
#line 150 "parser.y"
    {(yyval.node)=Allocate(CFACTOR);  (yyval.node)->child=Allocate(CONST_value); (yyval.node)->child->semantic_value.const1=(yyvsp[(1) - (1)].const1);;}
    break;

  case 48:
#line 151 "parser.y"
    {(yyval.node)=Allocate(CFACTOR);   makechild((yyval.node),(yyvsp[(2) - (3)].node));;}
    break;

  case 49:
#line 154 "parser.y"
    {(yyval.node)=Allocate(INIT_ID_LIST);    makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->firstborn=(yyval.node); ;}
    break;

  case 50:
#line 155 "parser.y"
    {(yyval.node)=Allocate(INIT_ID_LIST);  makesibling((yyvsp[(1) - (3)].node),(yyval.node)); makefirstborn((yyval.node),(yyvsp[(1) - (3)].node));  makechild((yyval.node),(yyvsp[(3) - (3)].node));;}
    break;

  case 51:
#line 158 "parser.y"
    {(yyval.node)=Allocate(INIT_ID);  (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (1)].lexeme); (yyval.node)->semantic_value.type=STR_VAR_;;}
    break;

  case 52:
#line 159 "parser.y"
    {(yyval.node)=Allocate(INIT_ID);  (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (2)].lexeme); makesibling((yyval.node)->child,(yyvsp[(2) - (2)].node)); (yyval.node)->semantic_value.type=ARR_; ;}
    break;

  case 53:
#line 160 "parser.y"
    {(yyval.node)=Allocate(INIT_ID);  (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (3)].lexeme); makesibling((yyval.node)->child,(yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.type=ASSIGN_;;}
    break;

  case 54:
#line 163 "parser.y"
    {(yyval.node)=Allocate(STMT_LIST);  makesibling((yyvsp[(1) - (2)].node),(yyval.node)); makefirstborn((yyval.node),(yyvsp[(1) - (2)].node)); makechild((yyval.node),(yyvsp[(2) - (2)].node));;}
    break;

  case 55:
#line 164 "parser.y"
    {(yyval.node)=Allocate(STMT_LIST);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->firstborn=(yyval.node); ;}
    break;

  case 56:
#line 169 "parser.y"
    {(yyval.node)=Allocate(STMT);  makechild((yyval.node), (yyvsp[(2) - (3)].node)); (yyval.node)->semantic_value.stmt=STMT_BLOCK;;}
    break;

  case 57:
#line 170 "parser.y"
    {(yyval.node)=Allocate(STMT); makechild((yyval.node), (yyvsp[(3) - (5)].node)); makesibling((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node)); (yyval.node)->semantic_value.stmt=STMT_WHILE;;}
    break;

  case 58:
#line 171 "parser.y"
    {(yyval.node)=Allocate(STMT); makechild((yyval.node), (yyvsp[(3) - (9)].node)); makesibling((yyvsp[(3) - (9)].node), (yyvsp[(5) - (9)].node)); makesibling((yyvsp[(5) - (9)].node), (yyvsp[(7) - (9)].node)); makesibling((yyvsp[(7) - (9)].node), (yyvsp[(9) - (9)].node)); (yyval.node)->semantic_value.stmt=STMT_FOR;;}
    break;

  case 59:
#line 172 "parser.y"
    {(yyval.node)=Allocate(STMT);  makechild((yyval.node), (yyvsp[(1) - (4)].node)); makesibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node)); (yyval.node)->semantic_value.stmt=STMT_ASSIGN;;}
    break;

  case 60:
#line 173 "parser.y"
    { (yyval.node)=Allocate(STMT);  makechild((yyval.node), (yyvsp[(3) - (5)].node)); makesibling((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node)); (yyval.node)->semantic_value.stmt=STMT_IF;;}
    break;

  case 61:
#line 174 "parser.y"
    { (yyval.node)=Allocate(STMT);  makechild((yyval.node), (yyvsp[(3) - (7)].node)); makesibling((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node)); makesibling((yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node)); (yyval.node)->semantic_value.stmt=STMT_IF_ELSE;;}
    break;

  case 62:
#line 175 "parser.y"
    {(yyval.node)=Allocate(STMT);  (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (5)].lexeme); makesibling((yyval.node)->child, (yyvsp[(3) - (5)].node));   (yyval.node)->semantic_value.stmt=STMT_FUNC_CALL;;}
    break;

  case 63:
#line 176 "parser.y"
    {(yyval.node)=Allocate(STMT);  (yyval.node)->semantic_value.stmt=STMT_NONE;;}
    break;

  case 64:
#line 177 "parser.y"
    {(yyval.node)=Allocate(STMT);  (yyval.node)->semantic_value.stmt=STMT_RETURN_VOID;;}
    break;

  case 65:
#line 178 "parser.y"
    {(yyval.node)=Allocate(STMT);  makechild((yyval.node), (yyvsp[(2) - (3)].node)); (yyval.node)->semantic_value.stmt=STMT_RETURN;;}
    break;

  case 66:
#line 181 "parser.y"
    {(yyval.node)=Allocate(ASSIGN_EXPR_LIST);  makechild((yyval.node), (yyvsp[(1) - (1)].node));;}
    break;

  case 67:
#line 182 "parser.y"
    {(yyval.node)=Allocate(ASSIGN_EXPR_LIST); ;}
    break;

  case 68:
#line 185 "parser.y"
    {(yyval.node)=Allocate(NONEMPTY_ASSIGN_EXPR_LIST);  makesibling((yyvsp[(1) - (3)].node), (yyval.node)); makefirstborn((yyval.node), (yyvsp[(1) - (3)].node)); makechild((yyval.node), (yyvsp[(3) - (3)].node));;}
    break;

  case 69:
#line 186 "parser.y"
    {(yyval.node)=Allocate(NONEMPTY_ASSIGN_EXPR_LIST);  (yyval.node)->child=(yyvsp[(1) - (1)].node); (yyval.node)->firstborn=(yyval.node);;}
    break;

  case 70:
#line 189 "parser.y"
    {(yyval.node)=Allocate(TEST);  makechild((yyval.node), (yyvsp[(1) - (1)].node));;}
    break;

  case 71:
#line 192 "parser.y"
    {(yyval.node)=Allocate(ASSIGN_EXPR);  (yyval.node)->child=Allocate(ID_value); (yyval.node)->child->semantic_value.lexeme= (yyvsp[(1) - (3)].lexeme); makesibling((yyval.node)->child,  (yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.type=ASSIGN_;;}
    break;

  case 72:
#line 193 "parser.y"
    {(yyval.node)=Allocate(ASSIGN_EXPR);  makechild((yyval.node), (yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.type=VOID_;;}
    break;

  case 73:
#line 196 "parser.y"
    {(yyval.node)=Allocate(RELOP_EXPR);  makechild((yyval.node), (yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.op_type=OPT_NONE;;}
    break;

  case 74:
#line 197 "parser.y"
    {(yyval.node)=Allocate(RELOP_EXPR);  makechild((yyval.node), (yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_OR;;}
    break;

  case 75:
#line 200 "parser.y"
    {(yyval.node)=Allocate(RELOP_TERM);  makechild((yyval.node), (yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.op_type=OPT_NONE;;}
    break;

  case 76:
#line 201 "parser.y"
    {(yyval.node)=Allocate(RELOP_TERM);  makesibling((yyval.node), (yyvsp[(1) - (3)].node)); makechild((yyval.node), (yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_AND;;}
    break;

  case 77:
#line 204 "parser.y"
    {(yyval.node)=Allocate(RELOP_FACTOR);  makechild((yyval.node), (yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.op_type=OPT_NONE;;}
    break;

  case 78:
#line 205 "parser.y"
    {(yyval.node)=Allocate(RELOP_FACTOR); makechild((yyval.node), (yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node)); makesibling((yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_REL;;}
    break;

  case 79:
#line 208 "parser.y"
    {(yyval.node)=Allocate(REL_OP);  (yyval.node)->semantic_value.op_type=OPT_EQ;;}
    break;

  case 80:
#line 209 "parser.y"
    {(yyval.node)=Allocate(REL_OP);  (yyval.node)->semantic_value.op_type=OPT_GE;;}
    break;

  case 81:
#line 210 "parser.y"
    {(yyval.node)=Allocate(REL_OP);  (yyval.node)->semantic_value.op_type=OPT_LE;;}
    break;

  case 82:
#line 211 "parser.y"
    {(yyval.node)=Allocate(REL_OP);  (yyval.node)->semantic_value.op_type=OPT_NE;;}
    break;

  case 83:
#line 212 "parser.y"
    {(yyval.node)=Allocate(REL_OP);  (yyval.node)->semantic_value.op_type=OPT_GT;;}
    break;

  case 84:
#line 213 "parser.y"
    {(yyval.node)=Allocate(REL_OP);  (yyval.node)->semantic_value.op_type=OPT_LT;;}
    break;

  case 85:
#line 223 "parser.y"
    {(yyval.node)=Allocate(RELOP_EXPR_LIST);  makechild((yyval.node),(yyvsp[(1) - (1)].node));;}
    break;

  case 86:
#line 224 "parser.y"
    {(yyval.node)=Allocate(RELOP_EXPR_LIST); ;}
    break;

  case 87:
#line 227 "parser.y"
    {(yyval.node)=Allocate(NONEMPTY_RELOP_EXPR_LIST);  makesibling((yyvsp[(1) - (3)].node),(yyval.node)); makefirstborn((yyval.node),(yyvsp[(1) - (3)].node)); makechild((yyval.node),(yyvsp[(3) - (3)].node));;}
    break;

  case 88:
#line 228 "parser.y"
    {(yyval.node)=Allocate(NONEMPTY_RELOP_EXPR_LIST);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->firstborn=(yyval.node);;}
    break;

  case 89:
#line 231 "parser.y"
    {(yyval.node)=Allocate(EXPR);  makechild((yyval.node),(yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node)); makesibling((yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_REL;;}
    break;

  case 90:
#line 232 "parser.y"
    {(yyval.node)=Allocate(EXPR);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.op_type=OPT_NONE;;}
    break;

  case 91:
#line 235 "parser.y"
    {(yyval.node)=Allocate(ADD_OP);  (yyval.node)->semantic_value.op_type=OPT_ADD;;}
    break;

  case 92:
#line 236 "parser.y"
    {(yyval.node)=Allocate(ADD_OP);  (yyval.node)->semantic_value.op_type=OPT_SUB;;}
    break;

  case 93:
#line 239 "parser.y"
    {(yyval.node)=Allocate(TERM);  makechild((yyval.node),(yyvsp[(1) - (3)].node)); makesibling((yyvsp[(1) - (3)].node),(yyvsp[(2) - (3)].node)); makesibling((yyvsp[(2) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)->semantic_value.op_type=OPT_REL;;}
    break;

  case 94:
#line 240 "parser.y"
    {(yyval.node)=Allocate(TERM);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.op_type=OPT_NONE;;}
    break;

  case 95:
#line 243 "parser.y"
    {(yyval.node)=Allocate(MUL_OP);  (yyval.node)->semantic_value.op_type=OPT_MUL;;}
    break;

  case 96:
#line 244 "parser.y"
    {(yyval.node)=Allocate(MUL_OP);  (yyval.node)->semantic_value.op_type=OPT_DIV;;}
    break;

  case 97:
#line 247 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),(yyvsp[(2) - (3)].node)); (yyval.node)->semantic_value.factor=F_REL;;}
    break;

  case 98:
#line 248 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),(yyvsp[(3) - (4)].node)); (yyval.node)->semantic_value.factor=F_REL_MINUS;;}
    break;

  case 99:
#line 249 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),(yyvsp[(3) - (4)].node)); (yyval.node)->semantic_value.factor=F_REL_NOT;;}
    break;

  case 100:
#line 250 "parser.y"
    {(yyval.node)=Allocate(FACTOR); makechild((yyval.node),Allocate(CONST_value)); (yyval.node)->child->semantic_value.const1=(yyvsp[(1) - (1)].const1); (yyval.node)->semantic_value.factor=F_CONST;;}
    break;

  case 101:
#line 251 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),Allocate(CONST_value)); (yyval.node)->child->semantic_value.const1=(yyvsp[(2) - (2)].const1); (yyval.node)->semantic_value.factor=F_CONST_MINUS;;}
    break;

  case 102:
#line 252 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),Allocate(CONST_value)); (yyval.node)->child->semantic_value.const1=(yyvsp[(2) - (2)].const1); (yyval.node)->semantic_value.factor=F_CONST_NOT;;}
    break;

  case 103:
#line 253 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),Allocate(ID_value)); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (4)].lexeme); makesibling((yyval.node)->child,(yyvsp[(3) - (4)].node)); (yyval.node)->semantic_value.factor=F_ID;;}
    break;

  case 104:
#line 254 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),Allocate(ID_value)); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(2) - (5)].lexeme); makesibling((yyval.node)->child,(yyvsp[(4) - (5)].node)); (yyval.node)->semantic_value.factor=F_ID_MINUS;;}
    break;

  case 105:
#line 255 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),Allocate(ID_value)); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(2) - (5)].lexeme); makesibling((yyval.node)->child,(yyvsp[(4) - (5)].node)); (yyval.node)->semantic_value.factor=F_ID_NOT;;}
    break;

  case 106:
#line 256 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),(yyvsp[(1) - (1)].node)); (yyval.node)->semantic_value.factor=F_VAR;;}
    break;

  case 107:
#line 257 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),(yyvsp[(2) - (2)].node)); (yyval.node)->semantic_value.factor=F_VAR_MINUS;;}
    break;

  case 108:
#line 258 "parser.y"
    {(yyval.node)=Allocate(FACTOR);  makechild((yyval.node),(yyvsp[(2) - (2)].node)); (yyval.node)->semantic_value.factor=F_VAR_NOT;;}
    break;

  case 109:
#line 261 "parser.y"
    {(yyval.node)=Allocate(VAR_REF);  makechild((yyval.node),Allocate(ID_value)); (yyval.node)->child->semantic_value.lexeme=(yyvsp[(1) - (1)].lexeme); (yyval.node)->semantic_value.type=STR_;;}
    break;

  case 110:
#line 262 "parser.y"
    {(yyval.node)=Allocate(VAR_REF);  makechild((yyval.node),(yyvsp[(1) - (2)].node)); makesibling((yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); (yyval.node)->semantic_value.type=ARR_;;}
    break;

  case 111:
#line 266 "parser.y"
    {(yyval.node)=Allocate(DIM);  makechild((yyval.node),(yyvsp[(2) - (3)].node));;}
    break;


/* Line 1267 of yacc.c.  */
#line 2151 "parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 271 "parser.y"


#include "lex.yy.c"
main (argc, argv)
int argc;
char *argv[];
  {
     yyin = fopen(argv[1],"r");
     yyparse();
	 printf("%s\n", "Parsing completed. No errors found.");
//	 printGV(prog);
	 insert_buildin_functions();
	 build_symtable_check(prog);
  } /* main */


int yyerror (mesg)
char *mesg;
  {
  printf("%s\t%d\t%s\t%s\n", "Error found in Line ", linenumber, "next token: ", yytext );
  exit(1);
  }




