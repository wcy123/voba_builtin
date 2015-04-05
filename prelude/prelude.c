#include <stdint.h>
#include <assert.h>
#define EXEC_ONCE_TU_NAME "prelude/prelude.voba built at 2015-4-5 11:32:46."
#define EXEC_ONCE_DEPENDS {"voba.module"};
#include <voba/value.h>
#include <voba/core/builtin.h> // import builtin by default
#include <exec_once.h>
#include <voba/module.h>
#define voba_match_eq voba_eql
static voba_value_t gf_match __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t get_class_1bf0456 /* get_class */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t str_1bf0546 /* str */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t print_1bf0646 /* print */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t len_1bf0736 /* len */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t range_1bf0576 /* range */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _2B_1bf0936 /* + */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3E_1bf0a26 /* > */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_1bf0b16 /* < */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3E_3D_1bf0c96 /* >= */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_3D_1bf0d86 /* <= */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3D_3D_1bf0e76 /* == */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _25_1bf0f66 /* % */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t _3C_3C_1bf1056 /* << */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t array_1bf1146 /* array */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t eq_1bf1236 /* eq */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t i32_mod_1bf1326 /* i32_mod */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t eq_i32_mod_0_1bf14a6 /* eq_i32_mod_0 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_i8_1bf1596 /* cls_i8 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_i16_1bf1686 /* cls_i16 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_i32_1bf1776 /* cls_i32 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_u8_1bf1866 /* cls_u8 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_u16_1bf1956 /* cls_u16 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_u32_1bf1a46 /* cls_u32 */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_float_1bf1b36 /* cls_float */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t cls_str_1bf1c26 /* cls_str */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t array_2Diter_1bf1d16 /* array-iter */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t argv_1bf3416 /* argv */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t read_module_info_1bf3e66 /* read_module_info */ __attribute__((unused)) = VOBA_UNDEF;
    voba_value_t load_2Dmodule_1bf3f56 /* load-module */ __attribute__((unused)) = VOBA_UNDEF;
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
         "cls_i8",
         "cls_i16",
         "cls_i32",
         "cls_u8",
         "cls_u16",
         "cls_u32",
         "cls_float",
         "cls_str",
         "array-iter",
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
    get_class_1bf0456 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("get_class")));
}
{
    str_1bf0546 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("str")));
}
{
    print_1bf0646 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("print")));
}
{
    len_1bf0736 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("len")));
}
{
    range_1bf0576 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("range")));
}
{
    _2B_1bf0936 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("+")));
}
{
    _3E_1bf0a26 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr(">")));
}
{
    _3C_1bf0b16 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<")));
}
{
    _3E_3D_1bf0c96 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr(">=")));
}
{
    _3C_3D_1bf0d86 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<=")));
}
{
    _3D_3D_1bf0e76 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("==")));
}
{
    _25_1bf0f66 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("%")));
}
{
    _3C_3C_1bf1056 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("<<")));
}
{
    array_1bf1146 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("array")));
}
{
    eq_1bf1236 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("eq")));
}
{
    i32_mod_1bf1326 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("i32_mod")));
}
{
    eq_i32_mod_0_1bf14a6 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("eq_i32_mod_0")));
}
{
    cls_i8_1bf1596 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_i8")));
}
{
    cls_i16_1bf1686 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_i16")));
}
{
    cls_i32_1bf1776 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_i32")));
}
{
    cls_u8_1bf1866 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_u8")));
}
{
    cls_u16_1bf1956 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_u16")));
}
{
    cls_u32_1bf1a46 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_u32")));
}
{
    cls_float_1bf1b36 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_float")));
}
{
    cls_str_1bf1c26 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("cls_str")));
}
{
    array_2Diter_1bf1d16 = voba_module_var("builtin","28b4792c-366b-11e4-aa00-08002796644a",voba_make_string(voba_str_from_cstr("array-iter")));
}
{
    argv_1bf3416 = voba_module_var("sys","7e15786a-cb7d-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("argv")));
}
{
    read_module_info_1bf3e66 = voba_module_var("compiler/module_info","c4f0ee24-d107-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("read_module_info")));
}
{
    load_2Dmodule_1bf3f56 = voba_module_var("compiler/module_info","c4f0ee24-d107-11e4-bf65-0800272ae0cc",voba_make_string(voba_str_from_cstr("load-module")));
}
    /*let env*/
    voba_value_t mi_1bed896 /* mi */ __attribute__((unused)) = VOBA_UNDEF;

    /*decl let return value*/
    voba_value_t let_ret_0 __attribute__((unused)) = VOBA_UNDEF;
    /*let body*/
    voba_value_t apply_ret_3 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_4 [] = { 1 /* prepare arguments for apply */
             ,voba_make_i32(1) /* argument 1 */
        };
        apply_ret_3 = voba_apply(voba_symbol_value(argv_1bf3416 /* argv */),voba_make_tuple(apply_args_4));/* return value for apply */
        voba_value_t apply_ret_1 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_2 [] = { 1 /* prepare arguments for apply */
             ,apply_ret_3 /* argument 1 */
        };
        apply_ret_1 = voba_apply(voba_symbol_value(read_module_info_1bf3e66 /* read_module_info */),voba_make_tuple(apply_args_2));/* return value for apply */
        voba_value_t mi_5 __attribute__((unused)) = VOBA_UNDEF;
        mi_5 = apply_ret_1;/* value for set var*/
        mi_1bed896 = mi_5; /* set mi */
        voba_value_t apply_ret_6 __attribute__((unused)) = VOBA_UNDEF;/* return value for apply */
        voba_value_t apply_args_7 [] = { 1 /* prepare arguments for apply */
             ,mi_1bed896 /* mi */ /* argument 1 */
        };
        apply_ret_6 = voba_apply(voba_symbol_value(load_2Dmodule_1bf3f56 /* load-module */),voba_make_tuple(apply_args_7));/* return value for apply */

    let_ret_0 = apply_ret_6; /* set letreturn value*/
}

