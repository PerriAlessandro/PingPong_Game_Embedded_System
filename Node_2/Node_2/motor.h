#define DIR  PIO_PD10
#define EN   PIO_PD9
#define SEL  PIO_PD2
#define NOT_RST  PIO_PD1
#define NOT_OE   PIO_PD0
#define ENC_MSK  0x1FE

uint8_t game_over=0;
uint8_t start_game=1;

void motor_init(){
	REG_PIOD_PER= NOT_OE || NOT_RST || SEL || EN || DIR  ; //PIO Controller PIO Enable Register
	REG_PIOD_OER= NOT_OE || NOT_RST || SEL || EN || DIR  ; //PIO Controller PIO Output Enable Register
	
	REG_PIOD_SODR= NOT_RST || EN; //PIO Controller Set Output Data Register, not encoder reset (P1) ,encoder mj1 enable high(P10)
	REG_PIOD_CODR = NOT_OE || SEL || DIR; //PIO Controller Clear Output Data Register,encoder output enable (P0), encoder select(P2) ,mj1 set dir(P10)
	
}

uint16_t read_encoder(){
	
	REG_PIOD_CODR=REG_PIOD_CODR = NOT_OE || SEL ; //set !OE and SEL low
	_delay_us(20); //Wait approx. 20 microseconds for output to settle
	uint8_t high_byte  = (REG_PIOC_PDSR & ENC_MSK)>>1; // Read MJ2 to get high byte
	REG_PIOD_SODR= SEL; //Set SEL high to output low byte	_delay_us(20);
	uint8_t low_byte = (REG_PIOC_PDSR & ENC_MSK)>>1; // Read MJ2 to get low byte
	REG_PIOD_CODR=REG_PIOD_SODR = NOT_OE; //Set !OE to high	uint16_t enc_value= high_byte<<8 || low_byte;	return enc_value;
}

void reset_encoder(){
	REG_PIOD_CODR= NOT_RST;
}

void servo_init(){

	REG_PIOC_PER=PIO_PER_P16; ////PIO Controller PIO Enable Register
	PIOC->PIO_ODR=PIO_ODR_P16; //PIO Controller Output Disable Register
	PIOC->PIO_PUDR=PIO_PUDR_P16; //PIO Pull Up Disable Register
	PMC->PMC_PCER0|=(1<<ID_PIOC); // Peripheral Clock Enable 0
	REG_PIOC_AIMER=PIO_AIMER_P16;
	REG_PIOC_IER|=PIO_IER_P16;
	REG_PIOC_ESR=PIO_ESR_P16;
	REG_PIOC_REHLSR=PIO_REHLSR_P16;
	REG_PIOC_SCDR=PIO_SCDR_DIV(100); //debouncing delay
	REG_PIOC_IFER=PIO_IFER_P16;  //enable debouncing delta
	REG_PIOC_DIFSR=PIO_DIFSR_P16; //enable debouncing filter for one specific
	NVIC_EnableIRQ(PIOC_IRQn);	
	
}

uint8_t game_is_over(){
	return game_over;
}

void reset_timer(){
	game_over=0;
	start_timer();
	
}

 void PIOC_Handler(){
	 
	uint32_t status=REG_PIOC_ISR;
	 if(status & PIO_ISR_P16){
			//printf("interrupt captured\n\r");
			if (!start_game){
				game_over= 1;
			}
			else start_game=0;

		}
	 
 }
 
 