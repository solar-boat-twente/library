/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PowerHandler.h
 * Author: Sander Oosterveld
 *
 * Created on March 1, 2019, 9:05 PM
 */

#ifndef CONVERT_POWER_H
#define CONVERT_POWER_H

#include "../include/structures.h"

//namespace power {

class PowerHandler {
  /*Main Goal:
   *  - Fill up the power_output structure
   * Sub Goals:
   *  - Write input throttle to output throttle taking reverse etc into account
   *  - Turn on/off all of the panels
   *  - Set the Motor state to flywheel or not
   *  - Check whether balancing should be on
   *  - Check whether contractor should be on
   *  - Lets know if the there is an error anywhere
   */
  
 public:
  PowerHandler(structures::PowerInput* power_input,
                  structures::PowerOutput* power_output,
                  structures::UserInput* user_input,
                  structures::TelemetryInput* telemetry_input);
  
  void run();
  //Function calling all the private function, this one should be run in a thread.

 private:
  bool calculateThrottle();
  //Uses the reverse state to calculate the throttle (adds a minus if reverse).
  //Returns if there is success or not
  
  signed short int mapThrottle(unsigned char raw_throttle);
  //Maps the throttle according to a very nice function
  
  bool setRelay(); 
  //Returns whether there is success, functions for switching the relays of the solar panels.

  bool setMotorState();
  //Sets the motor state by checking the user_input (if the motor is on or not)
  
  bool setBalancing();
  //Checks if the BMS is wants to balance and whether that is allowed or not
  
  bool setContactor();
  //Checks if the Contactor should be open or not and sets it so
  
   
  //Pointers to the different structures used by this class
  structures::PowerInput* power_input;
  structures::PowerOutput* power_output;
  structures::UserInput* user_input;
  structures::TelemetryInput* telemetry_input;



};
//}

#endif /* CONVERT_POWER_H */

