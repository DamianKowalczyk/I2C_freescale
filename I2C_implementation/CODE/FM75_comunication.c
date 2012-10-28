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

int convertToCelsjusz(int temper){  
  return ((temper>>7)/2); 
}

int getTemperature(int* temp_pointer){

  int temperature = 0;
  int tmp= 0;
  int tmp2 = 0;
  int delay = 65536;
  
          
  //clearInteruptFlag();
// 1 comment 
  //setRegBit(IICC1, IICEN);  // enable I2C
  
  setTransmitMode();
    
  I2C_SendStart();
  
  //the function below are not correct     
    
  sendByteOfData(0b10011111); // set address of FM75 and inform about reading process
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 7;    
      
  delay = 65535;  
  while(getRegBit(IICS, RXAK) && delay != 0)  // wait for ack
    delay--;
    
  if (delay==0)  // end if no ack get
    return 5;
  
  clearInteruptFlag();
  
  setReceiveMode();  
  
  clrRegBit(IICC1, TXAK); // send ack after receiving first byte of data
  getReg(IICD);
    
  delay = 65535;
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct sent
    return 7;
  
  
  clearInteruptFlag();   
    
  setRegBit(IICC1, TXAK);  // No acknowledge signal response is sent
  
  tmp = getReg(IICD);    
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 7;
  
  I2C_SendStop();
  //clrRegBit(IICC1, IICEN);  // disable I2C
  
  // for tests only delete after this
  tmp2 = getReg(IICD); 
  temperature = tmp<<8 | tmp2;   
  *temp_pointer = temperature;
  
  
  clearInteruptFlag();
//2 added this line  
  //setRegBit(IICC1, IICEN);  // enable I2C
  
  
  
  return 1;

}

int getTemperature_New(int* temp_pointer){
  
  int tmp = 0;
  int tmp2 = 0;
  byte result = 15;
    
  I2C_SendStart();
  
  result = I2C_SendByte_Ack(0b10011111);  // set address of FM75 
  
  if(result!=0)
    return result;
  
  result = I2C_ReceiveByte_Ack(&tmp);
  
  if(result!=0)
    return result;
  
  tmp2 = tmp<<8;
  
  result = I2C_ReceiveByte_No_Ack(&tmp); 
  
  if(result!=0)
    return result;
  
  *temp_pointer = tmp2 | tmp;
  
  I2C_SendStop();
  
  return 0;
  
}

int getTemperature2(int* temp_pointer){
  
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


void checkTemperature(int* temp_pointer){
  int tmp =0;
  getTemperature(&tmp);
  *temp_pointer =  convertToCelsjusz(tmp);
}


/* END FM75_comunication */
