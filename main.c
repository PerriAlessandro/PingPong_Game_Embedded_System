#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "Uart_driver.h"
#include "usart_driver.h"
#include "xmem_driver.h"
#include "ADC.h"
#include "positions.h"
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

void OLED_init()
 {
	 xmem_write(0x01, 0xae, BASE_ADDRESS_OLED); // display off
	 xmem_write(0x01, 0xa1, BASE_ADDRESS_OLED); //segment remap
	 xmem_write(0x01, 0xda, BASE_ADDRESS_OLED); //common pads hardware: alternative
	 xmem_write(0x01, 0x12, BASE_ADDRESS_OLED);
	 xmem_write(0x01, 0xc8, BASE_ADDRESS_OLED); //common output scan direction:com63~com0
	 xmem_write(0x01, 0xa8, BASE_ADDRESS_OLED); //multiplex ration mode:63
	 xmem_write(0x01, 0x3f, BASE_ADDRESS_OLED);
	 xmem_write(0x01, 0xd5, BASE_ADDRESS_OLED); //display divide ratio/osc. freq. mode
	 xmem_write(0x01, 0x80, BASE_ADDRESS_OLED);
	 xmem_write(0x01, 0x81, BASE_ADDRESS_OLED); //contrast control
	 xmem_write(0x01, 0x50, BASE_ADDRESS_OLED);
	 xmem_write(0x01, 0xd9, BASE_ADDRESS_OLED); //set pre-charge period
	 xmem_write(0x01, 0x21, BASE_ADDRESS_OLED);
	 xmem_write(0x01, 0x20, BASE_ADDRESS_OLED); //Set Memory Addressing Mode
	 xmem_write(0x01, 0x02, BASE_ADDRESS_OLED);
	 xmem_write(0x01, 0xdb, BASE_ADDRESS_OLED); //VCOM deselect level mode
	 xmem_write(0x01, 0x30, BASE_ADDRESS_OLED);
	 xmem_write(0x01, 0xad, BASE_ADDRESS_OLED); //master configuration
	 xmem_write(0x01, 0x00, BASE_ADDRESS_OLED);
	 xmem_write(0x01, 0xa4, BASE_ADDRESS_OLED); //out follows RAM content
	 xmem_write(0x01, 0xa6, BASE_ADDRESS_OLED); //set normal display
	 xmem_write(0x01, 0xaf, BASE_ADDRESS_OLED); // display on
} 

/*
void OLED_print_arrow ( uint8_t row , uint8_t col )
{
OLED_pos ( row , col );
	OLED_write_data (0b00011000 );
	OLED_write_data (0 b00011000 );
	OLED_write_data (0 b01111110 );
	OLED_write_data (0 b00111100 );
	OLED_write_data (0 b00011000 );
}
*/

int main(){
	uart_init(9600);
	stdout = &mystdout;
	xmem_init();
	PWM_init();
	uint8_t data=154;
	uint16_t addre1=0x01;
	uint16_t addre2=0;
	uint16_t seed;
	addre1=0;
	printf("///////////////\n");
	uint8_t value = 0;
	// DDRB = 0x00;
	//value = PINB;
	OLED_init();
	
	while(1){
		xmem_write(0x01, 0x00, 0b0001001010100101); 
	} 
}

/*
joystick = get_joypos();
slider=get_sliderpos();
printf("-----------------------------------------------------------\n");
printf("xjoy= %d%% yjoy= %d%% left= %d%% right = %d%% \n",joystick.x_pos, joystick.y_pos, slider.left, slider.right);
printf("Current joystick's direction: %s, %s\n",joystick.x_currdir,joystick.y_currdir);
*/




