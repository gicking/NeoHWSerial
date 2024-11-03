/*
  Simple LIN 2.x master to generate frames for the LIN sniffer
  Create alternating frames of lengths 8 and 2.

  Requires LIN master library from https://github.com/gicking/LIN_master_portable_Arduino
*/

// include files                                                                       
#include "LIN_master_HardwareSerial.h"

// pause between LIN frames
#define LIN_PAUSE     200

// setup LIN node
LIN_Master_HardwareSerial   LIN(Serial3, "LIN_HW");             // parameter: HW-interface, name


// call once
void setup(void)
{
  // open LIN interface
  LIN.begin(19200);  

} // setup()


// call repeatedly
void loop(void)
{
  // transmit buffers
  static uint8_t  Tx_1[8] = {0,0,0,0,0,0,0,0};    // data bytes
  static uint8_t  Tx_2[8] = {0,0,0,0,0,0,0,0};    // data bytes

  // send frame 1 and increase Tx[0]
  LIN.sendMasterRequestBlocking(LIN_Master::LIN_V2, 0x07, 8, Tx_1);
  LIN.resetStateMachine();
  LIN.resetError();
  Tx_1[0]++;

  // wait a bit
  delay(LIN_PAUSE);

  // send frame 1 and increase Tx[1]
  LIN.sendMasterRequestBlocking(LIN_Master::LIN_V2, 0x04, 2, Tx_2);
  LIN.resetStateMachine();
  LIN.resetError();
  Tx_2[1]++;

  // wait a bit
  delay(LIN_PAUSE);

} // loop()
