#pragma once
typedef struct compiler_fun_s {
    voba_value_t a_var_A; // arguments: array of var object
    voba_value_t a_var_C; // closure: array of var object
    // parent:
    //   env for the enclosing lexical scope
    //   compiler_fun for the enclosing compiler_fun
    //   nil for the top level
    voba_value_t parent;
    int  is_generator  ;
}compiler_fun_t;
#define COMPILER_FUN(s) VOBA_USER_DATA_AS(compiler_fun_t *,s)


