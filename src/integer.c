#define EXEC_ONCE_TU_NAME "voba.builtin.integer"
#define EXEC_ONCE_DEPENDS {"voba.builtin"}
#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"

static inline int voba_is_int(voba_value_t a )
{
    return voba_is_a(a,voba_cls_i32);
}
/* comparison */

VOBA_FUNC static voba_value_t equal_int(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t b = voba_tuple_at(args,1);
    if(voba_is_int(b)){
        int64_t a1 = voba_value_to_i32(a);
        int64_t b1 = voba_value_to_i32(b);
        if(a1==b1) ret = VOBA_TRUE;
    }else{
        ret = VOBA_UNDEF;
    }
    return ret;
}
VOBA_FUNC static voba_value_t gt_int(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t b = voba_tuple_at(args,1);
    if(voba_is_int(b)){
        int64_t a1 = voba_value_to_i32(a);
        int64_t b1 = voba_value_to_i32(b);
        if(a1>b1) ret = VOBA_TRUE;
    }else{
        ret = VOBA_UNDEF;
    }
    return ret;
}
/* + */
VOBA_FUNC static voba_value_t plus_int(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    voba_value_t ret = voba_make_i32(0);
    int64_t r = 0;
    int64_t len = voba_tuple_len(args);
    for(int64_t i = 0; i < len; ++i){
        voba_value_t x = voba_tuple_at(args,i);
        if(voba_is_int(x)){
            r += voba_value_to_i32(x);
        }else{
            ret = VOBA_UNDEF;
            break;
        }
    }
    if(!voba_is_undef(ret)){
        ret = voba_make_i32((int32_t)r);
    }else{
    }
    return ret;
}

/* % */
VOBA_FUNC static voba_value_t mod_int(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    voba_value_t ret = VOBA_UNDEF;
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a, voba_cls_i32, 0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t b = voba_tuple_at(args,1);
    VOBA_ASSERT_ARG_ISA(b, voba_cls_i32, 1);
    int32_t a1 = voba_value_to_i32(a);
    int32_t b1 = voba_value_to_i32(b);
    int32_t c = a1 % b1;
    ret = voba_make_i32(c);
    return ret;
}

EXEC_ONCE_PROGN{
    voba_gf_add_class(gf_plus,voba_cls_i32,voba_make_func(plus_int));
    voba_gf_add_class(gf_mod,voba_cls_i32,voba_make_func(mod_int));
    voba_gf_add_class(gf_gt,voba_cls_i32,voba_make_func(gt_int));
    voba_gf_add_class(gf_equal,voba_cls_i32,voba_make_func(equal_int));
}
