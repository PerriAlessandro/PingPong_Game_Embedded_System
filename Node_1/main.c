#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

#include "usart_driver.h"
#include "xmem_driver.h"
#include "ADC.h"
#include "positions.h"
#include "OLED.h"
#include "GUI.h"




int main(){
	uart_init(9600);
	stdout = &mystdout;
	xmem_init();
	PWM_init();
	OLED_init();
	OLED_clear();
	GUI_menu_init();
	MCP2515_init();
	button_init();
	printf("START NODE 1\n\r");
	CAN_message score_message;
	while (1){
		menu_navigation();
		CAN_send_slider();
		CAN_receive(&score_message);
		check_game(&score_message);
		_delay_ms(1000);
	}

}




