#pragma once
#define VOBA_MODULE_ID "28b4792c-366b-11e4-aa00-08002796644a"
#define VOBA_SYMBOL_TABLE(XX)                   \
    XX(get_class)                               \
    XX(to_string)                               \
    XX(to_i32)                                  \
    XX(print)                                   \
    XX(_2B)

//(gf_apply)                              
//(apply)                                 

#define VOBA_MODULE_NAME "voba_builtin"
#include <voba/include/module_end.h>


