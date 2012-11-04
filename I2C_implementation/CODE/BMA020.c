/** ###################################################################
**     Filename  : BMA020.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-11-03, 08:36
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE BMA020 */
#include "I2C_functions.h"
#include "PE_Types.h"
#include "BMA020.h"

byte BMA020_readRegistry(byte reg_addr); 

struct bma020_str bma020;

/** function for initialize the BMA020 device for using it in the future here we should set the registries of device to 
    get correct values */
void BMA020_init()
{
  bma020.reservedBitsFromRegistry_0x14 = readRegistry(0x14) & 11100000;
  bma020.accelerationMeasurementRange = 0;
  bma020.bandwidth = 0; 
  
  BMA020_checkSensor(); 
}

void BMA020_readAccelerationValues(char* value_of_bytes)
{
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(0x02);
  I2C_SendStop();
  
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_RD_ADDR);
  I2C_Receive_N_Bytes(value_of_bytes, 6);
  I2C_SendStop(); 
}
  

// im not sure if this function will work ????
byte BMA020_readRegistry(byte reg_addr)
{
  byte data = 0;
  
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(reg_addr);
  I2C_SendStop();
  
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_RD_ADDR);
  I2C_ReceiveByte_No_Ack(&data);
  I2C_SendStop(); 
  
  return data;       
}

void BMA020_setRegistry(byte reg_addr, byte value)
{
  if (reg_addr == 0x14)
  {
    value = (value & 00011111) | reservedBitsFromRegistry_0x14; // Bits 5, 6 and 7 of register addresses 14h do contain 
                      //  critical sensor individual calibration data which must not be changed or deleted by any means.                                                                  
  } 
  else if (reg_addr == 0x0A) 
  {
    value &= 01001111;    //Bit 7, bit 5 and bit 4 of register 0Ah should be left at a value of '0'
  }
  
  // i2c comunication
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(reg_addr);
  I2C_SendByte_Ack(value);  
  I2C_SendStop();
}  



/** function sets the range of measurement accleration, and the bandwidth of digital filters 
    val_ran  range             val_band  bandwidth (Hz) 
    0    ->   +/- 2g            0    ->   25
    1    ->   +/- 4g            1    ->   50
    2    ->   +/- 8g            2    ->   100
                                3    ->   190
                                4    ->   375
                                5    ->   750
                                6    ->   1500
*/
void BMA020_setRangeAndBandwidth(byte val_ran, byte val_band){
  val_ran = (val_ran<<3) | val_band;
  
  BMA020_setRegistry(0x14, (val_ran));  
}


/** generate self test of sensor and get the results if correct return 0  */
bool BMA020_checkSensor()
{ 
  bool result = 0;
  byte endSelfTestFlag = 0;
                          
  BMA020_setRegistry(0x0A, (1<<2)); // start selfTest0
  
  do {
    waitForEndingMeasurement();  // in future time i should do something better than this
    endSelfTestFlag = BMA020_readRegistry(0x0A) & 00000100;
  } while (endSelfTestFlag != 0);  
  
  result = BMA020_readRegistry(0x09);
  
  result >>= 7;
  
  // maybe is possible to write it in different form???
  if (result == 1)
    return 0;
  else 
    return 1;  
}


/* END BMA020 */
