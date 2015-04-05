#define EXEC_ONCE_TU_NAME "voba.compiler.parser"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <voba/value.h>
#include <exec_once.h>
#include "./parser.h"
#include "../source/source.h"
#include "../source/source_c.h"
#include "./parser_y.h"
typedef void *yyscan_t ;
int yylex_init ( yyscan_t * ptr_yy_globals ) ;
int yylex_destroy ( yyscan_t yyscanner ) ;
void yyset_debug (int  bdebug , yyscan_t yyscanner);
struct yy_buffer_state*  yy_scan_bytes (char *bytes,int len ,yyscan_t yyscanner );
extern int yydebug;
EXEC_ONCE_PROGN{
    yydebug = getenv("VOBA_YYDEBUG") != NULL;
}
voba_value_t src2syn(voba_value_t source)
{
    voba_str_t * content = SOURCE(source)->content;
    void * scanner;
    yylex_init(&scanner);
    yy_scan_bytes(content->data,content->len,scanner);
    voba_value_t ret =  VOBA_NIL;
    yyparse(scanner,&ret, source);
    yylex_destroy(scanner);
    return ret;
}
VOBA_FUNC static voba_value_t parse(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t source = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(source,voba_symbol_value(s_source_2Dclass),0);
    return src2syn(source);
}
EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_parse,voba_make_func(parse));
}
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
