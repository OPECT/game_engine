#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define PLAYER1 0
#define PLAYER2 1

#define MAX_OUTPUT_BUF_LEN 256

struct player_func_list;

typedef enum {
   MENU_ITEM_CLICKABLE,
   MENU_ITEM_EDITABLE,
   MENU_ITEM_TEXT
} menu_item_type_t;

typedef enum {
   GS_PLAYER1_VICTORY,
   GS_PLAYER2_VICTORY,
   GS_DRAW,
   GS_ONGOING
} game_status_t;

typedef struct menu_item {
   uint8_t id;
   const char *(* get_title)();
   menu_item_type_t type;
   void (* action)(struct menu_item const *);
   void *data;
} menu_item_t;

typedef struct menu_list {
   uint8_t size;
   uint8_t action_item_num;
   void (* configure_settings)();
   menu_item_t menu[];
} menu_list_t;

typedef struct point {
   uint8_t x;
   uint8_t y;
} point_t;

typedef struct {
   uint8_t **marked_fld;
   uint8_t **own_fld;
} ai_data_t;

typedef struct player_ent {
   const struct player_func_list *func_list;
   char name[MAX_OUTPUT_BUF_LEN];
   void *player_ctx;
} player_ent_t;

#endif