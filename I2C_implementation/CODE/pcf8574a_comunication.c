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
  byte result = 15;
      
  I2C_SendStart();     
  
  result = I2C_SendByte_Ack(0b01111110); // send address of Expander                 
  
  if(result!=0)
    return result;  
 
  result = I2C_SendByte_Ack(number); // send value to expand                  
      
  I2C_SendStop();
  
  return 0;    
} 

byte getSampleDataFromExpander(char* data)
{           
  byte result = 15;
      
  I2C_SendStart();     
  
  result = I2C_SendByte_Ack(0b01111111); // send address of Expander                 
  
  if(result!=0)
    return result;  
 
  result = I2C_Receive_N_Bytes(data, 1);
  
  return 0;   
}

void expanderBlinkDiodes()
{
  byte i, j; 
  
  for (j=0, i=0;j<10;j++)
  {    
    sendSampleDataToExpander(0b10101010);
    i++;
    wait();
    sendSampleDataToExpander(0b01010101);
    i++;
    wait();         
  }  
   
  leds_PutVal(15); 
   
}

void expanderGetValues()
{
  byte i, j;
  char dataFromExpander[] = {0,0,0,0,0,0,0,0,0,0};
  
  for (j=0;j<10;j++)
  {    
    getSampleDataFromExpander(&dataFromExpander[j]);     
    wait();  
  }
}

/* END pcf8574a_comunication */
