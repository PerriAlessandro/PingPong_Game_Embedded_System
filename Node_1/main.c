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



int main(){
	uart_init(9600);
	stdout = &mystdout;
	xmem_init();
	PWM_init();
	OLED_init();
	OLED_clear();
	GUI_menu_init();
	MCP2515_init();


	while (1){
		menu_navigation();
		CAN_send_joypos();
		
		_delay_ms(1000);
	}

}


/*

	CAN_message message1,message2,message3;
	CAN_message read_message1,read_message2,read_message3;
	set_msg_id(&message1, 1);
	set_msg_id(&message2, 2);
	set_msg_id(&message3, 3);
	set_msg_length(&message1,8);
	set_msg_length(&message2,7);
	set_msg_length(&message3,6);
	for(int i=0; i<message1.length; i++){
		message1.data[i] = 1*i;
	}
	for(int i=0; i<message2.length; i++){
		message2.data[i] = 2*i;
	}
	for(int i=0; i<message3.length; i++){
		message3.data[i] = 3*i;
	}
	
	//CAN_transmit(&message3, 2);
	
	CAN_transmit(&message2, 1);
	_delay_ms(1000);
	CAN_receive(&read_message1);
	_delay_ms(1000);
	CAN_transmit(&message1, 0);
	_delay_ms(1000);
	CAN_receive(&read_message2);
	uint8_t intf = MCP2515_read(MCP_CANINTF);
	printf("INTF: %d\n", intf);
	
	_delay_ms(1000);
	


	
	_delay_ms(100);

	_delay_ms(100);
	//CAN_receive(&read_message3);
	printf("------------------------\n");
	CAN_print(&read_message1);
	CAN_print(&read_message2);
	//CAN_print(&read_message3);


*/


