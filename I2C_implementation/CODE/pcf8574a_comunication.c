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

int sendSampleDataToExpander_New(char number) 
{
  byte result = 15;
      
  I2C_SendStart();     
  
  result = I2C_SendByte_Ack(0b01111110); // send address of Expander                 
  //sendByteOfData(0b01111110);
  if(result!=0)
    return result;  
 
  result = I2C_SendByte_Ack(number); // send address                  
  //sendByteOfData(number);
    
  I2C_SendStop();
  
  return result;
    
} 



byte getSampleDataFromExpander(char* data){
  
  int delay = 65536;
          
  clearInteruptFlag();
  
   // check if it is in transmit mode
    // this fragment was changed
  if(getRegBit(IICC1, TX)==0)
    setRegBit(IICC1, TX);
    
  I2C_SendStart();     
    
  sendByteOfData(0b01111111); // inform expander that i will get some data from him
  
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
  
  clrRegBit(IICC1, TX); // receive information from device 
    
  setRegBit(IICC1, TXAK);  // No acknowledge signal response is sent
  
  *data = getReg(IICD);
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 7;
  
  clearInteruptFlag();
  
  I2C_SendStop();
  
  return 1;
  
}


/* END pcf8574a_comunication */
