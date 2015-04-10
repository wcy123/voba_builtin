#include <stdint.h>
#include <assert.h>
#define EXEC_ONCE_TU_NAME "prelude/prelude.voba built at 2015-4-10 7:40:52."
#define EXEC_ONCE_DEPENDS {"voba.module"};
#include <voba/value.h>
#include <voba/core/builtin.h> // import builtin by default
#include <exec_once.h>
#include <voba/module.h>
#define voba_match_eq voba_eql
    voba_value_t get_class_149bde6 /* get_class */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t str_149bed6 /* str */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t print_149bfd6 /* print */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t len_149c0c6 /* len */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t range_149bf06 /* range */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _2B_149c2c6 /* + */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3E_149c3b6 /* > */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_149c4a6 /* < */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3E_3D_149c626 /* >= */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_3D_149c716 /* <= */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3D_3D_149c806 /* == */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _25_149c8f6 /* % */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_3C_149c9e6 /* << */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t array_149cad6 /* array */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t eq_149cbc6 /* eq */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t i32_mod_149ccb6 /* i32_mod */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t eq_i32_mod_0_149ce36 /* eq_i32_mod_0 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_i32_149cf26 /* cls_i32 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_float_149d016 /* cls_float */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_str_149d106 /* cls_str */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t array_2Diter_149d1f6 /* array-iter */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t isa_149d2e6 /* isa */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t match_2Dtuple_149d3d6 /* match-tuple */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t tuple_149d4c6 /* tuple */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t argv_149eae6 /* argv */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t read_module_info_149f536 /* read_module_info */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t load_2Dmodule_149f626 /* load-module */ __attribute__((unused)) = VOBA_UNDEF;
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
        symbols2[sizeof(symbols)/sizeof(const char*)] = {           
        sizeof(symbols)/sizeof(const char*) - 1, VOBA_NIL,          
    };                                                              
    for(size_t i = 0 ; symbols[i]!=NULL; ++i){                      
        symbols2[i+1] =                                             
            voba_make_string(                                       
                    voba_str_from_cstr(symbols[i]));                
    }                                                               
    voba_import_module(name,id,voba_make_tuple(symbols2));          
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
        symbols2[sizeof(symbols)/sizeof(const char*)] = {           
        sizeof(symbols)/sizeof(const char*) - 1, VOBA_NIL,          
    };                                                              
    for(size_t i = 0 ; symbols[i]!=NULL; ++i){                      
        symbols2[i+1] =                                             
            voba_make_string(                                       
                    voba_str_from_cstr(symbols[i]));                
    }                                                               
    voba_import_module(name,id,voba_make_tuple(symbols2));          
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
        symbols2[sizeof(symbols)/sizeof(const char*)] = {           
        sizeof(symbols)/sizeof(const char*) - 1, VOBA_NIL,          
    };                                                              
    for(size_t i = 0 ; symbols[i]!=NULL; ++i){                      
        symbols2[i+1] =                                             
            voba_make_string(                                       
                    voba_str_from_cstr(symbols[i]));                
    }                                                               
    voba_import_module(name,id,voba_make_tuple(symbols2));          
}
{
    get_class_149bde6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("get_class")));
}
{
    str_149bed6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("str")));
}
{
    print_149bfd6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("print")));
}
{
    len_149c0c6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("len")));
}
{
    range_149bf06 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("range")));
}
{
    _2B_149c2c6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("+")));
}
{
    _3E_149c3b6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr(">")));
}
{
    _3C_149c4a6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<")));
}
{
    _3E_3D_149c626 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr(">=")));
}
{
    _3C_3D_149c716 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<=")));
}
{
    _3D_3D_149c806 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("==")));
}
{
    _25_149c8f6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("%")));
}
{
    _3C_3C_149c9e6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<<")));
}
{
    array_149cad6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("array")));
}
{
    eq_149cbc6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("eq")));
}
{
    i32_mod_149ccb6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("i32_mod")));
}
{
    eq_i32_mod_0_149ce36 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("eq_i32_mod_0")));
}
{
    cls_i32_149cf26 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_i32")));
}
{
    cls_float_149d016 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_float")));
}
{
    cls_str_149d106 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_str")));
}
{
    array_2Diter_149d1f6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("array-iter")));
}
{
    isa_149d2e6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("isa")));
}
{
    match_2Dtuple_149d3d6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("match-tuple")));
}
{
    tuple_149d4c6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("tuple")));
}
{
    argv_149eae6 = voba_module_var("sys","7e15786a-cb7d-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("argv")));
}
{
    read_module_info_149f536 = voba_module_var("compiler/module_info","c4f0ee24-d107-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("read_module_info")));
}
{
    load_2Dmodule_149f626 = voba_module_var("compiler/module_info","c4f0ee24-d107-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("load-module")));
}
    /*let env*/
    voba_value_t mi_1499296 /* mi */ __attribute__((unused)) = VOBA_UNDEF;

    /*decl let return value*/
    voba_value_t let_ret_0 __attribute__((unused)) = VOBA_UNDEF;
    /*let body*/
    voba_value_t apply_ret_3 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_4 [] = { 1 /* prepare arguments for apply */
             ,voba_make_i32(1) /* argument 1 */
        };
        apply_ret_3 = voba_apply(voba_symbol_value(argv_149eae6 /* argv */),voba_make_tuple(apply_args_4));/* return value for apply */
        voba_value_t apply_ret_1 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_2 [] = { 1 /* prepare arguments for apply */
             ,apply_ret_3 /* argument 1 */
        };
        apply_ret_1 = voba_apply(voba_symbol_value(read_module_info_149f536 /* read_module_info */),voba_make_tuple(apply_args_2));/* return value for apply */
        voba_value_t mi_5 __attribute__((unused)) = VOBA_UNDEF;
        mi_5 = apply_ret_1;/* value for set var*/
        mi_1499296 = mi_5; /* set mi */
        voba_value_t apply_ret_6 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_7 [] = { 1 /* prepare arguments for apply */
             ,mi_1499296 /* mi */ /* argument 1 */
        };
        apply_ret_6 = voba_apply(voba_symbol_value(load_2Dmodule_149f626 /* load-module */),voba_make_tuple(apply_args_7));/* return value for apply */

    let_ret_0 = apply_ret_6; /* set letreturn value*/
}

