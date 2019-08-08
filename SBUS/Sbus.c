#include "Sbus.h"
#include "bsp_usart1.h"
#include "string.h"

//不懂的朋友可以看我的博客，有一片sbus的内容

uint16_t values[16]={0};


void sbus_out(uint16_t num_values)
{
	int i=0;
	uint16_t value=0;
	uint8_t byteindex = 1;
	uint8_t offset = 0;
	uint8_t oframe[25] = { 0 };
	memset(oframe,0,25);
	oframe[0]=0x0f;
	oframe[24]=0x00;

	for (i = 0; (i < num_values) && (i < 16); ++i)
	{
		value = (unsigned short)(((values[i] - SBUS_SCALE_OFFSET) / SBUS_SCALE_FACTOR) + .5f);
		if (value > 0x07ff)
		{
			value = 0x07ff;
		}

		while (offset >= 8)
		{
			++byteindex;
			offset -= 8;
		}
		
		oframe[byteindex] |= (value << (offset)) & 0xff;
		oframe[byteindex + 1] |= (value >> (8 - offset)) & 0xff;
		oframe[byteindex + 2] |= (value >> (16 - offset)) & 0xff;
		offset += 11;
	}
	
	for (i=0;i<25;i++)
	{
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
		USART_SendData(USART1, (uint16_t)oframe[i]);     
	}
}


void sbus_decode(unsigned char *frame)
{
	unsigned int pick=0,channel=0,value1=0,piece=0;
	const struct sbus_bit_pick *decode;
	for (channel = 0; channel < 16; channel++) 
	{
		value1 = 0;

		for (pick = 0; pick < 3; pick++) 
		{
			decode = &sbus_decoder[channel][pick];

			if (decode->mask != 0) 
			{
				piece = frame[1 + decode->byte];
				piece >>= decode->rshift;
				piece &= decode->mask;
				piece <<= decode->lshift;

				piece &= 0x07ff;

				value1 |= piece;
			}
		}
		values[channel] = (uint16_t)(value1 * SBUS_SCALE_FACTOR + .5f) + SBUS_SCALE_OFFSET;
		if(channel==1)
		{
			values[channel]=3029-values[channel];
		}
	}
}

