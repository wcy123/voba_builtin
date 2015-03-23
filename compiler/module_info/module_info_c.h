#pragma once
typedef struct module_info_s{
    voba_value_t syn_name;
    voba_value_t syn_id;
    voba_value_t a_syn_symbols; // an array of names
}module_info_t;
#define MODULE_INFO(v) VOBA_USER_DATA_AS(module_info_t*,v)


