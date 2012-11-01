/** ###################################################################
**     Filename  : BMP085.H
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-28, 22:36
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __BMP085_H
#define __BMP085_H

/* MODULE BMP085 */
#include "PE_Types.h"

/* BMP085 I2C Address */    
#define BMP085_I2C_WR_ADDR		    0b11101110
#define BMP085_I2C_RD_ADDR	    	0b11101111

#define BMP085_PROM_START_ADDR		0xAA 
#define BMP085_T_MEASURE          0x2E				// temperature measurent 
#define BMP085_P_MEASURE          0x34				// pressure measurement

#define BMP085_NUMBER_OF_CAL_PARAMETERS 11

/** this structure holds all device specific calibration parameters 
*/
struct bmp085_calibration_parameters 
{   
   short ac1;
   short ac2;
   short ac3;
   unsigned short ac4;
   unsigned short ac5;
   unsigned short ac6;
   short b1;
   short b2;
   short mb;
   short mc;
   short md;      		   
}; 

/** BMP085 image registers data structure
  // probably some of this fields are not neccessary if not delete it after tests
*/
struct bmp085_str 
{	
  struct bmp085_calibration_parameters cal_param;		
	long param_b5;
	short oversampling_setting;
};


/* END BMP085 */

#endif

