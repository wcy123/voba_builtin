#pragma once
#ifndef MODULE_NAME
#define MODULE_NAME "builtin_module"
#endif
#define SYMBOL_TABLE(XX)                        \
    XX(get_class)                               \
    XX(gf_apply)                                \
    XX(apply)                                   \
    XX(to_string)                               \
    XX(to_i32)                                  \
    XX(print)
#include "module_begin.h"

#define IMP "./libbuiltin_module.so"
