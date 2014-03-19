#ifndef __UI_ENGINE_H__
#define __UI_ENGINE_H__

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <vector>

extern "C" {
   #include "types.h"
}

using namespace std;

class UI_engine {
private:
   static const int32_t SCREEN_WIDTH = 1024;
   static const int32_t SCREEN_HEIGHT = 768;
   static const int32_t SCREEN_BPP = 32;

   static const SDL_Color textColor;

   static const string res_folder;

   static UI_engine *instanse;

   uint8_t menu_length;
   uint8_t font_size;

   uint32_t figure_width;
   uint32_t figure_height;

   SDL_Surface *screen;
   SDL_Surface *background;
   SDL_Surface *horiz_line;
   SDL_Surface *vert_line;
   SDL_Surface *main_diag_line;
   SDL_Surface *supl_diag_line;
   SDL_Surface *cross;
   SDL_Surface *nought;

   vector<SDL_Surface *> items;

   TTF_Font *font;

   UI_engine(string name);

   static void close_sdl();

   void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);
   SDL_Surface *apply_font(string text, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip);
   SDL_Surface *load_image(string filename);
   void clean_up_data();
   void clear_items();
   int8_t get_item_num(int32_t x, int32_t y);
   bool get_figure_idx(int32_t x, int32_t y, point_t *res);

public:
   static UI_engine* get_ui_instanse(string name);
   static void delete_ui_instanse();

   ~UI_engine();
   bool basic_loads();
   void show_menu(vector<string> &list);
   void show_field(uint8_t **field, point_t const *size, vector<string> figures);
   void show_result(uint8_t state, player_ent_t const *player, winning_data_t *);
   uint8_t get_menu_input();
   bool get_game_input(point_t *input);
};

class UI_engine_err {
private:
   string message;
public:
   UI_engine_err(string msg) : message(msg) { }
   string get_message() { return message; }
};

#endif