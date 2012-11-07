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
bool BMA020_checkSensor(); 

struct bma020_str bma020;

/** function reads necessary parameters from device and checks if device works correctly 
*/
bool BMA020_init()
{
  bma020.reservedBitsFromRegistry_0x14 = BMA020_readRegistry(0x14) & 11100000;
  bma020.accelerationMeasurementRange = 0; // default values after
  bma020.filterBandwidth = 0;       // power on are 0
  bma020.coefficient = COEF_RANGE_2G; 
  
  return BMA020_checkSensor(); 
}

void BMA020_readAccelerationValues(unsigned char* bytes_val)
{
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(0x02);
  I2C_SendStop();
  
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_RD_ADDR);
  I2C_Receive_N_Bytes(bytes_val, 6);
  //I2C_SendStop(); 
}

void BMA020_convertAccelerationValues(unsigned char* bytes_val, short* acceler_val)
{
  char i, j;
  unsigned long int tmp_result = 0;
  unsigned short tmp_val_lsb = 0;
  unsigned short tmp_val_msb = 0;
  unsigned short sign = 0;

  for (i=0, j=0; i<3; i++, j+=2)
  {
    tmp_val_lsb = *(bytes_val + j) >> 6;
    tmp_val_msb = *(bytes_val + j +1) & 0b01111111;
    tmp_val_msb <<= 2;
    sign = *(bytes_val + j +1) & 0b10000000;

    tmp_result = tmp_val_lsb | tmp_val_msb;
    tmp_result = (tmp_result * bma020.coefficient)/ 1000;

    if (sign) //if the negative number
    {
      *(acceler_val+i) = (-1) * (short) tmp_result; // change sign of this number make it negatibe
    }
    else
    {
      *(acceler_val+i) = (short) tmp_result;
    }
  }
}

void BMA020_getAcceleration(short* acceler_val) 
{
  unsigned char bytesFromAccel[6];
  BMA020_readAccelerationValues(bytesFromAccel);
  BMA020_convertAccelerationValues(bytesFromAccel, acceler_val);  
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
  //I2C_SendStop(); check it!!! 
  
  return data;       
}

void BMA020_setRegistry(byte reg_addr, byte value)
{
  if (reg_addr == 0x14)
  {
    value = (value & 0b00011111) | bma020.reservedBitsFromRegistry_0x14; // Bits 5, 6 and 7 of register addresses 14h do contain 
                      //  critical sensor individual calibration data which must not be changed or deleted by any means.                                                                  
  } 
  else if (reg_addr == 0x0A) 
  {
    value &= 0b01001111;    //Bit 7, bit 5 and bit 4 of register 0Ah should be left at a value of '0'
  }           
            // i2c comunication
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(reg_addr);
  I2C_SendByte_Ack(value);  
  I2C_SendStop();
}  



/** function sets the range of measurement accleration 
   val_ran   range              
    0    ->   +/- 2g            
    1    ->   +/- 4g            
    2    ->   +/- 8g */
void BMA020_setRangeAndBandwidth(byte val_ran)
{
  bma020.accelerationMeasurementRange = val_ran;
  
  switch (val_ran) 
  {
    case 0:
      bma020.coefficient = COEF_RANGE_2G;
      break;
    case 1:
      bma020.coefficient = COEF_RANGE_4G;
      break;
    case 2:
      bma020.coefficient = COEF_RANGE_8G;
      break;
  }
  
  val_ran = val_ran<<3 | bma020.filterBandwidth;
  
  BMA020_setRegistry(0x14, val_ran);  
}

/** function sets the bandwidth of digital filters
val_band  bandwidth (Hz) 
  0    ->   25
  1    ->   50
  2    ->   100
  3    ->   190
  4    ->   375
  5    ->   750
  6    ->   1500 */
void BMA020_setBandwidth(byte val_band)
{
  bma020.filterBandwidth = val_band;
  
  val_band = bma020.accelerationMeasurementRange <<3 | val_band;
  
  BMA020_setRegistry(0x14, val_band);  
}


/** generate self test of sensor and get the results if correct return 0  */
bool BMA020_checkSensor()
{ 
  bool result = 0;
  byte endSelfTestFlag = 0;
                          
  BMA020_setRegistry(0x0A, (1<<2)); // start selfTest0
  
  do {
    waitForEndingMeasurement();  // in future time i should do something better than this
    endSelfTestFlag = BMA020_readRegistry(0x0A) & 0b00000100;
  } while (endSelfTestFlag != 0);  
  
  result = BMA020_readRegistry(0x09);
  
  result >>= 7;
  
  // maybe is possible to write it in different form???
  // return (result == 1) ? 0 : 1; 
  
  if (result == 1)
    return 0;
  else 
    return 1;  
}


void checRegistersIntoAccelerometer(byte* bytes_val)
{
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(0x00);
  I2C_SendStop();
  
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_RD_ADDR);
  I2C_Receive_N_Bytes(bytes_val, 22);         
}

void checSpecifiedRegistersIntoAccelerometer(byte* values)
{
  byte i;
  byte regist[22];
  regist[0] = 0;
  regist[1] =0;
  
  /*I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(0x14);  
  I2C_SendByte_Ack(0xFF);
  I2C_SendByte_Ack(0x15);
  I2C_SendByte_Ack(0xFF);
  
  I2C_SendStop();
  
   waitForHMC588L();
  
  /*
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(0x15);
  I2C_SendByte_Ack(0x0F);  
  I2C_SendStop();*/
   
   waitForHMC588L();   

  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_WR_ADDR);
  I2C_SendByte_Ack(0x0C);
  I2C_SendStop();
  
  waitForHMC588L();
  
  I2C_SendStart();
  I2C_SendByte_Ack(BMA020_RD_ADDR);
  I2C_Receive_N_Bytes(regist, 10);
  
  values = regist;
  
  i= 0;         
}

/* END BMA020 */
