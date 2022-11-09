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
#include "can_interrupt.h"
#include "pwm.h"
#include "PID.h"
#include "motor.h"
#include "timer.h"
#include "DAC.h"


#define SCORE_CAN_ID 2
#define SCORE_CAN_DATA_LENGTH 1


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
	PID_init(&PID,K_P,K_I,K_D, PERIOD);
	CAN_MESSAGE score_message;
	score_message.id=SCORE_CAN_ID;
	score_message.data_length=SCORE_CAN_DATA_LENGTH;
	
	
	//printf("START GAME\n\r");
    while (1){
		uint16_t encVal=read_encoder();
		//printf("enc: %d\n\r",encVal);
		print_status_play();
		if (game_is_over()){	
			clk_value=read_value_timer();
			printf("Your score is: %d\n\r",clk_value);
			score_message.data[0]=clk_value;
			can_send(&score_message,0);
			reset_timer();
		}
		
	}
	
}
