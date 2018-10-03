#include <CapacitiveSensor.h>
#include <Plotter.h>


CapacitiveSensor   cs_9_10 = CapacitiveSensor(9,10);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

long x;
Plotter p;

void setup()                    
{
  // cs_9_10.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   p.Begin();
   p.AddTimeGraph( "Time/capacitve", 500, "capacitve", x );
}
void loop() 
{                   

    long start = millis();
    long total1 =  cs_9_10.capacitiveSensor(30);

    Serial.print(millis() - start); ;        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    x = total1;
    p.Plot();
    Serial.print(x);                  // print sensor output 1
    Serial.println("");

    delay(1000);                         // 1 seconds
}
