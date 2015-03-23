#pragma once
typedef struct syntax_s {
    uint32_t start_pos;
    uint32_t end_pos;
    voba_value_t source;
    voba_value_t value;
} syntax_t;
#define SYNTAX(s) VOBA_USER_DATA_AS(syntax_t *,s)


