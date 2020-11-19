#include <ModbusMaster.h>
#define MAX485_DE 4
#define MAX485_RE_NEG 15
ModbusMaster node;
 
void preTransmission()
{
    digitalWrite(MAX485_RE_NEG, 1);
    digitalWrite(MAX485_DE, 1);
}
 
void postTransmission()
{
    digitalWrite(MAX485_RE_NEG, 0);
    digitalWrite(MAX485_DE, 0);
}
 
void setup()
{
    pinMode(MAX485_RE_NEG, OUTPUT);
    pinMode(MAX485_DE, OUTPUT);
 
    digitalWrite(MAX485_RE_NEG, 0);
    digitalWrite(MAX485_DE, 0);
    Serial.begin(19200, SERIAL_8N1,3,1); //(Baud rate = 19200, Configuration = [8 Data bits,No parity,1 Stop bit], Rx pin, Tx pin)
    node.begin(1, Serial);                 // Modbus slave ID 1

 // Callbacks allow us to configure the RS485 transceiver correctly
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
}
 
bool state = true;

uint16_t V1,V2,C1,C2,P1,P2;
uint8_t result1,result2,result3,result4,result5;
float v1,c1,p1,energy,e1;

void loop()
{
  result1 = node.readHoldingRegisters(0x0100,2); //This loop is to get the output of 4 bytes (Float datatype) [readHoldingRegisters(Address of the register, Number of registers want to be read from this address)]
  if (result1 == node.ku8MBSuccess)
  {
    V1 = node.getResponseBuffer(0x00);
    V2 = node.getResponseBuffer(0x01);
    uint16_t data[2] = {V1, V2};
    memcpy(&v1, data, 4);
    Serial.print("Phase A Voltage: ");
    Serial.print(v1,2);
    Serial.println(" V");
    delay(1000);
  }

  result2 = node.readHoldingRegisters(0x0120,2); //This loop is to get the output of 4 bytes (Float datatype)
  if (result2 == node.ku8MBSuccess)
  {
    C1 = node.getResponseBuffer(0x00);
    C2 = node.getResponseBuffer(0x01);
    uint16_t data[2] = {C1, C2};
    memcpy(&c1, data, 4);
    Serial.print("Phase A Current: ");
    Serial.print(c1,3);
    Serial.println(" A");
    delay(1000);
  }

  result3 = node.readHoldingRegisters(0x0134,2); //This loop is to get the output of 4 bytes (Float datatype)
  if (result3 == node.ku8MBSuccess)
  {
    P1 = node.getResponseBuffer(0x00);
    P2 = node.getResponseBuffer(0x01);
    uint16_t data[2] = {P1, P2};
    memcpy(&p1, data, 4);
    Serial.print("Phase A Power: ");
    Serial.print(p1,3);
    Serial.println(" W");
    delay(1000);
  }

   result4 = node.readHoldingRegisters(0x015C,2); //This loop is to get the output of 4 bytes (uint datatype)
    if(result4==node.ku8MBSuccess)
    {
      energy =((node.getResponseBuffer(0x01)<<16) + node.getResponseBuffer(0x00));
      float e1=energy/1000;
      Serial.print("Energy= ");
      Serial.print(e1,3);
      Serial.println(" kWh");
      delay(1000);
    }

    result5 = node.readHoldingRegisters(0x0004,1); //This loop is to get the output of 2 bytes (uint,word datatype)
    if(result5==node.ku8MBSuccess)
    {
      Serial.print("Second= ");
      Serial.println(node.getResponseBuffer(0x00));
      Serial.println("  ");
      delay(1000);
    }  
}
