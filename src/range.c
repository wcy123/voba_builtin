#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"
/* range */
VOBA_FUNC static voba_value_t range_next(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[]);
VOBA_FUNC voba_value_t range(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    int64_t len = voba_tuple_len(args);
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t a1 = voba_tuple_at( args, 0);
    VOBA_ASSERT_ARG_ISA(a1,voba_cls_i32, 0);
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
        voba_value_t a2 = voba_tuple_at( args, 1);
        VOBA_ASSERT_ARG_ISA(a2, voba_cls_i32, 1);
        from = a1;
        to = a2;
        break;
    }
    case 3:{
        voba_value_t a2 = voba_tuple_at( args, 1);
        VOBA_ASSERT_ARG_ISA(a2, voba_cls_i32, 1);
        voba_value_t a3 = voba_tuple_at( args, 2);
        VOBA_ASSERT_ARG_ISA(a3, voba_cls_i32, 2);
        from = a1;
        to = a2;
        step = a3;
        break;
    }
    }
    int64_t ifrom = voba_value_to_i32(from);
    int64_t ito = voba_value_to_i32(to);
    int64_t istep = voba_value_to_i32(step);
    if(!((istep < 0 && ifrom >= ito ) ||
         (istep > 0 && ifrom <= ito ))){
        VOBA_THROW(VOBA_CONST_CHAR("infinite loop: "),
                   VOBA_CONST_CHAR(" from = "),
                   voba_str_fmt_int64_t(ifrom,10),
                   VOBA_CONST_CHAR(" to = "),
                   voba_str_fmt_int64_t(ito,10),
                   VOBA_CONST_CHAR(" step = "),
                   voba_str_fmt_int64_t(istep,10));
    }
    return voba_make_closure_3(range_next, ifrom, ito, istep);
}
VOBA_FUNC static voba_value_t range_next(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    assert(voba_tuple_len(fun) == 3);
    int64_t from = voba_tuple_at(fun,0);
    int64_t to   = voba_tuple_at(fun,1);
    int64_t step = voba_tuple_at(fun,2);
    assert((step < 0 && to >= from) ||
           (step > 0 && from <= to ));
    voba_value_t ret = VOBA_DONE;
    if(from != to){
        ret = voba_make_i32((int32_t) from);
        from += step;
        voba_tuple_set(fun,0,from);
    }
    return ret;
}
    
