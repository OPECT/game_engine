#include <stdlib.h>
#include "inc/callbacks.h"
#include "console_io/console_io.h"
#include "inc/global_settings.h"
#include "ttt_game/ttt_rule.h"

#define GET_TURN(player) (player == g_player1 ? PLAYER1_TURN : PLAYER2_TURN)
#define SWITCH_PLAYERS(player) player = player == g_player1 ? g_player2 : \
                              g_player1

int main(void) {
   uint8_t **field;
   point_t field_size, input;
   game_status_t state;
   player_ent_t *cur_player;

   g_player1->input = &player_callbacks;
   g_player2->input = &player_callbacks;

   rule_func.get_field_size(&field_size);

   field = (uint8_t **) calloc(field_size.y, sizeof(uint8_t *));
   for (int i = 0; i < field_size.y; i++)
      field[i] = (uint8_t *) calloc(field_size.x, sizeof(uint8_t));

   while (1) {
      rule_func.fill_field(field);
      if (g_player1->input->init_player)
         g_player1->input->init_player(g_player1);
      if (g_player2->input->init_player)
         g_player2->input->init_player(g_player2);

      io_func.show_field(field, &field_size);
      cur_player = g_player1;

      while(1) {
         cur_player->input->get_player_input(&input, cur_player);
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
         SWITCH_PLAYERS(cur_player);
      }
      if (g_player1->input->clear_data)
         g_player1->input->clear_data(g_player1);
      if (g_player2->input->clear_data)
         g_player2->input->clear_data(g_player2);

      break;
   }

   for (int i = 0; i < field_size.y; i++)
      free(field[i]);
   free(field);
}