#include "mcp2515.h"

typedef struct{
	unsigned short id;
	unsigned char length;
	char data [8];
}can_message;

void can_transmit(struct can_message *message, uint8_t buffer){
	uint8_t id_low = (message->id) << 5;
	uint8_t id_high = (message->id) >> 3;
	uint8_t length = message->length;
	uint8_t reg_high,reg_low,reg_dlc,reg_data,instr;

	if(buffer == 0){
		reg_high=TXB0SIDH;
		reg_low=TXB0SIDL;
		reg_dlc=TXB0DLC;
		reg_data=TXB0D0;
		instr=0b10000001;
	}
	else if (buffer == 1){
		reg_high=TXB1SIDH;
		reg_low=TXB1SIDL;
		reg_dlc=TXB1DLC;
		reg_data=TXB1D0;
		instr=0b10000010;		
	}
	else {
		reg_high=TXB2SIDH;
		reg_low=TXB2SIDL;
		reg_dlc=TXB2DLC;
		reg_data=TXB2D0;
		instr=0b10000100;			
	}
	MCP2515_write(reg_high, id_high);
	MCP2515_write(reg_low, id_low);
	MCP2515_write(reg_dlc, length);
	for(int i=0; i<8; i++){
		MCP2515_write(reg_data +i, message->data[i]);
	}
	MCP2515_request_to_send(instr);
}