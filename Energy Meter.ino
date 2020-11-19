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
 // Init in receive mode
    digitalWrite(MAX485_RE_NEG, 0);
    digitalWrite(MAX485_DE, 0);
    Serial.begin(19200, SERIAL_8N1,3,1);
    node.begin(1, Serial); // Modbus slave ID 1
 // Callbacks allow us to configure the RS485 transceiver correctly
    node.preTransmission(preTransmission);
    node.postTransmission(postTransmission);
}
 
bool state = true;
 
void loop()
{

    uint16_t vl1, v11;
    uint8_t result1,result2,result3;
    float output,v,v1;
    result1 = node.readHoldingRegisters(0x0005,2);   //To get the output of word, uint(2 byte) data type
    if(result1 == node.ku8MBSuccess)
    {
      Serial.print("value = ");
      Serial.print(node.getResponseBuffer(0x00));
      Serial.print('\n');
      delay(1000);
    }

    result2 = node.readHoldingRegisters(0x0100,2); //To get the output of uint(4 byte) data type
    if(result2 == node.ku8MBSuccess)
    {
      Serial.print("Instantaneous Power: ");
      v = (node.getResponseBuffer(0x00)+(node.getResponseBuffer(0x01)<<16));
      output = v/1000;
      Serial.print(output,2);
      delay(1000);
    }

    result3 = node.readHoldingRegisters(0x015C,2);  //To get the output of float(4 byte) data type
    if(result3 == node.ku8MBSuccess)
    {
      vl1 = node.getResponseBuffer(0x01);
      v11 = node.getResponseBuffer(0x00);
      uint16_t data[2] = {v11, vl1};
      memcpy(&v1, data, 4);
      Serial.print("Voltage: ");
      Serial.println(v1);
      delay(1000);
    }
}
