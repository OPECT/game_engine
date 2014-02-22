#include <stdlib.h>
#include "callbacks.h"
#include "console_io/console_io.h"
#include "menu_engine.h"
#include "global_settings.h"
#include "ttt_game/ttt_rule.h"
#include "output_code.h"

#define GET_TURN(player) (player == g_player[0] ? PLAYER1 : PLAYER2)
#define GET_NEXT_TURN(player) (player == g_player[0] ? PLAYER2 : PLAYER1)
#define SWITCH_PLAYERS(player) player = g_player[GET_NEXT_TURN(player)]

static void global_init() {
   set_players();
   set_player_name(PLAYER1, io_func.get_code_str(DEFAULT_PLAYER_NAME1));
   set_player_name(PLAYER2, io_func.get_code_str(DEFAULT_PLAYER_NAME2));
}

int main(void) {
   uint8_t **field;
   point_t field_size, input;
   game_status_t state;
   player_ent_t *cur_player;

   global_init();
   if (!show_start_menu())
      return 0;

   rule_func.get_field_size(&field_size);

   field = (uint8_t **) calloc(field_size.y, sizeof(uint8_t *));
   for (int i = 0; i < field_size.y; i++)
      field[i] = (uint8_t *) calloc(field_size.x, sizeof(uint8_t));

   while (1) {
      rule_func.fill_field(field);
      if (g_player[0]->func_list->init_player)
         g_player[0]->func_list->init_player(g_player[0]);
      if (g_player[1]->func_list->init_player)
         g_player[1]->func_list->init_player(g_player[1]);

      io_func.show_field(field, &field_size);
      cur_player = g_player[0];

      while(1) {
         cur_player->func_list->get_player_input(&input, cur_player);
         if (!rule_func.check_and_apply_move(GET_TURN(cur_player),
            (void *) &input)) {
            continue;
         }
         io_func.show_field(field, &field_size);
         state = rule_func.check_end_conditions();
         if (state != GS_ONGOING) {
            io_func.show_result(state, cur_player);
            break;
         }
	 cur_player = g_player[GET_NEXT_TURN(cur_player)];
      }
      if (g_player[0]->func_list->clear_data)
         g_player[0]->func_list->clear_data(g_player[0]);
      if (g_player[1]->func_list->clear_data)
         g_player[1]->func_list->clear_data(g_player[1]);

      if (!show_finish_menu())
         break;
   }

   for (int i = 0; i < field_size.y; i++)
      free(field[i]);
   free(field);
}
