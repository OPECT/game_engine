#ifndef __OUTPUT_CODE_H__
#define __OUTPUT_CODE_H__

#include "enum_macro.h"

BEGIN_ENUM(output_code)
ENUM(EXIT, "exit"),
ENUM(BACK, "back"),
ENUM(NOT_READY, "this section is not ready yet"),
ENUM(AI, "computer"),
ENUM(NETWORK, "network"),
ENUM(HOT_SEAT, "hot seat"),
ENUM(DEFAULT_PLAYER_NAME1, "player1"),
ENUM(DEFAULT_PLAYER_NAME2, "player2"),
ENUM(DEFAULT_AI_NAME, "GeniusTheGreatest"),
ENUM(ENTER_PLAYER_NAME, "enter player's name"),
ENUM(START_GAME, "start game"),
ENUM(SWITCH_START_GAME, "switch players and start game"),
ENUM(END_GAME, "End of the game. %s\nPress any key to continue"),
ENUM(DRAW_MSG, "This is draw."),
ENUM(PLAYER_WINS, "The winner is %s."),
ENUM(BACK_2_MAIN, "back to main"),
ENUM(NONE, "")
END_ENUM(output_code)

#endif