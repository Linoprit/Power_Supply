/*
 * uart_messaging.h
 *
 *  Created on: 16.12.2018
 *      Author: harald
 */

#ifndef USB_PRINTF_H_
#define USB_PRINTF_H_

// C interface
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC int tx_printf(const char *format, ...);
EXTERNC int tx_printBuff(uint8_t* buffer, uint8_t len) ;
EXTERNC void usb_receive(uint8_t* buf, uint32_t len);
EXTERNC uint8_t tx_cycle(void);

#undef EXTERNC
#ifdef __cplusplus

// put cpp includes here!!




#endif // C interface
#endif /* USB_PRINTF_H_ */
