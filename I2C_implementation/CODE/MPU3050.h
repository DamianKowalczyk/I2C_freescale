/** ###################################################################
**     Filename  : MPU3050.H
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-11-04, 22:33
**     Contents  :
**         User source code
**
** ###################################################################*/

#ifndef __MPU3050_H
#define __MPU3050_H

/* MODULE MPU3050 */
#include "PE_Types.h"

#define MPU3050_WR_ADDR  0x68  // didnt know if this values are correct
#define MPU3050_RD_ADDR  0x69// necessary to check the connection on the board

struct MPU3050_str 
{
  byte range;
  byte filter_bandwidth;  
};

/* END MPU3050 */

#endif

