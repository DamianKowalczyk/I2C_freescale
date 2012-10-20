/** ###################################################################
**     Filename  : Events.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-17, 16:00
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

#ifdef ISR_IN_NONBANKED
#pragma CODE_SEG __NEAR_SEG NON_BANKED
#endif
/*
** ===================================================================
**     Interrupt handler : I2C_interrupt_handler
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
ISR(I2C_interrupt_handler)
{
  /* Write your interrupt code here ... */

}
#ifdef ISR_IN_NONBANKED
#pragma CODE_SEG DEFAULT
#endif


/* END Events */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
