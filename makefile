SUBDIRS = console_io ttt_rule
CLEAN_SUBDIR = $(patsubst %,%_clean,$(SUBDIRS))
INC_DIR = inc
CC = gcc
CFLAGS = -I$(INC_DIR) -std=gnu99 -g
OBJ = game.o menu_engine.o callbacks.o global_settings.o

game_engine: $(OBJ) $(SUBDIRS)
	 $(CC) $(CFLAGS) -o game_engine $(OBJ) console_io/console_io.o ttt_rule/ttt_rule.o

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
