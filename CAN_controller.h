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
	for(int i=0; i<length; i++){
		MCP2515_write(reg_data +i, message->data[i]);
	}
	MCP2515_request_to_send(instr);
}

struct can_message can_receive(uint8_t buffer){
	struct can_message * new_message;
	uint8_t intf = MCP2515_read(CANINTF)
	uint8_t int0 = (intf & 0b00000001);
	uint8_t int1 = (intf & 0b00000010);
	uint8_t reg_high,reg_low,reg_dlc,reg_data;

	if(!int0){
		reg_high = MCP_RXB0SIDH;
		reg_low = MCP_RXB0SIDL;
		reg_dlc = MCP_RXB0DLC;
		reg_data = MCP_RXB0D0;
		MCP2515_bit_modify(CANINTF, 0b00000001, 0x00);
		int1=1;
	}
	if(!int1){
		reg_high = MCP_RXB1SIDH;
		reg_low = MCP_RXB1SIDL;
		reg_dlc = MCP_RXB1DLC;
		reg_data = MCP_RXB1D0;
		MCP2515_bit_modify(CANINTF, 0b00000010, 0x00);
	}
	if(!int0 | !int1){
		new_message->id = MCP2515_read(reg_high) << 3 | (MCP2515_read(reg_low) >> 5);
		new_message->length = read(reg_dlc);
		for(int i=0; i<new_message->length; i++){
			new_message->data[i] = MCP2515_read(reg_data) +i;
		}
	}
}