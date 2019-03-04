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

#include "structures.h"

namespace power {

class PowerHandler {
 public:
  void PowerHandler(structures::PowerInput& power_input,
                    structures::PowerOutput& power_output,
                    structures::UserInput& user_input,
                    structures::TelemetryInput& telemetry_input);
  void run();

 private:

  bool turnRelayOff();
  bool setThrottle();

  structures::PowerInput& power_input;
  structures::PowerOutput& power_output;
  structures::UserInput& user_input;
  structures::TelemetryInput& telemetry_input;



}
}






}


#endif /* CONVERT_POWER_H */

