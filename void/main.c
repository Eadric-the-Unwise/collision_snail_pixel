//sound.h is the SFX page.
#include <gb/gb.h>
#include <stdio.h>

#include "wallMap1tile.c"
#include "wallSprites1tile.c"

unsigned char joystate;

const char blankmap[1] = {0x00};

UBYTE gamerunning;
UINT16 PosX, PosY;
INT16 SpdX, SpdY;
joypads_t joypads;

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

UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery);  //forward declare
void updateplayer();
UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery) {
    UINT16 indexTLx, indexTLy, tileindexTL;
    UBYTE result;

    indexTLx = (newplayerx - 8) / 8;
    indexTLy = (newplayery - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;

    result = WallMap1tile[tileindexTL] == blankmap[0];

    return result;
}
void updateplayer() {
    PosX += SpdX, PosY += SpdY;

    // translate to pixels and move sprite
    move_sprite(0, PosX, PosY);
}
void main() {
    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    set_bkg_data(0, 5, WallSprites1tile);
    set_bkg_tiles(0, 0, 20, 18, WallMap1tile);  //0,0 is the start, 20, 18 is the end result (aka full screen size, no scrolling)

    set_sprite_data(0, 4, sprite_data);
    set_sprite_tile(0, 0);  //defines the tiles numbers

    PosX = PosY = 48;
    SpdX = SpdY = 0;

    move_sprite(0, PosX, PosY);

    joypad_init(1, &joypads);

    while (gamerunning) {
        performantdelay(1);

        // poll joypads
        joypad_ex(&joypads);

        // game object
        if (joypads.joy0 & J_UP) {
            if (canplayermove(PosX, PosY - 3)) {
                SpdY -= 2;
                if (SpdY < -4) SpdY = -4;
                updateplayer();
            }
            // else SpdY = 4;
        } else if (joypads.joy0 & J_DOWN) {
            if (canplayermove(PosX, PosY + 10)) {
                SpdY += 2;
                if (SpdY > 4) SpdY = 4;
                updateplayer();
            }
            // else SpdY = -4;
        }
        if (joypads.joy0 & J_LEFT) {
            if (canplayermove(PosX - 3, PosY)) {
                SpdX -= 2;
                if (SpdX < -4) SpdX = -4;
                updateplayer();
            }

        } else if (joypads.joy0 & J_RIGHT) {
            if (canplayermove(PosX + 10, PosY)) {
                SpdX += 2;
                if (SpdX > 4) SpdX = 4;
                updateplayer();
            }
        }

        // decelerate
        if (SpdY >= 0) {
            if (SpdY) SpdY--;
        } else
            SpdY++;
        if (SpdX >= 0) {
            if (SpdX) SpdX--;
        } else
            SpdX++;
        wait_vbl_done();
    }
}
