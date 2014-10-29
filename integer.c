VOBA_FUNC voba_value_t str_int (voba_value_t self,voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a1 = voba_array_at(args,0);
    int64_t a2  = voba_int_value_to_i64(a1);
    voba_str_t* a3 = voba_str_fmt_int64_t(a2,10);
    voba_value_t ret = voba_make_string(a3);
    return ret;
}

/* comparison */

VOBA_FUNC static voba_value_t equal_int(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_array_at(args,0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t b = voba_array_at(args,1);
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
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_array_at(args,0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t b = voba_array_at(args,1);
    if(voba_is_int(b)){
        int64_t a1 = voba_int_value_to_i64(a);
        int64_t b1 = voba_int_value_to_i64(b);
        if(a1>b1) ret = VOBA_TRUE;
    }else{
        ret = VOBA_UNDEF;
    }
    return ret;
}
/* + */
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
}else{
}
    return ret;
}

EXEC_ONCE_PROGN{
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i8,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i16,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i32,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u8,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u16,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u32,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_float,voba_make_func(match_single));

    voba_gf_add_class(gf_plus,voba_cls_i8,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_i16,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_i32,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_u8,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_u16,voba_make_func(plus_int));
    voba_gf_add_class(gf_plus,voba_cls_u32,voba_make_func(plus_int));

    voba_gf_add_class(gf_str,voba_cls_i8,voba_make_func(str_int));
    voba_gf_add_class(gf_str,voba_cls_i16,voba_make_func(str_int));
    voba_gf_add_class(gf_str,voba_cls_i32,voba_make_func(str_int));
    voba_gf_add_class(gf_str,voba_cls_u8,voba_make_func(str_int));
    voba_gf_add_class(gf_str,voba_cls_u16,voba_make_func(str_int));
    voba_gf_add_class(gf_str,voba_cls_u32,voba_make_func(str_int));
    
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
