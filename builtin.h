#pragma once
#define VOBA_MODULE_ID "28b4792c-366b-11e4-aa00-08002796644a"
#define VOBA_SYMBOL_TABLE(XX)                   \
    XX(get_class)                               \
    XX(gf_apply)                                \
    XX(apply)                                   \
    XX(to_string)                               \
    XX(to_i32)                                  \
    XX(print)

#define VOBA_MODULE_NAME "libvoba_builtin"
#include <voba/include/module_end.h>


