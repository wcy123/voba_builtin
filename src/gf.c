#define EXEC_ONCE_TU_NAME "voba.builtin.gf"
#define EXEC_ONCE_DEPENDS {"voba.module"}
#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"
/*
 * ==, >, <, >=, and <=
 * usually, you only need to define `==' and `>'
 * so no default implementation for `==' and `>'
 */
VOBA_FUNC static voba_value_t gt_eq(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    voba_value_t ret = voba_apply(gf_equal, args);
    if(voba_eq(ret,VOBA_FALSE)){
        ret = voba_apply(gf_gt,args);
    }
    return ret;
}
VOBA_FUNC static voba_value_t lt(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    return voba_not(voba_apply(gf_gt_eq,args));
}
VOBA_FUNC static voba_value_t lt_eq(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    return voba_not(voba_apply(gf_gt,args));
}
voba_value_t gf_len = VOBA_UNDEF;
voba_value_t gf_apply = VOBA_UNDEF;
voba_value_t gf_equal = VOBA_UNDEF;
voba_value_t gf_gt = VOBA_UNDEF;
voba_value_t gf_gt_eq = VOBA_UNDEF;
voba_value_t gf_lt = VOBA_UNDEF;
voba_value_t gf_lt_eq = VOBA_UNDEF;
voba_value_t gf_plus = VOBA_UNDEF;
voba_value_t gf_mod = VOBA_UNDEF;
voba_value_t gf_left_shift = VOBA_UNDEF;
EXEC_ONCE_PROGN{
    gf_len = voba_make_generic_function("len",0);
    gf_apply = voba_make_generic_function("apply",0);
    gf_equal = voba_make_generic_function("==",0);
    gf_gt = voba_make_generic_function(">",0);
    gf_gt_eq = voba_make_generic_function(">=",gt_eq);
    gf_lt = voba_make_generic_function("<",lt);
    gf_lt_eq = voba_make_generic_function("<=",lt_eq);
    gf_plus = voba_make_generic_function("+",0);
    gf_mod = voba_make_generic_function("%",0);
    gf_left_shift = voba_make_generic_function("<<",0);
}



