/*
 * frames.h
 *
 *  Created on: Mar 19, 2023
 *      Author: marko
 */

#ifndef INC_FRAMES_H_
#define INC_FRAMES_H_

#include "main.h"

#define SLEEP_TIMEOUT 5000
#define NUM_FRAMES 4

typedef struct frame{ uint16_t p[12]; } frame;
typedef struct cframe{ uint8_t p[12][3]; } cframe;

cframe sconvert(frame*);
void sdraw(cframe*, SPI_HandleTypeDef*);
void strobe(void);
void enterSleep(void);
void exitSleep(void);

extern cframe scFrame;
extern uint32_t lClick;
extern uint8_t aSleep;
extern uint8_t cFrame;

#endif /* INC_FRAMES_H_ */
