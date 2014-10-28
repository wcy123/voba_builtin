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
