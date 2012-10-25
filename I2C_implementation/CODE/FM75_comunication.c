/** ###################################################################
**     Filename  : FM75_comunication.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-24, 18:42
**     Contents  :
**         User source code
**
** ###################################################################*/

#include "I2C_functions.h"
#include "IO_Map.h"

// FM75 address 0b
/* MODULE FM75_comunication */

  // address of FM75 is 1001111
/* The same initial settings of bus speed as in expander should work also for this device */

int getTemperature(){

  int temperature = 0;
  int delay = 65536;
  
          
  clearInteruptFlag();
  
  setTransmitMode();
    
  sendStartSignal();
  
  //the function below are not correct     
    
  sendByteOfData(0b10011111); // set address of FM75 and inform about reading process
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 7;
  
  clearInteruptFlag();
    
  delay = 65535;  
  
  while(getRegBit(IICS, RXAK) && delay != 0)  // wait for ack
    delay--;
    
  if (delay==0)  // end if no ack get
    return 5;
  
  setReceiveMode();  
  
  clrRegBit(IICC1, TXAK); // send ack after receiving first byte of data
  
  temperature = getReg(IICD)<<8; 
   
  
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 7;
  
  clearInteruptFlag();   
    
  setRegBit(IICC1, TXAK);  // No acknowledge signal response is sent
  
  temperature |= getReg(IICD);
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 7;
  
  clearInteruptFlag();
  
  sendStopSignal();
  
  return 1;


}



/* END FM75_comunication */
