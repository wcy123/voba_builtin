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
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i8,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i16,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_i32,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u8,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u16,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_u32,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),
                      voba_cls_float,voba_make_func(match_single));
    voba_gf_add_class(voba_symbol_value(gf_match),voba_cls_str,voba_make_func(match_single));
}
