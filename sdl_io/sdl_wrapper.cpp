#include "ui_engine.h"
#include <vector>

extern "C" {

   #include "error.h"
   #include "interface_io.h"
   #include "output_code.h"
   #include "stdio.h"
   #include "callback_types.h"

   extern rule_func_t rule_func;

   #undef BEGIN_ENUM
   #undef ENUM
   #undef END_ENUM

   #define BEGIN_ENUM(name) const char * name ## _table[] = {
   #define ENUM(name, value) value
   #define END_ENUM(name) };

   #undef __OUTPUT_CODE_H__
   #include "output_code.h"
   #include "../ttt_rule/ttt_str_code.h"

   #undef BEGIN_ENUM
   #undef ENUM
   #undef END_ENUM
}

UI_engine *ui_engine;

char const * get_code_str(uint8_t code) {
   return output_code_table[code];
}

uint8_t init_io() {
   ui_engine = UI_engine::get_ui_instanse(output_code_table[TITLE]);
   if (!ui_engine) {
      printf("inti failed\n");
      return 1;
   }
   if (!ui_engine->basic_loads()) {
      printf("background failed\n");
      return 1;
   }
   return 0;
}

void clear_io() {
   UI_engine::delete_ui_instanse();
}

void show_menu(menu_list_t const *list) {
   vector<string> item_list;
   string item;

   for (int ind = 0; ind < list->size; ind++) {
      switch (list->menu[ind].type) {
         case MENU_ITEM_EDITABLE:
            item = list->menu[ind].get_title();
            break;
         case MENU_ITEM_TEXT:
         case MENU_ITEM_CLICKABLE:
            item = output_code_table[list->menu[ind].id];
            break;
         default:
            item = "item not supported";
      }
      item_list.push_back(item);
   }
   try {
      ui_engine->show_menu(item_list);
   }
   catch (UI_engine_err *e) {
      delete e;
   }
}

void show_field(uint8_t **field, point_t const *size) {
   vector<string> figures;

   for (int idx = 0; idx < sizeof(ttt_code_table) / sizeof(char*); idx++)
      figures.push_back(ttt_code_table[idx]);
   ui_engine->show_field(field, size, figures);
}

void show_result(uint8_t state, player_ent_t const *player) {
   winning_data_t data;

   rule_func.get_winning_cond(&data);
   try {
      ui_engine->show_result(state, player, &data);
   }
   catch (UI_engine_err *e) {
      set_error(e->get_message().c_str(), e->get_message().size());
      delete e;
   }
}

uint8_t get_menu_input(menu_list_t const *list) {
   uint8_t choice = 0;

   while(TRUE) {
      try {
         choice = ui_engine->get_menu_input();
      }
      catch(UI_engine_err e) {
         set_error(e.get_message().c_str(), e.get_message().size());
         break;
      }
      if (list->menu[choice].type != MENU_ITEM_TEXT)
         return choice;
   }
   return choice;
}

void get_string_input(menu_item_t const *menu, char *input) {}

int get_player_input(point_t *input, player_ent_t const *player) {
   uint8_t res;

   try {
      res = ui_engine->get_game_input(input);
   }
   catch(UI_engine_err e) {
      set_error(e.get_message().c_str(), e.get_message().size());
      return FALSE;
   }
   return res;
}

void show_error(char *msg) {
   if (is_error())
      printf("ERROR:%s\n", get_error());
}