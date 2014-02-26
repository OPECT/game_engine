#include "global_settings.h"
#include <stdio.h>

player_ent_t player_ent1;
player_ent_t player_ent2;
player_ent_t *g_player[2];

ai_data_t g_ai_data;

void set_players() {
   g_player[0] = &player_ent1;
   g_player[1] = &player_ent2;
}

void switch_players() {
   g_player[0] = g_player[0] == &player_ent1 ? &player_ent2 : &player_ent1;
   g_player[1] = g_player[1] == &player_ent2 ? &player_ent1 : &player_ent2;
}

void set_player_name(uint8_t player_id, char const *value) {
   snprintf(g_player[player_id]->name, MAX_OUTPUT_BUF_LEN, "%s", value);
}

void set_player_func_list(uint8_t player_id,
   player_func_list_t const *func_list) {
   g_player[player_id]->func_list = func_list;
}

void set_player_ctx(uint8_t player_id, void *ctx) {
   g_player[player_id]->player_ctx = ctx;
}

char const *get_player_name(uint8_t player_id) {
   return g_player[player_id]->name;
}

player_func_list_t const *get_player_func_list(uint8_t player_id) {
   return g_player[player_id]->func_list;
}

void *get_player_ctx(uint8_t player_id) {
   return g_player[player_id]->player_ctx;
}
