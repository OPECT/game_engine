#ifndef __MENU_ENGINE_H__
#define __MENU_ENGINE_H__

#include "types.h"

uint8_t show_start_menu();
uint8_t show_finish_menu();
uint8_t show_context_menu();

uint8_t show_simple_menu(menu_item_t const *ctx);
uint8_t switch_and_start_game(menu_item_t const *ctx);
uint8_t simple_start_game(menu_item_t const *ctx);
uint8_t continue_game(menu_item_t const *ctx);
uint8_t show_main_menu(menu_item_t const *ctx);

uint8_t apply_player_name(menu_item_t const *ctx);
const char *get_player1_name();
const char *get_player2_name();

void set_hot_seat_mode();
void set_computer_oponent_mode();

#endif
