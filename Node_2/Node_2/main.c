/*
 * Node_2.c
 *
 * Created: 14.10.2022 16:51:24
 * Author : lucapre
 */ 

#include <stdio.h>
#include "printf-stdarg.h"
#include "sam.h"
#include "can_controller.h"
//#include "can_interrupt.h"
#include "pwm.h"
#include "motor.h"

void CAN_print(CAN_MESSAGE *message){

printf("START CAN Message print. \n \r")	;
printf("ID: %d \n \r",message->id);
printf("Length: %d \n \r",message->data_length)	;
for(uint8_t i=0; i<(uint8_t)(message->data_length); i++){
	
	printf("Package [%d]: %d \n \r", i, message->data[i])	;
	
}
printf("END CAN Message print. \n \r")	;
}

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	pwn_init();
	uint8_t PHASE_2 = 5;
	uint8_t PHASE_1 = 6;
	uint8_t PROPAG = 1;
	uint8_t SJW = 0;
	uint8_t BRP = 41;
	uint8_t SMP = 0;
	uint32_t can_br = PHASE_2 | (PHASE_1 << 4) | (PROPAG << 8) | (SJW << 12) | (BRP << 16) | (SMP << 24);
	
	uint8_t old_value = 0;
	uint8_t new_value = 1;
	can_init_def_tx_rx_mb(can_br);
	servo_init();
	CAN_MESSAGE message;
    while (1){
		
		//CAN_print(&message);
		can_receive(&message, 0);
		if(old_value != new_value){
			 pwm_set_dutycycle(&message);
			 old_value = new_value;
		}
		new_value = message.data[1];
		send_score();
	
	}
	
}
