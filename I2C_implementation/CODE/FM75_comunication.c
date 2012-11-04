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


// for testing only ********************************************************
int setPointerToControlRegister(){
  byte result = 15;
  byte value = 254;
      
  I2C_SendStart();
  
  result = I2C_SendByte_Ack(0b10011110);  // set address of FM75 
  
  if(result!=0)
    return result;
  
  result = I2C_SendByte_Ack(0x01);  // pointer address
  
  if(result!=0)
    return result;
  
  I2C_SendRepeatStart();
  
  result = I2C_SendByte_Ack(0b10011111);  // set address of FM75 
  
  if(result!=0)
    return result;
  
  result = I2C_SendByte_Ack(0b10011111);  // set address of FM75 
  
  if(result!=0)
    return result;
  
  result = I2C_ReceiveByte_No_Ack(&value);    
}

int readTemperatureAfterSetingPointer(int* temp_pointer){
  byte result = 15;
  byte value = 254;
  
  char temperature[] = {0,0};
  int tmp =0;
      
  I2C_SendStart();
  
  result = I2C_SendByte_Ack(0b10011110);  // set address of FM75 
  
  if(result!=0)
    return result;
  
  result = I2C_SendByte_Ack(0x00);  // pointer address
  
  if(result!=0)
    return result;
  
  I2C_SendRepeatStart();
  
  result = I2C_SendByte_Ack(0b10011111);  // set address of FM75 
  
  if(result!=0)
    return result;    
      
  result = I2C_Receive_N_Bytes(temperature, 2);
  
  tmp = temperature[0]<<8 | temperature[1];
  
  *temp_pointer =  convertToCelsjusz(tmp);
  
  return result;  
}

/* END FM75_comunication */
