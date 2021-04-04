#include <stdio.h>
#include <gb/gb.h>
#include "wallMap1tile.c"
#include "wallSprites1tile.c"
#include "snailSprite.c"

UINT8 playerlocation[2];

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done(); //vbl_done = every time the screen is finished writing
    }     
}

// UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery){

// }

void main(){

    set_bkg_data(0, 4, WallSprites1tile);
    set_bkg_tiles(0, 0, 20, 18, WallMap1tile); //0,0 is the start, 20, 18 is the end result (aka full screen size, no scrolling)

    set_sprite_data(0, 1, SnailSprite); //defines the sprite data
    set_sprite_tile(0, 0); //defines the tiles numbers

    playerlocation[0] = 16;
    playerlocation[1] = 24;

    move_sprite(0, playerlocation[0], playerlocation[1]);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while(1){
        if(joypad() & J_LEFT){
            playerlocation[0] -=8;
            move_sprite(0, playerlocation[0], playerlocation[1]);
        }
        else if(joypad() & J_RIGHT){
            playerlocation[0] +=8;
            move_sprite(0, playerlocation[0], playerlocation[1]);
        }
        else if(joypad() & J_UP){
            playerlocation[1] -=8;
            move_sprite(0, playerlocation[0], playerlocation[1]);
        }
         else if(joypad() & J_DOWN){
            playerlocation[1] +=8;
            move_sprite(0, playerlocation[0], playerlocation[1]);
        }
        performantdelay(6);
    }

}
