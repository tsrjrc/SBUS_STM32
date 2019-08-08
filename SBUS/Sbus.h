#ifndef __SBUS_H_
#define __SBUS_H_

#include "stm32f10x.h"

#define SBUS_FRAME_SIZE 	25
#define SBUS_RANGE_MIN		200.0f
#define SBUS_RANGE_MAX		1800.0f
#define SBUS_TARGET_MIN		1000.0f
#define SBUS_TARGET_MAX		2000.0f	
#define SBUS_SCALE_FACTOR	((SBUS_TARGET_MAX - SBUS_TARGET_MIN)/(SBUS_RANGE_MAX-SBUS_RANGE_MIN))//0.625f
#define SBUS_SCALE_OFFSET (int)(SBUS_TARGET_MIN - (SBUS_SCALE_FACTOR * SBUS_RANGE_MIN + 0.5f))	//874.5f

struct sbus_bit_pick {
	unsigned char byte;
	unsigned char rshift;
	unsigned char mask;
	unsigned char lshift;
};

static const struct sbus_bit_pick sbus_decoder[16][3] = {
	/*  0 */{ { 0, 0, 0xff, 0 },{ 1, 0, 0x07, 8 },{ 0, 0, 0x00,  0 } },
	/*  1 */{ { 1, 3, 0x1f, 0 },{ 2, 0, 0x3f, 5 },{ 0, 0, 0x00,  0 } },
	/*  2 */{ { 2, 6, 0x03, 0 },{ 3, 0, 0xff, 2 },{ 4, 0, 0x01, 10 } },
	/*  3 */{ { 4, 1, 0x7f, 0 },{ 5, 0, 0x0f, 7 },{ 0, 0, 0x00,  0 } },
	/*  4 */{ { 5, 4, 0x0f, 0 },{ 6, 0, 0x7f, 4 },{ 0, 0, 0x00,  0 } },
	/*  5 */{ { 6, 7, 0x01, 0 },{ 7, 0, 0xff, 1 },{ 8, 0, 0x03,  9 } },
	/*  6 */{ { 8, 2, 0x3f, 0 },{ 9, 0, 0x1f, 6 },{ 0, 0, 0x00,  0 } },
	/*  7 */{ { 9, 5, 0x07, 0 },{ 10, 0, 0xff, 3 },{ 0, 0, 0x00,  0 } },
	/*  8 */{ { 11, 0, 0xff, 0 },{ 12, 0, 0x07, 8 },{ 0, 0, 0x00,  0 } },
	/*  9 */{ { 12, 3, 0x1f, 0 },{ 13, 0, 0x3f, 5 },{ 0, 0, 0x00,  0 } },
	/* 10 */{ { 13, 6, 0x03, 0 },{ 14, 0, 0xff, 2 },{ 15, 0, 0x01, 10 } },
	/* 11 */{ { 15, 1, 0x7f, 0 },{ 16, 0, 0x0f, 7 },{ 0, 0, 0x00,  0 } },
	/* 12 */{ { 16, 4, 0x0f, 0 },{ 17, 0, 0x7f, 4 },{ 0, 0, 0x00,  0 } },
	/* 13 */{ { 17, 7, 0x01, 0 },{ 18, 0, 0xff, 1 },{ 19, 0, 0x03,  9 } },
	/* 14 */{ { 19, 2, 0x3f, 0 },{ 20, 0, 0x1f, 6 },{ 0, 0, 0x00,  0 } },
	/* 15 */{ { 20, 5, 0x07, 0 },{ 21, 0, 0xff, 3 },{ 0, 0, 0x00,  0 } }
};



void sbus_out(uint16_t num_values);
void sbus_decode(unsigned char *frame);
void sbus_output(void);

#endif
