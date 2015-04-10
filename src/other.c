#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"
VOBA_FUNC voba_value_t get_class(voba_value_t fun, voba_value_t v, voba_value_t* next_fun, voba_value_t next_args[])
{
    return voba_get_class(v);
}
