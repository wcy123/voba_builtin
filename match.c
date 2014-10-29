VOBA_FUNC static voba_value_t match_single(voba_value_t self, voba_value_t args) 
{
    voba_value_t ret = VOBA_FALSE;
    VOBA_ASSERT_N_ARG(args,0);
    voba_value_t cls = voba_array_at(args,0);
    VOBA_ASSERT_N_ARG(args,1);
    voba_value_t v = voba_array_at(args,1);
    VOBA_ASSERT_N_ARG(args,2);
    voba_value_t index = voba_array_at(args,2);
    VOBA_ASSERT_N_ARG(args,3);
    voba_value_t len = voba_array_at(args,3);
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
