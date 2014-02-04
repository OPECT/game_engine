#ifndef __CONSOLE_IO_H__
#define __CONSOLE_IO_H__

#include "../inc/types.h"
#include <stdio.h>

void show_field(uint8_t **field, point_t *size) {
   printf("under constraction\n");
}
void show_result(game_status_t state, player_ent_t *player) {
   printf("under constraction\n");
}

void get_player_input(point_t *input, player_ent_t *player) { input->x = 0;
   input->y = 0; }

#endif