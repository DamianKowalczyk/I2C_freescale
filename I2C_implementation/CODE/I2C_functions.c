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

#define del                          65535         /* value of waiting time for IICIF or ACK from slave */
/* Include inherited beans */

void clearInteruptFlag();
void setTransmitMode();
void setReceiveMode();
void sendByteOfData(char data);


/* MODULE I2C_functions */  

void I2C_SendStart() 
{ 
  setTransmitMode(); 
  
  if(getRegBit(IICC1, MST)==1) //maybe i should wait after this change
    clrRegBit(IICC1, MST);     
  
  setRegBit(IICC1, MST); // start signal: mst 0->1
}

void I2C_SendStop()
{       
  setTransmitMode();

  if(getRegBit(IICC1, MST)==0)
    setRegBit(IICC1, MST);    
  
  clrRegBit(IICC1, MST); // stop signal: mst 1->0
} 

void I2C_SendRestart()   // i didnt check this function yet
{
  clearInteruptFlag();
  setTransmitMode();
  
  setRegBit(IICC1, RSTA); // repeat start
}

byte I2C_SendByte_Ack(char data)
{
  int delay = del;
      
  clearInteruptFlag();
  setTransmitMode();
      
  sendByteOfData(data);
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  
    return TRANSMISSION_FAILD;
    
  delay = del;  
  
  while(getRegBit(IICS, RXAK) && delay != 0)  // wait for ACK
    delay--;
    
  if (delay==0)  
    return NO_ACK_RECEIVED;  
  
  return OK;
}

byte I2C_SendByte_No_Ack(char data)
{                         
  int delay = del;
      
  clearInteruptFlag();
  setTransmitMode();
     
  sendByteOfData(data);
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  
    return TRANSMISSION_FAILD;
  
  return OK;  
}

// this function sends stop signal before end to get information from IICD registry
byte I2C_ReceiveByte_No_Ack(char* data)
{
  int delay = del;

  clearInteruptFlag();
  
  setReceiveMode();  
  
  setRegBit(IICC1, TXAK);  // No acknowledge signal response is sent
  getReg(IICD);    
  
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct sent
    return TRANSMISSION_FAILD;   
  
  I2C_SendStop();   
  
  *data = getReg(IICD);
  
  setTransmitMode(); 
  
  return OK; 
}

byte I2C_Receive_N_Bytes(char* data, byte n)   // i'm not sure about byte value - how exacly it is interpreted
{
  int delay = del;
  
  if (n==1)
  {
  
    clearInteruptFlag();
    setReceiveMode();
    
    setRegBit(IICC1, TXAK);  // No acknowledge signal response is sent
    getReg(IICD);
    
    while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
    if (delay==0)  // if the byte was not correct sent
      return TRANSMISSION_FAILD;
       
  } 
  else if(n>1)
  {
    
    clearInteruptFlag();
    setReceiveMode();
    
    clrRegBit(IICC1, TXAK);  // ACK signal response is sent
    getReg(IICD);
    
    delay = del;
    while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
    if (delay==0)  // if the byte was not correct sent
      return TRANSMISSION_FAILD;
    
    for(n; n>1; n--)
    {
      clearInteruptFlag();
      
      if((n-1)==1)
        setRegBit(IICC1, TXAK);  // No acknowledge signal response is sent
        
      *data = getReg(IICD);
      
      delay = del;
      while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
      delay--;
      
      if (delay==0)  // if the byte was not correct sent
        return TRANSMISSION_FAILD;
      
      data++;  
    }    
  }
  
  I2C_SendStop();
  
  *data = getReg(IICD);
  
  delay = del;
  while(getRegBit(IICS, IICIF) == 0 && delay != 0)  // wait for copletly sent byte
    delay--;
    
  if (delay==0)  // if the byte was not correct sent
    return TRANSMISSION_FAILD;
  
  return OK;    
}                                            




void clearInteruptFlag()
{                   
  setRegBit(IICS, IICIF);  // clear interrupt flag
}

void setTransmitMode()
{
  setRegBit(IICC1, TX);
}

void setReceiveMode()
{
  clrRegBit(IICC1, TX); 
}

void sendByteOfData(char data)
{      
  setReg(IICD, data); // write sequence to sent  
}

/* END I2C_functions */
