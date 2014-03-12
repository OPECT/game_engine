#include "ttt_rule.h"
#include "enum_macro.h"
#include "ttt_str_code.h"
#include "error.h"
#include <stdio.h>
#include <string.h>

#define WIDTH_SIZE 3
#define HEIGHT_SIZE 3

#define CELL(field, point) field[point->y][point->x]

uint8_t **main_field;

static uint8_t check_horizontal(uint8_t line) {
   return main_field[line][0] == main_field[line][1] &&
      main_field[line][0] == main_field[line][2];
}

static uint8_t check_vertical(uint8_t col) {
   return main_field[0][col] == main_field[1][col] &&
      main_field[0][col] == main_field[2][col];
}

static uint8_t check_diagonal(short main_diag) {
   return main_field[0][main_diag ? 0 : 2] == main_field[1][1] &&
      main_field[0][main_diag ? 0 : 2] == main_field[2][main_diag ? 2 : 0];
}

void get_field_size(point_t *size) {
   size->x = WIDTH_SIZE;
   size->y = HEIGHT_SIZE;
}

uint8_t **get_field() {
   return main_field;
}

void fill_field(uint8_t **field) {
   for (int i = 0; i < HEIGHT_SIZE; i++) {
      for (int j = 0; j < WIDTH_SIZE; j++)
         field[i][j] = EMPTY;
   }
   main_field = field;
}

uint8_t check_and_apply_move(uint8_t turn, void *data) {
   point_t *move = (point_t *) data;

   if (move->x >= WIDTH_SIZE || move->y >= HEIGHT_SIZE) {
      return FALSE;
   }
   if (CELL(main_field, move) != EMPTY) {
      return FALSE;
   }

   CELL(main_field, move) = (turn == PLAYER1 ? CROSS : NOUGHT);
   return TRUE;
}

uint8_t check_end_conditions() {
   uint8_t is_empty = FALSE;

   for (int i = 0; i < HEIGHT_SIZE; i++) {
      for ( int j = 0; j < WIDTH_SIZE; j++) {
         switch (main_field[i][j]) {
         case EMPTY:
            is_empty = TRUE;
            break;
         case CROSS:
         case NOUGHT:
            if ((i == 0 && check_vertical(j)) || (j == 0 &&
               check_horizontal(i)) || (i == 0 && (j == 0 || j == 2)
               && check_diagonal((j == 0)))) {
               return main_field[i][j] == CROSS ? GS_PLAYER1_VICTORY :
                  GS_PLAYER2_VICTORY;
            }
            break;
         default: set_error("rule error: wrong sign",
            strlen("rule error: wrong sign"));
         }
      }
   }
   return is_empty ? GS_ONGOING : GS_DRAW;
}
