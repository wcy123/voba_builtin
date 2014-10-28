// str
VOBA_FUNC static voba_value_t str_string(voba_value_t self,voba_value_t v)
{
    voba_str_t* ret = voba_str_from_char('"',1);
    ret = voba_strcat(ret,voba_value_to_str(voba_array_at(v,0)));
    ret = voba_strcat_char(ret,'"');
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t str_funcp(voba_value_t self, voba_value_t v)
{
    voba_str_t * ret = voba_str_empty();
    ret = voba_strcat_cstr(ret,"<funcp ");
    ret = voba_strcat(ret,voba_str_fmt_pointer(((void*)voba_array_at(v,0))));
    ret = voba_strcat_cstr(ret," >");    
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t str_closure(voba_value_t self,voba_value_t vs)
{
    voba_str_t *ret = voba_str_empty();
    ret = voba_strcat_cstr(ret,"<closure ");
    ret = voba_strcat(ret,voba_str_fmt_pointer((void*) (intptr_t)voba_closure_func(voba_array_at(vs,0))));
    ret = voba_strcat_char(ret,',');
    ret = voba_strcat(ret,voba_str_fmt_uint32_t(voba_array_len(voba_closure_array(voba_array_at(vs,0))),10));
    ret = voba_strcat_char(ret,'>');
    return voba_make_string(ret);
}
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
VOBA_FUNC static voba_value_t str_pair(voba_value_t self,voba_value_t vs)
{
    voba_value_t args[] = {1, VOBA_NIL};
    voba_value_t v = voba_array_at(vs,0);
    voba_str_t* ret = voba_str_empty();
    ret = voba_strcat_char(ret,'(');
    int i = 0; 
    voba_value_t x = v;
    while(1){ // circular pair would cause infinite loop;
        if(i!=0){
            ret = voba_strcat_char(ret,',');
        }
        args[1] = voba_head(x);
        ret = voba_strcat(ret,
                          voba_value_to_str(
                              voba_apply(gf_str,voba_make_array(args))));
        x = voba_tail(x);
        if(voba_is_nil(x)){
            break;
        }else if(!voba_is_a(x,voba_cls_pair)){
            ret = voba_strcat_char(ret,'.');
            args[1] = x;
            ret = voba_strcat(ret,
                              voba_value_to_str(
                                  voba_apply(gf_str,voba_make_array(args))));
            break;
        }
        i ++;
    }
    ret = voba_strcat_char(ret,')');
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t str_la(voba_value_t self,voba_value_t vs)
{
    voba_value_t args[] = {1, VOBA_NIL};
    voba_value_t v = voba_array_at(vs,0);
    voba_str_t* ret = voba_str_empty();
    ret = voba_strcat_char(ret,'[');
    int i = 0; 
    voba_value_t x = voba_la_copy(v);
    while(1){ // circular la would cause infinite loop;
        if(i!=0){
            ret = voba_strcat_char(ret,',');
        }
        args[1] = voba_la_car(x);
        ret = voba_strcat(ret,
                          voba_value_to_str(
                              voba_apply(gf_str,voba_make_array(args))));
        x = voba_la_cdr(x);
        if(voba_la_is_nil(x)){
            break;
        }
        i ++;
    }
    ret = voba_strcat_char(ret,']');
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t str_nil(voba_value_t self,voba_value_t vs)
{
    voba_str_t *ret = voba_str_from_cstr("nil");
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t str_undef(voba_value_t self,voba_value_t vs)
{
    voba_str_t *ret = voba_str_from_cstr("undef");
    return voba_make_string(ret);
}

VOBA_FUNC static voba_value_t str_boolean(voba_value_t self,voba_value_t vs)
{
    voba_value_t v = voba_array_at(vs,0);
    if(voba_is_true(v)){
        voba_str_t *ret = voba_str_from_cstr("TRUE");
        return voba_make_string(ret);
    }
    if(voba_is_false(v)){
        voba_str_t *ret = voba_str_from_cstr("FALSE");
        return voba_make_string(ret);
    }
    assert(0);
    voba_str_t *ret = voba_str_from_cstr("unknown");
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t str_symbol(voba_value_t self,voba_value_t args)
{
    voba_value_t s = voba_array_at(args,0);
    return voba_make_string(voba_vstrcat(
                                voba_strdup(voba_value_to_str(voba_symbol_name(s))),
                                VOBA_CONST_CHAR("@0x"),
                                voba_str_fmt_uint64_t(s,16),NULL));
}
EXEC_ONCE_PROGN{
    gf_str = voba_make_generic_function("str");
    VOBA_DEFINE_MODULE_SYMBOL(s_str, gf_str);
    voba_gf_add_class(gf_str,voba_cls_str,voba_make_func(str_string));
    voba_gf_add_class(gf_str,voba_cls_func,voba_make_func(str_funcp));
    voba_gf_add_class(gf_str,voba_cls_closure,voba_make_func(str_closure));
    voba_gf_add_class(gf_str,voba_cls_array,voba_make_func(str_array));
    voba_gf_add_class(gf_str,voba_cls_nil,voba_make_func(str_nil));
    voba_gf_add_class(gf_str,voba_cls_pair,voba_make_func(str_pair));
    voba_gf_add_class(gf_str,voba_cls_la,voba_make_func(str_la));
    voba_gf_add_class(gf_str,voba_cls_undef,voba_make_func(str_undef));
    voba_gf_add_class(gf_str,voba_cls_bool,voba_make_func(str_boolean));
    voba_gf_add_class(gf_str,voba_cls_symbol,voba_make_func(str_symbol));
}

#define DEFINE_STR_FOR_SMALL_TYPE(tag,name,type)                  \
    VOBA_FUNC voba_value_t str_##name                             \
    (voba_value_t self,voba_value_t args)                               \
    {                                                                   \
        voba_value_t v = voba_array_at(args,0);                         \
        voba_str_t* ret =                                               \
            voba_str_fmt_##type(voba_value_to_##name(v),10);            \
        return voba_make_string(ret);                                   \
    }                                                                   \
    EXEC_ONCE_PROGN{                                                    \
        voba_gf_add_class(                                              \
            gf_str,                                               \
            voba_cls_##name,                                            \
            voba_make_func(str_##name));                          \
    }

VOBA_SMALL_TYPES(DEFINE_STR_FOR_SMALL_TYPE)



