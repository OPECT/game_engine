#include "output_code.h"
#include "callback_types.h"
#include "global_settings.h"

#include "ttt_game/tic_tac_toe_menu.h"

extern io_func_t io_func;
extern player_func_list_t player_callbacks;

static uint8_t is_exit;
static uint8_t start_game;

void show_simple_menu(menu_item_t const *ctx) {
   uint8_t input;
   menu_list_t *menu = (menu_list_t*) ctx->data;

   if (menu->configure_settings)
      menu->configure_settings();

   while (1) {
      io_func.show_menu(menu);
      input = io_func.get_menu_input();

      if (menu->menu[input].id == BACK)
         return;
      if (menu->menu[input].id == EXIT) {
         is_exit = 1;
         return;
      }

      if (menu->menu[input].action)
         menu->menu[input].action(&menu->menu[input]);

      if (is_exit || start_game)
         return;
   }
}

void switch_and_start_game(menu_item_t const *ctx) {
   switch_players();
   start_game = 1;
}

void simple_start_game(menu_item_t const *ctx) {
   start_game = 1;
}

uint8_t show_start_menu() {
   menu_item_t main_item = { .id = NONE, .type = MENU_ITEM_CLICKABLE,
      .data = (void *) &main_menu };
   show_simple_menu(&main_item);

   return !is_exit;
}

uint8_t show_finish_menu() {
   is_exit = start_game = 0;
   menu_item_t finish_item = { .id = NONE, .type = MENU_ITEM_CLICKABLE,
         .data = (void *) &finish_menu };
   show_simple_menu(&finish_item);

   return !is_exit;
}

void apply_player_name(menu_item_t const *ctx) {
   uint64_t player_id = (uint64_t) ctx->data;
   char input[MAX_OUTPUT_BUF_LEN];

   io_func.get_string_input(ctx, input);
   set_player_name(player_id, input);
}

const char *get_player1_name() {
   return get_player_name(PLAYER1);
}

const char *get_player2_name() {
   return get_player_name(PLAYER2);
}

void set_hot_seat_mode() {
   set_player_func_list(PLAYER1, &player_callbacks);
   set_player_func_list(PLAYER2, &player_callbacks);
}