/*
 * Node2.c
 *
 * Created: 13.10.2022 17:14:48
 * Author : alessp
 */ 


#include "sam.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    /* Initialize the SAM system */
    SystemInit();





    /* Replace with your application code */
    while (1) 
    {
		
	PIOD->PIO_SODR = PIO_SODR_P0 ;
	PIOD->PIO_PER= PIO_PER_P0;
	PIOD->PIO_OER= PIO_OER_P0;


    }
}
