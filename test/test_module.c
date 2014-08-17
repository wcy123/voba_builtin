#include "voba_value.h"
#include "voba_module.h"
#include "../src/voba_builtin_module.h"

#include "s_macro.h"

EXEC_ONCE_START
int main(int argc, char *argv[])
{
    char module_name[128];
    char pwd [128];
    fscanf(stdin,"%s %s",module_name,pwd);
    voba_value_t args [] = {1, voba_import(voba_make_string(voba_str_from_cstr(module_name)),
                                           voba_make_string(voba_str_from_cstr(pwd))) };
    S(voba_symbol_value(s_print), A(args));
    args [1] = voba_import(voba_make_string(voba_str_from_cstr(module_name)),
                           voba_make_string(voba_str_from_cstr(pwd)));
    S(voba_symbol_value(s_print), A(args));
    return 0;
}
