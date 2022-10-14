/*
 * Node_2.c
 *
 * Created: 14.10.2022 16:51:24
 * Author : lucapre
 */ 

#include <stdio.h>
#include "printf-stdarg.h"
#include "sam.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit();
	configure_uart();
	

    /* Replace with your application code */
    while (1) 
    {
		
		printf("Ciao a tutti sono Clovis  \n ");
		printf("Ciao a tutti sono Pedro  \n ");
    }
}
