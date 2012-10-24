/** ###################################################################
**     Filename  : pcf8574a_comunication.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-24, 18:11
**     Contents  :
**         User source code
**
** ###################################################################*/
#include "I2C_functions.h"
#include "IO_Map.h"

/* MODULE pcf8574a_comunication */

int sendSampleDataToExpander(char number) 
{

  int delay = 65536;
  
  //setRegBit(IICS, IICIF);  // clear interrupt flag   
  clearInteruptFlag();
    
  sendStartSignal();     
  
  //setReg(IICD, 0b01111110); // address of expander + WR bit
  sendByteOfData(0b01111110);
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 7;
  
  //setRegBit(IICS, IICIF);  // clear interrupt flag
  clearInteruptFlag();
    
  delay = 65535;  
  
  while(getRegBit(IICS, RXAK) && delay != 0)  // wait for ack
    delay--;
    
  if (delay==0)  // end if no ack get
    return 5;
  
  //setReg(IICD, number); // write sequence to sent
  sendByteOfData(number);
   
  delay = 65535;
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 8;
  
  //setRegBit(IICS, IICIF);  // clear interrupt flag  
  clearInteruptFlag();
  
  delay = 65535;
  while(getRegBit(IICS, RXAK) && delay != 0)  // wait for ack
    delay--;
    
  if (delay==0)
    return 6;
  
  //clrRegBit(IICC1, MST); // stop signal - probably  
  sendStopSignal();
  
  return 1;
    
} 


/* END pcf8574a_comunication */
