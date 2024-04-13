/**
 * @file game_state_handler.c
 * @author Maciej Kwiecinski
 * @date 29.05.2022
 * @brief Map and drawing handler file.
 */
#include "game_state_handler.h"




/// Function used to "random" draw coordinates of the bombs and change value of that block.
/// This function is activated on every start/restart of the game.
/// @param array This is pointer to table with blocks values.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void losuj_bomby(int *array,struct ustawienia *settings){
    int i;
    int liczba=0;
    for(i=(*settings).bomb_count;i>0;i--){
            liczba =1+rand()%((*settings).block_count*(*settings).block_count);
        if(array[liczba]!=15){
            array[liczba]=15;
        }else{
            i++;
        }
    }
}



/// Function used to restart the game.
/// This function will change mostly everything to start new game.
/// @param block_array_pointer This is pointer to to table with block's values.
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param standard_block This is pointer to standard block, because after restart we will use only normal blocks to draw the board of the game.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
/// @see wyzeruj_tablice() losuj_bomby() sprawdz_plansze()
void restart_game(int *block_array_pointer,BITMAP *buffer,BITMAP *standard_block,struct ustawienia *settings){
    (*settings).is_started = 0;
    (*settings).win_state = 0;
    (*settings).lose_state = 0;
    (*settings).start_count = (*settings).count;
    (*settings).block_count+=1;
    clear(buffer);
    wyzeruj_tablice(block_array_pointer,settings);//poczatkowe zerowanie tablicy - kazdy blok ma stan rowny 0
    (*settings).block_count-=1;
    losuj_bomby(block_array_pointer,settings);
    sprawdz_plansze(block_array_pointer,settings);
     int i=0;int j=0;//Tymczasowe zmienne do petli
        for(i=0;i<(*settings).block_count;i++){
            for(j=0;j<(*settings).block_count;j++){
                draw_sprite(buffer,standard_block,(*settings).starting_x+(i*(*settings).block_size),(*settings).starting_y+(j*(*settings).block_size));//Rysowanie grafiki wszystkich blokow do wirtualnego ekranu
            }
        }
        draw_sprite(screen,buffer,0,0);
}
