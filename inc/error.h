#include "types.h"

void set_error(const char *msg, uint8_t len);
void clear_error();
uint8_t is_error();
char *get_error();