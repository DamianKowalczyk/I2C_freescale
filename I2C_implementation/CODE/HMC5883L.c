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



/** in this function we should set the device into appropriate mode e.g. single measurement or continuous mode
    default the device is set into single measurement mode
*/ 
void init()
{   
  setContinuousMeasurementMode();  // measure magnetic field 15 times per second - default value 
                                    // this mode is more difficult than single mode because we have to measure time between two's reading from registry
                                    // to get correct values   
}

/** this function gets all measurement from device
    but only after setting 0x02 registry (the pointer will be increased) or after correct getting all values
*/
void getMeasuredValues(short* values)
{   
  I2C_SendStart();
  I2C_SendByte_Ack(HMC5883L_RD_ADDR);
  I2C_Receive_N_Bytes(val, 6); // im not sure if this function is correct because there wasnt any information in 
  // documentatin of after receiving last byte of information i should send ACK or NACK??????
  I2C_SendStop();  
}

/** set appropriate value into  */
void setRegistry(byte registry_address, byte value)
{
  I2C_SendStart();
  I2C_SendByte_Ack(HMC5883L_WR_ADDR);
  I2C_SendByte_Ack(registry_address);    
  I2C_SendByte_Ack(value);
  I2C_SendStop();
}

void setContinuousMeasurementMode()
{ 
  setRegistry(HMC5883L_MODE_REGISTER, 0x00); 
 /* I2C_SendStart();
  I2C_SendByte_Ack(HMC5883L_WR_ADDR);
  I2C_SendByte_Ack(HMC5883L_MODE_REGISTER);    
  I2C_SendByte_Ack(0x00);
  I2C_SendStop(); */  
}

/** probably this function starts measurement, it wasn't clearly described in documentation
*/
void setSingleMeasurement()
{
  I2C_SendStart();
  I2C_SendByte_Ack(HMC5883L_WR_ADDR);
  I2C_SendByte_Ack(HMC5883L_MODE_REGISTER);    
  I2C_SendByte_Ack(0x01);
  I2C_SendStop();  
}

/** starts single measurement and get results 
    max value is 2047 and min value is -2048, in case of overflow or underflow for the given channel the value -4096 is into registry
*/
void getValuesFromSingleMeasurement(short* values)
{
  int i, j;
  
  setContinuousMeasurementMode();
  
  waitForEndingMeasurement();
 
  getMeasuredValues(values);   
}

void generateSelfTest(){

}

void convertValues(){

}

void setPointerOnHMC5883L(byte reg_addr){
  I2C_SendStart();
  I2C_SendByte_Ack(HMC5883L_WR_ADDR);
  I2C_SendByte_Ack(reg_addr);    
  I2C_SendStop();    
}

void waitForEndingMeasurement()
{
   //probably 6ms - but should use different form of this implementation
  for(i=0;i<6;i++)
    for (j=0; j<16000; j++)
      ;
}


/* END HMC5883L */
