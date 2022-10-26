void servo_init(){
	PIOD -> PIO_SODR = PIO_SODR_P9;		//mj1 enable high
	PIOD -> PIO_SODR = PIO_CODR_P10;	// mj1 set dir
}

void send_score(){

	REG_PIOC_PER=PIO_PER_P16;
	PIOC->PIO_ODR=PIO_ODR_P16;
	PIOC->PIO_PUDR=PIO_PUDR_P16;
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

 void PIOC_Handler(){
	 
	uint32_t status=REG_PIOC_ISR;
	 if(status & PIO_ISR_P16)
			printf("interrupt captured\n\r");
	 
 }