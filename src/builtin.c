#define EXEC_ONCE_TU_NAME "voba.builtin"
// "voba.builtin.gf": generic function objects must be defined first
// "voba.module": I don't remember why depends on it.
#define EXEC_ONCE_DEPENDS {"voba.builtin.gf"}
#include <voba/value.h>
#include <voba/module.h>
#include "builtin.h"
#include "gf.h"
#include "range.h"
#include "array.h"
#include "other.h"

VOBA_FUNC static voba_value_t f_eq(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t b = voba_tuple_at(args,1);
    return a == b ? VOBA_TRUE:VOBA_FALSE;
}
VOBA_FUNC static voba_value_t i32_mod(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a, voba_cls_i32, 0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t b = voba_tuple_at(args,1);
    VOBA_ASSERT_ARG_ISA(b, voba_cls_i32, 1);
    a = (a>>8);
    b = (b>>8);
    voba_value_t c = a%b;
    return voba_make_i32((int32_t)c);
}
VOBA_FUNC static voba_value_t eq_i32_mod_0(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a, voba_cls_i32, 0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t b = voba_tuple_at(args,1);
    VOBA_ASSERT_ARG_ISA(b, voba_cls_i32, 1);
    a = (a>>8);
    b = (b>>8);
    voba_value_t c = a%b;
    return c == 0 ? VOBA_TRUE: VOBA_FALSE;
}

EXEC_ONCE_PROGN{
    /* functions */
    VOBA_DEFINE_MODULE_SYMBOL(s_get_class,voba_make_func(get_class));
    VOBA_DEFINE_MODULE_SYMBOL(s_str, voba_gf_to_string);
    VOBA_DEFINE_MODULE_SYMBOL(s_range, voba_make_func(range));
    VOBA_DEFINE_MODULE_SYMBOL(s_print, voba_make_func(voba_print));
    VOBA_DEFINE_MODULE_SYMBOL(s_array, voba_make_func(array));
    VOBA_DEFINE_MODULE_SYMBOL(s_eq, voba_make_func(f_eq));
    VOBA_DEFINE_MODULE_SYMBOL(s_i32_mod, voba_make_func(i32_mod));
    VOBA_DEFINE_MODULE_SYMBOL(s_eq_i32_mod_0, voba_make_func(eq_i32_mod_0));
    VOBA_DEFINE_MODULE_SYMBOL(s_len, gf_len);
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
    /* % mod */
    VOBA_DEFINE_MODULE_SYMBOL(s__25, gf_mod);
    /* << */
    VOBA_DEFINE_MODULE_SYMBOL(s__3C_3C, gf_left_shift);
    /* cls */
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_i32, voba_cls_i32);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_float, voba_cls_float);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_str, voba_cls_str);
    /* array iterator */
    VOBA_DEFINE_MODULE_SYMBOL(s_array_2Diter,voba_make_func(array_iter));
}
/** @brief match for builtin classes
 @todo add document for this function.
 */
VOBA_FUNC static voba_value_t isa_closure(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    voba_value_t cls = voba_tuple_at(fun,0);
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t v = voba_tuple_at(args,0);
    int64_t args_len = voba_tuple_len(args);
    voba_value_t ret = voba_is_a(v,cls);
    switch(args_len){
    case 1: break;// do nothing, normal function invoke
    case 3:{ // pattern match
        voba_value_t index = voba_tuple_at(args,1);
        voba_value_t len = voba_tuple_at(args,2);
        int32_t index1 = voba_value_to_i32(index);
        int32_t len1 = voba_value_to_i32(len);
        switch(index1){
        case -1: // check if the number of argument match
            if(len1 == 1 && voba_is_a(v,cls)){
                ret = VOBA_TRUE;
            }else{
                ret = VOBA_FALSE;
            }
            break;
        case 0:
            assert(len1 == 1);
            assert(voba_is_a(v,cls));
            ret = v;
            break;
        default:
            assert(0&&"never goes here");
        }
    }
    }
    return ret;
}
VOBA_FUNC static voba_value_t isa(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[]) 
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t cls = voba_tuple_at(args,0);
    return voba_make_closure_1(isa_closure,cls);
}
EXEC_ONCE_PROGN {
    VOBA_DEFINE_MODULE_SYMBOL(s_isa,voba_make_func(isa));
}
VOBA_FUNC static voba_value_t match_tuple(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t value = voba_tuple_at(args,0);
    voba_value_t ret = VOBA_FALSE;
    if(!voba_is_a(value,voba_cls_tuple)){
        ret = VOBA_FALSE;
    }else{
        voba_value_t len = voba_tuple_len(value);
        VOBA_ASSERT_N_ARG(args,1);
        int32_t index = voba_value_to_i32(voba_tuple_at(args,1));
        VOBA_ASSERT_N_ARG(args,2);
        int32_t match_len = voba_value_to_i32(voba_tuple_at(args,2));
        if(index == -1){
            if( match_len != len ){
                ret = VOBA_FALSE;
            }else{
                ret = VOBA_TRUE;
            }
        }else{
            assert(index < match_len);
            assert(index < len);
            ret = voba_tuple_at(value,index);
        }
    }
    return ret;
}
EXEC_ONCE_PROGN {
    VOBA_DEFINE_MODULE_SYMBOL(s_match_2Dtuple, voba_make_func(match_tuple));
}

VOBA_FUNC static voba_value_t tuple(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    int64_t len = voba_tuple_len(args);
    voba_value_t * p = voba_alloc(len + 1);
    p[0] = len;
    voba_value_t ret = voba_make_tuple(p);
#ifndef NDEBUG
    void * r =
#endif
	memcpy(voba_tuple_base(ret), voba_tuple_base(args),sizeof(voba_value_t)*len);
    assert(r!=NULL);
    return ret;
}
EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_tuple,voba_make_func(tuple));
}
// the main entry
voba_value_t voba_init(voba_value_t this_module)
{
    return VOBA_NIL;
}
