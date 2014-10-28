#pragma once
VOBA_FUNC static voba_value_t str_string(voba_value_t self,voba_value_t v);
VOBA_FUNC static voba_value_t str_funcp(voba_value_t self, voba_value_t v);
VOBA_FUNC static voba_value_t str_array(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t str_closure(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t str_pair(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t str_la(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t str_undef(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t str_nil(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t str_boolean(voba_value_t self,voba_value_t vs);
VOBA_FUNC static voba_value_t str_symbol(voba_value_t self,voba_value_t vs);
static voba_value_t gf_str = VOBA_UNDEF;


