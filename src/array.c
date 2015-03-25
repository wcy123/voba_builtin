#define EXEC_ONCE_TU_NAME "voba.builtin.array"
#define EXEC_ONCE_DEPENDS {"voba.builtin"}
#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"
/* str */
/* gf len */
VOBA_FUNC static voba_value_t len_array(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a,voba_cls_array,0);
    return voba_make_u32((uint32_t)voba_array_len(a));
}
/* gf << */
VOBA_FUNC static voba_value_t array_left_shift(voba_value_t self, voba_value_t args)
{
    int64_t len = voba_tuple_len(args);
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a,voba_cls_array,0);
    for(int64_t i = 1; i < len; ++i){
        a = voba_array_push(a,voba_tuple_at(args,i));
    }
    return a;
}
VOBA_FUNC voba_value_t array (voba_value_t self, voba_value_t args)
{
    return voba_array_from_tuple(args);
}

EXEC_ONCE_PROGN{
    voba_gf_add_class(gf_len, voba_cls_array,voba_make_func(len_array));
    voba_gf_add_class(gf_left_shift, voba_cls_array,voba_make_func(array_left_shift));
}
VOBA_FUNC static voba_value_t iter_array_closure(voba_value_t self, voba_value_t args);
VOBA_FUNC voba_value_t array_iter(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_NIL;
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a,voba_cls_array,0);
    ret = voba_make_closure_2(iter_array_closure,a,0);
    return ret;
}
VOBA_FUNC static voba_value_t iter_array_closure(voba_value_t self, voba_value_t args)
{
    voba_value_t a = voba_tuple_at(self,0);
    voba_value_t i = voba_tuple_at(self,1);
    int64_t len = voba_array_len(a);
    voba_value_t ret = VOBA_DONE;
    if(i < len){
        ret = voba_array_at(a, i);
        i++;
        voba_tuple_set(self,1,i);
    }
    return ret;
}
