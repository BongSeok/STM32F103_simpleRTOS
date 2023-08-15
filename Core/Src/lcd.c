/*
 * lcd.c
 *
 *  Created on: 2020. 8. 5.
 *      Author: lilol
 */

#include "main.h"
#include <stdbool.h>
#include "lcd.h"

#define DISP_CMD_CLS		0x01
#define DISP_CMD_FNCT		0x3B
#define DISP_CMD_MODE		0x06
#define DISP_CMD_ON_OFF		0x0C

static uint8_t DispMaxCols;
static uint8_t DispMaxRows;

static void DispSel(uint8_t sel);
static void DispDataWr(uint8_t data);
static void DispCursorSet(uint8_t row, uint8_t col);

static void DispSel(uint8_t sel)
{
	if( sel == DISP_SEL_CMD_REG ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
	}
}

static void DispDataWr(uint8_t data)
{
	if( data & 0x80 ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
	}
	if( data & 0x40 ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	if( data & 0x20 ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	}
	if( data & 0x10 ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	}
	if( data & 0x08 ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	}
	if( data & 0x04 ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	}
	if( data & 0x02 ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	}
	if( data & 0x01 ){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	}

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
	//HAL_Delay(1);
}

void DispInit(uint8_t maxrows, uint8_t maxcols)
{
	DispMaxRows = maxrows;
	DispMaxCols = maxcols;

	DispSel(DISP_SEL_CMD_REG);
	HAL_Delay(50);
	DispDataWr(DISP_CMD_FNCT);
	HAL_Delay(2);
	DispDataWr(DISP_CMD_FNCT);
	HAL_Delay(2);
	DispDataWr(DISP_CMD_FNCT);
	HAL_Delay(2);
	DispDataWr(DISP_CMD_FNCT);
	HAL_Delay(2);

	DispDataWr(DISP_CMD_ON_OFF);
	DispDataWr(DISP_CMD_MODE);
	DispDataWr(DISP_CMD_CLS);
	HAL_Delay(2);
}

static void DispCursorSet(uint8_t row, uint8_t col)
{
	DispSel(DISP_SEL_CMD_REG);
	switch( row ){
	case 0:
		DispDataWr(0x80 + col);
		break;
	case 1:
		DispDataWr(0xC0 + col);
		break;
	}
}

void DispStr(uint8_t row, uint8_t col, char *s)
{
	uint8_t i;

	if( row<DispMaxRows && col<DispMaxCols ){
		DispCursorSet(row, col);
		HAL_Delay(1);
		DispSel(DISP_SEL_DATA_REG);
		i = col;
		while( i<DispMaxCols && *s != '\0' ){
			DispDataWr(*s++);
			HAL_Delay(1);
			i++;
		}
	}
}
