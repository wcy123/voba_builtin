#pragma once
#define DECLARE_GF(n)                           \
    extern voba_value_t gf_##n;                 \

#define BUILTIN_GF(XX)                          \
XX(str)                                         \
XX(len)                                         \
XX(iter)                                        \
XX(apply)                                       \
XX(equal)                                       \
XX(gt)                                          \
XX(gt_eq)                                       \
XX(lt)                                          \
XX(lt_eq)                                       \
XX(plus)                                        \
XX(mod)                                         \
XX(left_shift)                                  \

extern voba_value_t gf_match;

BUILTIN_GF(DECLARE_GF);


