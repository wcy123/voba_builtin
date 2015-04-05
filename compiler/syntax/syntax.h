#pragma once
#define VOBA_MODULE_ID "0fde17fe-d045-11e4-bf65-0800272ae0cc"

#define VOBA_SYMBOL_TABLE(XX)           \
    XX(make_2Dsyntax)                   \
    XX(syntax_2Dvalue)                  \
    XX(syntax_2Dstart_pos)              \
    XX(syntax_2Dend_pos)                \
    XX(syntax_2Dsource)                 \
    XX(syntax_2Dclass)                  \
    
    
#define VOBA_MODULE_NAME "compiler/syntax"
#include <voba/module_end.h>
