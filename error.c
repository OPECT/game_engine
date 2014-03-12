#include "error.h"
#include <stdio.h>

char err_msg[MAX_OUTPUT_BUF_LEN];
uint8_t error = FALSE;

void set_error(char *msg, uint8_t len) {
   error = TRUE;
   snprintf(err_msg, len + 1 < MAX_OUTPUT_BUF_LEN ? len + 1 :
      MAX_OUTPUT_BUF_LEN, "%s", msg);
}

void clear_error() {
   error = FALSE;
}

uint8_t is_error() {
   return error;
}

char *get_error() {
   return err_msg;
}