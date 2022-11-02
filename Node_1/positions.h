#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "CAN_controller.h"

#define BASE_ADDRESS_ADC 0x1400

struct joy_pos {   // Structure declaration
  uint8_t x_pos;           
  uint8_t y_pos;
  const char* x_currdir;
  const char* y_currdir;         
};

struct slider_pos {   // Structure declaration
  uint8_t left;           
  uint8_t right;       
};

struct joy_pos joystick;
struct slider_pos slider;


struct joy_pos get_joypos(){
	ADC_init_read();
	joystick.x_pos = xmem_read(0x00, BASE_ADDRESS_ADC);
	joystick.y_pos = xmem_read(0x00, BASE_ADDRESS_ADC);	
	xmem_read(0x00, BASE_ADDRESS_ADC);
    xmem_read(0x00, BASE_ADDRESS_ADC);
	_delay_us(5000);

	if (joystick.x_pos>160 && joystick.x_pos<175) 
		{joystick.x_pos = 0;
		joystick.x_currdir="NEUTRAL";
		}
	else if(joystick.x_pos>=0 && joystick.x_pos<160) {
		joystick.x_pos=(joystick.x_pos*100/166)-100;
		joystick.x_currdir="LEFT";
		}	
	else if(joystick.x_pos>=175 && joystick.x_pos<256){
		joystick.x_pos=((joystick.x_pos-170)*100/85);
		joystick.x_currdir="RIGHT";
		}
	else{
		joystick.x_pos=0;
		joystick.x_currdir="---";
		
	}

	if (joystick.y_pos>155 && joystick.y_pos<170) {
		joystick.y_pos = 0;
		joystick.y_currdir="NEUTRAL";
		}
	else if(joystick.y_pos>=0 && joystick.y_pos<=155) {
		joystick.y_pos=(joystick.y_pos*100/166)-100;
		joystick.y_currdir="DOWN";
		}
	else if(joystick.y_pos>=170 && joystick.y_pos<256){
		joystick.y_pos=((joystick.y_pos-170)*100/85);
		joystick.y_currdir="UP";
		}
	else{
		joystick.y_pos=0;
		joystick.y_currdir="---";
	}
	return joystick;		
}


struct slider_pos get_sliderpos(){
	ADC_init_read();
	xmem_read(0x00, BASE_ADDRESS_ADC);
    xmem_read(0x00, BASE_ADDRESS_ADC);
	slider.left = xmem_read(0x00, BASE_ADDRESS_ADC)*100/255;
	slider.right = xmem_read(0x00, BASE_ADDRESS_ADC)*100/255;
	_delay_us(5000);
	return slider;			
}


//unused
void CAN_send_joypos(){
	joystick = get_joypos();
	CAN_message joystick_pos_msg;
	
	set_msg_id(&joystick_pos_msg ,1);
	set_msg_length(&joystick_pos_msg, 4);
	
	
	if (joystick.x_currdir =="LEFT"){
		joystick_pos_msg.data[0] =-joystick.x_pos ;
		joystick_pos_msg.data[1] =0 ;
	}
	else
	{
		joystick_pos_msg.data[0] =0 ;
		joystick_pos_msg.data[1] = joystick.x_pos;
	}
	
	if (joystick.y_currdir =="DOWN"){
		joystick_pos_msg.data[2] =-joystick.y_pos ;
		joystick_pos_msg.data[3] =0 ;
	}
	else
	{
		joystick_pos_msg.data[2] =0 ;
		joystick_pos_msg.data[3] = joystick.y_pos;
	}
		
	
	CAN_transmit(&joystick_pos_msg,0);
}

void CAN_send_slider(){
	slider = get_sliderpos();
	CAN_message slider_pos_msg;
	
	set_msg_id(&slider_pos_msg ,1);
	set_msg_length(&slider_pos_msg, 2);
	
	slider_pos_msg.data[0] =slider.left;
	slider_pos_msg.data[1] =slider.right;
	
	CAN_transmit(&slider_pos_msg,0);
}