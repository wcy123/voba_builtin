#define EXEC_ONCE_TU_NAME "voba.builtin.function"
#define EXEC_ONCE_DEPENDS {"voba.builtin",NULL}
#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"
/* iter */
VOBA_FUNC voba_value_t iter_func (voba_value_t self, voba_value_t args)
{
    return voba_array_at(args,0);
}
EXEC_ONCE_PROGN {
    voba_gf_add_class(voba_symbol_value(s_gf_iter), voba_cls_func, voba_make_func(iter_func));
    voba_gf_add_class(voba_symbol_value(s_gf_iter), voba_cls_closure, voba_make_func(iter_func));
}
