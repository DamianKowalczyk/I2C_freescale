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
#include "I2C_functions.h"

bmp085_calibration_parameters *p_cal_param = 0;                      /**< pointer to BMP085 device area */

void get_calibration_coefficients() 
{
  unsigned char data[BMP085_PROM_DATA_LEN];
  
  // for sure write 0 to all places into this memory
  
  
  
  
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

// helper functions to get correct results
unsigned short convert_temperature(unsigned short data){
  unsigned short temperature =0;
  
  // write here code
  
  return temperature;
}

unsigned short convert_pressure(unsigned short data){
  unsigned short pressure =0;
  
  // write here code
  
  return pressure;
}

/* END BMP085 */
