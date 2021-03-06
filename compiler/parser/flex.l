%{

#include <stdlib.h>
#include <string.h>
#define EXEC_ONCE_TU_NAME "voba.compiler.parser.flex"
#include <exec_once.h>
#include <voba/value.h>
#include "../source/source.h"
#include "../source/source_c.h"
#include "../syntax/syntax.h"
#include "../syntax/syntax_c.h"
#include "flex_parser.h"
#include "./parser_y.h"

int fileno(FILE *stream);
int yyget_column  (yyscan_t yyscanner);
#include <math.h>
#include <assert.h>
#include <exec_once.h>
#include <voba/value.h>

#define MAX_STR_CONST 1024
static char string_buf[MAX_STR_CONST];
static char *string_buf_ptr;

#define YY_DECL int yylex \
               (YYSTYPE * yylval_param, YYLTYPE * yylloc_param , yyscan_t yyscanner, voba_value_t source)


#define YY_USER_ACTION                                      \
    yylloc->start_pos = yylloc->end_pos;                    \
    yylloc->end_pos += yyleng;                              \
%}
%option yylineno
%option outfile="flex.c"
%option bison-bridge
%option bison-locations
%option reentrant
%option debug
%option noyywrap
%x comment str
DIGIT    [0-9]
ID       [a-zA-Z_><+*/=%:|.-][a-zA-Z0-9?_><+*/=%:|.-]*
%%


-?{DIGIT}+    {      /* ------INT_TOKEN----- */
    VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),voba_make_i32(atoi(yytext)),voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
    return T_VALUE;
}

-?{DIGIT}+"."{DIGIT}*        {   /* ------FLOAT_TOKEN----- */
    VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),voba_make_float(strtof(yytext,NULL)),voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
    return T_VALUE;
}

-?{DIGIT}*\.?{DIGIT}*e[-+]?{DIGIT}+        {   /* ------FLOAT_TOKEN----- */
     VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),voba_make_float(strtof(yytext,NULL)),voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
     return T_VALUE;
}

true  {
     VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),VOBA_TRUE,voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
     return T_VALUE;
}
false  {
     VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),VOBA_FALSE,voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
     return T_VALUE;
}
undef  {
     VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),VOBA_UNDEF,voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
     return T_VALUE;
}
nil  {
     VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),VOBA_NIL,voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
     return T_VALUE;
}
{ID}   {          /* -----------ID_TOKEN-------------- */
     // TODO: add a global variable for symbol table.
     VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),voba_make_symbol(voba_str_from_data(yytext,yyleng),VOBA_NIL),voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
     return T_VALUE;
}


\?\\[a-zA-Z] {
     return yytext[2];
}

\"      {  /*--------------STRING_TOKEN---------------*/
     string_buf_ptr = string_buf;
     BEGIN(str);
}
<str>\"        { /* saw closing quote - all done */
     BEGIN(INITIAL);
     *string_buf_ptr = '\0';
     // return the literal string
     VOBA_APPLY(*yylval,voba_symbol_value(s_make_2Dsyntax),voba_make_cstr(GC_strdup(string_buf)),voba_make_i32(yylloc->start_pos),voba_make_i32(yylloc->end_pos),source);
     return T_VALUE;
}
<str>\n        {
   // multiline constant literal string, 
   *string_buf_ptr++ = '\n';
}
<str>\\[0-7]{1,3} {
     /* octal escape sequence */
     int result;
     (void) sscanf( yytext + 1, "%o", &result );
     if ( result > 0xff )
          /* error, constant is out-of-bounds */
          *string_buf_ptr++ = result;
}

<str>\\[0-9]+ {
     /* generate error - bad escape sequence; something
      * like '\48' or '\0777777'
      */
     fprintf(stderr,"bad escap sequence.\n");
     exit(1);
}

<str>\\n  *string_buf_ptr++ = '\n';
<str>\\t  *string_buf_ptr++ = '\t';
<str>\\r  *string_buf_ptr++ = '\r';
<str>\\b  *string_buf_ptr++ = '\b';
<str>\\f  *string_buf_ptr++ = '\f';

<str>\\(.|\n)  *string_buf_ptr++ = yytext[1];

<str>[^\\\n\"]+        {
     char *yptr = yytext;
     while ( *yptr )
          *string_buf_ptr++ = *yptr++;
}


[`&(){};=,] {  // singal token
     return yytext[0];
}
\[     {
     return '[';
}
\] {
     return ']';
}
\' {
   return '\'';
}
#\ [0-9]+\ \"[^\"]+\"\ *[0-9]*\ *$ { /*line and file control for cpp output*/
     int line ;
     int flag;
     char * filename;
     int r;
     filename = (char*)malloc(strlen(yytext));
     r = sscanf(yytext,"# %d \"%[^\"]\" %d",&line,filename,&flag);
     if(r==0){
          assert(0);// can not read anything
     }else if(r==2){// flag is not provided by cpp
          //printf("file:%s:%d, noxx flags.\n",filename,line);
     }else if(r==3){ // a flag is available

     }else if(r==EOF){
          assert(0);
     }else {
          assert(0);
     }
     free(filename);
}

#.*$    { 
    /* eat up one-line comments */
    ;
}
;.*$    { 
    /* eat up one-line comments */
    ;
}
\/\/.*$    { 
   /* eat up c++ style one-line comments */
   ;
}

[ \f\t]+ { /* eat up whitespace */
}
\n   {
}

. {
   fprintf(stderr,"unrecoganized token %d %s\n", yytext[0], yytext);
   exit(1);
}
%%

void flex_foo()
{
   // avoid warning, unused function yyuninput
   if(0){
     yyunput(1,NULL,NULL);
     input(NULL);
   }
}
