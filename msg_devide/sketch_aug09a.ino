#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
long unsigned int CMD;  
long unsigned int SID;
long unsigned int DID;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128]; 

#define CAN0_INT 2                  
MCP_CAN CAN0(10);         

void setup()
{
    Serial.begin(115200);
    if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    CAN0.setMode(MCP_NORMAL);
    pinMode(CAN0_INT, INPUT);    

}
  
void loop()
{
      if(!digitalRead(CAN0_INT))                        
         {
              CAN0.readMsgBuf(&rxId, &len, rxBuf);    
              rxId =  (rxId & 0x1FFFFFFF);

              FindID(rxId);
             
              sprintf(msgString, "rxId: 0x%.8lX, CMD: %.2lX , SID: %.3lX, DID:%.3lX ", rxId, CMD, SID, DID);
              
              Serial.print(msgString);
              Serial.println();
          }
}

void FindID(long unsigned int rxId){
          CMD = ((rxId & 0x1FFFFFFF) & 0x1F);
          SID = ((rxId & 0x1FFFFFFF) << 8) >> 20;
          DID = ((rxId & 0x1FFFFFFF) << 20) >> 20;
}




