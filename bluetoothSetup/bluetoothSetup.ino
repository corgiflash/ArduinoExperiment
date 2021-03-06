#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); 
char c = ' ';
boolean NL = true;

void setup() 
{
      Serial.begin(9600);      
      // FC-114 default baud rate is 9600
      BTSerial.begin(9600);  
      Serial.println("BTserial started at 9600");
      
}

void loop()
{

    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTSerial.available())
    {
        c = BTSerial.read();
        Serial.write(c);
    }
    
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
        BTSerial.write(c);   
        
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }

}

