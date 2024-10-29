/*
  Simple LIN 2.x master to generate frames for the LIN sniffer
  Create alternating frames of lengths 8 and 2.
*/

// include files                                                                       
#include "LIN_master3.h"      // send LIN frames via Serial3

// pause between LIN frames
#define LIN_PAUSE     200


void setup(void)
{
  // initialize LIN master (blocking operation)
  LIN_master3.begin(19200, LIN_V2, false);

} // setup()



void loop(void)
{
  static uint32_t lastCall = LIN_PAUSE;
  static uint8_t  count = 0;
  static uint8_t  Tx[8] = {0,0,0,0,0,0,0,0};    // daty bytes
  

  // simple LIN scheduler
  if (millis() - lastCall > LIN_PAUSE) {
    lastCall = millis();

    // send frame 1
    if (count == 0)
    {
      // increase frame index
      count++;

      // send master request
      LIN_master3.sendMasterRequest(0x07, 8, Tx);

      // increase data_byte[0]
      Tx[0]++;

    }

    // send frame 2
    else
    {
      // revert frame index
      count = 0;
      
      // send master request
      LIN_master3.sendMasterRequest(0x04, 2, Tx);

      // decrease data_byte[1]
      Tx[1]--;

    }
      
  } // scheduler
    
} // loop()
