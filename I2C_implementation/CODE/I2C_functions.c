/** ###################################################################
**     Filename  : I2C_functions.C
**     Project   : I2C_implementation
**     Processor : MCF51AC256ACLK
**     Compiler  : CodeWarrior ColdFireV1 C Compiler
**     Date/Time : 2012-10-20, 13:09
**     Contents  :
**         User source code
**
** ###################################################################*/

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */


/* MODULE I2C_functions */  

void sendStartSignal() {
  
  if(getRegBit(IICC1, MST)==1)
    clrRegBit(IICC1, MST);     
  
  setRegBit(IICC1, MST); // start signal: mst 0->1
}

void sendStopSignal(){

  if(getRegBit(IICC1, MST)==0)
    setRegBit(IICC1, MST);   // start signal: mst 0->1  
  
  clrRegBit(IICC1, MST); // stop signal: mst 1->0
}

void sendByte(char* data){

  //setRegBit(IICS, IICIF); // clear IICIF

  //setRegBit(IICC1, MST); // master mode
  
  //setReg(IICD, *data);
  
  //check if transmision was complete
    
}

void send_sequence_of_bytes(char* long_data){
}

void receiveByte_Ack(char* data){
}

void receiveByte_No_Ack(char* data){
}


int sendSampleDataToExpander(char number) 
{

  int delay = 65536;
  
  setRegBit(IICS, IICIF);  // clear interrupt flag   
  
  //setRegBit(IICC1, MST); // start signal - probably
  sendStartSignal();     
  
  setReg(IICD, 0b01111110); // address of expander + WR bit
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 7;
  
  setRegBit(IICS, IICIF);  // clear interrupt flag
    
  delay = 65535;  
  
  while(getRegBit(IICS, RXAK) && delay != 0)  // wait for ack
    delay--;
    
  if (delay==0)  // end if no ack get
    return 5;
  
  setReg(IICD, number); // write sequence to sent
  
  delay = 65535;
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct send
    return 8;
  
  setRegBit(IICS, IICIF);  // clear interrupt flag  
  
  delay = 65535;
  while(getRegBit(IICS, RXAK) && delay != 0)
    delay--;
    
  if (delay==0)
    return 6;
  
  //clrRegBit(IICC1, MST); // stop signal - probably  
  sendStopSignal();
  
  return 1;
  
  
    
}



// generate stop signal
// I2C Enable
// set I2C to Transfer mode
// set I2C to Receive mode









/* END I2C_functions */
