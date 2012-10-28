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

/* MODULE FM75_comunication */     

int getTemperature(int* temp_pointer)
{       
  char temperature[] = {0,0};
    
  byte result = 15;
    
  I2C_SendStart();
  
  result = I2C_SendByte_Ack(0b10011111);  // set address of FM75 
  
  if(result!=0)
    return result;
  
  result = I2C_Receive_N_Bytes(temperature, 2);
  
  *temp_pointer = temperature[0]<<8 | temperature[1];
  
  return result;  
}



int convertToCelsjusz(int temper)
{  
  return ((temper>>7)/2); 
}

void checkTemperature(int* temp_pointer)
{
  int tmp =0;
  getTemperature(&tmp);
  *temp_pointer =  convertToCelsjusz(tmp);
} 

/* END FM75_comunication */
