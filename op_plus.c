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
