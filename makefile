SUBDIRS = console_io ttt_game
INC_DIR = inc
CC = gcc
CFLAGS = -I$(INC_DIR) -std=gnu99 -g
OBJ = game.o menu_engine.o callbacks.o global_settings.o

game_engine: $(OBJ) $(SUBDIRS)
	 $(CC) $(CFLAGS) -o game_engine $(OBJ) console_io/console_io.o ttt_game/ttt_rule.o

$(OBJ): %.o: %.c
	 $(CC) -c $(CFLAGS) $< -o $@

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	 $(MAKE) -C $@

clean: clean_console_io clean_ttt_game
	 rm -rf *.o
	 rm -rf game_engine

clean_console_io:
	 rm -rf console_io/*.o

clean_ttt_game:
	 rm -rf ttt_game/*.o
