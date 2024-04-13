
 /**
 * @file main.c
 * @author Maciej Kwiecinski
 * @date 29.05.2022
 * @brief Main file of the project.
 */



/*Allegro 4.2.2 Syntax*/
// https://phoxis.org/2009/02/13/allegro-422/
// Dostêp: 2017-10-29
#include "settings_handler.h"
#include "game_state_handler.h"
#include "click_handler.h"
#include "map_and_drawing_handler.h"


/// Function to clear values of the block's type;
///
/// @param array This is pointer to table to clear
/// @param settings This is pointer to settings structure with one will have informations about how large should be table.
void wyzeruj_tablice(int *array,struct ustawienia *settings)
{
    int i;
    for(i=0; i<(*settings).block_count*(*settings).block_count; i++)
    {
        array[i]=0;
    }
}



/// Function to count how many blocks are Untouched or Flagged.
/// IF there are only blocks that are not a bombs, it will change actual game state to WIN.
/// @param block_array_pointer This is pointer to table with block's values.
/// @param settings settings This is pointer to settings structure with one will have most of the informations like how many blocks are there, how many bombs and stuff like that...
void count_untouched_blocks(int *block_array_pointer,struct ustawienia *settings){
    int i;
    int number = 0;
    for(i=0;i<(*settings).block_count*(*settings).block_count;i++){
        if(block_array_pointer[i]<40||block_array_pointer[i]>300){
            number++;
        }
    }
    if(number==(*settings).bomb_count+1){
        (*settings).win_state = 1;
    }
}





int count=0; //!< Global Variable for void time counter.
/// Function used to count time every second.
void counter()
{
    count++;
}

int main(void)
{

    srand(time(NULL));
    allegro_init();
    install_keyboard();
    install_mouse();
    install_timer();
    install_int(counter, 1000);

      //START_OF_DEFAULT_SETTINGS
            struct ustawienia settings;
                settings.starting_x = 25;
                settings.starting_y = 75;
                settings.block_size = 25;
                settings.block_count = 10;
                settings.bomb_count = 5;
                settings.lose_state = 0;
                settings.win_state = 0;
                settings.is_started = 0;
                settings.custom_game_state = 0;
                settings.is_settings_open = 0;
                settings.background_muted = 0;
                settings.count = 0;
                settings.start_count = 0;
        //END_OF_DEFAULT_SETTINGS

    set_color_depth(8);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1920,1000,0,0))
    {
        allegro_message(allegro_error);
        exit(0);
    }

    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL)) {
      allegro_message("Sound Error: %s", allegro_error);
      return 1;
    }
       show_mouse(screen);

    //START_OF_BITMAP's
            BITMAP *BITMAPS_LIST[39];
            load_bitmaps(BITMAPS_LIST);

        BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);//Buffer czyli zastępczy wirutalny ekran na którym rysowana jest kolejna klatka - zapobiega migotaniu ekranu
        clear(buffer);//Standardowa bitmapa nie jest wyczyszczona i może zawierać zbędny szum, dlatego należy ją wyczyścić0
    //END_OF_BITMAPS

    //START OF MUSIC AND FONT
        int background_music = allocate_voice(load_sample("Outside.wav"));
        SAMPLE *clicked_block_music =  load_sample("clicked_box.wav");
        SAMPLE *explosion = load_sample("explosion.wav");
        voice_set_playmode(background_music, PLAYMODE_LOOP);
        voice_start(background_music);
    FONT *zegar = load_font("zegar.pcx", NULL, NULL);
    //END OF MUSIC AND FONT

    // STANY_BLOKOW - {0-standardowy,1-jedna bomba...8-osiem bomb, >50-odsloniety block, >300-flaga, 15-bomba , 20-bomba zlikwidowana, 25-bomba zdetonowana}
    int *block_array_pointer = (int *)calloc(5000, sizeof(int)); //dynamiczna tablica przechowywująca stan bloku
    wyzeruj_tablice(block_array_pointer,&settings);//poczatkowe zerowanie tablicy - kazdy blok ma stan rowny 0




    losuj_bomby(block_array_pointer,&settings);
    sprawdz_plansze(block_array_pointer,&settings);
    draw_board(buffer,BITMAPS_LIST,&settings,zegar);
     int i=0;int j=0;//Tymczasowe zmienne do petli
        for(i=0;i<settings.block_count;i++){
            for(j=0;j<settings.block_count;j++){
                draw_sprite(buffer,BITMAPS_LIST[9],settings.starting_x+(i*settings.block_size),settings.starting_y+(j*settings.block_size));//Rysowanie grafiki wszystkich blokow do wirtualnego ekranu
            }
        }

        draw_sprite(screen,buffer,0,0);
        //zmienne potrzebne do dzialania programu;
        int x_cords;//zmienne tymczasowe do zapisywania kordynatow bloku, sluza do zamieniania kordynatow myszki na kordynaty startowe bloku (upraszcza zapis)
        int y_cords;
        int element;//trzecia zmienna zapisuje obecnie wcisniety element - index w tablicy, zmienna pomocnicza
        int flags=0;
        settings.start_count = count;
            while(!key[KEY_ESC])//Mozliwosc opuszczenia programu i petli klawiszem ESC
            {
                    textprintf(buffer,zegar,settings.starting_x+settings.block_count*25-47,settings.starting_y-35,RED,"%3d ", settings.time_passed);
                    textprintf(screen,zegar,settings.starting_x+settings.block_count*25-47,settings.starting_y-35,RED,"%3d ", settings.time_passed);
                    settings.count = count;

                if(settings.lose_state == 0 && settings.win_state == 0 || settings.is_settings_open==1 ){
                    draw_sprite(screen, BITMAPS_LIST[36],((settings.block_count*25)/2)+settings.starting_x-10,settings.starting_y-35);
                    settings.time_passed = settings.count-settings.start_count;
                }
                if(settings.lose_state == 1&&settings.is_settings_open == 0 ){
                    draw_sprite(screen, BITMAPS_LIST[34],((settings.block_count*25)/2)+settings.starting_x-10,settings.starting_y-35);
                    textprintf_ex(screen,zegar,((settings.block_count*25)/2)+settings.starting_x-25,settings.starting_y-70,RED,makecol(138,138,138),"LOSSER");
                }
                if(settings.win_state == 1&&settings.is_settings_open == 0 ){
                    draw_sprite(screen, BITMAPS_LIST[35],((settings.block_count*25)/2)+settings.starting_x-10,settings.starting_y-35);
                    textprintf_ex(screen,zegar,((settings.block_count*25)/2)+settings.starting_x-25,settings.starting_y-70,RED,makecol(138,138,138),"WINNER");
                }
                if(key[KEY_PLUS_PAD]&&(settings.lose_state==1||settings.win_state==1||settings.is_started==0)&&settings.custom_game_state==1){
                    settings.block_count+=1;
                    rest(300);
                    restart_game(block_array_pointer,buffer,BITMAPS_LIST[9],&settings);
                    settings.start_count = count;
                    settings.is_settings_open = 0;
                    draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                    clear(screen);
                    draw_sprite(screen,buffer,0,0);
                }
                if(key[KEY_MINUS_PAD]&&(settings.lose_state==1||settings.win_state==1||settings.is_started==0)&&settings.custom_game_state==1){
                    if(settings.block_count>5){
                        settings.block_count-=1;
                        rest(300);
                        restart_game(block_array_pointer,buffer,BITMAPS_LIST[9],&settings);
                        settings.start_count = count;
                        settings.is_settings_open = 0;
                        draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                        clear(screen);
                        draw_sprite(screen,buffer,0,0);
                    }
                }
                if(key[KEY_SLASH_PAD]&&(settings.lose_state==1||settings.win_state==1||settings.is_started==0)&&settings.custom_game_state==1){
                        settings.bomb_count=settings.bomb_count+1;
                        rest(300);
                        restart_game(block_array_pointer,buffer,BITMAPS_LIST[9],&settings);
                        settings.start_count = count;
                        settings.is_settings_open = 0;
                        draw_board(buffer,BITMAPS_LIST,&settings,zegar);

                        draw_sprite(screen,buffer,0,0);
                }
                if(key[KEY_ASTERISK]&&(settings.lose_state==1||settings.win_state==1||settings.is_started==0)&&settings.custom_game_state==1){
                        settings.bomb_count=settings.bomb_count-1;
                        rest(300);
                        restart_game(block_array_pointer,buffer,BITMAPS_LIST[9],&settings);
                        settings.start_count = count;
                        settings.is_settings_open = 0;
                        draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                        clear(screen);
                        draw_sprite(screen,buffer,0,0);
                }



                if(key[KEY_R]&&(settings.lose_state==1||settings.win_state==1)){
                    restart_game(block_array_pointer,buffer,BITMAPS_LIST[9],&settings);
                    settings.start_count = count;
                    draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                    draw_sprite(screen,buffer,0,0);
                }

                if(mouse_b&1){//Wykrycie klikniecia lewym przyciskiem myszki
                    if((settings.lose_state==0&&settings.win_state==0)&&(mouse_x<(settings.starting_x+(settings.block_size*settings.block_count))&&(mouse_x>settings.starting_x-1)&&(mouse_y<settings.starting_y+(settings.block_size*settings.block_count))&&(mouse_y>settings.starting_y-1)&&settings.is_settings_open == 0)){ // IF zwraca prawdę gdy pozycja myszki znajduje się na planszy
                        settings.is_started = 1;
                        element = ((mouse_x-settings.starting_x+settings.block_size)/settings.block_size)+(((mouse_y-settings.starting_y)/settings.block_size)*settings.block_count);
                        if(block_array_pointer[element]<300){
                            x_cords = ((element-1)%settings.block_count)*settings.block_size;
                            y_cords = ((element - (element-1)%settings.block_count)/settings.block_count)*settings.block_size;
                            draw_sprite(buffer,screen,0,0);
                            check_clicked(element,block_array_pointer,buffer,BITMAPS_LIST,&settings,clicked_block_music,explosion);
                            draw_sprite(screen,buffer,0,0);
                            rest(300);
                        }
                        count_untouched_blocks(block_array_pointer, &settings);
                    }
                    if(mouse_x<settings.starting_x+75&&mouse_x>settings.starting_x-1&&mouse_y<25&&mouse_y>=0){
                        settings.lose_state = 1;
                        if(settings.is_settings_open == 0){
                            settings.is_settings_open = 1;
                            rest(300);
                            open_settings(buffer,BITMAPS_LIST[0],BITMAPS_LIST[9],&settings);


                        }else{
                            settings.is_settings_open = 0;
                            restart_game(block_array_pointer,buffer,BITMAPS_LIST[9],&settings);
                            settings.start_count = count;
                            draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                            draw_sprite(screen,buffer,0,0);
                            rest(300);
                        }
                    }
                    if(mouse_x>=settings.block_count*settings.block_size-60+settings.starting_x&&mouse_x<=settings.block_count*settings.block_size+15+settings.starting_x&&mouse_y>=settings.starting_y-75&&mouse_y<=settings.starting_y-50&&(settings.is_started==0||settings.win_state==1||settings.lose_state==1)){
                            restart_game(block_array_pointer,buffer,BITMAPS_LIST[9],&settings);
                            settings.start_count = count;
                            draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                            textprintf(buffer,zegar,settings.starting_x+settings.block_count*25-47,settings.starting_y-35,RED,"%3d ", settings.time_passed);
                            draw_sprite(screen,buffer,0,0);
                            rest(300);
                    }
                    if(settings.is_settings_open==1){
                        if(mouse_x>settings.starting_x+14&&mouse_x<settings.starting_x+14+settings.block_size&&mouse_y>settings.starting_y+59&&mouse_y<settings.starting_y+59+settings.block_size){
                            settings.block_count = 10;
                            settings.bomb_count = 5;
                            settings.custom_game_state = 0;
                            clear(screen);
                            draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                            draw_sprite(screen,buffer,0,0);
                            open_settings(buffer,BITMAPS_LIST[0],BITMAPS_LIST[9],&settings);
                        }
                        if(mouse_x>settings.starting_x+79&&mouse_x<settings.starting_x+79+settings.block_size&&mouse_y>settings.starting_y+59&&mouse_y<settings.starting_y+59+settings.block_size){
                            settings.block_count = 15;
                            settings.bomb_count = 25;
                            settings.custom_game_state = 0;
                            clear(screen);
                            draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                            draw_sprite(screen,buffer,0,0);
                            open_settings(buffer,BITMAPS_LIST[0],BITMAPS_LIST[9],&settings);
                        }
                        if(mouse_x>settings.starting_x+149&&mouse_x<settings.starting_x+149+settings.block_size&&mouse_y>settings.starting_y+59&&mouse_y<settings.starting_y+59+settings.block_size){
                            settings.block_count = 20;
                            settings.bomb_count = 70;
                            settings.custom_game_state = 0;
                            clear(screen);
                            draw_board(buffer,BITMAPS_LIST,&settings,zegar);
                            draw_sprite(screen,buffer,0,0);
                            open_settings(buffer,BITMAPS_LIST[0],BITMAPS_LIST[9],&settings);
                        }
                        if(mouse_x>settings.starting_x+214&&mouse_x<settings.starting_x+214+settings.block_size&&mouse_y>settings.starting_y+59&&mouse_y<settings.starting_y+59+settings.block_size){
                            settings.custom_game_state = 1;
                        }
                        if(mouse_x>settings.starting_x+14&&mouse_x<settings.starting_x+14+settings.block_size&&mouse_y>settings.starting_y+114&&mouse_y<settings.starting_y+114+settings.block_size&&settings.background_muted==0){
                            voice_stop(background_music);
                            settings.background_muted=1;
                            rest(500);
                        }else if(mouse_x>settings.starting_x+14&&mouse_x<settings.starting_x+14+settings.block_size&&mouse_y>settings.starting_y+114&&mouse_y<settings.starting_y+114+settings.block_size&&settings.background_muted==1){
                            voice_start(background_music);
                            settings.background_muted=0;
                            rest(300);
                        }
                    }
                }
                if(mouse_b&2&&(settings.lose_state==0&&settings.win_state==0)&&settings.is_settings_open == 0){
                    if((mouse_x<(settings.starting_x+(settings.block_size*settings.block_count))&&(mouse_x>settings.starting_x-1)&&(mouse_y<settings.starting_y+(settings.block_size*settings.block_count))&&(mouse_y>settings.starting_y-1))){
                        element = ((mouse_x-settings.starting_x+settings.block_size)/settings.block_size)+(((mouse_y-settings.starting_y)/settings.block_size)*settings.block_count);
                        x_cords = ((element-1)%settings.block_count)*settings.block_size;x_cords=x_cords+25;
                        y_cords = ((element - (element-1)%settings.block_count)/settings.block_count)*settings.block_size;y_cords=y_cords+75;
                        if(block_array_pointer[element]<50 && block_array_pointer[element]!=25&&block_array_pointer[element]!=20){
                            draw_sprite(screen,BITMAPS_LIST[10],x_cords,y_cords);
                            draw_sprite(buffer,BITMAPS_LIST[10],x_cords,y_cords);
                            block_array_pointer[element]=block_array_pointer[element]+300;
                            flags++;
                        }else{
                            if(block_array_pointer[element]>299){
                                draw_sprite(screen,BITMAPS_LIST[9],x_cords,y_cords);
                                draw_sprite(buffer,BITMAPS_LIST[9],x_cords,y_cords);
                                block_array_pointer[element]=block_array_pointer[element]-300;
                                flags--;
                            }
                        }
                    rest(500);
                    }
                }


            }

   //START OF CLEARING MEMORY
        free(block_array_pointer);
        block_array_pointer = NULL;
        for(i=0;i<11;i++){
            destroy_bitmap(BITMAPS_LIST[i]);
        }
        destroy_bitmap(BITMAPS_LIST[15]);
        destroy_bitmap(BITMAPS_LIST[20]);
        for(i=25;i<39;i++){
            destroy_bitmap(BITMAPS_LIST[i]);
        }
        destroy_bitmap(buffer);
   //END OF CLEARING MEMORY
    allegro_exit();
    return 0;
}
END_OF_MAIN();






