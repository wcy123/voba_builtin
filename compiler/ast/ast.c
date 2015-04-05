#define EXEC_ONCE_TU_NAME "voba.compiler.ast"
#include <voba/value.h>
#include "exec_once.h"
#include "ast.h"
#include "ast_c.h"
VOBA_DEF_CLS(sizeof(ast_t),ast);
VOBA_FUNC static voba_value_t make_2Dast(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_NIL;
    return ret;
}
VOBA_FUNC static voba_value_t ast_to_string(voba_value_t self, voba_value_t args)
{
    return voba_make_string(voba_str_from_cstr("not implemeneted"));
}
EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_make_2Dast, voba_make_func(make_2Dast));
    voba_gf_add_class(voba_gf_to_string,voba_cls_ast,voba_make_func(ast_to_string));
    VOBA_DEFINE_MODULE_SYMBOL(s_ast_2Dclass, voba_cls_ast);    
}
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
