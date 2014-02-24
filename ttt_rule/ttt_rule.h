#ifndef __TTT_RULE_H__
#define __TTT_RULE_H__

#include "types.h"

void get_field_size(point_t *);
uint8_t **get_field();
void fill_field(uint8_t **);
uint8_t check_and_apply_move(uint8_t , void *);
uint8_t check_end_conditions();

#endif