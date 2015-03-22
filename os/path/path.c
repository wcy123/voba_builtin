#include <stdio.h>
#include <stdlib.h>
#define EXEC_ONCE_TU_NAME "os.path"
#include <exec_once.h>
#include <voba/value.h>

#include "../../src/builtin.h"
static VOBA_FUNC voba_value_t voba_pathstr_file(voba_value_t self, voba_value_t args);
static VOBA_FUNC voba_value_t voba_pathstr_dir(voba_value_t self, voba_value_t args);
static VOBA_FUNC voba_value_t voba_is_pathstr(voba_value_t self,voba_value_t args);


#include "path.h"
#define win32_sep  '\\'
#define unix_sep  '/'
static const char native_sep =
#ifdef WIN32
    win32_sep
#else
    unix_sep
#endif
    ;
#define win32_delimiter  ';'
#define unix_delimiter  ':'
/* static const char native_delimiter =  */
/* #ifdef WIN32 */
/*     win32_delimiter */
/* #else */
/*     unix_delimiter */
/* #endif */
/*     ; */

typedef char bool;
typedef struct path_s{
    bool is_abs_m;
    bool is_dir_m;
    char sep_m;
#ifdef WIN32
    char drive_m;
#endif
    voba_value_t components_m;
}path_t;

VOBA_DEF_CLS(sizeof(path_t),path);
#define PATH(v) VOBA_USER_DATA_AS(path_t*,v)

static inline
voba_value_t split_path(voba_value_t s1)
{
    voba_value_t ret = voba_make_array_0();
    voba_str_t * pathname = voba_value_to_str(s1);
    uint32_t j = 0;
    for(uint32_t i = 0; i < pathname->len; i = j){
        j = voba_str_find(pathname, unix_delimiter, i);
        if(j == UINT32_MAX){ j = pathname->len; };
        voba_str_t * name = voba_substr(pathname,i,j-i);
        // TODO throw exception if name is not valid file name
        voba_array_push(ret,voba_make_string(name));
    }
    return ret;
}
VOBA_FUNC static 
voba_value_t to_filename(voba_value_t a0, char sep)
{
    path_t * p = PATH(a0);
    voba_str_t * s = voba_str_empty();
    if(!p->is_abs_m){
        s = voba_strcat_char(s,'.');
    }
    int64_t len = voba_array_len(p->components_m);
    if(len > 0){ 
        for(int64_t i = 0; i < len; ++i){
            s = voba_strcat_char(s,sep);
            s = voba_strcat(s,voba_value_to_str(voba_array_at(p->components_m,i)));
        }
    }
    if(p->is_dir_m){
        s = voba_strcat_char(s,sep);
    }
    return voba_make_string(s);
}

VOBA_FUNC static 
voba_value_t to_native(voba_value_t self, voba_value_t args)
{
    voba_value_t a0 = voba_tuple_at(args,0);
    assert(voba_get_class(a0) == voba_cls_path);
    return to_filename(a0,native_sep);
}
EXEC_ONCE_PROGN{voba_gf_add_class(voba_symbol_value(s_str), voba_cls_path, voba_make_func(to_native));}

static inline
voba_value_t voba_pathstr_common(voba_value_t args, int is_dir)
{
    voba_value_t ret = voba_make_user_data(voba_cls_path);
    PATH(ret)->is_abs_m = 0;
    PATH(ret)->is_dir_m = is_dir;
#ifdef WIN32
    PATH(ret)->drive_m = 'C';
#endif
    PATH(ret)->components_m = voba_make_array_0();
    int64_t len = voba_tuple_len(args);
    for(int64_t i = 0 ; i < len; ++i){
        voba_value_t a = voba_tuple_at(args,i);
        if(voba_is_a(a,voba_cls_str)){
            a = split_path(a);
        }else if(voba_eq(voba_direct_apply_n(voba_is_pathstr, a), VOBA_TRUE)){
            a = PATH(a)->components_m;
        }else{
            VOBA_THROW(VOBA_CONST_CHAR("unexpected type of arg, expected a string or pathstr. i = ")
                       ,voba_str_fmt_int64_t(i,10)
                );
        }
        voba_array_concat(PATH(ret)->components_m,a);
    }
    return ret;
}

static VOBA_FUNC voba_value_t voba_pathstr_file(voba_value_t self, voba_value_t args)
{
    return voba_pathstr_common(args,0);
}
EXEC_ONCE_PROGN{VOBA_DEFINE_MODULE_SYMBOL(s_file, voba_make_func(voba_pathstr_file));}

static VOBA_FUNC voba_value_t voba_pathstr_dir(voba_value_t self, voba_value_t args)
{
    return voba_pathstr_common(args,1);
}
EXEC_ONCE_PROGN{VOBA_DEFINE_MODULE_SYMBOL(s_dir, voba_make_func(voba_pathstr_dir));}

static VOBA_FUNC voba_value_t voba_is_pathstr(voba_value_t self,voba_value_t args)
{
    assert(voba_tuple_len(args) == 1);
    return voba_get_class(voba_tuple_at(args,0)) == voba_cls_path?VOBA_TRUE:VOBA_FALSE;
}


// the main entry
voba_value_t voba_init(voba_value_t this_module)
{
    exec_once_init();
    return VOBA_NIL;
}

