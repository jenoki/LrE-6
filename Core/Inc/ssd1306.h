/**
 * @file	ssd1306.h
 * @brief	SSD1306 OLED Library Header.
 * @author	totally modified by jenoki
 * @copyright	MIT License
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__

#include <stddef.h>
#include <stdbool.h>
#include <_ansi.h>

_BEGIN_STD_C

#include "stm32f0xx_hal.h"
#include "ssd1306_fonts.h"

//! @def LrE-6 I2C hardware
#define SSD1306_I2C_PORT		hi2c1
#define SSD1306_I2C_ADDR        (0x3C << 1)
extern	I2C_HandleTypeDef		SSD1306_I2C_PORT;
#define SSD1306_PWRUP_WAIT		10	//(ms)

#define SSD1306_CMD				0x00
#define	SSD1306_DATA			0x40

#define SSD1306_CONTINUE    	0x80
#define SSD1306_TAIL        	0
#define SSD1306_WRITE       	0
#define	SSD1306_TRANSMIT_TO		250

//! @def SSD1306 Commands
#define	CMD_SET_ADDRESS_MD		0x20
#define CMD_SET_PAGE_RANGE		0x22
#define CMD_SET_START_LINE		0x40
#define CMD_SET_CONTRAST		0x81
#define CMD_SET_CHARGE_PUMP		0x8D
#define CMD_NON_MIRROR			0xA0
#define CMD_MIRROR				0xA1
#define	CMD_REFLECT_FBUF		0xA4
#define	CMD_ALL_DOTS_ON			0xA5
#define	CMD_NON_INVERT			0xA6
#define	CMD_INVERT				0xA7
#define CMD_SET_MPX_RATIO		0xA8
#define CMD_DISPLAY_OFF			0xAE
#define CMD_DISPLAY_ON			0xAF
#define CMD_SET_PAGE0			0xB0
#define CMD_SET_VMIRROR			0xC8
#define CMD_SET_NON_VMIRROR		0xC0
#define	CMD_SET_VOFFSET			0xD3
#define CMD_SET_OSCDIV			0xD5
#define CMD_SET_PRECHARGE		0xD9
#define CMD_SET_COMCONFIG		0xDA
#define	CMD_SET_VCOMH			0xDB

#define VAL_HORIZON_ADDRSS		0x00
#define VAL_CONTRAST_MAX		0xFF
#define VAL_OSC_FREQ_MAX		0xF0
#define VAL_PRECHG_DEFAULT		0x22
#define VAL_VCOMH_DEFAULT		0x20
#define	VAL_CHG_PUMP_ENABLE		0x14
#define VAL_VOFFSET_NONE		0x00

#define VAL_MPX_RATIO_32L		0x1F
#define VAL_COM_CONFIG_32L		0x02
#define VAL_START_PAGE			0x00
#define VAL_END_PAGE_32L		0x03

//! @def SSD1306 OLED screen dimensions
#define SSD1306_HEIGHT          32		// height
#define SSD1306_WIDTH           128		// width

//! @def SSD1306 OLED character rendering
#define SCREEN_BLANK			0x00
#define FONT_PRINTABLE_START	0x20
#define FONT_PRINTABLE_END		0x83
#define BYTES_PER_CHAR_DATA		16
#define BITS_PER_PAGE			8
#define MAX_PAGE				(SSD1306_HEIGHT / BITS_PER_PAGE)
#define FB_SIZE					(SSD1306_WIDTH * (SSD1306_HEIGHT / BITS_PER_PAGE))

enum screen_stat {
	OFF = false,//!< OFF
	ON = true,  //!< ON
};

enum render_operator {
	INP,	//!< render content may overwritten.
	XOR,	//!< render content are 'xor'ed with frame buffer
};

/*
 * Function prototype definitions
 */
void SSD1306_Initialize(void);
void SSD1306_ClearBuffer(void);
bool SSD1306_FlashScreen(void);
void SSD1306_SetScreen(bool on);
void SSD1306_Render2Buffer(void);

_END_STD_C

#endif // __SSD1306_H__