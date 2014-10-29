/* str */
VOBA_FUNC static  voba_value_t str_array(voba_value_t self,voba_value_t vs)
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
                          voba_value_to_str(voba_apply(gf_str,voba_make_array(args))));
    }
    ret = voba_strcat_char(ret,']');
    return voba_make_string(ret);
}
/* iter */
VOBA_FUNC static voba_value_t iter_array_next (voba_value_t self, voba_value_t args);
VOBA_FUNC static voba_value_t iter_array (voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t a = voba_array_at(args,0);
    VOBA_ASSERT_CLS(a,voba_cls_array,0);
    voba_value_t ret = voba_make_closure_2(iter_array_next,a,0);
    return ret;
}
VOBA_FUNC static voba_value_t iter_array_next (voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(self,0);
    voba_value_t a = voba_array_at(self,0);
    VOBA_ASSERT_CLS(a,voba_cls_array,0);
    VOBA_ASSERT_N_ARG(self,1);
    voba_value_t i = voba_array_at(self,1);
    int64_t len = voba_array_len(a);
    voba_value_t ret = VOBA_UNDEF;
    if(i < len){
        ret = voba_array_at(a, i);
        i++;
        voba_array_set(self,1,i);
    }
    return ret;
}
VOBA_FUNC static voba_value_t apply_array(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t index1 = voba_array_at(args,0);
    VOBA_ASSERT_IS(index1,voba_is_int,0);
    int64_t index = (index1 >> 8);
    return voba_array_at(self,index);
}
EXEC_ONCE_PROGN{
    voba_gf_add_class(gf_str,voba_cls_array,voba_make_func(str_array));
    voba_gf_add_class(gf_iter, voba_cls_array, voba_make_func(iter_array));
    voba_gf_add_class(voba_gf_apply,voba_cls_array,voba_make_func(apply_array));
}