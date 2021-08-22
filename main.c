//sound.h is the SFX page.
#include <gb/gb.h>
#include <stdio.h>

#include "hUGEDriver.h"
#include "snailSprite.c"
#include "sound.h"
#include "wallMap1tile.c"
#include "wallSprites1tile.c"

extern const hUGESong_t songmario;  //there is a var called twitchsong somewhere
extern const hUGESong_t songwinner;
extern const hUGESong_t songbaseball;
unsigned char current_sfx = 0;
unsigned char joystate;

const char blankmap[1] = {0x00};
UINT8 playerlocation[2];
UBYTE debug = 0;  //equals 1 by default (but not for tut?)
UBYTE gamerunning;
UINT8 currentspriteindex = 0;

UINT8 sprite_data[] = {
    0x3C, 0x3C, 0x42, 0x7E, 0x99, 0xFF, 0xA9, 0xFF, 0x89, 0xFF, 0x89, 0xFF, 0x42, 0x7E, 0x3C, 0x3C,
    0x3C, 0x3C, 0x42, 0x7E, 0xB9, 0xFF, 0x89, 0xFF, 0x91, 0xFF, 0xB9, 0xFF, 0x42, 0x7E, 0x3C, 0x3C,
    0x3C, 0x3C, 0x42, 0x7E, 0x99, 0xFF, 0x89, 0xFF, 0x99, 0xFF, 0x89, 0xFF, 0x5A, 0x7E, 0x3C, 0x3C,
    0x3C, 0x3C, 0x42, 0x7E, 0xA9, 0xFF, 0xA9, 0xFF, 0xB9, 0xFF, 0x89, 0xFF, 0x42, 0x7E, 0x3C, 0x3C

};

//defining a function
void performantdelay(UINT8 numloops) {
    UINT8 i;
    for (i = 0; i < numloops; i++) {
        wait_vbl_done();  //vbl_done = every time the screen is finished writing
    }
}

UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery);        //forward declare
void animatesprite(UINT8 spriteindex, INT8 movex, INT8 movey);  //forward declare
void movecheck() {
    if (joypad() & J_LEFT) {
        if (canplayermove(playerlocation[0] - 8, playerlocation[1])) {
            playerlocation[0] -= 8;
            animatesprite(0, -8, 0);
        }
    }

    else if (joypad() & J_RIGHT) {
        if (canplayermove(playerlocation[0] + 8, playerlocation[1])) {
            playerlocation[0] += 8;
            animatesprite(0, +8, 0);
            // move_sprite(0, playerlocation[0], playerlocation[1]);
        }
    } else if (joypad() & J_UP) {
        if (canplayermove(playerlocation[0], playerlocation[1] - 8)) {
            playerlocation[1] -= 8;
            animatesprite(0, 0, -8);
            // move_sprite(0, playerlocation[0], playerlocation[1]);
        }
    } else if (joypad() & J_DOWN) {
        if (canplayermove(playerlocation[0], playerlocation[1] + 8)) {
            playerlocation[1] += 8;
            animatesprite(0, 0, +8);
            // move_sprite(0, playerlocation[0], playerlocation[1]);
        }
        delay(20);
    }
}

UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery) {
    UINT16 indexTLx, indexTLy, tileindexTL;
    UBYTE result;

    indexTLx = (newplayerx - 8) / 8;
    indexTLy = (newplayery - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;

    result = WallMap1tile[tileindexTL] == blankmap[0];

    return result;
}

void animatesprite(UINT8 spriteindex, INT8 movex, INT8 movey) {
    while (movex != 0) {
        scroll_sprite(spriteindex, movex < 0 ? -1 : 1, 0);
        movex += (movex < 0 ? 1 : -1);
        wait_vbl_done();
    }
    while (movey != 0) {
        scroll_sprite(spriteindex, 0, movey < 0 ? -1 : 1);
        movey += movey < 0 ? 1 : -1;
        wait_vbl_done();
    }
}
UINT16 PosX, PosY;

void main() {
    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    __critical {
        hUGE_init(&songbaseball);
        add_VBL(hUGE_dosound);
    }

    set_bkg_data(0, 5, WallSprites1tile);
    set_bkg_tiles(0, 0, 20, 18, WallMap1tile);  //0,0 is the start, 20, 18 is the end result (aka full screen size, no scrolling)

    set_sprite_data(0, 4, sprite_data);
    set_sprite_tile(0, 0);  //defines the tiles numbers

    playerlocation[0] = 48;
    playerlocation[1] = 40;

    move_sprite(0, playerlocation[0], playerlocation[1]);

    while (gamerunning) {
        performantdelay(1);
        PosX = PosY = 64;

        joystate = joypad();
        // movecheck(); //will movecheck for every button press from here rather than below
        switch (joystate) {
            case J_A:

                movecheck();
                waitpadup();
                break;
            case J_B:

                movecheck();
                waitpadup();
                break;
            case J_UP:

                movecheck();
                // waitpadup();
                performantdelay(2);
                break;
            case J_DOWN:

                movecheck();
                break;
            case J_LEFT:

                movecheck();
                // waitpadup();
                performantdelay(2);
                break;
            case J_RIGHT:

                movecheck();
                // waitpadup();
                performantdelay(2);
                break;
            case J_START:

                movecheck();
                waitpadup();
                break;
            case J_SELECT:

                movecheck();
                waitpadup();
                break;
            default:
                break;
        }

        wait_vbl_done();
    }
}
