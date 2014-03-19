#include "callbacks.h"
#include "interface_io.h"
#include "../ttt_rule/ttt_rule.h"
#include "../ai/ai.h"

io_func_t io_func = {
   .init_io = init_io,
   .clear_io = clear_io,
   .get_code_str = get_code_str,
   .show_menu = show_menu,
   .show_field = show_field,
   .show_result = show_result,
   .get_menu_input = get_menu_input,
   .get_string_input = get_string_input,
   .show_error = show_error
};

rule_func_t rule_func = {
   .get_field_size = get_field_size,
   .fill_field = fill_field,
   .get_field = get_field,
   .check_and_apply_move = check_and_apply_move,
   .check_end_conditions = check_end_conditions,
   .get_winning_cond = get_winning_cond
};

player_func_list_t player_callbacks = { .get_player_input = get_player_input };

player_func_list_t ai_callbacks = {
   .init_player = init_data,
   .get_player_input = make_move,
   .clear_data = clear_data
};
