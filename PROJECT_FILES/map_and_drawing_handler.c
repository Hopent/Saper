/**
 * @file map_and_drawing_handler.c
 * @author Maciej Kwiecinski
 * @date 29.05.2022
 * @brief Map and drawing handler file.
 */
#include "map_and_drawing_handler.h"


/// Function used to check value of every block in the array.
/// This function will mostly check and save how many bombs are in every block neighborhood.
/// @param array This is pointer to array with values to check.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void sprawdz_plansze(int *array,struct ustawienia *settings){
    int index;
    for(index=1;index<((*settings).block_count*(*settings).block_count)+1;index++){
      if(array[index]==0){
        int liczba_min=0;
            //lewy_gorny
            if((index-(*settings).block_count-1)>0&&(index%(*settings).block_count)!=1){
                if(array[index-(*settings).block_count-1]==15){
                    liczba_min++;
                }
            }
            //srodek_gorny
            if((index-(*settings).block_count)>0){
                if(array[index-(*settings).block_count]==15){
                    liczba_min++;
                }

            }
            //prawo_gorny
            if(((index-(*settings).block_count+1)>0)&&((index%(*settings).block_count)!=0)){
                if(array[index-(*settings).block_count+1]==15){
                    liczba_min++;
                }
            }
            //lewo_srodek
            if((index-1)>0&&(index%(*settings).block_count)!=1){
                if(array[index-1]==15){
                    liczba_min++;
                }
            }
            //prawo_srodek
            if((index%(*settings).block_count)!=0){
               if(array[index+1]==15){
                    liczba_min++;
                }
            }
            //lewo_dolny
            if(((index+(*settings).block_count-1)<((*settings).block_count*(*settings).block_count)+1)&&(index%(*settings).block_count)!=1){
                if(array[index+(*settings).block_count-1]==15){
                    liczba_min++;
                }
            }
            //srodek_dolny
            if((index+(*settings).block_count)<((*settings).block_count*(*settings).block_count)+1){
                if(array[index+(*settings).block_count]==15){
                    liczba_min++;
                }
            }
            //prawo_dolny
            if(((index+(*settings).block_count+1)<((*settings).block_count*(*settings).block_count)+1)&&((index+(*settings).block_count)%(*settings).block_count!=0)){
                if(array[index+(*settings).block_count+1]==15){
                    liczba_min++;
                }
            }

            array[index]=liczba_min;//zapisuje ilosc min[bomb] w obrębie jednej kradki
        }
    }

}

/// Function used to reveal every block on the board.
/// This function will check value of every block and depends on it draw the correct BITMAP.
/// It will be activated on lose state of the game.
/// @param block_array_pointer This is pointer to to table with block's values.
/// @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
/// @param BITMAPS_LIST This is pointer to table with all the bitmaps used for drawing.
/// @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void odslon_wszystko(int *block_array_pointer,BITMAP *buffer,BITMAP *BITMAPS_LIST[],struct ustawienia *settings){
    int i=0;int j=0;int element=0;//Tymczasowe zmienne do petli
    for(i=0;i<(*settings).block_count;i++){
        for(j=0;j<(*settings).block_count;j++){
            element++;
            if(block_array_pointer[element]>250){
                    block_array_pointer[element]=block_array_pointer[element]-300;
                    if(block_array_pointer[element]==15){
                        block_array_pointer[element]=20;
                    }
            }
            if(block_array_pointer[element]<50){draw_sprite(buffer,BITMAPS_LIST[block_array_pointer[element]],(*settings).starting_x+(j*(*settings).block_size),(*settings).starting_y+(i*(*settings).block_size));};

        }
    }
    (*settings).lose_state=1;
}


/**@brief
* Function used to draw the board itself.
* This function will draw every single block needed.
* @param buffer This is pointer to BITMAP we use as a buffer for screen visualizing.
* @param BITMAPS_LIST This is pointer to table with all the bitmaps used for drawing.
* @param settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
* @param zegar This is pointer to FONT data type used for drawing actual time.
*
*/
void draw_board(BITMAP *buffer,BITMAP *BITMAPS_LIST[],struct ustawienia *settings,FONT *zegar){
    draw_sprite(buffer,BITMAPS_LIST[30],(*settings).starting_x-25,(*settings).starting_y-75);//Rog lewy gora
    draw_sprite(buffer,BITMAPS_LIST[31],(*settings).starting_x+((*settings).block_size*(*settings).block_count),(*settings).starting_y-75);//Rog prawy gora
    draw_sprite(buffer,BITMAPS_LIST[27],(*settings).starting_x-25,(*settings).starting_y+((*settings).block_size*(*settings).block_count));//Rog lewy dol
    draw_sprite(buffer,BITMAPS_LIST[28],(*settings).starting_x+((*settings).block_size*(*settings).block_count),(*settings).starting_y+((*settings).block_size*(*settings).block_count));//Rog prawy gora
    int i=0;int z=0;//Tymczasowe zmienne do petli
        for(z=0;z<(*settings).block_count+2;z++){
            draw_sprite(buffer,BITMAPS_LIST[32],(*settings).starting_x-25,(*settings).starting_y+((*settings).block_size*z) - 50);//Ramka lewo
            draw_sprite(buffer,BITMAPS_LIST[33],(*settings).starting_x+((*settings).block_size*(*settings).block_count),(*settings).starting_y+((*settings).block_size*z)-50);//Ramka prawo
            }
        for(i=0;i<(*settings).block_count;i++){
            draw_sprite(buffer,BITMAPS_LIST[26],(*settings).starting_x+((*settings).block_size*i),(*settings).starting_y-75);//Ramka gora
            draw_sprite(buffer,BITMAPS_LIST[26],(*settings).starting_x+((*settings).block_size*i),(*settings).starting_y+((*settings).block_size*(*settings).block_count));//Ramka dol
            draw_sprite(buffer,BITMAPS_LIST[0],(*settings).starting_x+((*settings).block_size*i),(*settings).starting_y-50);//Wypelnienie
            draw_sprite(buffer,BITMAPS_LIST[29],(*settings).starting_x+((*settings).block_size*i),(*settings).starting_y-25);//Wypelnienie
    }
    draw_sprite(buffer,BITMAPS_LIST[37],(*settings).starting_x,(*settings).starting_y-75);
    draw_sprite(buffer,BITMAPS_LIST[38],(*settings).block_count*(*settings).block_size-60+(*settings).starting_x,(*settings).starting_y-75);
    draw_sprite(buffer, BITMAPS_LIST[36],(((*settings).block_count*25)/2)+(*settings).starting_x-10,(*settings).starting_y-35);
    textprintf(buffer,zegar,(*settings).starting_x,(*settings).starting_y-35,RED,"%3d ",(*settings).bomb_count);
}


/// Function used to load every needed BITMAP to table of BITMAPS
/// @param BITMAPS_LIST This is pointer to table with all the bitmaps.
void load_bitmaps(BITMAP *BITMAPS_LIST[]){
            BITMAPS_LIST[0] = create_bitmap(25,25);
            BITMAPS_LIST[0] = load_bitmap("bitmaps/0_block.bmp",NULL);
            BITMAPS_LIST[1] = create_bitmap(25,25);
            BITMAPS_LIST[1] = load_bitmap("bitmaps/1_block.bmp",NULL);
            BITMAPS_LIST[2] = create_bitmap(25,25);
            BITMAPS_LIST[2] = load_bitmap("bitmaps/2_block.bmp",NULL);
            BITMAPS_LIST[3] = create_bitmap(25,25);
            BITMAPS_LIST[3] = load_bitmap("bitmaps/3_block.bmp",NULL);
            BITMAPS_LIST[4] = create_bitmap(25,25);
            BITMAPS_LIST[4] = load_bitmap("bitmaps/4_block.bmp",NULL);
            BITMAPS_LIST[5] = create_bitmap(25,25);
            BITMAPS_LIST[5] = load_bitmap("bitmaps/5_block.bmp",NULL);
            BITMAPS_LIST[6] = create_bitmap(25,25);
            BITMAPS_LIST[6] = load_bitmap("bitmaps/6_block.bmp",NULL);
            BITMAPS_LIST[7] = create_bitmap(25,25);
            BITMAPS_LIST[7] = load_bitmap("bitmaps/7_block.bmp",NULL);
            BITMAPS_LIST[8] = create_bitmap(25,25);
            BITMAPS_LIST[8] = load_bitmap("bitmaps/8_block.bmp",NULL);
            BITMAPS_LIST[9] = create_bitmap(25,25);
            BITMAPS_LIST[9] = load_bitmap("bitmaps/standard_block.bmp",NULL);
            BITMAPS_LIST[10] = create_bitmap(25,25);
            BITMAPS_LIST[10] = load_bitmap("bitmaps/flag_block.bmp",NULL);
            BITMAPS_LIST[15] = create_bitmap(25,25);
            BITMAPS_LIST[15] = load_bitmap("bitmaps/bomb_block.bmp",NULL);
            BITMAPS_LIST[20] = create_bitmap(25,25);
            BITMAPS_LIST[20] = load_bitmap("bitmaps/bomb2_block.bmp",NULL);
            BITMAPS_LIST[25] = create_bitmap(25,25);
            BITMAPS_LIST[25] = load_bitmap("bitmaps/bomb3_block.bmp",NULL);
        //END_OF_BLOCK'S_BITMAPS

        //START_OF_GAME_BOARD_BITMAPS
            BITMAPS_LIST[26] = create_bitmap(25,25);
            BITMAPS_LIST[26] = load_bitmap("bitmaps/ramka_dol.bmp",NULL);
            BITMAPS_LIST[27] = create_bitmap(25,25);
            BITMAPS_LIST[27] = load_bitmap("bitmaps/ramka_dollewy.bmp",NULL);
            BITMAPS_LIST[28] = create_bitmap(25,25);
            BITMAPS_LIST[28] = load_bitmap("bitmaps/ramka_dolprawy.bmp",NULL);
            BITMAPS_LIST[29] = create_bitmap(25,25);
            BITMAPS_LIST[29] = load_bitmap("bitmaps/ramka_fill.bmp",NULL);
            BITMAPS_LIST[30] = create_bitmap(25,25);
            BITMAPS_LIST[30] = load_bitmap("bitmaps/ramka_goralewy.bmp",NULL);
            BITMAPS_LIST[31] = create_bitmap(25,25);
            BITMAPS_LIST[31] = load_bitmap("bitmaps/ramka_goraprawy.bmp",NULL);
            BITMAPS_LIST[32] = create_bitmap(25,25);
            BITMAPS_LIST[32] = load_bitmap("bitmaps/ramka_lewy.bmp",NULL);
            BITMAPS_LIST[33] = create_bitmap(25,25);
            BITMAPS_LIST[33] = load_bitmap("bitmaps/ramka_prawy.bmp",NULL);
        //END_OF_GAME_BOARD_BITMAPS

        //START_OF_GAME_STATE_BITMAPS
            BITMAPS_LIST[34] = create_bitmap(25,25);
            BITMAPS_LIST[34] = load_bitmap("bitmaps/face_lose.bmp",NULL);
            BITMAPS_LIST[35] = create_bitmap(25,25);
            BITMAPS_LIST[35] = load_bitmap("bitmaps/face_win.bmp",NULL);
            BITMAPS_LIST[36] = create_bitmap(25,25);
            BITMAPS_LIST[36] = load_bitmap("bitmaps/face0.bmp",NULL);
            BITMAPS_LIST[37] = create_bitmap(75,25);
            BITMAPS_LIST[37] = load_bitmap("bitmaps/settings_icon.bmp",NULL);
            BITMAPS_LIST[38] = create_bitmap(75,25);
            BITMAPS_LIST[38] = load_bitmap("bitmaps/restart_icon.bmp",NULL);
        //END_OF_GAME_STATE_BITMAPS



}
