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

/*

void CAN_print(CAN_MESSAGE *message){
	printf("\n START CAN Message print. \n");
	printf(" ID: %d \n",message->id);
	printf(" Length: %d \n",message->data_length);
	for(uint8_t i=0; i<(uint8_t)(message->data_length); i++){
		printf(" Package [%d]: %d \n", i, message->data[i]);
	}
	printf(" END CAN Message print. \n");
}*/


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	uint8_t PHASE_2 = 6;
	uint8_t PHASE_1 = 7;
	uint8_t PROPAG = 2;
	uint8_t SJW = 0;
	uint8_t BRP = 3;
	uint8_t SMP = 0;
	uint32_t can_br = PHASE_2 | (PHASE_1 << 4) | (PROPAG << 8) | (SJW << 12) | (BRP << 16) | (SMP << 24);
	printf("can_br = %x \n", can_br);
	can_init_def_tx_rx_mb(can_br);
    /* Replace with your application code */
	CAN_MESSAGE message;
	uint8_t data;
    while (1) 
    {
		/*if(can_receive(&msg,0)){
			printf("nothing\n");
		}
		else{
			CAN_print(&msg);
		}*/
		
		
	can_receive(&message,1);
	printf("START CAN Message print. \n ")	;
	printf("ID: %d \n",message.id);
	printf("Length: %d \n",message.data_length)	;
		for(uint8_t i=0; i<(uint8_t)(message.data_length); i++){
			
			printf("Package [%d]: %d \n", i, message.data[i])	;
			
		}
	
	printf("END CAN Message print. \n ")	;
	/*
 	printf("\n START CAN Message print. \n");
 	printf(" ID: %d \n",message.id);
 	printf(" Length: %d \n",message.data_length);
 	for(uint8_t i=0; i<(uint8_t)(message.data_length); i++){
	 	printf(" Package [%d]: %d \n", i, message.data[i]);
 	}
 	printf(" END CAN Message print. \n");*/
		//printf("Ciao a tutti sono Clovis  \n ");
		//printf("\n START CAN Message print. \n");
		//printf("Ciao a tutti sono Pedro  \n ");
    }
}
