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

void clearInteruptFlag(){
   
  setRegBit(IICS, IICIF);  // clear interrupt flag
}

void setTransmitMode(){
  //if(getRegBit(IICC1, TX)==0)
    setRegBit(IICC1, TX);
}

void setReceiveMode(){
  //if(getRegBit(IICC1, TX)==1)
    clrRegBit(IICC1, TX); 
}

void sendByteOfData(char data){

  setReg(IICD, data); // write sequence to sent  
}


void send_sequence_of_bytes(char* long_data){
}

void receiveByte_Ack(char* data){
}

void receiveByte_No_Ack(char* data){
}

/* END I2C_functions */
