#ifndef __MENU_ENGINE_H__
#define __MENU_ENGINE_H__

#include "types.h"

uint8_t show_start_menu();
uint8_t show_finish_menu();

void show_simple_menu(menu_item_t const *ctx);
void switch_and_start_game(menu_item_t const *ctx);
void simple_start_game(menu_item_t const *ctx);

void apply_player_name(menu_item_t const *ctx);
const char *get_player1_name();
const char *get_player2_name();

void set_hot_seat_mode();

#endif
