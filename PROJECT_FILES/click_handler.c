/**
 * @file click_handler.c
 * @author Maciej Kwiecinski
 * @date 29.05.2022
 * @brief Click handler file.
 */
#include "click_handler.h"


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
void check_clicked(int element,int *block_array_pointer,BITMAP *buffer,BITMAP *BITMAPS_LIST[],struct ustawienia *settings,SAMPLE *clicked_block_music,SAMPLE *explosion){
        if(block_array_pointer[element]<300&&(*settings).lose_state==0&&(*settings).win_state==0){
            if(block_array_pointer[element]!=15&&block_array_pointer[element]<50){play_sample(clicked_block_music, 255, 0, 1000, 0);play_sample(clicked_block_music,255,255,1000,0);}
            if(block_array_pointer[element]==15){
                play_sample(explosion,255,0, 1000,0);
                play_sample(explosion,255,255, 1000,0);
                block_array_pointer[element]=25;
                odslon_wszystko(block_array_pointer,buffer,BITMAPS_LIST,settings);
            }
            if(block_array_pointer[element]<10){
                odslon_kwadrat(element,block_array_pointer,buffer,BITMAPS_LIST,settings);
                block_array_pointer[element] = block_array_pointer[element]+50;
                if(block_array_pointer[element]-50==0){
                    //gora
                    if(element>(*settings).block_count){
                         check_clicked(element-(*settings).block_count,block_array_pointer,buffer,BITMAPS_LIST,settings,clicked_block_music,explosion);
                    }
                    //prawo
                    if((element%(*settings).block_count)!=0){
                        check_clicked(element+1,block_array_pointer,buffer,BITMAPS_LIST,settings,clicked_block_music,explosion);
                    }
                    //dol
                    if((element+(*settings).block_count)<((*settings).block_count*(*settings).block_count)){
                            check_clicked(element+(*settings).block_count,block_array_pointer,buffer,BITMAPS_LIST,settings,clicked_block_music,explosion);
                       }
                    //lewo
                    if(element%(*settings).block_count!=1){
                            check_clicked(element-1,block_array_pointer,buffer,BITMAPS_LIST,settings,clicked_block_music,explosion);
                    }
                }
            }
        }
}

/// Function used to draw/reveal a block.
/// It will also calculate coordinates, where should it draw it.
/// @param element This is number of actual checking block.
/// It is needed to check proper element from block_array_pointer array.
/// @param block_array_pointer This is pointer to to table with block's values.
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param BITMAPS_LIST This is pointer to table with all the bitmaps used for drawing.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void odslon_kwadrat(int element,int *block_array_pointer,BITMAP *buffer,BITMAP *BITMAPS_LIST[],struct ustawienia *settings){
            int x = (*settings).starting_x+((element-1)%(*settings).block_count)*(*settings).block_size;
            int y = (*settings).starting_y+((element - (element-1)%(*settings).block_count)/(*settings).block_count)*(*settings).block_size;
            draw_sprite(buffer,BITMAPS_LIST[block_array_pointer[element]],x,y);
}
