#ifndef __INTERFACE_IO_H__
#define __INTERFACE_IO_H__

#include "types.h"

char const * get_code_str(uint8_t code);

uint8_t init_io();
void clear_io();
void show_menu(menu_list_t const *list);
void show_field(uint8_t **field, point_t const *size);
void show_result(uint8_t state, player_ent_t const *player);

uint8_t get_menu_input(menu_list_t const *list);
void get_string_input(menu_item_t const *menu, char *input);
int get_player_input(point_t *input, player_ent_t const *player);

void show_error(char *msg);
#endif
