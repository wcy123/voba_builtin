#include <time.h>
#include <voba/value.h>
#define EXEC_ONCE_TU_NAME "voba.compiler.read_module_info"
#include <exec_once.h>
#include "../source/source.h"
#include "../source/source_c.h"
#include "../syntax/syntax.h"
#include "../syntax/syntax_c.h"
#include "./module_info.h"
#include "./module_info_c.h"
static voba_value_t voba_cls_module_info;
static VOBA_DEF_CLS(sizeof(module_info_t),module_info);

static voba_value_t make_module_info()
{
    voba_value_t ret = voba_make_user_data(voba_cls_module_info);
    MODULE_INFO(ret)->syn_name = VOBA_NIL;
    MODULE_INFO(ret)->syn_id = VOBA_NIL;
    MODULE_INFO(ret)->a_syn_symbols = voba_make_array_0();
    return ret;
}

#define YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  uint32_t start_pos;
  uint32_t end_pos;
} YYLTYPE;

#include "module_info_lex.inc"

static inline voba_value_t search_module_header_file(voba_value_t module_name,voba_value_t attempts, voba_str_t * pwd);
static inline voba_value_t search_module_so_file(voba_value_t module_name,voba_value_t attempts, voba_str_t * pwd);
static inline voba_value_t random_module_id(voba_value_t module_name);
static inline voba_value_t read_module_info_1(voba_value_t module_name, voba_value_t pwd)
{
    /// @todo, the so file and header file should not be searched
    /// twice, we need a new function to load a module from a
    /// module_info object.
    voba_value_t ret = VOBA_NIL;
    voba_value_t attempts = voba_make_array_0();
    voba_value_t module_header_file = search_module_header_file(module_name,attempts,voba_value_to_str(pwd));
    if(voba_is_nil(module_header_file)){
        voba_value_t module_so_file = search_module_so_file(module_name,attempts,voba_value_to_str(pwd));
        if(voba_is_nil(module_so_file)){
            voba_str_t * text = voba_str_empty();
            text = voba_strcat(text, VOBA_CONST_CHAR("cannot find module:"));
            text = voba_strcat(text,voba_value_to_str(module_name));
            text = voba_strcat(text, VOBA_CONST_CHAR(", and following file names are tried:"));
            int64_t len = voba_array_len(attempts);
            for(int64_t i = 0; i < len ; ++i){
                text = voba_strcat(text,VOBA_CONST_CHAR("\n    "));
                text = voba_strcat(text,voba_value_to_str(voba_array_at(attempts,i)));
            }
            voba_throw_exception(voba_make_string(text));
        }else{
            ret = make_module_info();
            module_info_t * mi = MODULE_INFO(ret);
            voba_value_t source = VOBA_NIL;
            {
                /// @todo, this part is ugly, because make-source and
                /// make-syntax are exported by other module
                /// compiler/source and compiler/syntax, function
                /// definitions are in a shared library, which cannot
                /// be linked directly.
                voba_value_t tmpargs[] = {2
                                          ,voba_make_string(voba_str_from_cstr("<anonymous module header>"))
                                          ,voba_make_string(
                                              voba_vstrcat(
                                                  voba_str_from_cstr("\""),
                                                  voba_value_to_str(module_name),
                                                  voba_str_from_cstr("\""),NULL))};
                source = voba_apply(
                    voba_symbol_value(s_make_2Dsource), voba_make_tuple(tmpargs));
            }
            VOBA_APPLY(mi->syn_name,
                       voba_symbol_value(s_make_2Dsyntax),
                       module_name,
                       voba_make_i32(1),
                       voba_make_i32(voba_value_to_str(module_name)->len + 1),
                       source);
            voba_value_t anonymous_module_id = random_module_id(module_name);
            {
                voba_value_t tmpargs[] = {2
                                          ,voba_make_string(voba_str_from_cstr("<anonymous module header>"))
                                          ,voba_make_string(
                                              voba_vstrcat(
                                                  voba_str_from_cstr("\""),
                                                  voba_value_to_str(anonymous_module_id),
                                                  voba_str_from_cstr("\""),NULL))};
                source = voba_apply(
                    voba_symbol_value(s_make_2Dsource), voba_make_tuple(tmpargs));
            }
            VOBA_APPLY(mi->syn_id,
                       voba_symbol_value(s_make_2Dsyntax),
                       anonymous_module_id
                       ,voba_make_i32(1)
                       ,voba_make_i32(voba_value_to_str(anonymous_module_id)->len + 1)
                       ,source);
            mi->a_syn_symbols = voba_make_array_0();
            /// @todo add mi->header_file and mi->so_file here
        }
    }else{
        voba_value_t source = VOBA_NIL;
        {
            voba_value_t tmpargs[] = {1, module_header_file};
            source = voba_apply(
                voba_symbol_value(s_make_2Dsource), voba_make_tuple(tmpargs));
        }
        if(!voba_is_nil(source)) {
            ret = make_module_info();
            voba_str_t * content = SOURCE(source)->content;
            void * scanner;
            yylex_init(&scanner);
            yy_scan_bytes(content->data,content->len,scanner);
            YYLTYPE pos;
            YYSTYPE s;
            module_lex(ret,source,scanner,&s,&pos);
            yylex_destroy(scanner);
            if(voba_is_nil(MODULE_INFO(ret)->syn_name)){
                voba_throw_exception(voba_make_string(VOBA_CONST_CHAR("read_module_info: VOBA_MODULE_NAME is not defined.")));
            }
            if(voba_is_nil(MODULE_INFO(ret)->syn_id)){
                voba_throw_exception(voba_make_string(VOBA_CONST_CHAR("read_module_info: VOBA_MODULE_ID is not defined.")));
            }
            if(voba_array_len(MODULE_INFO(ret)->a_syn_symbols) == 0){ 
                //voba_throw_exception(voba_make_string(VOBA_CONST_CHAR("read_module_info: no symbol is defined.")));
            }
            ///@todo add mi->header_file and mi->so_file here
        }
    }
    return ret;
}
static inline voba_value_t search_module_header_file(voba_value_t module_name,voba_value_t attempts, voba_str_t * pwd)
{
    voba_str_t* prefix = voba_str_empty();
    voba_str_t* suffix = VOBA_CONST_CHAR(".h");
    int resolv_realpath = 0;
    voba_str_t * file = voba_find_file(voba_module_path(),
                                       voba_value_to_str(module_name),
                                       pwd,
                                       prefix, suffix,
                                       resolv_realpath,
                                       attempts
        );
    voba_value_t ret = VOBA_NIL;
    if(file) ret = voba_make_string(file) ;
    return ret;
}
static inline voba_value_t search_module_so_file(voba_value_t module_name,voba_value_t attempts, voba_str_t * pwd)
{
    voba_str_t* prefix = VOBA_CONST_CHAR("lib");
    voba_str_t* suffix = VOBA_CONST_CHAR(".so");
    int resolv_realpath = 0;
    voba_str_t * file = voba_find_file(voba_module_path(),
                                       voba_value_to_str(module_name),
                                       pwd,
                                       prefix, suffix,
                                       resolv_realpath,
                                       attempts
        );
    voba_value_t ret = VOBA_NIL;
    if(file) ret = voba_make_string(file) ;
    return ret;
}
static inline voba_value_t random_module_id(voba_value_t module_name)
{
    time_t xt;
    time(&xt);
    struct tm xtm;
    gmtime_r(&xt,&xtm);
    voba_str_t* ret = voba_str_empty();
    ret = VOBA_STRCAT(ret,
                      voba_value_to_str(module_name),
                      VOBA_CONST_CHAR(" built at "),
                      voba_str_fmt_int32_t(xtm.tm_year + 1900,10),
                      VOBA_CONST_CHAR("-"),
                      voba_str_fmt_int32_t(xtm.tm_mon + 1,10),
                      VOBA_CONST_CHAR("-"),
                      voba_str_fmt_int32_t(xtm.tm_mday,10),
                      VOBA_CONST_CHAR(" "),
                      voba_str_fmt_int32_t(xtm.tm_hour,10),
                      VOBA_CONST_CHAR(":"),
                      voba_str_fmt_int32_t(xtm.tm_min,10),
                      VOBA_CONST_CHAR(":"),
                      voba_str_fmt_int32_t(xtm.tm_sec,10),
                      VOBA_CONST_CHAR("."));
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t read_module_info(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  module_name = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(module_name,voba_cls_str,0);
    int64_t len = voba_tuple_len(args);
    voba_value_t pwd = voba_make_string(voba_str_from_cstr("."));
    if(len > 1){
        pwd = voba_tuple_at(args,1);
        VOBA_ASSERT_ARG_ISA(pwd,voba_cls_str,0);
    }
    return read_module_info_1(module_name,pwd);
}
VOBA_FUNC static voba_value_t module_info_to_string(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  module_info = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(module_info,voba_cls_module_info,0);
    module_info_t * mi = MODULE_INFO(module_info);
    voba_str_t* ret = voba_str_empty();
    ret = voba_strcat(ret, VOBA_CONST_CHAR("module: "));
    ret = voba_strcat(ret, voba_value_to_str(SYNTAX(mi->syn_name)->value));
    ret = voba_strcat(ret, VOBA_CONST_CHAR("\nid: "));
    ret = voba_strcat(ret, voba_value_to_str(SYNTAX(mi->syn_id)->value));
    ret = voba_strcat(ret, VOBA_CONST_CHAR("\nsymbols: "));
    int64_t len = voba_array_len(mi->a_syn_symbols);
    for(int64_t i = 0 ; i < len ; ++i){
        voba_value_t sym = SYNTAX(voba_array_at(mi->a_syn_symbols,i))->value;
        ret = voba_strcat(ret, VOBA_CONST_CHAR(" "));
        ret = voba_strcat(ret, voba_value_to_str(sym));
    }
    return voba_make_string(ret);
}
VOBA_FUNC static voba_value_t load_module(voba_value_t fun, voba_value_t args, voba_value_t* next_fun, voba_value_t next_args[])
{
    VOBA_ASSERT_N_ARG( args, 0);
    voba_value_t  module_info = voba_tuple_at(args, 0);
    VOBA_ASSERT_ARG_ISA(module_info,voba_cls_module_info,0);
    module_info_t * mi = MODULE_INFO(module_info);
    int64_t len = voba_array_len(mi->a_syn_symbols);
    voba_value_t tmpargs[len+1];
    tmpargs[0] = len;
    for(int64_t i = 0 ; i < len ; ++i){
        voba_value_t sym = SYNTAX(voba_array_at(mi->a_syn_symbols,i))->value;
        tmpargs[i+1] = sym;
    }
    voba_value_t ret = voba_import_module(
        voba_str_to_cstr(voba_value_to_str(SYNTAX(mi->syn_name)->value)),
        voba_str_to_cstr(voba_value_to_str(SYNTAX(mi->syn_id)->value)),
        voba_make_tuple(tmpargs)
        );
    return ret;
}
EXEC_ONCE_PROGN{
    voba_gf_add_class(voba_gf_to_string,voba_cls_module_info,voba_make_func(module_info_to_string));
    VOBA_DEFINE_MODULE_SYMBOL(s_read_module_info,voba_make_func(read_module_info));
    VOBA_DEFINE_MODULE_SYMBOL(s_load_2Dmodule,voba_make_func(load_module));    
}
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
