#pragma once
#define VOBA_MODULE_ID "28b4792c-366b-11e4-aa00-08002796644a"
#define VOBA_SYMBOL_TABLE(XX)                       \
    XX(get_class)                                   \
    XX(to_string)                                   \
    XX(to_i32)                                      \
    XX(print)                                       \
    XX(_2B)/*+*/                                    \
    XX(_3E)/*>*/                                    \
    XX(_3C)/*<*/                                    \
    XX(_3E_3D)/*>=*/                                    \
    XX(_3C_3D)/*<=*/                                    \
    XX(_3D_3D)/*==*/                                    \
    XX(cls_i8)                                      \
    XX(cls_i16)                                     \
    XX(cls_i32)                                     \
    XX(cls_u8)                                      \
    XX(cls_u16)                                     \
    XX(cls_u32)                                     \
    XX(cls_float)                                   \
    XX(cls_str)                                     \

//(gf_apply)                              
//(apply)                                 

#define VOBA_MODULE_NAME "voba_builtin"
#include <voba/include/module_end.h>


