
#ifndef MAP_AND_DRAWING_HANDLER_H_INCLUDED
#define MAP_AND_DRAWING_HANDLER_H_INCLUDED
#include "allegro.h"
#include "settings_handler.h"


/// Function used to "random" draw coordinates of the bombs and change value of that block.
/// This function is activated on every start/restart of the game.
/// @param array This is pointer to table with blocks values.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void sprawdz_plansze(int *tablica,struct ustawienia *settings);


/// Function used to reveal every block on the board.
/// This function will check value of every block and depends on it draw the correct BITMAP.
/// It will be activated on lose state of the game.
/// @param block_array_pointer This is pointer to to table with block's values.
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param BITMAPS_LIST This is pointer to table with all the bitmaps used for drawing.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void odslon_wszystko(int *block_array_pointer,BITMAP *buffer,BITMAP *BITMAPS_LIST[],struct ustawienia *settings);

/// Function used to draw the board itself.
/// This function will draw every single block needed.
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param BITMAPS_LIST This is pointer to table with all the bitmaps used for drawing.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
/// @param zegar This is pointer to FONT data type used for drawing actual time.
void draw_board(BITMAP *buffer,BITMAP *BITMAPS_LIST[],struct ustawienia *settings,FONT *zegar);


/// Function used to load every needed BITMAP to table of BITMAPS
/// @param BITMAPS_LIST This is pointer to table with all the bitmaps.
void load_bitmaps(BITMAP *BITMAPS_LIST[]);

#endif // MAP_AND_DRAWING_HANDLER_H_INCLUDED
