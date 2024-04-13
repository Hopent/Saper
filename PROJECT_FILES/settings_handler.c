/**
 * @file settings_handler.c
 * @author Maciej Kwiecinski
 * @date 29.05.2022
 * @brief Settings handler file
 */
#include "settings_handler.h"



/// Function used to handle settings window.[Mostly draw it]
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param zero_block This is pointer to one of the BITMAP element, needed to draw the board.
/// @param standard_block This is pointer to one of the BITMAP element, needed to draw the board.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void open_settings(BITMAP *buffer, BITMAP *zero_block,BITMAP *standard_block,struct ustawienia *settings){
    int i,j;
    clear(buffer);
       for(i=0;i<(*settings).block_count;i++){
            for(j=0;j<(*settings).block_count;j++){
                draw_sprite(buffer,zero_block,j*(*settings).block_size,i*(*settings).block_size);
            }
        }
        draw_sprite(screen,buffer,(*settings).starting_x,(*settings).starting_y);
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+30,GREEN,makecol(138,138,138),"Poziom trudnosci :");
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+45,GREEN,makecol(138,138,138),"(Latwy , Sredni, Trudny, Custom)");
        draw_sprite(screen,standard_block,(*settings).starting_x+15,(*settings).starting_y+60);
        draw_sprite(screen,standard_block,(*settings).starting_x+80,(*settings).starting_y+60);
        draw_sprite(screen,standard_block,(*settings).starting_x+150,(*settings).starting_y+60);
        draw_sprite(screen,standard_block,(*settings).starting_x+215,(*settings).starting_y+60);
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+95,GREEN,makecol(138,138,138),"Mute background music : ");
        draw_sprite(screen,standard_block,(*settings).starting_x+15,(*settings).starting_y+115);
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+150,GREEN,makecol(138,138,138),"KEYS : ");
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+165,GREEN,makecol(138,138,138),"R - Restart Game ");
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+180,BLUE,makecol(138,138,138),"For Custom game only :  ");
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+195,BLUE,makecol(138,138,138),"NUMPAD + : ADD COLUMN ");
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+210,BLUE,makecol(138,138,138),"NUMPAD - : DELETE COLUMN ");
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+225,BLUE,makecol(138,138,138),"NUMPAD * : ADD BOMB ");
        textprintf_ex(screen,font,(*settings).starting_x,(*settings).starting_y+240,BLUE,makecol(138,138,138),"NUMPAD / : SUBSTRAT BOMB ");
}
