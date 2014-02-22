#ifndef __TIC_TAC_TOE_MENU_H__
#define __TIC_TAC_TOE_MENU_H__

#include "menu_macros.h"
#include "menu_engine.h"
#include <stdio.h>

START_MENU(ai_menu, NULL)
TEXT_ITEM(NOT_READY),
SIMPLE_ITEM(BACK)
END_MENU(ai_menu, 2, 1)

START_MENU(network_menu, NULL)
TEXT_ITEM(NOT_READY),
SIMPLE_ITEM(BACK)
END_MENU(network_menu, 2, 1)

START_MENU(hot_seat_menu, set_hot_seat_mode)
EDITABLE_ITEM(DEFAULT_PLAYER_NAME1, apply_player_name, get_player1_name,
   (void *) PLAYER1),
EDITABLE_ITEM(DEFAULT_PLAYER_NAME2, apply_player_name, get_player2_name,
   (void *) PLAYER2),
ACTION_ITEM(START_GAME, simple_start_game, NULL),
SIMPLE_ITEM(BACK)
END_MENU(hot_seat_menu, 4, 4)

START_MENU(main_menu, NULL)
ACTION_ITEM(AI, show_simple_menu, &ai_menu),
ACTION_ITEM(NETWORK, show_simple_menu, &network_menu),
ACTION_ITEM(HOT_SEAT, show_simple_menu, &hot_seat_menu),
SIMPLE_ITEM(EXIT)
END_MENU(main_menu, 4, 4)

START_MENU(finish_menu, NULL)
ACTION_ITEM(START_GAME, simple_start_game, NULL),
ACTION_ITEM(SWITCH_START_GAME, switch_and_start_game, NULL),
ACTION_ITEM(BACK_2_MAIN, show_simple_menu, &main_menu),
SIMPLE_ITEM(EXIT)
END_MENU(finish_menu, 4, 4)

#endif