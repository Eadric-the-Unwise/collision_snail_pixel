//sound.h is the SFX page.
#include <stdio.h>
#include <gb/gb.h>
#include "wallMap1tile.c"
#include "wallSprites1tile.c"
#include "snailSprite.c"
#include "hUGEDriver.h"
#include "sound.h"

extern const hUGESong_t songmario; //there is a var called twitchsong somewhere
extern const hUGESong_t songwinner;
extern const hUGESong_t songbaseball;
unsigned char current_sfx = 0;
unsigned char joystate;

const char blankmap[1] = {0x00};
UINT8 playerlocation[2];
UBYTE debug = 0;  //equals 1 by default (but not for tut?)
UBYTE haskey = 0; //equals 1 by default (but not for tut?)
UBYTE gamerunning;

//defining a function
void performantdelay(UINT8 numloops)
{
    UINT8 i;
    for (i = 0; i < numloops; i++)
    {
        wait_vbl_done(); //vbl_done = every time the screen is finished writing
    }
}

UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery);       //forward declare
void animatesprite(UINT8 spriteindex, INT8 movex, INT8 movey); //forward declare
void movecheck()
{
    if (joypad() & J_LEFT)
    {
        if (canplayermove(playerlocation[0] - 8, playerlocation[1]))
        {
            playerlocation[0] -= 8;
            animatesprite(0, -8, 0);
        }
    }

    else if (joypad() & J_RIGHT)
    {
        if (canplayermove(playerlocation[0] + 8, playerlocation[1]))
        {
            playerlocation[0] += 8;
            animatesprite(0, +8, 0);
            // move_sprite(0, playerlocation[0], playerlocation[1]);
        }
    }
    else if (joypad() & J_UP)
    {
        if (canplayermove(playerlocation[0], playerlocation[1] - 8))
        {
            playerlocation[1] -= 8;
            animatesprite(0, 0, -8);
            // move_sprite(0, playerlocation[0], playerlocation[1]);
        }
    }
    else if (joypad() & J_DOWN)
    {
        if (canplayermove(playerlocation[0], playerlocation[1] + 8))
        {
            playerlocation[1] += 8;
            animatesprite(0, 0, +8);
            // move_sprite(0, playerlocation[0], playerlocation[1]);
        }
    }
}

UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery)
{
    UINT16 indexTLx, indexTLy, tileindexTL;
    UBYTE result;

    indexTLx = (newplayerx - 8) / 8;
    indexTLy = (newplayery - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;

    if (debug)
    {
        printf("%u %u\n", (UINT16)(newplayerx), (UINT16)(newplayery));
        printf("%u %u %u\n", (UINT16)indexTLx, (UINT16)indexTLy, (UINT16)tileindexTL);
    }

    result = WallMap1tile[tileindexTL] == blankmap[0];

    //   set_bkg_tiles(1,11,1,1, chest);

    if (tileindexTL == 161)
    {
        //collect key
        result = 1; //allows you to walk into the previously inaccessable space
        haskey = 1;
        sfx_play(SFX_5);
        set_bkg_tiles(1, 8, 1, 1, blankmap); //the tile at the key location will blank
    }
    // else if (tileindexTL == 122)
    // {
    //     sfx_play(SFX_6);
    // }
    else if (tileindexTL == 122 && haskey)
    {
        //open door
        sfx_play(SFX_7);
        result = 1;
        set_bkg_tiles(2, 6, 1, 1, blankmap);
    }

    if (tileindexTL == 201)
    {
        //open chest
        sfx_play(SFX_3);
        result = 1;
        set_bkg_tiles(1, 10, 1, 1, blankmap);
    }
    else if (tileindexTL == 240 || tileindexTL == 260)
    {
        //finish game
        gamerunning = 0;

        HIDE_SPRITES;
        printf("\n \n \n \n \n \n \n \n \n      YOU WIN!");
        result = 1;
        __critical
        {
            hUGE_init(&songwinner); //adding add_VBL(hUGE_dosound); twice actually speeds up the audio 2x
        }
    }

    return result;
}

void animatesprite(UINT8 spriteindex, INT8 movex, INT8 movey)
{
    while (movex != 0)
    {
        scroll_sprite(spriteindex, movex < 0 ? -1 : 1, 0);
        movex += (movex < 0 ? 1 : -1);
        wait_vbl_done();
    }
    while (movey != 0)
    {
        scroll_sprite(spriteindex, 0, movey < 0 ? -1 : 1);
        movey += movey < 0 ? 1 : -1;
        wait_vbl_done();
    }
}

void main()
{

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    __critical
    {
        hUGE_init(&songbaseball);
        add_VBL(hUGE_dosound);
    }

    set_bkg_data(0, 5, WallSprites1tile);
    set_bkg_tiles(0, 0, 20, 18, WallMap1tile); //0,0 is the start, 20, 18 is the end result (aka full screen size, no scrolling)

    set_sprite_data(0, 1, SnailSprite); //defines the sprite data
    set_sprite_tile(0, 0);              //defines the tiles numbers

    playerlocation[0] = 16;
    playerlocation[1] = 24;

    move_sprite(0, playerlocation[0], playerlocation[1]);

    while (gamerunning)
    {
        //debugging feature
        //  if(joypad() & J_A){
        //     debug = (debug == 0 ? 1 : 0);
        // }

        performantdelay(6);

        joystate = joypad();
        // movecheck(); //will movecheck for every button press from here rather than below
        switch (joystate)
        {
        case J_A:
            // sfx_play(SFX_0);
            movecheck();
            waitpadup();
            break;
        case J_B:
            // sfx_play(SFX_1);
            movecheck();
            waitpadup();
            break;
        case J_UP:
            sfx_play(SFX_4);
            movecheck();
            // waitpadup();
            performantdelay(2);
            break;
        case J_DOWN:
            sfx_play(SFX_4);
            movecheck();
            // waitpadup();
            performantdelay(2);
            break;
        case J_LEFT:
            sfx_play(SFX_4);
            movecheck();
            // waitpadup();
            performantdelay(2);
            break;
        case J_RIGHT:
            sfx_play(SFX_4);
            movecheck();
            // waitpadup();
            performantdelay(2);
            break;
        case J_START:
            sfx_play(SFX_2);
            movecheck();
            waitpadup();
            break;
        case J_SELECT:
            // sfx_play(SFX_7);
            movecheck();
            waitpadup();
            break;
        default:
            break;
        }
        sfx_update();
        wait_vbl_done();
    }
}
