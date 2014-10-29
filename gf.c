#define EXEC_ONCE_TU_NAME "voba.builtin.gf"
#define EXEC_ONCE_DEPENDS {"voba.builtin",NULL}
#include <voba/include/value.h>
#include <voba/include/module.h>
#include "builtin.h"
#include "gf.h"


/*
 * ==, >, <, >=, and <=
 * usually, you only need to define `==' and `>'
 * so no default implementation for `==' and `>'
 */
VOBA_FUNC static voba_value_t gt_eq(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = voba_apply(gf_equal, args);
    if(voba_eq(ret,VOBA_FALSE)){
        ret = voba_apply(gf_gt,args);
    }
    return ret;
}
VOBA_FUNC static voba_value_t lt(voba_value_t self, voba_value_t args)
{
    return voba_not(voba_apply(gf_gt_eq,args));
}
VOBA_FUNC static voba_value_t lt_eq(voba_value_t self, voba_value_t args)
{
    return voba_not(voba_apply(gf_gt,args));
}

voba_value_t gf_match = VOBA_UNDEF;


EXEC_ONCE_PROGN{
    VOBA_GF(gf_gt_eq)->fun = gt_eq;
    VOBA_GF(gf_lt)->fun = lt;
    VOBA_GF(gf_lt_eq)->fun = lt_eq;
}
