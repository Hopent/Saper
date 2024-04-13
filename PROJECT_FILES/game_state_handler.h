
#ifndef GAME_STATE_HANDLER_H_INCLUDED
#define GAME_STATE_HANDLER_H_INCLUDED
#include "allegro.h"
#include "settings_handler.h"

/// Function used to "random" draw coordinates of the bombs and change value of that block.
/// This function is activated on every start/restart of the game.
/// @param array This is pointer to table with blocks values.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void losuj_bomby(int *array,struct ustawienia *settings);


/// Function used to restart the game.
/// This function will change mostly everything to start new game.
/// @param block_array_pointer This is pointer to to table with block's values.
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param standard_block This is pointer to standard block, because after restart we will use only normal blocks to draw the board of the game.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
/// @see wyzeruj_tablice() losuj_bomby() sprawdz_plansze()
void restart_game(int *block_array_pointer,BITMAP *buffer,BITMAP *standard_block,struct ustawienia *settings);

#endif // GAME_STATE_HANDLER_H_INCLUDED
