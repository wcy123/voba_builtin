#define EXEC_ONCE_TU_NAME "voba_builtin_module"
#define EXEC_ONCE_DEPENDS {"voba_module",NULL}
#include <voba/include/value.h>
#include <voba/include/module.h>
#include "builtin.h"

VOBA_FUNC static voba_value_t get_class(voba_value_t self,voba_value_t v);
VOBA_FUNC static voba_value_t print(voba_value_t self, voba_value_t a1) ;
VOBA_FUNC static voba_value_t to_string_string(voba_value_t self,voba_value_t v);
VOBA_FUNC static voba_value_t to_string_funcp(voba_value_t self, voba_value_t v);
VOBA_FUNC static voba_value_t apply_array(voba_value_t self, voba_value_t v);
VOBA_FUNC static voba_value_t to_string_array(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t to_string_closure(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t to_string_pair(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t to_string_la(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t to_string_undef(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t to_string_nil(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t to_string_boolean(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t to_string_symbol(voba_value_t self,voba_value_t vs);

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
    gf_to_i32 =  voba_make_generic_function();
    VOBA_DEFINE_MODULE_SYMBOL(s_to_i32,gf_to_i32);
}
// apply
EXEC_ONCE_PROGN{voba_gf_add_class(voba_gf_apply,voba_cls_array,voba_make_func(apply_array));}
VOBA_FUNC static voba_value_t apply_array(voba_value_t self, voba_value_t v)
{
    int32_t index = voba_value_to_i32(voba_apply(gf_to_i32,v));
    return voba_array_at(self,index);
}

// to_string
static voba_value_t gf_to_string = VOBA_UNDEF;
EXEC_ONCE_PROGN{
    gf_to_string = voba_make_generic_function();
    VOBA_DEFINE_MODULE_SYMBOL(s_to_string, gf_to_string);
}
EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_str,voba_make_func(to_string_string));}
VOBA_FUNC static voba_value_t to_string_string(voba_value_t self,voba_value_t v)
{
    voba_str_t* ret = voba_str_from_char('"',1);
    ret = voba_strcat(ret,voba_value_to_str(voba_array_at(v,0)));
    ret = voba_strcat_char(ret,'"');
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_func,voba_make_func(to_string_funcp));}
VOBA_FUNC static voba_value_t to_string_funcp(voba_value_t self, voba_value_t v)
{
    voba_str_t * ret = voba_str_empty();
    ret = voba_strcat_cstr(ret,"<funcp ");
    ret = voba_strcat(ret,voba_str_fmt_pointer(((void*)voba_array_at(v,0))));
    ret = voba_strcat_cstr(ret," >");    
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_closure,voba_make_func(to_string_closure));}
VOBA_FUNC static voba_value_t to_string_closure(voba_value_t self,voba_value_t vs)
{
    voba_str_t *ret = voba_str_empty();
    ret = voba_strcat_cstr(ret,"<closure ");
    ret = voba_strcat(ret,voba_str_fmt_pointer((void*) (intptr_t)voba_closure_func(voba_array_at(vs,0))));
    ret = voba_strcat_char(ret,',');
    ret = voba_strcat(ret,voba_str_fmt_uint32_t(voba_array_len(voba_closure_array(voba_array_at(vs,0))),10));
    ret = voba_strcat_char(ret,'>');
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_array,voba_make_func(to_string_array));}
VOBA_FUNC static  voba_value_t to_string_array(voba_value_t self,voba_value_t vs)
{
    voba_value_t v = voba_array_at(vs,0);
    int64_t len = voba_array_len(v);
    voba_value_t * p = voba_array_base(v);
    voba_str_t* ret = voba_str_empty();
    ret = voba_strcat_char(ret,'[');
    for(int i = 0; i < len ; ++i){
        if(i!=0){
            ret = voba_strcat_char(ret,',');
        }
        voba_value_t args[] = {1,p[i]};
        ret = voba_strcat(ret,
                          voba_value_to_str(voba_apply(gf_to_string,voba_make_array(args))));
    }
    ret = voba_strcat_char(ret,']');
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_pair,voba_make_func(to_string_pair));}
VOBA_FUNC static voba_value_t to_string_pair(voba_value_t self,voba_value_t vs)
{
    voba_value_t args[] = {1, VOBA_NIL};
    voba_value_t v = voba_array_at(vs,0);
    voba_str_t* ret = voba_str_empty();
    ret = voba_strcat_char(ret,'(');
    int i = 0; 
    voba_value_t x = v;
    while(1){ // circular pair would cause infinite loop;
        if(i!=0){
            ret = voba_strcat_char(ret,',');
        }
        args[1] = voba_head(x);
        ret = voba_strcat(ret,
                          voba_value_to_str(
                              voba_apply(gf_to_string,voba_make_array(args))));
        x = voba_tail(x);
        if(voba_is_nil(x)){
            break;
        }else if(!voba_is_a(x,voba_cls_pair)){
            ret = voba_strcat_char(ret,'.');
            args[1] = x;
            ret = voba_strcat(ret,
                              voba_value_to_str(
                                  voba_apply(gf_to_string,voba_make_array(args))));
            break;
        }
        i ++;
    }
    ret = voba_strcat_char(ret,')');
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_la,voba_make_func(to_string_la));}
VOBA_FUNC static voba_value_t to_string_la(voba_value_t self,voba_value_t vs)
{
    voba_value_t args[] = {1, VOBA_NIL};
    voba_value_t v = voba_array_at(vs,0);
    voba_str_t* ret = voba_str_empty();
    ret = voba_strcat_char(ret,'[');
    int i = 0; 
    voba_value_t x = voba_la_copy(v);
    while(1){ // circular la would cause infinite loop;
        if(i!=0){
            ret = voba_strcat_char(ret,',');
        }
        args[1] = voba_la_car(x);
        ret = voba_strcat(ret,
                          voba_value_to_str(
                              voba_apply(gf_to_string,voba_make_array(args))));
        x = voba_la_cdr(x);
        if(voba_la_is_nil(x)){
            break;
        }
        i ++;
    }
    ret = voba_strcat_char(ret,']');
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_nil,voba_make_func(to_string_nil));}
VOBA_FUNC static voba_value_t to_string_nil(voba_value_t self,voba_value_t vs)
{
    voba_str_t *ret = voba_str_from_cstr("nil");
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_undef,voba_make_func(to_string_undef));}
VOBA_FUNC static voba_value_t to_string_undef(voba_value_t self,voba_value_t vs)
{
    voba_str_t *ret = voba_str_from_cstr("undef");
    return voba_make_string(ret);
}

EXEC_ONCE_PROGN{voba_gf_add_class(gf_to_string,voba_cls_bool,voba_make_func(to_string_boolean));}
VOBA_FUNC static voba_value_t to_string_boolean(voba_value_t self,voba_value_t vs)
{
    voba_value_t v = voba_array_at(vs,0);
    if(voba_is_true(v)){
        voba_str_t *ret = voba_str_from_cstr("TRUE");
        return voba_make_string(ret);
    }
    if(voba_is_false(v)){
        voba_str_t *ret = voba_str_from_cstr("FALSE");
        return voba_make_string(ret);
    }
    assert(0);
    voba_str_t *ret = voba_str_from_cstr("unknown");
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{
    voba_gf_add_class(gf_to_string,voba_cls_symbol,voba_make_func(to_string_symbol));
}
VOBA_FUNC static voba_value_t to_string_symbol(voba_value_t self,voba_value_t args)
{
    voba_value_t s = voba_array_at(args,0);
    return voba_make_string(voba_vstrcat(
                                voba_strdup(voba_value_to_str(voba_symbol_name(s))),
                                VOBA_CONST_CHAR("@0x"),
                                voba_str_fmt_uint64_t(s,16),NULL));
}

#define DEFINE_TO_STRING_FOR_SMALL_TYPE(tag,name,type)                  \
    VOBA_FUNC voba_value_t to_string_##name                             \
    (voba_value_t self,voba_value_t args)                               \
    {                                                                   \
        voba_value_t v = voba_array_at(args,0);                         \
        voba_str_t* ret =                                               \
            voba_str_fmt_##type(voba_value_to_##name(v),10);            \
        return voba_make_string(ret);                                   \
    }                                                                   \
    EXEC_ONCE_PROGN{                                                    \
        voba_gf_add_class(                                              \
            gf_to_string,                                               \
            voba_cls_##name,                                            \
            voba_make_func(to_string_##name));                          \
    }

VOBA_SMALL_TYPES(DEFINE_TO_STRING_FOR_SMALL_TYPE)
// print
EXEC_ONCE_PROGN{VOBA_DEFINE_MODULE_SYMBOL(s_print, voba_make_func(print));}
VOBA_FUNC static voba_value_t print(voba_value_t self, voba_value_t a1) 
{
    int64_t len = voba_array_len(a1);
    for(int i = 0; i < len; ++i){
        voba_value_t args[] = {1,voba_array_at(a1,i)};
        voba_value_t s = voba_apply(gf_to_string,voba_make_array(args));
        fwrite((const void*)voba_str_to_cstr(voba_value_to_str(s)),1,voba_strlen(voba_value_to_str(s)),stdout);
        if(i!=0){
             fputc(' ',stdout);
        }
    }
    fputc('\n',stdout);
    return VOBA_NIL;
}
// _2B = +
static voba_value_t gf_plus = VOBA_UNDEF;
EXEC_ONCE_PROGN{
    gf_plus = voba_make_generic_function();
    VOBA_DEFINE_MODULE_SYMBOL(s__2B, gf_plus);
}
VOBA_FUNC static voba_value_t plus_string(voba_value_t self, voba_value_t args);
EXEC_ONCE_PROGN{voba_gf_add_class(gf_plus,voba_cls_str,voba_make_func(plus_string));}
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
            voba_value_t s = voba_apply(gf_to_string,voba_make_array(tmp_args));
            ret = voba_strcat(ret, voba_value_to_str(s));
        }
    }
    return voba_make_string(ret);
}
static voba_value_t gf_gt = VOBA_UNDEF;
static voba_value_t gf_gt_eq = VOBA_UNDEF;
static voba_value_t gf_lt = VOBA_UNDEF;
static voba_value_t gf_lt_eq = VOBA_UNDEF;
static inline int64_t voba_value_int_to_i64(voba_value_t a)
{
    int64_t ret = 0;
    voba_value_t cls = voba_get_class(a);
    if(cls == voba_cls_i8){
        ret = (int64_t)voba_value_to_i8(a);
    }else if(cls == voba_cls_i16){
        ret = (int64_t)voba_value_to_i16(a);
    }else if(cls == voba_cls_i32){
        ret = (int64_t)voba_value_to_i32(a);
    }else if(cls == voba_cls_u8){
        ret = (int64_t)voba_value_to_u8(a);
    }else if(cls == voba_cls_u16){
        ret = (int64_t)voba_value_to_u16(a);
    }else if(cls == voba_cls_u32){
        ret = (int64_t)voba_value_to_u32(a);
    }else{
        assert(0&&"never goes here");
    }
    return ret;
}
VOBA_FUNC static voba_value_t gt_int(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_DEF_ARG3(a,args,0);
    VOBA_DEF_ARG3(b,args,1);
    int64_t a1 = voba_value_int_to_i64(a);
    int64_t b1 = voba_value_int_to_i64(b);
    if(a1>b1) ret = VOBA_TRUE;
    return ret;
}
VOBA_FUNC static voba_value_t lt_int(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_DEF_ARG3(a,args,0);
    VOBA_DEF_ARG3(b,args,1);
    int64_t a1 = voba_value_int_to_i64(a);
    int64_t b1 = voba_value_int_to_i64(b);
    if(a1<b1) ret = VOBA_TRUE;
    return ret;
}
VOBA_FUNC static voba_value_t gt_eq_int(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_DEF_ARG3(a,args,0);
    VOBA_DEF_ARG3(b,args,1);
    int64_t a1 = voba_value_int_to_i64(a);
    int64_t b1 = voba_value_int_to_i64(b);
    if(a1>=b1) ret = VOBA_TRUE;
    return ret;
}
VOBA_FUNC static voba_value_t lt_eq_int(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_DEF_ARG3(a,args,0);
    VOBA_DEF_ARG3(b,args,1);
    int64_t a1 = voba_value_int_to_i64(a);
    int64_t b1 = voba_value_int_to_i64(b);
    if(a1<=b1) ret = VOBA_TRUE;
    return ret;
}
EXEC_ONCE_PROGN{
    gf_gt = voba_make_generic_function();
    gf_gt_eq = voba_make_generic_function();
    gf_lt = voba_make_generic_function();
    gf_lt_eq = voba_make_generic_function();
    VOBA_DEFINE_MODULE_SYMBOL(s__3E, gf_gt);
    VOBA_DEFINE_MODULE_SYMBOL(s__3C, gf_lt);
    VOBA_DEFINE_MODULE_SYMBOL(s__3E_3D, gf_gt_eq);
    VOBA_DEFINE_MODULE_SYMBOL(s__3C_3D, gf_lt_eq);
    voba_gf_add_class(gf_gt,voba_cls_i8,voba_make_func(gt_int));
    voba_gf_add_class(gf_lt,voba_cls_i8,voba_make_func(lt_int));
    voba_gf_add_class(gf_gt_eq,voba_cls_i8,voba_make_func(gt_eq_int));
    voba_gf_add_class(gf_lt_eq,voba_cls_i8,voba_make_func(lt_eq_int));
    
    voba_gf_add_class(gf_gt,voba_cls_i16,voba_make_func(gt_int));
    voba_gf_add_class(gf_lt,voba_cls_i16,voba_make_func(lt_int));
    voba_gf_add_class(gf_gt_eq,voba_cls_i16,voba_make_func(gt_eq_int));
    voba_gf_add_class(gf_lt_eq,voba_cls_i16,voba_make_func(lt_eq_int));
    
    voba_gf_add_class(gf_gt,voba_cls_i32,voba_make_func(gt_int));
    voba_gf_add_class(gf_lt,voba_cls_i32,voba_make_func(lt_int));
    voba_gf_add_class(gf_gt_eq,voba_cls_i32,voba_make_func(gt_eq_int));
    voba_gf_add_class(gf_lt_eq,voba_cls_i32,voba_make_func(lt_eq_int));
    
    voba_gf_add_class(gf_gt,voba_cls_u8,voba_make_func(gt_int));
    voba_gf_add_class(gf_lt,voba_cls_u8,voba_make_func(lt_int));
    voba_gf_add_class(gf_gt_eq,voba_cls_u8,voba_make_func(gt_eq_int));
    voba_gf_add_class(gf_lt_eq,voba_cls_u8,voba_make_func(lt_eq_int));
    
    voba_gf_add_class(gf_gt,voba_cls_u16,voba_make_func(gt_int));
    voba_gf_add_class(gf_lt,voba_cls_u16,voba_make_func(lt_int));
    voba_gf_add_class(gf_gt_eq,voba_cls_u16,voba_make_func(gt_eq_int));
    voba_gf_add_class(gf_lt_eq,voba_cls_u16,voba_make_func(lt_eq_int));
    
    voba_gf_add_class(gf_gt,voba_cls_u32,voba_make_func(gt_int));
    voba_gf_add_class(gf_lt,voba_cls_u32,voba_make_func(lt_int));
    voba_gf_add_class(gf_gt_eq,voba_cls_u32,voba_make_func(gt_eq_int));
    voba_gf_add_class(gf_lt_eq,voba_cls_u32,voba_make_func(lt_eq_int));
}

//
static voba_value_t gf_match = VOBA_UNDEF;
VOBA_FUNC static voba_value_t match_single(voba_value_t self, voba_value_t args) 
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_DEF_ARG3(cls,args,0);
    VOBA_DEF_ARG3(v,args,1);
    VOBA_DEF_ARG3(index,args,2);
    VOBA_DEF_ARG3(len,args,3);
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
    gf_match = voba_module_var(VOBA_MODULE_LANG_ID,VOBA_MODULE_LANG_ID,VOBA_MODULE_LANG_MATCH);
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
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_float,voba_make_func(match_single));
    VOBA_DEFINE_MODULE_SYMBOL(s_cls_str, voba_cls_str);
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_str,voba_make_func(match_single));
}
// the main entry
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
