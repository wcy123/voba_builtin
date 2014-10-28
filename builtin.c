#define EXEC_ONCE_TU_NAME "voba_builtin_module"
#define EXEC_ONCE_DEPENDS {"voba_module",NULL}
#include <voba/include/value.h>
#include <voba/include/module.h>
#include "builtin.h"
#include "str.h"
#include "str.c"
#include "cls.c"
#include "print.c"
#include "apply.c"
#include "op_plus.c"
#include "op_cmp.c"
#include "match.c"
#include "iter.c"
VOBA_FUNC static voba_value_t get_class(voba_value_t self, voba_value_t v)
{
    return voba_get_class(v);
}
EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_get_class,voba_make_func(get_class));
}
// the main entry
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}
