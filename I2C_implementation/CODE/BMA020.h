/** ###################################################################
**     Filename  : BMA020.H
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-11-03, 08:36
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __BMA020_H
#define __BMA020_H

/* MODULE BMA020 */
#define BMA020_WR_ADDR           0x70      
#define BMA020_RD_ADDR           0x71 

#define COEF_RANGE_2G            3906
#define COEF_RANGE_4G            7812
#define COEF_RANGE_8G           15625

/*
#define DIVIDER_RANGE_2G         1000
#define DIVIDER_RANGE_4G         1000
#define DIVIDER_RANGE_8G         1000

#define BASE_RANGE_2G           -2000
#define BASE_RANGE_4G           -4000
#define BASE_RANGE_8G           -8000
*/

struct bma020_str 
{
  char reservedBitsFromRegistry_0x14;
  char accelerationMeasurementRange;
  char filterBandwidth;
  
  unsigned long int coefficient;
};



/* END BMA020 */        

#endif

