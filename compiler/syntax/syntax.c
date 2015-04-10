#include <stdlib.h>
#define EXEC_ONCE_TU_NAME "voba.compiler.syntax"
#include <exec_once.h>
#include <voba/value.h>
#include "syntax.h"
#include "syntax_c.h"
extern voba_value_t voba_cls_syntax;
VOBA_DEF_CLS(sizeof(syntax_t),syntax);
void syntax_get_line_column(int start, voba_value_t syntax,uint32_t * line, uint32_t * col);
VOBA_FUNC static voba_value_t syntax_to_string(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  syntax = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(syntax,voba_cls_syntax,0);
    voba_value_t tmp_args[] = {1,SYNTAX(syntax)->value};
    return voba_apply(voba_gf_to_string, voba_make_tuple(tmp_args));
}
static voba_value_t make_syntax_1(voba_value_t v, uint32_t start_pos, uint32_t end_pos,voba_value_t source)
{
    voba_value_t ret = voba_make_user_data(voba_cls_syntax);
    SYNTAX(ret)->value = v;
    SYNTAX(ret)->start_pos = start_pos;
    SYNTAX(ret)->end_pos = end_pos;
    SYNTAX(ret)->source = source;
    return ret;
}
VOBA_FUNC static voba_value_t make_syntax(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG(args, 0);
    voba_value_t value = voba_tuple_at(args, 0);
    VOBA_ASSERT_N_ARG(args, 1);
    voba_value_t start_pos = voba_tuple_at(args,1);
    VOBA_ASSERT_ARG_ISA(start_pos,voba_cls_i32,1);
    VOBA_ASSERT_N_ARG(args, 2);
    voba_value_t end_pos = voba_tuple_at(args,2);
    VOBA_ASSERT_ARG_ISA(start_pos,voba_cls_i32,2);
    VOBA_ASSERT_N_ARG(args,3);
    voba_value_t source = voba_tuple_at(args,2);
    // VOBA_ASSERT_ARG_ISA(syntax,voba_cls_syntax,1);
    return make_syntax_1(value
                         ,(uint32_t)voba_value_to_i32(start_pos)
                         ,(uint32_t)voba_value_to_i32(end_pos)
                         ,source);
}
VOBA_FUNC static voba_value_t syntax_value(voba_value_t fun,voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  syntax = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(syntax,voba_cls_syntax,0);
    return SYNTAX(syntax)->value;
}
VOBA_FUNC static voba_value_t syntax_start_pos(voba_value_t fun,voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  syntax = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(syntax,voba_cls_syntax,0);
    return voba_make_i32((int32_t)SYNTAX(syntax)->start_pos);
}
VOBA_FUNC static voba_value_t syntax_end_pos(voba_value_t fun,voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  syntax = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(syntax,voba_cls_syntax,0);
    return voba_make_i32((int32_t)SYNTAX(syntax)->end_pos);
}
VOBA_FUNC static voba_value_t syntax_source(voba_value_t fun,voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  syntax = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(syntax,voba_cls_syntax,0);
    return SYNTAX(syntax)->source;
}
EXEC_ONCE_PROGN{
    voba_gf_add_class(voba_gf_to_string, voba_cls_syntax, voba_make_func(syntax_to_string));
    VOBA_DEFINE_MODULE_SYMBOL(s_make_2Dsyntax,voba_make_func(make_syntax));
    VOBA_DEFINE_MODULE_SYMBOL(s_syntax_2Dvalue,voba_make_func(syntax_value));
    VOBA_DEFINE_MODULE_SYMBOL(s_syntax_2Dstart_pos,voba_make_func(syntax_start_pos));
    VOBA_DEFINE_MODULE_SYMBOL(s_syntax_2Dend_pos,voba_make_func(syntax_end_pos));
    VOBA_DEFINE_MODULE_SYMBOL(s_syntax_2Dsource,voba_make_func(syntax_source));
    VOBA_DEFINE_MODULE_SYMBOL(s_syntax_2Dclass, voba_cls_syntax);
}
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
