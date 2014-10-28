VOBA_FUNC static voba_value_t apply_array(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t index1 = voba_array_at(args,0);
    VOBA_ASSERT_IS(index1,voba_is_int,0);
    int64_t index = (index1 >> 8);
    return voba_array_at(self,index);
}
EXEC_ONCE_PROGN{
    voba_gf_add_class(voba_gf_apply,voba_cls_array,voba_make_func(apply_array));
}
