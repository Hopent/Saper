/*Allegro 4.2.2 Syntax*/
// https://phoxis.org/2009/02/13/allegro-422/
// Dostêp: 2017-10-29
#include <stdio.h>
#include <allegro.h>

#define RED makecol(255,0,0)
#define GREEN makecol(0,255,0)
#define BLUE makecol(0,0,255)
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define BLACK makecol(0,0,0)



int main(void)
{


allegro_init();
install_keyboard();
install_mouse();
install_timer();


//allegro_message("This is the first allegro program (Press OK)");
set_color_depth(8);
if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0))
{
    allegro_message(allegro_error);
    exit(0);
}
//BITMAP *standard_block;
BITMAP *standard_block = create_bitmap(25,25);
standard_block = load_bitmap("standard_block.bmp",NULL);

//textprintf(screen,font,10,10,WHITE,"Screen Resolution %dx%d",SCREEN_W,SCREEN_H);
/*rect(screen,20,20,300,130,GREEN);
circle(screen,mouse_x,mouse_y/2,50,WHITE);
putpixel(screen,SCREEN_W/2,SCREEN_H/2,RED);
line(screen,300,300,200,200,GREEN);
triangle(screen,500,500,500,550,300,550,BLUE); */

show_mouse(screen);
int i=0;int j=0;
int starting_x=200;
int starting_y=150;
int block_size=25;
int block_count=15;
for(i=0;i<block_count;i++){
    for(j=0;j<block_count;j++){
        rect(screen,starting_x+(i*block_size),starting_y+(j*block_size),(starting_x+block_size)+(i*block_size),(starting_y+block_size)+(j*block_size),GREEN);
        draw_sprite(screen,standard_block,starting_x+(i*block_size),starting_y+(j*block_size));
    }
}



while(!key[KEY_ESC])
{


if(mouse_b&1){
    if((mouse_x<(starting_x+(block_size*block_count))&&(mouse_x>starting_x-1)&&(mouse_y<starting_y+(block_size*block_count))&&(mouse_y>starting_y-1))){ // IF zwraca prawdę gdy pozycja myszki znajduje się na planszy
        textprintf(screen,font,500,130,GREEN,"Numer wcisnietego bloku :%3d",((mouse_x-starting_x+block_size)/block_size)+(((mouse_y-starting_y)/block_size)*block_count)); // wyswietla napis obecnie klikniętego bloku
    }
}



//Diagnostyczne rzeczy :
textprintf(screen,font,500,10,WHITE,"Screen Resolution %dx%d",SCREEN_W,SCREEN_H);
textprintf(screen,font,500,30,RED,"Mouse Pos x:y=%3d:%3d",mouse_x,mouse_y);
textprintf(screen,font,500,50,BLUE,"Mouse Scroll Pos: %3d",mouse_z);
textprintf(screen,font,500,70,GREEN,"Mouse Left Button Pressed:%3s",((mouse_b&1)?"Yes":"No"));
textprintf(screen,font,500,90,GREEN,"Mouse Right Button Pressed:%3s",((mouse_b&2)?"Yes":"No"));
textprintf(screen,font,500,110,GREEN,"Mouse Middle Button Pressed:%3s",((mouse_b&4)?"Yes":"No"));
textprintf(screen,font,650,160,GREEN,"Raw Mouse :%d",mouse_b);
}



allegro_exit();
return 0;
}
END_OF_MAIN();







