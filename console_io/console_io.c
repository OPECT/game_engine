#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "console_io.h"
#include "output_code.h"

#undef BEGIN_ENUM
#undef ENUM
#undef END_ENUM

#define BEGIN_ENUM(name) const char * name ## _table[] = {
#define ENUM(name, value) value
#define END_ENUM(name) };

#undef __OUTPUT_CODE_H__
#include "output_code.h"

#undef BEGIN_ENUM
#undef ENUM
#undef END_ENUM

#define CHAR_TO_DIGIT(ch) (ch - 48)

#define INTRO "Enter your choice\n"
#define WRONG_LENGTH "Entered choice is too long\n"
#define WRONG_CHAR "Please enter only digit signs\n"

#define ENTER_PLAYER_NAME "Enter %s's new name\n"
#define ENTER_UNKNOWN_VALUE "Error in menu, item is unknown\n"

static menu_list_t const *cur_menu;

static void clear_input(char const *msg) {
   while (getchar() != '\n');

   printf("%s", msg);
}

static uint8_t is_input_correct(uint8_t input) {
   if (input > 0 && input <= cur_menu->action_item_num)
      return TRUE;
   printf(ENTER_UNKNOWN_VALUE);
   return FALSE;
}

static uint8_t choice2item(uint8_t choice) {
   int i;

   for (i = 0; i < cur_menu->size && choice; i++) {
      if (cur_menu->menu[i].type != MENU_ITEM_TEXT)
         choice--;
   }
   //XXX error case should be considered(choice != 0)
   return i - 1;
}

static uint8_t get_ushort_from_input() {
   uint8_t choice = 0, ch;

   while ((ch = getchar()) != '\n') {
      if (!isdigit(ch)) {
         clear_input(WRONG_CHAR);
         choice = 0;
         continue;
      }
      if (choice * 10 + CHAR_TO_DIGIT(ch) > USHRT_MAX) {
         clear_input(WRONG_LENGTH);
         choice = 0;
         continue;
      }
      choice = choice * 10 + CHAR_TO_DIGIT(ch);
   }
   return choice;
}

char const * get_code_str(uint8_t code) {
   return output_code_table[code];
}

void show_menu(menu_list_t const *list) {
   uint8_t num = 1;
   char item_msg[MAX_OUTPUT_BUF_LEN];

   system("clear");
   for (int ind = 0; ind < list->size; ind++) {
      switch (list->menu[ind].type) {
         case MENU_ITEM_CLICKABLE:
            snprintf(item_msg, MAX_OUTPUT_BUF_LEN, "%d) %s\n", num++,
               output_code_table[list->menu[ind].id]);
            break;
         case MENU_ITEM_EDITABLE:
            snprintf(item_msg, MAX_OUTPUT_BUF_LEN, "%d) %s\n", num++,
               list->menu[ind].get_title());
            break;
         case MENU_ITEM_TEXT:
            snprintf(item_msg, MAX_OUTPUT_BUF_LEN, "%s\n",
               output_code_table[list->menu[ind].id]);
            break;
         default:
            snprintf(item_msg, MAX_OUTPUT_BUF_LEN, "%s\n",
               "item not supported");
      }

      printf("%s", item_msg);
   }
   cur_menu = list;
}

void show_field(uint8_t **field, point_t const *size) {
   printf("under constraction\n");
}

void show_result(game_status_t state, player_ent_t const *player) {
   printf("under constraction\n");
}

uint8_t get_menu_input() {
   uint8_t choice;
   uint8_t item;

   printf("%s", INTRO);
   choice = get_ushort_from_input();
   while (!is_input_correct(choice)) {
      choice = get_ushort_from_input();
   }

   item = choice2item(choice);
   return item;
}

void get_string_input(menu_item_t const *menu, char *message) {
   switch (menu->id) {
      case DEFAULT_PLAYER_NAME1:
      case DEFAULT_PLAYER_NAME2:
         printf(ENTER_PLAYER_NAME, output_code_table[menu->id]);
         break;
      default:
         printf(ENTER_UNKNOWN_VALUE, output_code_table[menu->id]);
   }

   fgets(message, MAX_OUTPUT_BUF_LEN, stdin);
   if (message[strlen(message) - 1] == '\n')
      message[strlen(message) - 1] = '\0';
}

void get_player_input(point_t *input, player_ent_t const *player) {
   input->x = 0;
   input->y = 0;
}
