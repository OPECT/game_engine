#ifndef __GLOBAL_SETTINGS_H__
#define __GLOBAL_SETTINGS_H__

#include "types.h"
#include "callback_types.h"

extern player_ent_t *g_player[2];
extern ai_data_t g_ai_data;

void set_players();
void switch_players();

void set_player_name(uint8_t, char const *);
void set_player_func_list(uint8_t, player_func_list_t const *);
void set_player_ctx(uint8_t, void *);

char const *get_player_name(uint8_t);
player_func_list_t const *get_player_func_list(uint8_t);
void *get_player_ctx(uint8_t);

#endif
