/*
 * sd_spi_stm32.h
 *
 *  Created on: 10.08.2016
 *      Author: harald
 */

#ifndef SD_SPI_STM32_H_
#define SD_SPI_STM32_H_

#include "stm32f3xx_hal.h"
#include "ffconf.h"
#include "diskio.h"
#include "main.h"
#include <stdbool.h>


/* Martin Thomas begin */
/* Card type flags (CardType) */
#define CT_MMC              0x01
#define CT_SD1              0x02
#define CT_SD2              0x04
#define CT_SDC              (CT_SD1|CT_SD2)
#define CT_BLOCK            0x08

#ifndef RAMFUNC
#define RAMFUNC
#endif
/* Martin Thomas end */

#ifdef __cplusplus
 extern "C" {
#endif

// This function must be called in period of 10ms
RAMFUNC void disk_timerproc (void);

DSTATUS drv_disk_initialize (
	BYTE drv		/* Physical drive number (0) */
	);

DSTATUS drv_disk_status (
	BYTE drv		/* Physical drive number (0) */
	);

DRESULT drv_disk_read (
	BYTE drv,			/* Physical drive number (0) */
	BYTE *buff,			/* Pointer to the data buffer to store read data */
	DWORD sector,		/* Start sector number (LBA) */
	UINT count			/* Sector count (1..255) */
	);

DRESULT drv_disk_write (
	BYTE drv,			/* Physical drive number (0) */
	const BYTE *buff,	/* Pointer to the data to be written */
	DWORD sector,		/* Start sector number (LBA) */
	UINT count			/* Sector count (1..255) */
	);

DRESULT drv_disk_ioctl (
	BYTE drv,		/* Physical drive number (0) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
	);

#ifdef __cplusplus
}
#endif

#endif /* SD_SPI_STM32_H_ */
