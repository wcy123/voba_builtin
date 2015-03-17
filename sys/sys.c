#define EXEC_ONCE_TU_NAME "voba.sys"
#define EXEC_ONCE_DEPENDS {"voba.module"}
#include <voba/value.h>
#include <voba/module.h>
#include "sys.h"
EXEC_ONCE_PROGN{
    VOBA_DEFINE_MODULE_SYMBOL(s_argv,VOBA_NIL);
}
voba_value_t voba_init(voba_value_t this_module)
{
    return VOBA_NIL;
}
