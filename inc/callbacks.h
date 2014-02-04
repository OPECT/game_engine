#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

#include "callback_types.h"

void show_field(uint8_t **field, point_t *size);
void show_result(game_status_t state, player_ent_t *player);
void get_player_input(point_t *input, player_ent_t *player);

void get_field_size(point_t *size);
void fill_field(uint8_t **field);
uint8_t check_and_apply_move(uint8_t turn, void *move);
uint8_t check_end_conditions();

io_func_t io_func = {
   .show_field = show_field,   
   .show_result = show_result
};

rule_func_t rule_func = {
   .get_field_size = get_field_size,
   .fill_field = fill_field,
   .check_and_apply_move = check_and_apply_move,
   .check_end_conditions = check_end_conditions
};

player_func_list_t player_callbacks = { .get_player_input = get_player_input };

#endif