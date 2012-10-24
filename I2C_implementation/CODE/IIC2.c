/** ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename  : IIC2.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Component : Init_IIC
**     Version   : Component 01.065, Driver 01.17, CPU db: 3.00.053
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-24, 21:14
**     Abstract  :
**          This file implements the IIC (IIC1) module initialization
**          according to the Peripheral Initialization Bean settings, and defines
**          interrupt service routines prototypes.
**          The inter-integrated circuit (IIC) interface is a two wire, bidirectional 
**          serial bus which provides a simple, efficient way for data exchange between 
**          devices. The interface is designed for internal serial communication between
**          the MCU and other IIC devices.
**     Settings  :
**          Bean name                                      : IIC2
**          Device                                         : IIC1
**          Settings                                       : 
**          Clock settings                                 : 
**          Multiplier Factor                              : 1
**          Clock rate                                     : 36
**          SCL frequency                                  : 83.333 kHz
**          SDA Hold                                       : 2.042 us
**          Address                                        : 0
**          Transfer direction                             : Transmit
**          Transmit Acknowledge                           : yes
**          Pins                                           : 
**          SDA pin                                        : PTC1_SDA1
**          SDA pin signal                                 : 
**          SCL pin                                        : PTC0_SCL1
**          SCL pin signal                                 : 
**          Interrupts                                     : 
**          Interrupt                                      : Viic1
**          IIC interrupt                                  : Enabled
**          ISR name                                       : I2C_interrupt_handler
**          Initialization                                 : 
**          Call Init method                               : yes
**          Module Enable                                  : yes
**     Contents  :
**         Init - void IIC2_Init(void);
**
**     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE IIC2. */

#include "IIC2.h"

/*
** ###################################################################
**
**  The interrupt service routine(s) must be implemented
**  by user in one of the following user modules.
**
**  If the "Generate ISR" option is enabled, Processor Expert generates
**  ISR templates in the CPU event module.
**
**  User modules:
**      I2C_implementation.c
**      Events.c
**      FM75_comunication.c
**      pcf8574a_comunication.c
**      I2C_functions.c
**
** ###################################################################
ISR(I2C_interrupt_handler)
{
  // NOTE: The routine should include the following actions to obtain
  //       correct functionality of the hardware.
  //
  //  IICIF bit in the IICS register must be set to clear
  //  interrupt request flag.
  //  Example: IICS = IICS_IICIF_MASK;
}
*/

/*
** ===================================================================
**     Method      :  IIC2_Init (component Init_IIC)
**
**     Description :
**         This method initializes registers of the IIC module
**         according to this Peripheral Initialization Bean settings.
**         Call this method in user code to initialize the module.
**         By default, the method is called by PE automatically; see
**         "Call Init method" property of the bean for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void IIC2_Init(void)
{
  /* IICC2: GCAEN=0,ADEXT=0,??=0,??=0,??=0,AD10=0,AD9=0,AD8=0 */
  setReg8(IICC2, 0x00);                 
  /* IICA: AD7=0,AD6=0,AD5=0,AD4=0,AD3=0,AD2=0,AD1=0,??=0 */
  setReg8(IICA, 0x00);                  
  /* IICF: MULT1=0,MULT0=0,ICR5=1,ICR4=0,ICR3=0,ICR2=1,ICR1=0,ICR0=0 */
  setReg8(IICF, 0x24);                  
  /* IICS: TCF=1,IAAS=0,BUSY=0,ARBL=1,??=0,SRW=0,IICIF=1,RXAK=0 */
  setReg8(IICS, 0x92);                 /* Clear the interrupt flags */ 
  /* IICC1: IICEN=1 */
  setReg8Bits(IICC1, 0x80);             
  /* IICC1: IICEN=1,IICIE=1,MST=0,TX=1,TXAK=0,RSTA=0,??=0,??=0 */
  setReg8(IICC1, 0xD0);                 
}

/* END IIC2. */

/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
