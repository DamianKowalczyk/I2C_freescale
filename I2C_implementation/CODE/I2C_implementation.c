/** ###################################################################
**     Filename  : I2C_implementation.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Version   : Driver 01.00
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-17, 16:00
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE I2C_implementation */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "IIC2.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"


void wait()
{
  int a,b;
  for (a=0; a<100; a++)
      for (b=0; b<24000; b++)
        ;    
}

/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  byte i = 0;
  byte j;
  char results[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
  char dataFromExpander[] = {0,0,0,0,0,0,0,0,0,0};      
  int dataFromTerm[] = {0,0,0,0,0,0,0,0,0,0}; 
  short BMP085_temper[] = {0,0,0,0,0,0,0,0,0,0};
  long BMP085_pressure[] = {0,0,0,0,0,0,0,0,0,0};   
  unsigned long tmp;
  int connectionProblemdataFromTerm[] = {0,0,0,0,0,0,0,0,0,0};
  short HMC5883L_magnetic[30][3];
  short self_test_values[]= {0,0,0};
  byte accelerometer_selftest;
  short acceler_val[10][3];
  byte accel_registry[22];
    
  
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  /* 
  for (j=0, i=0;j<10;j++)
  {    
    results[i] = sendSampleDataToExpander(0b10101010);
    i++;
    wait();
    results[i] = sendSampleDataToExpander(0b01010101);
    i++;
    wait();      
  }  
  */   
  /*
  for (j=0;j<10;j++)
  {    
    results[j] = getSampleDataFromExpander(&dataFromExpander[j]);     
    wait();  
  }
  */
    /* 
  for (j=0;j<10;j++)
  {    
    results[j] = getTemperature(&dataFromTerm[j]);
    wait();    
  }
  */
  /*   
  for (j=0;j<10;j++)
  {    
    checkTemperature(&dataFromTerm[j]);
    wait();    
  } 
  */
  
  /* 
  for (j=0;j<10;j++)
  {    
    results[j] = readTemperatureAfterSetingPointer(&connectionProblemdataFromTerm[j]);
    wait();    
  } 
  */
    
  /*    
    // BMP085 check temperature     
  BMP085_init();  
  
  for (j=0;j<10;j++)
  {  
    tmp = BMP085_get_temperature();
    BMP085_temper[j] = BMP085_calculate_temperature(tmp);  
  }
    
  leds_PutVal(15);
  */

  /*
    // BMP085 check pressure 
  BMP085_init();  
  
  for (j=0;j<10;j++)
  {  
    tmp = BMP085_get_pressure();
    
    BMP085_pressure[j] = BMP085_calculate_pressure(tmp);
    waitForMeassure();  
  }
  leds_PutVal(15);
  */
  /*  // BMP085 check temperature and pressure 
  BMP085_init();    
  for (j=0;j<10;j++)
  {  
    BMP085_getTemperatureAndPressure(&BMP085_temper[j], &BMP085_pressure[j]);
    waitForMeassure();  
  }
  leds_PutVal(15);  */   
   
  //HMC5883L_generateSelfTest(self_test_values); 
    
  /* // get values from magnetrometer
  for (j=0;j<30;j++)
  {  
    HMC5883L_getValues_SingleMeassure(&HMC5883L_magnetic[j][0]);
    waitForHMC588L();        
  } 
  leds_PutVal(15);
  */
  
  //accelerometer
  //accelerometer_selftest = BMA020_init();
  
  checSpecifiedRegistersIntoAccelerometer(accel_registry);
  
  
  for (j=0;j<30;j++)
  {  
    BMA020_getAcceleration(&acceler_val[j][0]);
    waitForHMC588L();        
  } 
  leds_PutVal(15);  
  
    
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END I2C_implementation */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale ColdFireV1 series of microcontrollers.
**
** ###################################################################
*/
