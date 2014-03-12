#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
extern "C" {
#include "error.h"
#include "interface_io.h"
}

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

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *screen = NULL;

char const * get_code_str(uint8_t code) {
   return output_code_table[code];   
}

uint8_t init_io() {
   if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
      return false;    

   screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

   if (screen == NULL)
      return false;    

   if(TTF_Init() == -1)
      return false;

   if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
      return false;
       

   SDL_WM_SetCaption("Event test", NULL);
   return true;   
}
void clear_io() {
   Mix_CloseAudio();
   TTF_Quit();
   SDL_Quit();   
}

void show_menu(menu_list_t const *list) {}
void show_field(uint8_t **field, point_t const *size) {}
void show_result(uint8_t state, player_ent_t const *player) {}

uint8_t get_menu_input() {
   uint8_t result = 0;
   SDL_Event event;

   while (TRUE) {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT)
         set_error((char *)"quit", strlen("quit"));
         break;
   }
   return result;
}

void get_string_input(menu_item_t const *menu, char *input) {}
int get_player_input(point_t *input, player_ent_t const *player) {return 0;}

void show_error(char *msg) {
   if (is_error())
      printf("ERROR:%s\n", get_error());
}