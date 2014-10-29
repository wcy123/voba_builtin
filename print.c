#define EXEC_ONCE_TU_NAME "voba.builtin.print"
#define EXEC_ONCE_DEPENDS {"voba.builtin",NULL}
#include <voba/include/value.h>
#include <voba/include/module.h>
#include "gf.h"
VOBA_FUNC voba_value_t print(voba_value_t self, voba_value_t a1) 
{
    int64_t len = voba_array_len(a1);
    for(int i = 0; i < len; ++i){
        voba_value_t args[] = {1,voba_array_at(a1,i)};
        voba_value_t s = voba_apply(gf_str,voba_make_array(args));
        fwrite((const void*)voba_str_to_cstr(voba_value_to_str(s)),1,voba_strlen(voba_value_to_str(s)),stdout);
        if(i!=0){
             fputc(' ',stdout);
        }
    }
    fputc('\n',stdout);
    return VOBA_NIL;
}
