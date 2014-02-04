#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define PLAYER1_TURN 1
#define PLAYER2_TURN 2

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
   char *custom_title;
   menu_item_type_t type;
   void (* pre_action)();
   void (* action)(struct menu_item *);
   void *data;
} menu_item_t;

typedef struct menu_list {
   int32_t size;
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
   struct player_func_list *input;
   char name[MAX_OUTPUT_BUF_LEN];
   ai_data_t *ai_ctx;
} player_ent_t;

#endif