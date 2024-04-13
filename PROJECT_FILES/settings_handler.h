
#ifndef SETTINGS_HANDLER_H_INCLUDED
#define SETTINGS_HANDLER_H_INCLUDED
#include "allegro.h"

#define RED makecol(255,0,0)
#define GREEN makecol(0,255,0)
#define BLUE makecol(0,0,255)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define BLACK makecol(0,0,0)
/**
 * @brief Structure for settings parameters of the game.
 *
 *
 */
struct ustawienia{
    int starting_x; /**< Starting x position on the screen */
    int starting_y; /**< Starting y position on the screen */
    int block_size; /**< Size of blocks */
    int block_count; /**< Count of blocks */
    int bomb_count; /**< Bomb count */
    int lose_state; /**< Lose state of the game */
    int win_state; /**< Win state of the game */
    int is_started; /**< Value for indentificate if the game is already started. */
    int custom_game_state; /**< Custom game state */
    int is_settings_open; /**< Value for identificate if the settings are open */
    int background_muted; /**< Value for music mute */
    int start_count; /**< Value for start counting the time of actual game */
    int count; /**< Value that is increment every second*/
    int time_passed; /**< Value that is equal for count - start_count */
}settings;


/// Function used to handle settings window.[Mostly draw it]
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param zero_block This is pointer to one of the BITMAP element, needed to draw the board.
/// @param standard_block This is pointer to one of the BITMAP element, needed to draw the board.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void open_settings(BITMAP *buffer, BITMAP *zero_block,BITMAP *standard_block,struct ustawienia *settings);



#endif // SETTINGS_HANDLER_H_INCLUDED
