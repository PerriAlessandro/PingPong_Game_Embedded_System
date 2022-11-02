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
#include "pwm.h"
#include "motor.h"
#include "timer.h"
#include "DAC.h"

#define SCORE_CAN_ID 2
#define SCORE_CAN_DATA_LENGTH 1

void CAN_print(CAN_MESSAGE *message){

printf("START CAN Message print. \n \r")	;
printf("ID: %d \n \r",message->id);
printf("Length: %d \n \r",message->data_length)	;
for(uint8_t i=0; i<(uint8_t)(message->data_length); i++){
	
	printf("Package [%d]: %d \n \r", i, message->data[i])	;
	
}
printf("END CAN Message print. \n \r")	;
}
uint32_t clk_value=0;
int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	pwn_init();
	can_init_def_tx_rx_mb(get_can_br());
	servo_init();
	motor_init();
	DAC_init();
	CAN_MESSAGE score_message;
	score_message.id=SCORE_CAN_ID;
	score_message.data_length=SCORE_CAN_DATA_LENGTH;
	
	printf("START GAME\n\r");
    while (1){
		DAC_write(1000);
		if (game_is_over()){	
			clk_value=read_value_timer();
			printf("Your score is: %d\n\r",clk_value);
			score_message.data[0]=clk_value;
			can_send(&score_message,0);
			reset_timer();	
		}
		
	}
	
}
