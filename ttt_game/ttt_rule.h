#ifndef __TTT_RULE_H__
#define __TTT_RULE_H__

#include "../inc/types.h"

void get_field_size(point_t *size) { size->y = 3; size->x = 3; }

void fill_field(uint8_t **field) {}
uint8_t check_and_apply_move(uint8_t turn, void *move) { return TRUE; }
uint8_t check_end_conditions() { return GS_DRAW; }

#endif