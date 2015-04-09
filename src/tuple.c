#define EXEC_ONCE_TU_NAME "voba.builtin.tuple"
#define EXEC_ONCE_DEPENDS {"voba.builtin"}
#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"
/* gf len */
VOBA_FUNC static voba_value_t len_tuple(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a,voba_cls_tuple,0);
    return voba_make_i32((int32_t)voba_tuple_len(a));
}
EXEC_ONCE_PROGN{
    voba_gf_add_class(gf_len, voba_cls_tuple,voba_make_func(len_tuple));
}
