#include <CapPin.h>
#include <CapScroll.h>
#include <CapSlider.h>
#include <CapTouch.h>
#include <Keyboard.h>



CapPin cPin_10 = CapPin(10);    // read pin 10 (D10 on Flora) - connect to NES B
CapPin cPin_9  = CapPin(9);     // read pin 9 (D9 on Flora)   - connect to NES A
CapPin cPin_6  = CapPin(6);     // read pin 6 (D6 on Flora)   - connect to NES Start
CapPin cPin_12 = CapPin(12);    // read pin 12 (D12 on Flora) - connect to NES Select
CapPin cPin_1  = CapPin(1);     // read pin 1 (TX on Flora)   - connect to NES right
CapPin cPin_0  = CapPin(0);     // read pin 0 (RX on Flora)   - connect to NES up
CapPin cPin_2  = CapPin(2);     // read pin 2 (SDA on Flora)  - connect to NES left
CapPin cPin_3  = CapPin(3);     // read pin 3 (SCL on Flora)  - connect to NES down

CapPin pins[] = {cPin_10, cPin_9, cPin_6, cPin_12, cPin_1, cPin_0, cPin_2, cPin_3};

char Keys[] =   {  'a',    'b',    ' ',     KEY_RETURN, KEY_RIGHT_ARROW, KEY_UP_ARROW, KEY_LEFT_ARROW, KEY_DOWN_ARROW};

boolean currentPressed[] = {false, false, false, false, false, false, false, false};

// set the capactive touch threashhold, ajust the sensitive by changing the threash number
#define THRESH 500

float smoothed[8] = {0,0,0,0,0,0,0,0};

void setup()
{
  //while (!Serial)
  Serial.begin(115200);
  Serial.println("start");
  Keyboard.begin();
}


void loop()                    
{ 
  for (int i=0;i<8;i++) {
    delay(1);
    long total1 = 0;
    long start = millis();
    long total =  pins[i].readPin(2000);

    // sensing the touch on the fabric.
    if ((total > THRESH) && (! currentPressed[i])) {

      currentPressed[i] = true;
      Keyboard.press(Keys[i]);
    } 
    else if ((total <= THRESH) && (currentPressed[i])) {

      currentPressed[i] = false;
      Keyboard.release(Keys[i]);
    }

    delay(10);
  }
}

// simple lowpass filter
int smooth(int data, float filterVal, float smoothedVal){

  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .999999;
  }
  else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (int)smoothedVal;
}
