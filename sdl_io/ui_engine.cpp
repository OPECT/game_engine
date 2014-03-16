#include "ui_engine.h"

UI_engine *UI_engine::instanse = NULL;
const SDL_Color UI_engine::textColor = { 0, 0, 0 };

#ifdef WINDOWS
   const string UI_engine::res_folder = "res\\";
#else
   const string UI_engine::res_folder = "res/";
#endif

UI_engine *UI_engine::get_ui_instanse(string name) {
   if (UI_engine::instanse)
      return UI_engine::instanse;

   try {
      UI_engine::instanse = new UI_engine(name);
   }
   catch (UI_engine *e) {
      delete e;
      close_sdl();
      return NULL;
   }

   return instanse;
}

void UI_engine::delete_ui_instanse() {
   if (UI_engine::instanse)
      delete UI_engine::instanse;
}

void UI_engine::close_sdl() {
   Mix_CloseAudio();
   TTF_Quit();
   SDL_Quit();   
}

UI_engine::UI_engine(string name) {
   if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
      throw new UI_engine_err("SDL init failed\n");

   screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

   if (screen == NULL)
      throw new UI_engine_err("SDL video mode failed\n");

   if(TTF_Init() == -1)
      throw new UI_engine_err("SDL font init failed\n");

   if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
      throw new UI_engine_err("SDL audio init failed");

   SDL_WM_SetCaption(name.c_str(), NULL);
   font_size = 82;
}

void UI_engine::clear_items() {
   if (!items.empty()) {
      for (vector<SDL_Surface *>::iterator it = items.begin(); it != items.end(); it++)
         SDL_FreeSurface(*it);
   }
   items.clear();
}

void UI_engine::clean_up_data() {
   clear_items();
   SDL_FreeSurface(background);
   SDL_FreeSurface(horiz_line);
   SDL_FreeSurface(vert_line);
   SDL_FreeSurface(cross);
   SDL_FreeSurface(nought);
   TTF_CloseFont(font);
}

SDL_Surface *UI_engine::load_image(std::string filename) {
   SDL_Surface* loadedImage = NULL;
   SDL_Surface* optimizedImage = NULL;

   loadedImage = IMG_Load((res_folder + filename).c_str());
   if (loadedImage == NULL)
      return NULL;

   optimizedImage = SDL_DisplayFormat(loadedImage);
   SDL_FreeSurface(loadedImage);
   if (optimizedImage == NULL)
      return NULL;

   Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0xFF, 0xFF);
   SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);   
   return optimizedImage;
}

void UI_engine::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect *clip) {
   SDL_Rect offset;

   offset.x = x;
   offset.y = y;
   SDL_BlitSurface(source, clip, destination, &offset);
}

int8_t UI_engine::get_item_num(int32_t x, int32_t y) {
   uint8_t item_height = font_size + 10;
   uint16_t menu_off = (SCREEN_HEIGHT - menu_length * item_height) / 2;
   int8_t item_id = (y - menu_off) / item_height;

   if (y < menu_off || item_id >= menu_length)
      return -1;
   if (x < (SCREEN_WIDTH - items[item_id]->w) / 2 ||
      x > (SCREEN_WIDTH + items[item_id]->w) / 2) {
      return -1;
   }
   return item_id;
}

bool UI_engine::get_figure_idx(int32_t x, int32_t y, point_t *res) {
   uint8_t init_hor_offset = 80, init_vert_offset = 30;
   
   if (x < init_hor_offset || y < init_vert_offset)
      return FALSE;

   res->x = (x - init_hor_offset) / figure_width;
   res->y = (y - init_vert_offset) / figure_height;
   return TRUE;
}

UI_engine::~UI_engine() {
   clean_up_data();
   close_sdl();
}

bool UI_engine::basic_loads() {
   background = load_image("background.jpg");
   if (background == NULL)
      return false;

   font = TTF_OpenFont((res_folder + "Scrobbly.ttf").c_str(), font_size);
   if (font == NULL)
      return false;    

   horiz_line = load_image("horizontal.png");
   vert_line = load_image("vertical.png");
   cross = load_image("X.png");
   nought = load_image("O.png");

   figure_width = cross->w + (SCREEN_WIDTH - 3 * cross->w - 80) / 3;
   figure_height = cross->h + (SCREEN_HEIGHT - 3 * cross->h - 30) / 3;
   return true;
}

void UI_engine::show_menu(vector<string> &list) {
   uint8_t idx = 0;
   menu_length = list.size();
   uint8_t vert_offset = font_size + 10;
   uint16_t init_ver_offset = (SCREEN_HEIGHT - menu_length * vert_offset) / 2;

   clear_items();
   apply_surface(0, 0, background, screen, NULL);
   for (vector<string>::iterator it = list.begin(); it != list.end(); it++, idx++) {
      items.push_back(TTF_RenderText_Solid(font, (*it).c_str(), textColor));
      if (items[idx] == NULL)
         throw new UI_engine_err("menu item error\n");

      apply_surface((SCREEN_WIDTH - items[idx]->w) / 2, init_ver_offset + vert_offset * idx, items[idx], screen, NULL);
   }
   if (SDL_Flip(screen) == -1)
      throw new UI_engine_err("show menu error\n");
}

void UI_engine::show_field(uint8_t **field, point_t const *size, vector<string> figures) {
   uint8_t init_hor_offset = 80, init_vert_offset = 30;
   SDL_Surface *figure;

   apply_surface(0, 0, background, screen, NULL);

   apply_surface(0, (SCREEN_HEIGHT - horiz_line->h) / 3, horiz_line, screen, NULL);
   apply_surface(0, 2 * (SCREEN_HEIGHT - horiz_line->h) / 3, horiz_line, screen, NULL);
   apply_surface((SCREEN_WIDTH - vert_line->w) / 3, 0, vert_line, screen, NULL);
   apply_surface(2 * (SCREEN_WIDTH - vert_line->w) / 3, 0, vert_line, screen, NULL);

   for (uint8_t i = 0; i < size->y; i++) {
      for (uint8_t j = 0; j < size->x; j++) {
         if (field[i][j] == 1 || field[i][j] == 2) {
            figure = field[i][j] == 1 ? cross : nought;
            apply_surface(j * figure_width + init_hor_offset,
               i * figure_height + init_vert_offset, figure, screen, NULL);            
         }
      }
   }

   if (SDL_Flip(screen) == -1)
      throw new UI_engine_err("show menu error\n");
}

uint8_t UI_engine::get_menu_input() {
   SDL_Event event;

   while (TRUE) {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT) {
         throw new UI_engine_err("quit");
      }
      else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
         int32_t x, y;
         int8_t item;

         SDL_GetMouseState(&x, &y);
         item = get_item_num(x, y);
         if (item > -1)
            return item;
      }
   }
   return 0;
}

bool UI_engine::get_game_input(point_t *input) {
   SDL_Event event;

   while (TRUE) {
      SDL_PollEvent(&event);
      if (event.type == SDL_QUIT) {
         throw new UI_engine_err("quit");
      }
      else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
         return FALSE;
      }
      else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
         if (get_figure_idx(event.button.x, event.button.y, input))
            return TRUE;
      }      
   }
   return FALSE;
}