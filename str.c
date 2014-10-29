VOBA_FUNC static voba_value_t str_string(voba_value_t self,voba_value_t v)
{
    voba_str_t* ret = voba_str_from_char('"',1);
    ret = voba_strcat(ret,voba_value_to_str(voba_array_at(v,0)));
    ret = voba_strcat_char(ret,'"');
    return voba_make_string(ret);
}
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
EXEC_ONCE_PROGN{
    voba_gf_add_class(gf_str,voba_cls_str,voba_make_func(str_string));
    voba_gf_add_class(gf_plus,voba_cls_str,voba_make_func(plus_string));
}




