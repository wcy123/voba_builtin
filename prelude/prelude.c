#include <stdint.h>
#include <assert.h>
#define EXEC_ONCE_TU_NAME "prelude/prelude.voba built at 2015-4-30 15:16:21."
#define EXEC_ONCE_DEPENDS {"voba.module"};
#include <voba/value.h>
#include <voba/core/builtin.h> // import builtin by default
#include <exec_once.h>
#include <voba/module.h>
#define voba_match_eq voba_eql
    voba_value_t get_class_16d2de6 /* get_class */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t str_16d2ee6 /* str */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t print_16d2fd6 /* print */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t len_16d2e16 /* len */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t range_16d31d6 /* range */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _2B_16d32c6 /* + */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3E_16d33b6 /* > */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_16d3536 /* < */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3E_3D_16d3626 /* >= */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_3D_16d3716 /* <= */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3D_3D_16d3806 /* == */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _25_16d38f6 /* % */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_3C_16d39e6 /* << */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t array_16d3ad6 /* array */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t eq_16d3bc6 /* eq */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t i32_mod_16d3d46 /* i32_mod */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t eq_i32_mod_0_16d3e36 /* eq_i32_mod_0 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_i32_16d3f26 /* cls_i32 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_float_16d4016 /* cls_float */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_str_16d4106 /* cls_str */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t array_2Diter_16d41f6 /* array-iter */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t isa_16d42e6 /* isa */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t match_2Dtuple_16d43d6 /* match-tuple */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t tuple_16d44c6 /* tuple */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t argv_16d5b06 /* argv */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t read_module_info_16d6566 /* read_module_info */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t load_2Dmodule_16d6666 /* load-module */ __attribute__((unused)) = VOBA_UNDEF;
#ifndef VOBA_MODULE_DIRTY_HACK
voba_value_t voba_init(voba_value_t this_module)
#else
int main(int argc, char *argv[])
#endif
{
    exec_once_init();
    return VOBA_NIL;
}
EXEC_ONCE_PROGN {
{
    const char * name = "builtin";
    const char * id = "28b4792c-366b-11e4-aa00-08002796644a";
    const char * symbols[] = {
         "get_class",
         "str",
         "print",
         "len",
         "range",
         "+",
         ">",
         "<",
         ">=",
         "<=",
         "==",
         "%",
         "<<",
         "array",
         "eq",
         "i32_mod",
         "eq_i32_mod_0",
         "cls_i32",
         "cls_float",
         "cls_str",
         "array-iter",
         "isa",
         "match-tuple",
         "tuple",
         NULL
    };
    //fprintf(stderr,"loading %s(%s)\n",name,id);
    static voba_value_t                                    
        symbols2[sizeof(symbols)/sizeof(const char*) + 1] = {       
        sizeof(symbols)/sizeof(const char*) - 1, VOBA_NIL,          
    };                                                              
    size_t i;    for(i = 0 ; symbols[i]!=NULL; ++i){                      
        symbols2[i+1] =                                             
            voba_make_string(                                       
                    voba_str_from_cstr(symbols[i]));                
    }                                                               
    symbols2[i+1] = VOBA_BOX_END;    voba_import_module(name,id,voba_make_tuple(symbols2));          
}
{
    const char * name = "sys";
    const char * id = "7e15786a-cb7d-11e4-bf65-0800272ae0cc";
    const char * symbols[] = {
         "argv",
         NULL
    };
    //fprintf(stderr,"loading %s(%s)\n",name,id);
    static voba_value_t                                    
        symbols2[sizeof(symbols)/sizeof(const char*) + 1] = {       
        sizeof(symbols)/sizeof(const char*) - 1, VOBA_NIL,          
    };                                                              
    size_t i;    for(i = 0 ; symbols[i]!=NULL; ++i){                      
        symbols2[i+1] =                                             
            voba_make_string(                                       
                    voba_str_from_cstr(symbols[i]));                
    }                                                               
    symbols2[i+1] = VOBA_BOX_END;    voba_import_module(name,id,voba_make_tuple(symbols2));          
}
{
    const char * name = "compiler/module_info";
    const char * id = "c4f0ee24-d107-11e4-bf65-0800272ae0cc";
    const char * symbols[] = {
         "read_module_info",
         "load-module",
         NULL
    };
    //fprintf(stderr,"loading %s(%s)\n",name,id);
    static voba_value_t                                    
        symbols2[sizeof(symbols)/sizeof(const char*) + 1] = {       
        sizeof(symbols)/sizeof(const char*) - 1, VOBA_NIL,          
    };                                                              
    size_t i;    for(i = 0 ; symbols[i]!=NULL; ++i){                      
        symbols2[i+1] =                                             
            voba_make_string(                                       
                    voba_str_from_cstr(symbols[i]));                
    }                                                               
    symbols2[i+1] = VOBA_BOX_END;    voba_import_module(name,id,voba_make_tuple(symbols2));          
}
{
    get_class_16d2de6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("get_class")));
}
{
    str_16d2ee6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("str")));
}
{
    print_16d2fd6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("print")));
}
{
    len_16d2e16 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("len")));
}
{
    range_16d31d6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("range")));
}
{
    _2B_16d32c6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("+")));
}
{
    _3E_16d33b6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr(">")));
}
{
    _3C_16d3536 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<")));
}
{
    _3E_3D_16d3626 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr(">=")));
}
{
    _3C_3D_16d3716 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<=")));
}
{
    _3D_3D_16d3806 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("==")));
}
{
    _25_16d38f6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("%")));
}
{
    _3C_3C_16d39e6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<<")));
}
{
    array_16d3ad6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("array")));
}
{
    eq_16d3bc6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("eq")));
}
{
    i32_mod_16d3d46 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("i32_mod")));
}
{
    eq_i32_mod_0_16d3e36 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("eq_i32_mod_0")));
}
{
    cls_i32_16d3f26 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_i32")));
}
{
    cls_float_16d4016 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_float")));
}
{
    cls_str_16d4106 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_str")));
}
{
    array_2Diter_16d41f6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("array-iter")));
}
{
    isa_16d42e6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("isa")));
}
{
    match_2Dtuple_16d43d6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("match-tuple")));
}
{
    tuple_16d44c6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("tuple")));
}
{
    argv_16d5b06 = voba_module_var("sys","7e15786a-cb7d-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("argv")));
}
{
    read_module_info_16d6566 = voba_module_var("compiler/module_info","c4f0ee24-d107-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("read_module_info")));
}
{
    load_2Dmodule_16d6666 = voba_module_var("compiler/module_info","c4f0ee24-d107-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("load-module")));
}
    /*let env*/
    voba_value_t mi_16d01e6 /* mi */ __attribute__((unused)) = VOBA_UNDEF;

    /*decl let return value*/
    voba_value_t let_ret_0 __attribute__((unused)) = VOBA_UNDEF;
    /*let body*/
    voba_value_t apply_ret_3 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_4 [] = { 1 /* prepare arguments for apply */
             ,voba_make_i32(1) /* argument 1 */
        , VOBA_BOX_END };
        apply_ret_3 = voba_apply(voba_symbol_value(argv_16d5b06 /* argv */),voba_make_tuple(apply_args_4));/* return value for apply */
        voba_value_t apply_ret_1 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_2 [] = { 1 /* prepare arguments for apply */
             ,apply_ret_3 /* argument 1 */
        , VOBA_BOX_END };
        apply_ret_1 = voba_apply(voba_symbol_value(read_module_info_16d6566 /* read_module_info */),voba_make_tuple(apply_args_2));/* return value for apply */
        voba_value_t mi_5 __attribute__((unused)) = VOBA_UNDEF;
        mi_5 = apply_ret_1;/* value for set var*/
        mi_16d01e6 = mi_5; /* set mi */
        voba_value_t apply_ret_6 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_7 [] = { 1 /* prepare arguments for apply */
             ,mi_16d01e6 /* mi */ /* argument 1 */
        , VOBA_BOX_END };
        apply_ret_6 = voba_apply(voba_symbol_value(load_2Dmodule_16d6666 /* load-module */),voba_make_tuple(apply_args_7));/* return value for apply */

    let_ret_0 = apply_ret_6; /* set letreturn value*/
}

