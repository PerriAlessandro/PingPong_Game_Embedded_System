uint8_t game_over=0;
uint8_t start_game=1;

void motor_init(){
	REG_PIOD_PER=PIO_PER_P0 || PIO_PER_P1 || PIO_PER_P2 || PIO_PER_P9 || PIO_PER_P10; //PIO Controller PIO Enable Register
	REG_PIOD_OER=PIO_OER_P0 || PIO_OER_P1 || PIO_OER_P2 || PIO_OER_P9 || PIO_OER_P10; //PIO Controller PIO Output Enable Register
	
	REG_PIOD_SODR= PIO_SODR_P1 || PIO_SODR_P9; //PIO Controller Set Output Data Register, not encoder reset (P1) ,encoder mj1 enable high(P10)
	REG_PIOD_CODR = PIO_CODR_P0 || PIO_CODR_P2 || PIO_CODR_P10; //PIO Controller Clear Output Data Register,encoder output enable (P0), encoder select(P2) ,mj1 set dir(P10)
	
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
 
 