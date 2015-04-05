#pragma once
// compilation environment for looking up a symbol
typedef struct env_s {
    voba_value_t a_var; // local variables or top level variables
    // parent:
    //   env for the enclosing lexical scope
    //   compiler_fun for the enclosing compiler_fun
    //   nil for the top level
    voba_value_t parent; 
}env_t;
#define ENV(s)  VOBA_USER_DATA_AS(env_t *,s)
extern voba_value_t voba_cls_env;

