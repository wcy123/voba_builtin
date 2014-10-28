#define EXEC_ONCE_TU_NAME "voba_builtin_module"
#define EXEC_ONCE_DEPENDS {"voba_module",NULL}
#include <voba/include/value.h>
#include <voba/include/module.h>
#include "builtin.h"
#include "str.h"
#include "str.c"

VOBA_FUNC static voba_value_t apply_array(voba_value_t self, voba_value_t v);
VOBA_FUNC static voba_value_t get_class(voba_value_t self,voba_value_t v);
VOBA_FUNC static voba_value_t print(voba_value_t self, voba_value_t a1) ;

EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_get_class,voba_make_func(get_class));
}
VOBA_FUNC static voba_value_t get_class(voba_value_t self, voba_value_t v)
{
    return voba_get_class(v);
}

// to_i32
static voba_value_t gf_to_i32 = VOBA_UNDEF;
EXEC_ONCE_PROGN{
    gf_to_i32 =  voba_make_generic_function("to_i32");
    VOBA_DEFINE_MODULE_SYMBOL(s_to_i32,gf_to_i32);
}
// apply
EXEC_ONCE_PROGN{voba_gf_add_class(voba_gf_apply,voba_cls_array,voba_make_func(apply_array));}
VOBA_FUNC static voba_value_t apply_array(voba_value_t self, voba_value_t v)
{
    int32_t index = voba_value_to_i32(voba_apply(gf_to_i32,v));
    return voba_array_at(self,index);
}
VOBA_FUNC static voba_value_t print(voba_value_t self, voba_value_t a1) 
{
    int64_t len = voba_array_len(a1);
    for(int i = 0; i < len; ++i){
        voba_value_t args[] = {1,voba_array_at(a1,i)};
        voba_value_t s = voba_apply(gf_str,voba_make_array(args));
        fwrite((const void*)voba_str_to_cstr(voba_value_to_str(s)),1,voba_strlen(voba_value_to_str(s)),stdout);
        if(i!=0){
             fputc(' ',stdout);
        }
    }
    fputc('\n',stdout);
    return VOBA_NIL;
}
EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_print, voba_make_func(print));
}

// _2B = +
VOBA_FUNC static voba_value_t plus_string(voba_value_t self, voba_value_t args)
{
    voba_str_t* ret = voba_str_empty();
    int64_t len = voba_array_len(args);
    for(int64_t i = 0; i < len; ++i){
        voba_value_t ai = voba_array_at(args,i);
        if(voba_get_class(ai) == voba_cls_str){
            ret = voba_strcat(ret, voba_value_to_str(ai));
        }else{
            voba_value_t tmp_args[] = {1,ai};
            voba_value_t s = voba_apply(gf_str,voba_make_array(tmp_args));
            ret = voba_strcat(ret, voba_value_to_str(s));
        }
    }
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t plus_int(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = voba_make_i32(0);
    int64_t r = 0;
    int64_t len = voba_array_len(args);
    for(int64_t i = 0; i < len; ++i){
        voba_value_t x = voba_array_at(args,i);
        if(voba_is_int(x)){
            r += voba_int_value_to_i64(x);
        }else{
            ret = VOBA_UNDEF;
            break;
        }
    }
    if(!voba_is_undef(ret)){
        ret = i64_to_voba_int_value(r);
    }
    return ret;
}
static voba_value_t gf_plus = VOBA_UNDEF;
EXEC_ONCE_PROGN{
    gf_plus = voba_make_generic_function("+");
    VOBA_DEFINE_MODULE_SYMBOL(s__2B, gf_plus);
    voba_gf_add_class(gf_plus,voba_cls_str,voba_make_func(plus_string));
    voba_gf_add_class(gf_plus,voba_cls_i8,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_i16,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_i32,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_u8,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_u16,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_u32,voba_make_func(plus_int));
}
/*
 * ==, >, <, >=, and <=
 * usually, you only need to define `==' and `>'
 */
static voba_value_t gf_equal = VOBA_UNDEF;
static voba_value_t gf_gt = VOBA_UNDEF;
static voba_value_t gf_gt_eq = VOBA_UNDEF;
static voba_value_t gf_lt = VOBA_UNDEF;
static voba_value_t gf_lt_eq = VOBA_UNDEF;
VOBA_FUNC static voba_value_t equal_int(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_ASSERT_N_ARG(args,0); voba_value_t a = voba_array_at(args,0);
;
    VOBA_ASSERT_N_ARG(args,1); voba_value_t b = voba_array_at(args,1);
;
    if(voba_is_int(b)){
        int64_t a1 = voba_int_value_to_i64(a);
        int64_t b1 = voba_int_value_to_i64(b);
        if(a1==b1) ret = VOBA_TRUE;
    }else{
        ret = VOBA_UNDEF;
    }
    return ret;
}
VOBA_FUNC static voba_value_t gt_int(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_ASSERT_N_ARG(args,0); voba_value_t a = voba_array_at(args,0);
;
    VOBA_ASSERT_N_ARG(args,1); voba_value_t b = voba_array_at(args,1);
;
    if(voba_is_int(b)){
        int64_t a1 = voba_int_value_to_i64(a);
        int64_t b1 = voba_int_value_to_i64(b);
        if(a1>b1) ret = VOBA_TRUE;
    }else{
        ret = VOBA_UNDEF;
    }
    return ret;
}
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
EXEC_ONCE_PROGN{
    gf_gt = voba_make_generic_function(">");
    gf_gt_eq = voba_make_generic_function(">=");
    gf_lt = voba_make_generic_function("<");
    gf_lt_eq = voba_make_generic_function(">=");
    gf_equal = voba_make_generic_function("==");

    VOBA_GF(gf_gt_eq)->fun = gt_eq;
    VOBA_GF(gf_lt)->fun = lt;
    VOBA_GF(gf_lt_eq)->fun = lt_eq;
    
    VOBA_DEFINE_MODULE_SYMBOL(s__3D_3D, gf_equal);
    VOBA_DEFINE_MODULE_SYMBOL(s__3E, gf_gt);
    VOBA_DEFINE_MODULE_SYMBOL(s__3C, gf_lt);
    VOBA_DEFINE_MODULE_SYMBOL(s__3E_3D, gf_gt_eq);
    VOBA_DEFINE_MODULE_SYMBOL(s__3C_3D, gf_lt_eq);

    voba_gf_add_class(gf_gt,voba_cls_i8,voba_make_func(gt_int));
    voba_gf_add_class(gf_equal,voba_cls_i8,voba_make_func(equal_int));
    
    voba_gf_add_class(gf_gt,voba_cls_i16,voba_make_func(gt_int));
    voba_gf_add_class(gf_equal,voba_cls_i16,voba_make_func(equal_int));
    
    voba_gf_add_class(gf_gt,voba_cls_i32,voba_make_func(gt_int));
    voba_gf_add_class(gf_equal,voba_cls_i32,voba_make_func(equal_int));
    
    voba_gf_add_class(gf_gt,voba_cls_u8,voba_make_func(gt_int));
    voba_gf_add_class(gf_equal,voba_cls_u8,voba_make_func(equal_int));
    
    voba_gf_add_class(gf_gt,voba_cls_u16,voba_make_func(gt_int));
    voba_gf_add_class(gf_equal,voba_cls_u16,voba_make_func(equal_int));
    
    voba_gf_add_class(gf_gt,voba_cls_u32,voba_make_func(gt_int));
    voba_gf_add_class(gf_equal,voba_cls_u32,voba_make_func(equal_int));
    
}
//
static voba_value_t gf_match = VOBA_UNDEF;
VOBA_FUNC static voba_value_t match_single(voba_value_t self, voba_value_t args) 
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_ASSERT_N_ARG(args,0); voba_value_t cls = voba_array_at(args,0);
;
    VOBA_ASSERT_N_ARG(args,1); voba_value_t v = voba_array_at(args,1);
;
    VOBA_ASSERT_N_ARG(args,2); voba_value_t index = voba_array_at(args,2);
;
    VOBA_ASSERT_N_ARG(args,3); voba_value_t len = voba_array_at(args,3);
;
    int32_t index1 = voba_value_to_i32(index);
    int32_t len1 = voba_value_to_i32(len);
    switch(index1){
    case -1:
        if(len1 == 1 && voba_is_a(v,cls)){
            ret = VOBA_TRUE;
        }
        break;
    case 0:
        assert(len1 == 1);
        ret = v;
        break;
    default:
        assert(0&&"never goes here");
    }
    return ret;
}
EXEC_ONCE_PROGN{
    gf_match = voba_module_var(VOBA_MODULE_LANG_ID,
                               VOBA_MODULE_LANG_ID,VOBA_MODULE_LANG_MATCH);
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_i8, voba_cls_i8);
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i8,voba_make_func(match_single));
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_i16, voba_cls_i16);
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i16,voba_make_func(match_single));
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_i32, voba_cls_i32);
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i32,voba_make_func(match_single));
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_u8, voba_cls_u8);
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u8,voba_make_func(match_single));
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_u16, voba_cls_u16);
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u16,voba_make_func(match_single));
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_u32, voba_cls_u32);
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u32,voba_make_func(match_single));
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_float, voba_cls_float);
    voba_gf_add_class(voba_symbol_value(gf_match),
                      voba_cls_float,voba_make_func(match_single));
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_str, voba_cls_str);
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_str,voba_make_func(match_single));
}

/* iterator */
VOBA_FUNC static voba_value_t iter_array_next (voba_value_t self, voba_value_t args);
VOBA_FUNC static voba_value_t iter_array (voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0); voba_value_t a = voba_array_at(args,0);
VOBA_ASSERT_CLS(a,voba_cls_array,0);
;
    voba_value_t ret = voba_make_closure_2
        (iter_array_next,a,0);
    return ret;
}
VOBA_FUNC static voba_value_t iter_array_next (voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(self,0); voba_value_t a = voba_array_at(self,0);
VOBA_ASSERT_CLS(a,voba_cls_array,0);
;
    VOBA_ASSERT_N_ARG(self,1); voba_value_t i = voba_array_at(self,1);
;
    int64_t len = voba_array_len(a);
    voba_value_t ret = VOBA_UNDEF;
    if(i < len){
        ret = voba_array_at(a, i);
        i++;
        voba_array_set(self,1,i);
    }
    return ret;
}
static voba_value_t gf_iter = VOBA_UNDEF;
EXEC_ONCE_PROGN{
    gf_iter = voba_make_generic_function("iter");
    VOBA_DEFINE_MODULE_SYMBOL(s_iter, gf_iter);
    voba_gf_add_class(gf_iter,
                      voba_cls_array,
                      voba_make_func(iter_array));
}
/* range */
VOBA_FUNC static voba_value_t range_next(voba_value_t self, voba_value_t args);
VOBA_FUNC static voba_value_t range(voba_value_t self, voba_value_t args)
{
    int64_t len = voba_array_len(args);
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t a1 = voba_array_at( args, 0);
    VOBA_ASSERT_CLS(a1,voba_cls_i32, 0);
    voba_value_t from = voba_make_i32(0);
    voba_value_t to = voba_make_i32(0);
    voba_value_t step = voba_make_i32(1);
    switch(len){
    case 0:
        assert(0&&"never goes here");
        break;
    case 1:
        from = voba_make_i32(0);
        to = a1;
        break;
    case 2:{
        voba_value_t a2 = voba_array_at( args, 1);
        VOBA_ASSERT_CLS(a2, voba_cls_i32, 1);
        from = a1;
        to = a2;
        break;
    }
    case 3:{
        voba_value_t a2 = voba_array_at( args, 1);
        VOBA_ASSERT_CLS(a2, voba_cls_i32, 1);
        voba_value_t a3 = voba_array_at( args, 2);
        VOBA_ASSERT_CLS(a3, voba_cls_i32, 2);
        from = a1;
        to = a2;
        step = a3;
        break;
    }
    }
    int64_t ifrom = voba_value_to_i32(from);
    int64_t ito = voba_value_to_i32(to);
    int64_t istep = voba_value_to_i32(step);
    if(!((istep < 0 && ito >= ifrom) ||
         (istep > 0 && ifrom <= ito ))){
        VOBA_THROW(VOBA_CONST_CHAR("infinite loop: "),
                   VOBA_CONST_CHAR(" from = "),
                   voba_str_fmt_int32_t(ifrom,10),
                   VOBA_CONST_CHAR(" to = "),
                   voba_str_fmt_int32_t(ito,10),
                   VOBA_CONST_CHAR(" step = "),
                   voba_str_fmt_int32_t(istep,10));
    }
    return voba_make_closure_3(range_next, ifrom, ito, istep);
}
VOBA_FUNC static voba_value_t range_next(voba_value_t self, voba_value_t args)
{
    int64_t len = voba_array_len(self);
    assert(len == 3);
    int64_t from = voba_array_at(self,0);
    int64_t to   = voba_array_at(self,1);
    int64_t step = voba_array_at(self,2);
    assert((step < 0 && to >= from) ||
           (step > 0 && from <= to ));
    voba_value_t ret = VOBA_UNDEF;
    if(from != to){
        ret = voba_make_i32((int32_t) from);
        from += step;
        voba_array_set(self,0,from);
    }
    return ret;
}
EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_range, voba_make_func(range));
}

// the main entry
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
