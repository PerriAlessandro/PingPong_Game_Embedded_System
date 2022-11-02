#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "Uart_driver.h"
#include "usart_driver.h"
#include "xmem_driver.h"
#include "ADC.h"
#include "positions.h"
#include "OLED.h"
#include "GUI.h"

#define SCORE_CAN_ID 2


int main(){
	uart_init(9600);
	stdout = &mystdout;
	xmem_init();
	PWM_init();
	OLED_init();
	OLED_clear();
	GUI_menu_init();
	MCP2515_init();
	printf("START NODE 1\n\r");
	CAN_message score_message;
	while (1){
		menu_navigation();
		CAN_send_slider();
		CAN_receive(&score_message);
		if (score_message.id==SCORE_CAN_ID){
			display_highscore(score_message.data[0]);
			printf("highscore received: %d\n\r",score_message.data[0]);
			score_message.id=99;
		
		}
		_delay_ms(1000);
	}

}




