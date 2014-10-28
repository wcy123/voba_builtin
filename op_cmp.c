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



