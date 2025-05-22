/* A Bison parser, made by GNU Bison 2.0.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     PLUS = 259,
     MINUS = 260,
     MULTIPLY = 261,
     DIVIDE = 262,
     LPAREN = 263,
     RPAREN = 264,
     END = 265,
     UMINUS = 266
   };
#endif
#define NUMBER 258
#define PLUS 259
#define MINUS 260
#define MULTIPLY 261
#define DIVIDE 262
#define LPAREN 263
#define RPAREN 264
#define END 265
#define UMINUS 266




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 9 "parser.y"
typedef union YYSTYPE { int num; } YYSTYPE;
/* Line 1274 of yacc.c.  */
#line 61 "parser.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



