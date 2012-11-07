/** ###################################################################
**     Filename  : delay.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-11-04, 22:54
**     Contents  :
**         User source code
**
** ###################################################################*/

/* MODULE delay */

void waitForBMP085(){
  int j;  
    for (j=0; j<40; j++)
      ;  
}

void waitForMeassure(){
  char i;
  unsigned long j;
  for (i=0; i<2; i++)  
    for (j=0; j<1600000; j++)
      ;  
}

void waitForHMC588L(){
   int j;
   unsigned char i;
   for (i=0; i<10; i++)  
    for (j=0; j<16000; j++)
      ;    
}

/* END delay */
