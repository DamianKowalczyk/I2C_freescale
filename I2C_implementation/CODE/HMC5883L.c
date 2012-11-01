/** ###################################################################
**     Filename  : HMC5883L.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-11-01, 22:32
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE HMC5883L */
#include "I2C_functions.h"
#include "HMC5883L.h"



/** in this function we should set the device into appropriate mode e.g. single measurement or continuous mode */
void init(){

}

short getValues(short* values){
  short val[]= {0,0,0,0,0,0};
    
  
  I2C_SendStart();
  I2C_SendByte_Ack(HMC5883L_RD_ADDR);
  I2C_Receive_N_Bytes(val, 6); // im not sure if this function is correct because there wasnt any information in 
  // documentatin of after receiving last byte of information i should send ACK or NACK??????
  I2C_SendStop(); 
  
}

void setRegistry(){

}


void convertValues(){

}

void setContinuousMeasurementMode(){
  I2C_SendStart();
  I2C_SendByte_Ack(HMC5883L_WR_ADDR);
  I2C_SendByte_Ack(HMC5883L_MODE_REGISTER);    
  I2C_SendByte_Ack(0x00);
  I2C_SendStop();  
}

// probably this function should start measurement but after measurement we should wait for some time
void setSingleMeasuremen(){
  I2C_SendStart();
  I2C_SendByte_Ack(HMC5883L_WR_ADDR);
  I2C_SendByte_Ack(HMC5883L_MODE_REGISTER);    
  I2C_SendByte_Ack(0x01);
  I2C_SendStop();  
}


/* END HMC5883L */
