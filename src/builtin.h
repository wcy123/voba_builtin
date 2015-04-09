#pragma once 
#define VOBA_MODULE_ID "28b4792c-366b-11e4-aa00-08002796644a"
#define VOBA_SYMBOL_TABLE(XX)                           \
    XX(get_class)                                       \
    XX(str)                                             \
    XX(print)                                           \
    XX(len)                                             \
    XX(range)                                           \
    XX(_2B)/*+*/                                        \
    XX(_3E)/*>*/                                        \
    XX(_3C)/*<*/                                        \
    XX(_3E_3D)/*>=*/                                    \
    XX(_3C_3D)/*<=*/                                    \
    XX(_3D_3D)/*==*/                                    \
    XX(_25)/* % */                                      \
    XX(_3C_3C)/*<<*/                                    \
    XX(array)                                           \
    XX(eq)                                              \
    XX(i32_mod)                                         \
    XX(eq_i32_mod_0)                                    \
    XX(cls_i32)                                         \
    XX(cls_float)                                       \
    XX(cls_str)                                         \
    XX(array_2Diter)                                    \
    XX(isa)                                             \
    XX(match_2Dtuple)                                   \
    XX(tuple)                                           \
    
//(gf_apply)                              
//(apply)                                 

#define VOBA_MODULE_NAME "builtin"
#include <voba/module_end.h>


