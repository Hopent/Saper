
#ifndef CLICK_HANDLER_H_INCLUDED
#define CLICK_HANDLER_H_INCLUDED
#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include <unistd.h>
#include "settings_handler.h"

/// Function used to check already clicked block
/// This function will check block number that we will delivery as parameter and depends on the value end the game or reveal it.
/// This function will also play a sound after click and reveal everything if the clicked block is actually a bomb.
/// @param element This is number of actual checking block.
/// It is needed to check proper element from block_array_pointer array.
/// @param block_array_pointer This is pointer to to table with block's values.
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param BITMAPS_LIST This is pointer to table with all the bitmaps used for drawing.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
/// @param clicked_block_music This is pointer to SAMPLE data type, with sound of the clicked block.
/// @param explosion This is pointer to SAMPLE data type, with sound of the explosion.
/// @see odslon_wszystko() odslon_kwadrat() check_clicked()
void check_clicked(int element, int *block_array_pointer, BITMAP *buffer, BITMAP *BITMAPS_LIST[], struct ustawienia *settings, SAMPLE *clicked_block_music, SAMPLE *explosion);
/// Function used to draw/reveal a block.
/// It will also calculate coordinates, where should it draw it.
/// @param element This is number of actual checking block.
/// It is needed to check proper element from block_array_pointer array.
/// @param block_array_pointer This is pointer to to table with block's values.
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param BITMAPS_LIST This is pointer to table with all the bitmaps used for drawing.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void odslon_kwadrat(int element,int *block_array_pointer,BITMAP *buffer,BITMAP *BITMAPS_LIST[],struct ustawienia *settings);


#endif // CLICK_HANDLER_H_INCLUDED
