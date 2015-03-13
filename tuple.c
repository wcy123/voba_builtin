#define EXEC_ONCE_TU_NAME "voba.builtin.tuple"
#define EXEC_ONCE_DEPENDS {"voba.builtin"}
#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"
/* str */
VOBA_FUNC static  voba_value_t str_tuple(voba_value_t self,voba_value_t vs)
{
    voba_value_t v = voba_tuple_at(vs,0);
    int64_t len = voba_tuple_len(v);
    voba_str_t* ret = voba_str_empty();
    ret = voba_strcat_char(ret,'[');
    for(int i = 0; i < len ; ++i){
        if(i!=0){
            ret = voba_strcat_char(ret,',');
        }
        voba_value_t args[] = {1,voba_tuple_at(v,i)};
        ret = voba_strcat(ret,
                          voba_value_to_str(voba_apply(gf_str,voba_make_tuple(args))));
    }
    ret = voba_strcat_char(ret,']');
    return voba_make_string(ret);
}
/* iter */
VOBA_FUNC static voba_value_t iter_tuple_next (voba_value_t self, voba_value_t args)
{
    voba_value_t a = voba_tuple_at(self,0);
    voba_value_t i = voba_tuple_at(self,1);
    int64_t len = voba_tuple_len(a);
    voba_value_t ret = VOBA_DONE;
    if(i < len){
        ret = voba_tuple_at(a, i);
        i++;
        voba_tuple_set(self,1,i);
    }
    return ret;
}
VOBA_FUNC static voba_value_t tuple_iterator(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a,voba_cls_tuple,0);
    return voba_make_closure_2(iter_tuple_next,a,0);
}
/* apply */
VOBA_FUNC static voba_value_t apply_tuple(voba_value_t self, voba_value_t args)
{
    int64_t len = voba_tuple_len(args);
    if(len == 0){
        return voba_make_closure_2(iter_tuple_next,self,0);
    }
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t index1 = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_FUN(index1,voba_is_int,0);
    int64_t index = (index1 >> 8);
    return voba_tuple_at(self,index);
}
/* gf len */
VOBA_FUNC static voba_value_t len_tuple(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_tuple_at(args,0);
    VOBA_ASSERT_ARG_ISA(a,voba_cls_tuple,0);
    return voba_make_u32((uint32_t)voba_tuple_len(a));
}
EXEC_ONCE_PROGN{
    voba_gf_add_class(gf_str,voba_cls_tuple,voba_make_func(str_tuple));
    voba_gf_add_class(gf_len, voba_cls_tuple,voba_make_func(len_tuple));
    voba_gf_add_class(voba_gf_apply,voba_cls_tuple,voba_make_func(apply_tuple));
}
