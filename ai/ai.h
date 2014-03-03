#ifndef __AI_H__
#define __AI_H__

#include "types.h"

void init_data(player_ent_t *ctx);
int make_move(point_t *move, player_ent_t const *ctx);
void clear_data(player_ent_t *ctx);

#endif