#pragma once
VOBA_FUNC static voba_value_t match_single(voba_value_t self, voba_value_t args);
EXEC_ONCE_PROGN{
    gf_match = voba_module_var(VOBA_MODULE_LANG_ID, VOBA_MODULE_LANG_ID,VOBA_MODULE_LANG_MATCH);
}

