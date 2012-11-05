/** ###################################################################
**     Filename  : MPU3050.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-11-04, 22:33
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE MPU3050 */

void MPU3050_init(){
}

void MPU3050_setRegistry(char reg_addr, char value)
{
  I2C_SendStart();
  I2C_SendByte_Ack(MPU3050_WR_ADDR);
  I2C_SendByte_Ack(reg_addr);
  I2C_SendByte_Ack(value);
  I2C_SendStop();
}

void MPU3050_setN_ConsecutiveRegisters(byte start_reg_addr, byte n, byte* reg_values)
{
  byte i;
  
  I2C_SendStart();
  I2C_SendByte_Ack(MPU3050_WR_ADDR);
  I2C_SendByte_Ack(reg_addr);
  for(i=0; i<n; i++) 
  {
    I2C_SendByte_Ack(*(reg_values++));    
  }
  I2C_SendStop();
}


byte MPU3050_readRegistry(byte reg_addr)
{
  I2C_SendStart();
  I2C_SendByte_Ack(MPU3050_WR_ADDR);
  I2C_SendByte_Ack(reg_addr);
  I2C_SendRepeatStart();
  
  
  
  I2C_SendStop();      
}

void MPU3050_readAuxiliaryMeasurement(){
}

void MPU3050_readTemperatureMeasurement(){
}

void MPU3050_setBiasOffset(short x, short y, short z){  // 2's complementary 
}

void MPU3050_setBandwith(){
}





/* END MPU3050 */
