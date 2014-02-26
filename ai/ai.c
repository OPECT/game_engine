#include <stdlib.h>
#include <stdio.h>

#include "ai.h"
#include "enum_macro.h"
#include "../ttt_rule/ttt_str_code.h"
#include "callbacks.h"
#include "global_settings.h"

#define VALUE_2_NATIVE_SIGN 100
#define VALUE_2_OPPOSITE_SIGN 75
#define VALUE_NEW_NATIVE_SIGN 25
#define VALUE_NEW_NATIVE_SIGN_WITH_OPPOSITE_SIGN 12
#define VALUE_NEW_OPPOSITE_SIGN 12
#define VALUE_OCCUPIED_WITH_ITEM 0
#define VALUE_MINIMUM_CELL_VALUE 1

#define INIT_VALUE_CROSS_DIAG 12
#define INIT_VALUE_CROSS_CENTER VALUE_MINIMUM_CELL_VALUE
#define INIT_VALUE_CROSS_MIDDLE VALUE_MINIMUM_CELL_VALUE

#define INIT_VALUE_NOUGHT_DIAG 25
#define INIT_VALUE_NOUGHT_CENTER 50
#define INIT_VALUE_NOUGHT_MIDDLE VALUE_MINIMUM_CELL_VALUE

#define GET_MY_ITEMS_TYPE(player) (player == g_player[0] ? CROSS : NOUGHT)
#define GET_OP_ITEMS_TYPE(player) (player == g_player[0] ? NOUGHT : CROSS)

#define GET_DIAG_INIT_VAL(item) (item == CROSS ? INIT_VALUE_CROSS_DIAG : \
   INIT_VALUE_NOUGHT_DIAG)
#define GET_CENTER_INIT_VAL(item) (item == CROSS ? INIT_VALUE_CROSS_CENTER : \
   INIT_VALUE_NOUGHT_CENTER)
#define GET_MIDDLE_INIT_VAL(item) (item == CROSS ? INIT_VALUE_CROSS_MIDDLE : \
   INIT_VALUE_NOUGHT_MIDDLE)

#define FILL_POINT(point, xval, yval) point->x = xval; point->y = yval;
#define CELL(field, point) field[point->y][point->x]

#define ITEM_MASK 0x0003

static FILE *f;

static uint8_t check_and_apply_last_move(uint8_t **old_field,
      uint8_t const **new_field, point_t *move, uint8_t item) {
   point_t size;

   rule_func.get_field_size(&size);
   for (int i = 0; i < size.y; i++) {
      for (int j = 0; j < size.x; j++) {
         if (new_field[i][j] == old_field[i][j])
            continue;
         FILL_POINT(move, j, i);
         old_field[i][j] = item;
         return TRUE;
      }
   }

   return FALSE;
}

static void get_third_cell_in_sequence(point_t const *first,
      point_t const *second, point_t *result) {
   /* first CELL is move(M), second CELL is target(T), need to find third(?)
   * M| |   |M|   | | 
   * ----- ----- -----
   *  |T|   |?|  ?|T|M
   * ----- ----- -----
   *  | |?  |T|   | | 
   * if it is column (first->x==second->x), x = first->x, otherwise x should
   * differ from both, first->x and second->x, as it is row or diagonal
   * so find third coordinate from 00, 01 and 10.
   * Same for y.*/
   result->x = first->x != second->x ? ~(first->x ^ second->x) & ITEM_MASK :
      first->x;
   result->y = first->y != second->y ? ~(first->y ^ second->y) & ITEM_MASK :
      first->y;
}

#ifdef DEBUG_AI
static void store_values(uint8_t const **field) {
   char output[8];
   char *delimeter;
   int i, j;
   point_t size;

   rule_func.get_field_size(&size);
   delimeter = (char *) malloc(size->x * 4 * sizeof(char) + 2);
   for (i = 0; i < size->x * 4 - 1; i++)
      delimeter[i] = '-';
   delimeter[i] = '\n';
   delimeter[i + 1] = '\0';

   for ( int i = 0; i < size->y; i++) {
      for (int j = 0; j < size->x; j++) {
         snprintf(output, 8, "%03d%c", field[i][j],
            j == size->x - 1 ? '\n' : '|');
         fprintf(f, "%s", output);
      }
      if (i != size->y - 1)
         fprintf(f, "%s", delimeter);
   }
   fprintf(f, "\n");

   free(delimeter);
}
#endif

static uint8_t is_point_on_line(point_t const *first, point_t const *second) {
   if (first->x == second->x && first->y == second->y)
      return FALSE;
   else if (first->x == second->x || first->y == second->y)
      return TRUE;
   // main diagonal
   else if (first->x - first->y == 0 && second->x - second->y == 0)
      return TRUE;
   // suppl diagonal
   else if (first->x + first->y == 2 && second->x + second->y == 2)
      return TRUE;
   return FALSE;
}

static uint8_t recalculate_values(uint8_t const **field,
   uint8_t **values, point_t const *move, uint8_t ai_turn) {
   point_t size;

   rule_func.get_field_size(&size);
   CELL(values, move) = VALUE_OCCUPIED_WITH_ITEM;

   for (int i = 0; i < size.y; i++) {
      for (int j = 0; j < size.x; j++) {
         point_t target_cell, third_cell;
         FILL_POINT((&target_cell), j, i);

         if (field[i][j] != EMPTY || !is_point_on_line(move, &target_cell))
            continue;

         get_third_cell_in_sequence(move, &target_cell, &third_cell);
         if (CELL(field, move) == CELL(field, (&third_cell))) {
            CELL(values, (&target_cell)) += ai_turn ? VALUE_2_NATIVE_SIGN :
               VALUE_2_OPPOSITE_SIGN;
         }
         else if (!ai_turn) {
	    if (CELL(values, (&target_cell)) > VALUE_NEW_OPPOSITE_SIGN)
	       CELL(values, (&target_cell)) -= VALUE_NEW_OPPOSITE_SIGN;
	    else
	       CELL(values, (&target_cell)) = VALUE_MINIMUM_CELL_VALUE;
         }
         else {
	    /* if third cell has opponent sign add less */
            CELL(values, (&target_cell)) += CELL(field, (&third_cell)) == EMPTY ?
            VALUE_NEW_NATIVE_SIGN : VALUE_NEW_NATIVE_SIGN_WITH_OPPOSITE_SIGN;
         }
      }
   }
#ifdef DEBUG_AI
   store_values(values);
#endif
}

void init_data(player_ent_t *ctx) {
   point_t size;
   uint8_t **mark_field;
   uint8_t **own_field;
   ai_data_t *ai_ctx = (ai_data_t *) ctx->player_ctx;
   uint8_t item = GET_MY_ITEMS_TYPE(ctx);

#ifdef DEBUG_AI
   f = fopen("log.txt", "w");
#endif
   rule_func.get_field_size(&size);
   mark_field = (uint8_t **) calloc(size.y, sizeof(uint8_t *));
   own_field = (uint8_t **) calloc(size.y, sizeof(uint8_t *));

   for (int i = 0; i < size.y; i++) {
      mark_field[i] = (uint8_t *) calloc(size.x, sizeof(uint8_t));
      own_field[i] = (uint8_t *) calloc(size.x, sizeof(uint8_t));
      for (int j = 0; j < size.x; j++) {
         if (i == 1 && j == 1)
            mark_field[i][j] = GET_CENTER_INIT_VAL(item);
         else if (i == 1 || j == 1)
            mark_field[i][j] = GET_MIDDLE_INIT_VAL(item);
         else
            mark_field[i][j] = GET_DIAG_INIT_VAL(item);
      }
   }
   ai_ctx->marked_fld = mark_field;
   ai_ctx->own_fld = own_field;
}

void make_move(point_t *move, player_ent_t const *ctx) {
   point_t size, op_prev_move;
   uint8_t found_move = FALSE;
   ai_data_t *ai_ctx = (ai_data_t *) ctx->player_ctx;

   rule_func.get_field_size(&size);
   if (check_and_apply_last_move(ai_ctx->own_fld,
      (uint8_t const **)rule_func.get_field(), &op_prev_move,
      GET_OP_ITEMS_TYPE(ctx))) {

      recalculate_values((uint8_t const **) ai_ctx->own_fld, ai_ctx->marked_fld,
         &op_prev_move, FALSE);
   }

   for (int i = 0; i < size.y; i++) {
      for (int j = 0; j < size.x; j++) {
         if (!found_move && ai_ctx->own_fld[i][j] == EMPTY) {
            FILL_POINT(move, j, i);
            found_move = TRUE;
         }
         else if (found_move && CELL(ai_ctx->marked_fld, move) <
            ai_ctx->marked_fld[i][j]) {
            FILL_POINT(move, j, i);
         }
      }
   }

   if (found_move) {
      CELL(ai_ctx->own_fld, move) = GET_MY_ITEMS_TYPE(ctx);
      recalculate_values((uint8_t const **) ai_ctx->own_fld, ai_ctx->marked_fld,
	 move, TRUE);
   }
}

void clear_data(player_ent_t *ctx) {
   point_t size;
   ai_data_t *ai_ctx = (ai_data_t *) ctx->player_ctx;

   rule_func.get_field_size(&size);
   for (int i = 0; i < size.y; i++) {
      free(ai_ctx->marked_fld[i]);
      free(ai_ctx->own_fld[i]);
   }
   free(ai_ctx->marked_fld);
   free(ai_ctx->own_fld);
#ifdef DEBUG_AI   
   fclose(f);
#endif
}
