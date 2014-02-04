#ifndef __CALLBACKS_TYPE_H__
#define __CALLBACKS_TYPE_H__

#include "types.h"

typedef struct player_func_list {
   void (* init_player)(player_ent_t *);
   void (* get_player_input)(point_t *, player_ent_t *);
   void (* clear_data)(player_ent_t *);
} player_func_list_t;

typedef struct {
   void (* show_field)(uint8_t **, point_t *);
   void (* show_result)(game_status_t, player_ent_t *);
} io_func_t;

typedef struct {
   void (* get_field_size)(point_t *);
   void (* fill_field)(uint8_t **);
   uint8_t (* check_and_apply_move)(uint8_t, void *);
   uint8_t (* check_end_conditions)();
} rule_func_t;

#endif