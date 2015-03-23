#pragma once
typedef struct source_s {
    voba_str_t* filename;
    voba_str_t* content;
} source_t;
#define SOURCE(s) VOBA_USER_DATA_AS(source_t *,s)





