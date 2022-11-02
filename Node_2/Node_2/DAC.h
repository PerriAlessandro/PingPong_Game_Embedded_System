void DAC_init(){
	REG_PMC_PCR|= PMC_PCR_EN || PMC_PCR_DIV_PERIPH_DIV_MCK || ID_DACC << PMC_PCR_PID_Pos;
	REG_PMC_PCER1 |= 1<< (ID_DACC-32);
	REG_DACC_WPMR=DACC_WPMR_WPKEY(0x444143);
	REG_DACC_MR|=  DACC_MR_WORD_HALF || DACC_MR_USER_SEL_CHANNEL1 ; //DACC Mode Register, Half-Word Mode, Channel 1
	
	REG_DACC_CHER=DACC_CHER_CH1; //Channel Enable Register, enable channel 1
	DAC_write(0);
}


void DAC_write(uint16_t data){
	REG_DACC_CDR=data & 0x00FF;
	
	while(!DACC->DACC_ISR & DACC_ISR_EOC);	
}