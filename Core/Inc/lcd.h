/*
 * lcd.h
 *
 *  Created on: 2020. 8. 5.
 *      Author: lilol
 */

#ifndef _LCD_H_
#define _LCD_H_

#define DISP_SEL_CMD_REG			0
#define DISP_SEL_DATA_REG			1

void DispInit(uint8_t maxrows, uint8_t maxcols);
void DispStr(uint8_t row, uint8_t col, char *s);

#endif
