#include <gb/gb.h>
#include "sound.h"
#include "hUGEDriver.h"

extern void song[];
unsigned char current_sfx=0;
unsigned char joystate;

void main(void)
{
	__critical
	{
		NR52_REG = 0x80;
		NR51_REG = 0xFF;
		NR50_REG = 0x77;
		hUGE_init(song);
		add_VBL(hUGE_dosound);
	}
	while(1)
	{
		joystate = joypad();
		switch (joystate)
		{
			case J_A: 	sfx_play(SFX_0); waitpadup(); break;
			case J_B: 	sfx_play(SFX_1); waitpadup(); break;
			case J_UP: 	sfx_play(SFX_2); waitpadup(); break;
			case J_DOWN: 	sfx_play(SFX_3); waitpadup(); break;
			case J_LEFT:	sfx_play(SFX_4); waitpadup(); break;
			case J_RIGHT: 	sfx_play(SFX_5); waitpadup(); break;
			case J_START: 	sfx_play(SFX_6); waitpadup(); break;
			case J_SELECT: 	sfx_play(SFX_7); waitpadup(); break;
			default: break;
		}
		sfx_update();
		wait_vbl_done();
	}
}