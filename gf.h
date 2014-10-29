#pragma once
#define DECLARE_GF(n)                           \
static voba_value_t gf_##n = VOBA_UNDEF;        \
EXEC_ONCE_PROGN{                                \
    gf_ ## n = voba_make_generic_function(# n); \
}

#define BUILTIN_GF(XX)                          \
XX(str)                                         \
XX(match)                                       \
XX(plus)                                        \
XX(len)                                         \
XX(iter)                                        \
XX(apply)                                       \
XX(equal)                                       \
XX(gt)                                          \
XX(gt_eq)                                       \
XX(lt)                                          \
XX(lt_eq)                                       \



BUILTIN_GF(DECLARE_GF);


