#include "callbacks.h"
#include "../console_io/console_io.h"
#include "../ttt_rule/ttt_rule.h"

io_func_t io_func = {
   .get_code_str = get_code_str,
   .show_menu = show_menu,
   .show_field = show_field,
   .show_result = show_result,
   .get_menu_input = get_menu_input,
   .get_string_input = get_string_input
};

rule_func_t rule_func = {
   .get_field_size = get_field_size,
   .fill_field = fill_field,
   .check_and_apply_move = check_and_apply_move,
   .check_end_conditions = check_end_conditions
};

player_func_list_t player_callbacks = { .get_player_input = get_player_input };
