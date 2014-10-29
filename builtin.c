#define EXEC_ONCE_TU_NAME "voba_builtin_module"
#define EXEC_ONCE_DEPENDS {"voba_module",NULL}
#include <voba/include/value.h>
#include <voba/include/module.h>
#include "builtin.h"
#include "gf.h"
#include "match.h"

#include "gf.c"
#include "range.c"
#include "print.c"
#include "array.c"
#include "match.c"
#include "integer.c"
#include "str.c"
#include "other.c"

EXEC_ONCE_PROGN{
    /* functions */
    VOBA_DEFINE_MODULE_SYMBOL(s_get_class,voba_make_func(get_class));
    VOBA_DEFINE_MODULE_SYMBOL(s_range, voba_make_func(range));
    VOBA_DEFINE_MODULE_SYMBOL(s_print, voba_make_func(print));
    /* gf */
    VOBA_DEFINE_MODULE_SYMBOL(s_iter, gf_iter);
    VOBA_DEFINE_MODULE_SYMBOL(s_str, gf_str);
    /* + */
    VOBA_DEFINE_MODULE_SYMBOL(s__2B, gf_plus);
    /* == equal*/
    VOBA_DEFINE_MODULE_SYMBOL(s__3D_3D, gf_equal);
    /* > gt */
    VOBA_DEFINE_MODULE_SYMBOL(s__3E, gf_gt);
    /* < lt */
    VOBA_DEFINE_MODULE_SYMBOL(s__3C, gf_lt);
    /* >= gt_eq */
    VOBA_DEFINE_MODULE_SYMBOL(s__3E_3D, gf_gt_eq);
    /* <= lt_eq*/
    VOBA_DEFINE_MODULE_SYMBOL(s__3C_3D, gf_lt_eq);
    /* cls */
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_i8, voba_cls_i8);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_i16, voba_cls_i16);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_i32, voba_cls_i32);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_u8, voba_cls_u8);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_u16, voba_cls_u16);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_u32, voba_cls_u32);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_float, voba_cls_float);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_str, voba_cls_str);
}

// the main entry
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
