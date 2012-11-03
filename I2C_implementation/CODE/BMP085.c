/** ###################################################################
**     Filename  : BMP085.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-28, 22:36
**     Contents  :
**         User source code
**
** ###################################################################*/

          /* Temperature and pressure sensor */

/* MODULE BMP085 */ 
#include "BMP085.h"
#include "I2C_functions.h"

unsigned short BMP085_readData(byte registry_address);
void BMP085_get_calibration_coefficients();

/** structure to hold all calibration coefficients and other neccesary parameters */
struct bmp085_str bmp085;
  
/** call this funtion on the start before measure temperature or pressure*/
void BMP085_init(){
  bmp085.oversampling_setting = 0;  //valid only for ultra low power mode
  
  get_calibration_coefficients();
}

void BMP085_get_calibration_coefficients() 
{
  short data[BMP085_NUMBER_OF_CAL_PARAMETERS];    
  int i, j;
  
// for sure write 0 to all places into this memory
  // delete this lines after tests
  bmp085.cal_param.ac1 = 0;
  bmp085.cal_param.ac2 = 0;
  bmp085.cal_param.ac3 = 0;
  bmp085.cal_param.ac4 = 0;
  bmp085.cal_param.ac5 = 0;
  bmp085.cal_param.ac6 = 0;
  bmp085.cal_param.b1 = 0;
  bmp085.cal_param.b2 = 0;
  bmp085.cal_param.mb = 0;
  bmp085.cal_param.mc = 0;
  bmp085.cal_param.md = 0;
/////////////////////////////////////
  
    
  for(i=0, j=0; i<BMP085_NUMBER_OF_CAL_PARAMETERS; i++, j+=2)
    data[i] = BMP085_readData(BMP085_PROM_START_ADDR+j);
  
  /*parameters AC1-AC6*/  
  bmp085.cal_param.ac1 = data[0];
  bmp085.cal_param.ac2 = data[1];
  bmp085.cal_param.ac3 = data[2];
  bmp085.cal_param.ac4 = data[3];
  bmp085.cal_param.ac5 = data[4];
  bmp085.cal_param.ac6 = data[5];
  
  /*parameters B1,B2*/
  bmp085.cal_param.b1 = data[6];
  bmp085.cal_param.b2 = data[7];
  
  /*parameters MB,MC,MD*/
  bmp085.cal_param.mb = data[8];
  bmp085.cal_param.mc = data[9];
  bmp085.cal_param.md = data[10];
  
}

/* after test i should change the way of measure waiting time */
unsigned long BMP085_get_temperature() 
{ 
  unsigned long temperature = 0;
  int i, j; 
  
  I2C_SendStart();
  I2C_SendByte_Ack(BMP085_I2C_WR_ADDR);
  I2C_SendByte_Ack(0xF4);    
  I2C_SendByte_Ack(0x2E);
  I2C_SendStop();
  
  // wait 4.5 ms
  for (i=0;i<5;i++)
    for (j=0; j<16000; j++)
      ;  
  
  temperature = BMP085_readData(0xF6); 
  
  return temperature; 
}

/* after test i should change the way of measure waiting time and maybe it will be neccesary to implement some case to use different modes*/ 
unsigned long BMP085_get_pressure() 
{
  unsigned long pressure = 0;   
  int i, j; 
  byte reg_value = (bmp085.oversampling_setting << 8) + 0x34;
  
  I2C_SendStart();
  I2C_SendByte_Ack(BMP085_I2C_WR_ADDR);
  I2C_SendByte_Ack(0xF4);     
  I2C_SendByte_Ack(reg_value);
  I2C_SendStop();
  
  // wait time proportional to the setting 
    // for now it is only one mode: ultra low power 
  for (i=0;i<5;i++)
    for (j=0; j<16000; j++)
      ;  
  
  
  // if we will use different mode we should make some changes in code below
  pressure = BMP085_readData(0xF6); 
  
  return pressure; 
}   

/** calculate temperature from ut
  ut was read from the device via I2C
  \param ut parameter ut read from device
  \return temperature in steps of 0.1 deg celsius
*/
short BMP085_calculate_temperature(unsigned long ut)
{
  short temperature =0;
  long x1,x2;
  
  x1 = (((long) ut - (long) bmp085.cal_param.ac6) * (long) bmp085.cal_param.ac5) >> 15;
  x2 = ((long) bmp085.cal_param.mc << 11) / (x1 + bmp085.cal_param.md);
  bmp085.param_b5 = x1 + x2;
    
  temperature = ((bmp085.param_b5 + 8) >> 4);  // temperature in 0.1°C
  
  return temperature;
}


/** calculate pressure from up
  up was read from the device via I2C
  \param ut parameter ut read from device
  \return pressure in steps of 1.0 Pa
*/
long BMP085_calculate_pressure(unsigned long up)
{
   long pressure,x1,x2,x3,b3,b6;
   unsigned long b4, b7;
   
   b6 = bmp085.param_b5 - 4000;
   //*****calculate B3************
   x1 = (b6*b6) >> 12;	 	 
   x1 *= bmp085.cal_param.b2;
   x1 >>=11;

   x2 = (bmp085.cal_param.ac2*b6);
   x2 >>=11;

   x3 = x1 + x2;

   b3 = (((((long)bmp085.cal_param.ac1 )*4 + x3) <<bmp085.oversampling_setting) + 2) >> 2;

   //*****calculate B4************
   x1 = (bmp085.cal_param.ac3* b6) >> 13;
   x2 = (bmp085.cal_param.b1 * ((b6*b6) >> 12) ) >> 16;
   x3 = ((x1 + x2) + 2) >> 2;
   b4 = (bmp085.cal_param.ac4 * (unsigned long) (x3 + 32768)) >> 15;
     
   b7 = ((unsigned long)(up - b3) * (50000>>bmp085.oversampling_setting));   
   if (b7 < 0x80000000)
   {
     pressure = (b7 << 1) / b4;
   }
   else
   { 
     pressure = (b7 / b4) << 1;
   }
   
   x1 = pressure >> 8;
   x1 *= x1;
   x1 = (x1 * 3038) >> 16;
   x2 = (pressure * (-7357)) >> 16;
   pressure += (x1 + x2 + 3791) >> 4;	// pressure in Pa  

   return (pressure);
}

/** function for reading coefficients, temperature and pressure from registers*/
unsigned short BMP085_readData(byte registry_address) 
{
// after first worked tests i have to check if it will work for byte 
  unsigned short data[] = {0,0};
      
  I2C_SendStart();
  I2C_SendByte_Ack(BMP085_I2C_WR_ADDR);
  I2C_SendByte_Ack(registry_address);
  I2C_SendRepeatStart();
  I2C_SendByte_Ack(BMP085_I2C_RD_ADDR);
  I2C_Receive_N_Bytes(data, 2);
  I2C_SendStop();
  
  return data[0]<<8 | data[1];      
}

void BMP085_change_pressure_mode() //additional
{
  // attention if we want to change mode we should set the oversampling member to correct value

}

/* END BMP085 */
