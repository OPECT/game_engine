CLEAN_SUBDIR = $(patsubst %,%_clean,$(SUBDIRS))
INC_DIR = inc
CPPC = g++
CC = gcc -std=gnu99
CFLAGS = -I$(INC_DIR) -g
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

OBJ = game.o menu_engine.o callbacks.o global_settings.o error.o
SUBDIRS = ttt_rule ai
SUBDIRS += sdl_io

game_engine: $(OBJ) $(SUBDIRS)
	 $(CPPC) $(CFLAGS) -o game_engine $(OBJ) $(foreach file,$(SUBDIRS),$(subst $(file),$(file)/$(file).o,$(file))) $(LIBS)

$(OBJ): %.o: %.c
	 $(CC) -c $(CFLAGS) $< -o $@

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	 $(MAKE) -C $@

clean: $(CLEAN_SUBDIR)
	 rm -rf *.o
	 rm -rf game_engine

.PHONY: $(CLEAN_SUBDIR)
$(CLEAN_SUBDIR):
	rm -rf $(subst _clean,/*.o,$@)
