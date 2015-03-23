#define EXEC_ONCE_TU_NAME "voba.compiler.source"
#include <voba/value.h>
#include "exec_once.h"
#include "source.h"
#include "source_c.h"
VOBA_DEF_CLS(sizeof(source_t),source);

VOBA_FUNC static voba_value_t make_2Dsource(voba_value_t self, voba_value_t args)
{
    voba_value_t ret = VOBA_NIL;
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  filename = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA( filename,voba_cls_str, 0);
    int64_t len = voba_tuple_len(args);
    voba_value_t content = VOBA_NIL;
    if(len > 1){
        content = voba_tuple_at(args, 1);
        VOBA_ASSERT_ARG_ISA( content,voba_cls_str, 1);
    }else{
        FILE * fp = fopen(voba_str_to_cstr(voba_value_to_str(filename)),"r");
        if(fp != NULL){
            voba_str_t * ss = voba_str_from_FILE(fp);
            fclose(fp);
            if(ss != NULL){
                content = voba_make_string(ss); 
            }else{
                /// @todo throw an IO exception?
                voba_throw_exception(voba_make_string(
                                         VOBA_STRCAT(
                                             VOBA_CONST_CHAR("cannot read file: "),
                                             voba_value_to_str(filename))));
            }
        }else{
            /// @todo throw an IO exception?
            voba_throw_exception(voba_make_string(VOBA_STRCAT(
                                                      VOBA_CONST_CHAR("cannot open file: "),
                                                      voba_value_to_str(filename))));
        }
    }
    ret = voba_make_user_data(voba_cls_source);
    source_t * p_source  = SOURCE(ret);
    p_source->filename = voba_value_to_str(filename);
    p_source->content = voba_value_to_str(content);
    return ret;
}
VOBA_FUNC static voba_value_t source_2Dfilename(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  source = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(source,voba_cls_source,0);
    return voba_make_string(SOURCE(source)->filename);
}
VOBA_FUNC static voba_value_t source_2Dcontent(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  source = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(source,voba_cls_source,0);
    return voba_make_string(SOURCE(source)->content);
}
VOBA_FUNC static voba_value_t source_to_string(voba_value_t self, voba_value_t args)
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  src = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(src,voba_cls_source, 0);
    voba_str_t* ret = voba_str_empty();
    ret = voba_strcat(ret,voba_str_from_cstr(";;filename = "));
    ret = voba_strcat(ret,SOURCE(src)->filename);
    ret = voba_strcat(ret,voba_str_from_char('\n',1));
    ret = voba_strcat(ret,SOURCE(src)->content);
    return voba_make_string(ret);
}
EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_make_2Dsource, voba_make_func(make_2Dsource));
    VOBA_DEFINE_MODULE_SYMBOL(s_source_2Dfilename, voba_make_func(source_2Dfilename));
    VOBA_DEFINE_MODULE_SYMBOL(s_source_2Dcontent, voba_make_func(source_2Dcontent));
    voba_gf_add_class(voba_gf_to_string,voba_cls_source,voba_make_func(source_to_string));
}
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
