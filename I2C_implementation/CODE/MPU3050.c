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
#include "MPU3050.h"
#include "PE_Types.h"

struct MPU3050_str mpu3050;

void MPU3050_init()
{
  mpu3050.range = 0;
  mpu3050.filter_bandwidth = 0;  
}

void MPU3050_setRegistry_data(char reg_addr, char value)
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
  I2C_SendByte_Ack(start_reg_addr);
  for(i=0; i<n; i++) 
  {
    I2C_SendByte_Ack(*(reg_values++));    
  }
  I2C_SendStop();
}


byte MPU3050_readRegistry_data(byte reg_addr)
{
  I2C_SendStart();
  I2C_SendByte_Ack(MPU3050_WR_ADDR);
  I2C_SendByte_Ack(reg_addr);
  I2C_SendRepeatStart();
  I2C_SendByte_Ack(MPU3050_RD_ADDR);
  I2C_ReceiveByte_No_Ack();
  I2C_SendStop();      
}

void MPU3050_readN_ConsecutiveRegisters(byte start_reg_addr, byte n, byte* reg_values) 
{
  I2C_SendStart();
  I2C_SendByte_Ack(MPU3050_WR_ADDR);
  I2C_SendByte_Ack(start_reg_addr);
  I2C_SendRepeatStart();
  I2C_SendByte_Ack(MPU3050_RD_ADDR);
  I2C_Receive_N_Bytes(reg_values, n);
  I2C_SendStop();    
}

void MPU3050_readAngleMeasurement(short* angle_values)
{
  byte gyro_registers_values[6];
  byte* p_gyro_reg_val = gyro_registers_values;  
  
  byte i, j;
    
  MPU3050_readN_ConsecutiveRegisters(0x1D, 6, gyro_registers_values);
  
  for (i=0; i<3; i++)
  {
    *(angle_values) = *(p_gyro_reg_val++) << 8; // save msb value
    *(angle_values) |= *(p_gyro_reg_val++); // save also lsb value
    angle_values++;
  }        
}

void MPU3050_readTemperatureMeasurement(short* tmp_value)
{
  byte temp_registers_values[2];
  byte* p_temp_reg_val = temp_registers_values;   
    
  MPU3050_readN_ConsecutiveRegisters(0x1B, 2, temp_registers_values);   
 
  *(tmp_value) = *(p_temp_reg_val++) << 8; // save msb value
  *(tmp_value) |= *(p_temp_reg_val); // save also lsb value
}

/** */
void MPU3050_readTemperatureAndAngleMeasurement(short* temp_value, short* angle_values)
{
  byte i;
  byte tmp_registers_values[8];
  byte* p_tmp_reg_val = tmp_registers_values;
  
  MPU3050_readN_ConsecutiveRegisters(0x1B, 8, tmp_registers_values);
  
  *(temp_value) = *(p_tmp_reg_val++) << 8; // save msb value
  *(temp_value) |= *(p_tmp_reg_val++); // save also lsb value 
  
  for (i=0; i<3; i++)
  {
    *(angle_values) = *(p_tmp_reg_val++) << 8; // save msb value
    *(angle_values) |= *(p_tmp_reg_val++); // save also lsb value
    angle_values++;
  }   
}

void MPU3050_setBiasOffset(short x, short y, short z){  // 2's complementary 

  byte registry_data[6];
  
  registry_data[0] = x >> 8;
  registry_data[1] = x; // probably it will set lsb of x number
  
  registry_data[2] = y >> 8;
  registry_data[3] = y;
  
  registry_data[4] = z >> 8;
  registry_data[5] = z;
  
  MPU3050_setN_ConsecutiveRegisters(0x0C, 6, registry_data);
  
}

/**
DLPF_CFG  Low Pass Filter Bandwidth  Analog Sample Rate 
0           256Hz                           8kHz 
1           188Hz                           1kHz 
2           98Hz                            1kHz 
3           42Hz                            1kHz 
4           20Hz                            1kHz 
5           10Hz                            1kHz 
6           5Hz                             1kHz 
*/
void MPU3050_setBandwith(byte value)
{
  mpu3050.filter_bandwidth = value;
  
  value = (mpu3050.range << 3) | mpu3050.filter_bandwidth;
  
  MPU3050_setRegistry_data(0x16, value);    
}

/**
0  ±250°/sec 
1  ±500°/sec 
2  ±1000°/sec 
3  ±2000°/sec */
void MPU3050_setRange(byte value)
{ 
  mpu3050.range = value;
  
  value = (mpu3050.range << 3) | mpu3050.filter_bandwidth;
  
  MPU3050_setRegistry_data(0x16, value);   
}






/* END MPU3050 */
