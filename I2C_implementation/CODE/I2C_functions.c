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
#include "IO_Map.h"

#define OK                           0             /* transmission successfull */
#define TRANSMISSION_FAILD           1             /* transmission faild */
#define NO_ACK_RECEIVED              2             /* device didn't send ACK */
/* Include inherited beans */


/* MODULE I2C_functions */  

void I2C_SendStart() {
  
  if(getRegBit(IICC1, MST)==1) //maybe i should wait after this change
    clrRegBit(IICC1, MST);     
  
  setRegBit(IICC1, MST); // start signal: mst 0->1
}

void I2C_SendStop(){

  if(getRegBit(IICC1, MST)==0)
    setRegBit(IICC1, MST);    
  
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


byte I2C_SendByte_Ack(char data){
  int delay = 65535;
      
  clearInteruptFlag();
  setTransmitMode();
    
  I2C_SendStart();    
  sendByteOfData(data);
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  
    return TRANSMISSION_FAILD;
  
  clearInteruptFlag();
    
  delay = 65535;  
  
  while(getRegBit(IICS, RXAK) && delay != 0)  // wait for ACK
    delay--;
    
  if (delay==0)  
    return NO_ACK_RECEIVED;  
  
  return OK;
}

byte I2C_SendByte_No_Ack(char data){

  int delay = 65535;
      
  clearInteruptFlag();
  setTransmitMode();
      
  I2C_SendStart();     
  sendByteOfData(data);
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  
    return TRANSMISSION_FAILD;
  
  clearInteruptFlag();
  
  
  
}


void send_sequence_of_bytes(char* long_data){
}

void I2C_ReceiveByte_Ack(char* data){
}

void I2C_ReceiveByte_No_Ack(char* data){
}

/* END I2C_functions */
