#define EXEC_ONCE_TU_NAME "voba.builtin.range"
#define EXEC_ONCE_DEPENDS {"voba.builtin",NULL}
#include <voba/include/value.h>
#include <voba/include/module.h>
#include "gf.h"
/* range */
VOBA_FUNC static voba_value_t range_next(voba_value_t self, voba_value_t args);
VOBA_FUNC voba_value_t range(voba_value_t self, voba_value_t args)
{
    int64_t len = voba_array_len(args);
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t a1 = voba_array_at( args, 0);
    VOBA_ASSERT_IS(a1,voba_is_int, 0);
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
        VOBA_ASSERT_IS(a2, voba_is_int, 1);
        from = a1;
        to = a2;
        break;
    }
    case 3:{
        voba_value_t a2 = voba_array_at( args, 1);
        VOBA_ASSERT_IS(a2, voba_is_int, 1);
        voba_value_t a3 = voba_array_at( args, 2);
        VOBA_ASSERT_IS(a3, voba_is_int, 2);
        from = a1;
        to = a2;
        step = a3;
        break;
    }
    }
    int64_t ifrom = voba_int_value_to_i64(from);
    int64_t ito = voba_int_value_to_i64(to);
    int64_t istep = voba_int_value_to_i64(step);
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
    
