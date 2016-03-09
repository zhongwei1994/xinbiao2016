/*
 * Bluetooth.h
 *
 *  Created on: Mar 7, 2016
 *      Author: zhongwei
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

extern void initLINFlex_0_UART(void);
extern void intc_serial_port_0_RX(void);
extern void serial_port_0_TX_array(const BYTE data[], WORD n);
extern void serial_port_0_TX(BYTE data);

extern int g_serial_port_0_f;
extern unsigned int g_serial_port_0_data;

#endif /* BLUETOOTH_H_ */
