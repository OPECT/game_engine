#ifndef __CALLBACKS_TYPE_H__
#define __CALLBACKS_TYPE_H__

#include "types.h"

typedef struct player_func_list {
   void (* init_player)(player_ent_t *);
   int (* get_player_input)(point_t *, player_ent_t const*);
   void (* clear_data)(player_ent_t *);
} player_func_list_t;

typedef struct {
   uint8_t (* init_io)();
   void (* clear_io)();
   char const * (* get_code_str)(uint8_t);

   void (* show_menu)(menu_list_t const *);
   void (* show_field)(uint8_t **, point_t const *);
   void (* show_result)(uint8_t, player_ent_t const *);

   uint8_t (* get_menu_input)(menu_list_t const *);
   void (* get_string_input)(menu_item_t const *, char *);

   void (*show_error) (char *msg);
} io_func_t;

typedef struct {
   void (* get_field_size)(point_t *);
   void (* fill_field)(uint8_t **);
   uint8_t ** (* get_field)();
   uint8_t (* check_and_apply_move)(uint8_t, void *);
   uint8_t (* check_end_conditions)();
   uint8_t (* get_winning_cond)(void *);
} rule_func_t;

#endif
