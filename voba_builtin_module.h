#pragma once
#ifndef MODULE_NAME
#define MODULE_NAME "voba_builtin_module"
#endif
#define SYMBOL_TABLE(XX)                        \
    XX(get_class)                               \
    XX(gf_apply)                                \
    XX(apply)                                   \
    XX(to_string)                               \
    XX(to_i32)                                  \
    XX(print)
#define IMP "./libvoba_builtin.so"

#include "voba_module_end.h"


