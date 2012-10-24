/** ###################################################################
**     Filename  : I2C_implementation.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Version   : Driver 01.00
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-17, 16:00
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE I2C_implementation */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "IIC2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"


/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{

  int result = 0;
  char data = 0b10101010;
  int a,b;
  char table[] = {0,0,0,0,0,0,0,0,0,0};
  byte i = 0;
  int j;
  
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  for (j=0;j<10;j++){
    
    table[i] = sendSampleDataToExpander(data);
    i++;
    for (a=0; a<200; a++)
      for (b=0; b<24000; b++)
        ;    
    table[i] = sendSampleDataToExpander(0b01010101);
    i++;
    for (a=0; a<200; a++)
      for (b=0; b<24000; b++)
        ;      
  }
  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END I2C_implementation */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
