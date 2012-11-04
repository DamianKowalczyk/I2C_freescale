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
#define BMA020_WR_ADDR        0x70      
#define BMA020_RD_ADDR        0x71

struct bma020_str 
{
  char reservedBitsFromRegistry_0x14;
  char accelerationMeasurementRange;
  char bandwidth;
};



/* END BMA020 */

#endif

