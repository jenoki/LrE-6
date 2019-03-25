/*
 * wroom.c
 *
 *  Created on: 2019/03/20
 *      Author: jenoki
 */

#include <main.h>
extern UART_HandleTypeDef huart1;

uint8_t wroom_tx_buffer[WROOM_TX_BUFSIZE];
uint8_t wroom_rx_buffer[WROOM_RX_BUFSIZE];
uint8_t wroom_boot_state;

void WROOM_initialize(){
	wroom_boot_state = SET_STA;
}

//when goes to next stage call this func.
void WROOM_set_boot_state(uint8_t	state){
	uint16_t len;
	if (state == SET_STA) {
		strcpy(wroom_tx_buffer, AT_MODE);
		len = strlen(wroom_tx_buffer);
	} else if(state == CON_AP) {
		sprintf(wroom_tx_buffer,AT_CONNAP,SSID,PASSWD);
		len = strlen(wroom_tx_buffer);
	} else if(state == CON_IP) {
		sprintf(wroom_tx_buffer,AT_CNHOST,LrHOST,SEND_PORT);
		len = strlen(wroom_tx_buffer);
	} else if(state == SET_PATHR) {
		strcpy(wroom_tx_buffer, AT_PATHR);
		len = strlen(wroom_tx_buffer);
	} else if(state == SET_SEND){
		strcpy(wroom_tx_buffer, AT_SEND);
		len = strlen(wroom_tx_buffer);
	} else if(state == PASSTHRU){
		return;	//Do Nothing
	} else {//some error
		return;
	}
	HAL_UART_Transmit_DMA(&huart1, wroom_tx_buffer, len);
	HAL_UART_Receive_DMA(&huart1, wroom_rx_buffer, WROOM_RX_BUFSIZE);
	wroom_boot_state = state;
}
