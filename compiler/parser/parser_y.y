%{
#include <stdio.h>
#include <stdint.h>    
#include <math.h>
#define EXEC_ONCE_TU_NAME "voba.compiler.parser.parser_y"
#include <exec_once.h>
#include <voba/value.h>
#include "../syntax/syntax.h"
#include "../syntax/syntax_c.h"
    
#include "flex_parser.h"

# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
      {                                                                 \
          (Current).start_pos   = YYRHSLOC (Rhs, 1).start_pos;          \
          (Current).end_pos    = YYRHSLOC (Rhs, N).end_pos;             \
      }                                                                 \
      else                                                              \
      {                                                                 \
          (Current).start_pos   = (Current).end_pos   =                 \
              YYRHSLOC (Rhs, 0).end_pos;                                \
      }                                                                 \
    while (0)

    %}

/* handle locations */

%define api.value.type {voba_value_t}
%define api.pure full
 /* %no-lines */
%output "parser_y.c"
%locations
%lex-param   {void* scanner}
%parse-param {void* scanner} {voba_value_t * yy_program }
%param       {voba_value_t source}
%defines
%token   T_VALUE
%debug
%code {
    int yylex (YYSTYPE *lvalp, YYLTYPE *llocp, void *, voba_value_t src);
typedef void * yyscan_t;
void yyerror (YYLTYPE * locp, yyscan_t scanner, voba_value_t * p, voba_value_t module, char const *s);
void yyerror (YYLTYPE * locp, yyscan_t scanner, voba_value_t * p, voba_value_t module, char const *s) {
   fprintf (stderr, "%s\n", s);
}
}
%% 

program: list_of_sexp {
    VOBA_APPLY(*yy_program = $$
               ,voba_symbol_value(s_make_2Dsyntax)
               ,$1
               ,voba_make_i32(@$.start_pos)
               ,voba_make_i32(@$.end_pos)
               ,source);
}
;

list_of_sexp:
sexp { VOBA_APPLY($$
                  ,voba_symbol_value(s_make_2Dsyntax)
                  ,voba_make_array_1($1)
                  ,voba_make_i32(@$.start_pos)
                  ,voba_make_i32(@$.end_pos)
                  ,source);
} 
| list_of_sexp sexp {
    voba_array_push(SYNTAX($1)->value,$2);
    VOBA_APPLY($$
               ,voba_symbol_value(s_make_2Dsyntax)
               ,SYNTAX($1)->value
               ,voba_make_i32(@$.start_pos)
               ,voba_make_i32(@$.end_pos)
               ,source);
}
;

sexp:
T_VALUE     
| '(' list_of_sexp ')' {
    VOBA_APPLY($$
               ,voba_symbol_value(s_make_2Dsyntax)
               ,SYNTAX($2)->value
               ,voba_make_i32(@$.start_pos)
               ,voba_make_i32(@$.end_pos)
               ,source);
}
| '(' ')' {
    VOBA_APPLY($$
               ,voba_symbol_value(s_make_2Dsyntax)
               ,voba_make_array_0()
               ,voba_make_i32(@$.start_pos)
               ,voba_make_i32(@$.end_pos)
               ,source);
}
| '\'' sexp {
    voba_value_t s_quote = voba_make_symbol(VOBA_CONST_CHAR("quote"),VOBA_NIL);
    voba_value_t syn_s_quote = VOBA_NIL;
    VOBA_APPLY(syn_s_quote
               ,voba_symbol_value(s_make_2Dsyntax)
               ,s_quote
               ,voba_make_i32(@1.start_pos)
               ,voba_make_i32(@1.end_pos)
               ,source);
    VOBA_APPLY($$
               ,voba_symbol_value(s_make_2Dsyntax)
               ,voba_make_array_2(syn_s_quote, $2)
               ,voba_make_i32(@1.start_pos)
               ,voba_make_i32(@2.end_pos)
               ,source);
  }
| error { fprintf(stderr,"TODO ERRORR RECOVERY %d - %d\n",@$.start_pos, @$.end_pos); }
;

