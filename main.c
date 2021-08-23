#include <gb/gb.h>
#include <stdio.h>

#include "./res/bkg_map.h"
#include "./res/bkg_tiles.h"
#include "./res/collision_map.h"
#include "./res/collision_tiles.h"
#include "./res/collisions.h"
#include "./res/wall_map.h"
#include "./res/wall_tiles.h"
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

//forward declare
UBYTE canplayermoveTL(UINT8 newplayerx, UINT8 newplayery);
UBYTE canplayermoveTR(UINT8 newplayerx, UINT8 newplayery);
UBYTE canplayermoveBL(UINT8 newplayerx, UINT8 newplayery);
UBYTE canplayermoveBR(UINT8 newplayerx, UINT8 newplayery);
void updateplayer();
UBYTE canplayermoveTL(UINT8 newplayerx, UINT8 newplayery) {
    UINT16 indexTLx, indexTLy, tileindexTL;
    UBYTE result;

    indexTLx = (newplayerx - 8) / 8;
    indexTLy = (newplayery - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;

    result = COLLISION_MAP[tileindexTL] == blankmap[0];

    return result;
}
//top right pixel
UBYTE canplayermoveTR(UINT8 newplayerx, UINT8 newplayery) {
    UINT16 indexTRx, indexTRy, tileindexTR;
    UBYTE result;

    indexTRx = (newplayerx) / 8;
    indexTRy = (newplayery - 16) / 8;
    tileindexTR = 20 * indexTRy + indexTRx;

    result = COLLISION_MAP[tileindexTR] == blankmap[0];

    return result;
}
//bottom right pixel
UBYTE canplayermoveBR(UINT8 newplayerx, UINT8 newplayery) {
    UINT16 indexBRx, indexBRy, tileindexBR;
    UBYTE result;

    indexBRx = (newplayerx) / 8;
    indexBRy = (newplayery) / 8;
    tileindexBR = 20 * indexBRy + indexBRx;

    result = COLLISION_MAP[tileindexBR] == blankmap[0];

    return result;
}
//bottom left pixel
UBYTE canplayermoveBL(UINT8 newplayerx, UINT8 newplayery) {
    UINT16 indexBLx, indexBLy, tileindexBL;
    UBYTE result;

    indexBLx = (newplayerx - 8) / 8;
    indexBLy = (newplayery) / 8;
    tileindexBL = 20 * indexBLy + indexBLx;

    result = COLLISION_MAP[tileindexBL] == blankmap[0];

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
    BGP_REG = 0x1B;

    set_bkg_data(0, WALL_TILE_COUNT, WALL_TILE_DATA);
    set_bkg_tiles(0, 0, WALL_MAP_WIDTH, WALL_MAP_HEIGHT, WALL_MAP_DATA);  //0,0 is the start, 20, 18 is the end result (aka full screen size, no scrolling)

    set_sprite_data(0, 4, sprite_data);
    set_sprite_tile(0, 0);  //defines the tiles numbers

    PosX = PosY = 48;
    SpdX = SpdY = 0;

    move_sprite(0, PosX, PosY);

    joypad_init(1, &joypads);

    while (gamerunning) {
        // poll joypads
        joypad_ex(&joypads);

        // game object
        if (joypads.joy0 & J_UP) {
            if ((canplayermoveTL(PosX, PosY - 1)) && (canplayermoveTR(PosX, PosY - 1))) {
                SpdY -= 2;
                if (SpdY < -4) SpdY = -4;
                updateplayer();
            }
            // else SpdY = 4;
        } else if (joypads.joy0 & J_DOWN) {
            if (canplayermoveTL(PosX, PosY + 8)) {
                SpdY += 2;
                if (SpdY > 4) SpdY = 4;
                updateplayer();
            }
            // else SpdY = -4;
        }
        if (joypads.joy0 & J_LEFT) {
            if (canplayermoveTL(PosX - 1, PosY)) {
                SpdX -= 2;
                if (SpdX < -4) SpdX = -4;
                updateplayer();
            }

        } else if (joypads.joy0 & J_RIGHT) {
            if ((canplayermoveTR(PosX + 1, PosY)) && (canplayermoveBR(PosX, PosY + 1))) {
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
