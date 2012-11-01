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

unsigned short BMP085readData(byte registry_address);

bmp085_t *p_bmp085 = 0;                      /**< pointer to SMD500 / BMP085 device area */


struct bmp085_calibration_parameters bmp085_cal_param;


void get_calibration_coefficients() 
{
  unsigned short data[BMP085_NUMBER_OF_CAL_PARAMETERS];    
  int i, j;
  
// for sure write 0 to all places into this memory
  // delete this lines after tests
  bmp085_cal_param.ac1 = 0;
  bmp085_cal_param.ac2 = 0;
  bmp085_cal_param.ac3 = 0;
  bmp085_cal_param.ac4 = 0;
  bmp085_cal_param.ac5 = 0;
  bmp085_cal_param.ac6 = 0;
  bmp085_cal_param.b1 = 0;
  bmp085_cal_param.b2 = 0;
  bmp085_cal_param.mb = 0;
  bmp085_cal_param.mc = 0;
  bmp085_cal_param.md = 0;
/////////////////////////////////////
  
    
  for(i=0, j=0; i<BMP085_NUMBER_OF_CAL_PARAMETERS; i++, j+=2)
    data[i] = BMP085readData(BMP085_PROM_START_ADDR+j);
  
  /*parameters AC1-AC6*/  
  bmp085_cal_param.ac1 = data[0];
  bmp085_cal_param.ac2 = data[1];
  bmp085_cal_param.ac3 = data[2];
  bmp085_cal_param.ac4 = data[3];
  bmp085_cal_param.ac5 = data[4];
  bmp085_cal_param.ac6 = data[5];
  
  /*parameters B1,B2*/
  bmp085_cal_param.b1 = data[6];
  bmp085_cal_param.b2 = data[7];
  
  /*parameters MB,MC,MD*/
  bmp085_cal_param.mb = data[8];
  bmp085_cal_param.mc = data[9];
  bmp085_cal_param.md = data[10];
  
}

unsigned short get_temperature() 
{ 
  unsigned short data = 0;
  
  // wait value of time
  
   
 
}

void get_pressure() 
{

}

void change_pressure_mode() //additional
{

}

/** calculate temperature from ut
  ut was read from the device via I2C and fed into the right calc path for BMP085
  \param ut parameter ut read from device
  \return temperature in steps of 0.1 deg celsius
  \see bmp085_read_ut()
*/
short calculate_temperature(unsigned short ut)
{
  short temperature =0;
  long x1,x2;
  
  x1 = (((long) ut - (long) bmp085_cal_param.ac6) * (long) bmp085_cal_param.ac5) >> 15;
  x2 = ((long) bmp085_cal_param.mc << 11) / (x1 + bmp085_cal_param.md);
    
  temperature = ((x1 + x2 + 8) >> 4);  // temperature in 0.1°C
  
  return temperature;
}

/** calculate pressure from up
  up was read from the device via I2C and fed into the right calc path for either SMD500 or BMP085
  In case of SMD500 value averaging is done in this function, in case of BMP085 averaging is done through oversampling by the sensor IC

  \param ut parameter ut read from device
  \return temperature in steps of 1.0 Pa
  \see bmp085_read_up()
*/
unsigned short convert_pressure(unsigned short data)
{
  unsigned short pressure =0;
  
  // write here code
  
  return pressure;
}



//long bmp085_calc_pressure(unsigned long up)
long bmp085_get_pressure(unsigned long up)
{
   long pressure,x1,x2,x3,b3,b6;
   unsigned long b4, b7;
   
   b6 = p_bmp085->param_b5 - 4000;
   //*****calculate B3************
   x1 = (b6*b6) >> 12;	 	 
   x1 *= p_bmp085->cal_param.b2;
   x1 >>=11;

   x2 = (p_bmp085->cal_param.ac2*b6);
   x2 >>=11;

   x3 = x1 +x2;

	b3 = (((((long)p_bmp085->cal_param.ac1 )*4 + x3) <<p_bmp085->oversampling_setting) + 2) >> 2;

   //*****calculate B4************
   x1 = (p_bmp085->cal_param.ac3* b6) >> 13;
   x2 = (p_bmp085->cal_param.b1 * ((b6*b6) >> 12) ) >> 16;
   x3 = ((x1 + x2) + 2) >> 2;
   b4 = (p_bmp085->cal_param.ac4 * (unsigned long) (x3 + 32768)) >> 15;
     
   b7 = ((unsigned long)(up - b3) * (50000>>p_bmp085->oversampling_setting));   
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
   x1 = (x1 * SMD500_PARAM_MG) >> 16;
   x2 = (pressure * SMD500_PARAM_MH) >> 16;
   pressure += (x1 + x2 + SMD500_PARAM_MI) >> 4;	// pressure in Pa  

   return (pressure);
}




unsigned short BMP085readData(byte registry_address) 
{
// after first worked tests i have to check if it will work for byte 
  unsigned short data[] = {0,0};
      
  I2C_SendStart();
  I2C_SendByte_Ack(BMP085_I2C_WR_ADDR);
  I2C_SendByte_Ack(registry_address);
  I2C_SendRestart();
  I2C_SendByte_Ack(BMP085_I2C_RD_ADDR);
  I2C_Receive_N_Bytes(data, 2);
  I2C_SendStop();
  
  return data[0]<<8 | data[1];      
}

/* END BMP085 */
