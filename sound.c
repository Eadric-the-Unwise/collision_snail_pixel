#include <gb/gb.h>
#include "sound.h"
#include "hUGEdriver.h"

//{channel #, resume music delay,     reg, reg, reg, reg, reg,};
const unsigned char SFX_0[] = {0, 20, 0x00, 0x80, 0xB1, 0x82, 0x80};
const unsigned char SFX_1[] = {3, 1, 0x1D, 0xD1, 0x17, 0x80};
const unsigned char SFX_2[] = {3, 1, 0x04, 0x52, 0x20, 0x80};
const unsigned char SFX_3[] = {0, 14, 0x1E, 0x01, 0xF1, 0xEB, 0x87};
const unsigned char SFX_4[] = {0, 70, 0x17, 0x01, 0xF1, 0x23, 0x87};
const unsigned char SFX_5[] = {0, 10, 0x44, 0x81, 0xF3, 0x73, 0x86}; //pick up key
const unsigned char SFX_6[] = {0, 20, 0x00, 0x80, 0xB1, 0x82, 80};	 //bump into door
const unsigned char SFX_7[] = {3, 1, 0x00, 0xC2, 0x80, 0x80};		 //door breaking open

unsigned char Sound_ChannelResumeDelay[4] = {0, 0, 0, 0};

void sfx_update(void)
{
	unsigned char i = 0;
	while (i < 4)
	{
		switch (Sound_ChannelResumeDelay[i])
		{
		case 1:
			hUGE_mute_channel(i, UNMUTE);
			break;
		case 0:
			break;
		default:
			Sound_ChannelResumeDelay[i]--;
		}
		i++;
	}
}

void sfx_play(unsigned char *sfx_id)
{
	unsigned char chan = sfx_id[0];
	hUGE_mute_channel(chan, MUTE);
	Sound_ChannelResumeDelay[chan] = sfx_id[1];
	switch (chan)
	{
	case 0:
	{
		NR10_REG = sfx_id[2];
		NR11_REG = sfx_id[3];
		NR12_REG = sfx_id[4];
		NR13_REG = sfx_id[5];
		NR14_REG = sfx_id[6];
		break;
	}
	case 1:
	{
		NR21_REG = sfx_id[2];
		NR22_REG = sfx_id[3];
		NR23_REG = sfx_id[4];
		NR24_REG = sfx_id[5];
		break;
	}
	case 2:
	{
		NR30_REG = sfx_id[2];
		NR31_REG = sfx_id[3];
		NR32_REG = sfx_id[4];
		NR33_REG = sfx_id[5];
		NR34_REG = sfx_id[6];
		break;
	}
	case 3:
	{
		NR41_REG = sfx_id[2];
		NR42_REG = sfx_id[3];
		NR43_REG = sfx_id[4];
		NR44_REG = sfx_id[5];
		break;
	}
	default:
		break;
	}
	NR50_REG = 0x77U;
	NR51_REG = 0xFFU;
	NR52_REG = 0x80U;
}