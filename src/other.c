#include <voba/value.h>
#include <voba/module.h>
#include "gf.h"
VOBA_FUNC voba_value_t get_class(voba_value_t self, voba_value_t v)
{
    return voba_get_class(v);
}
