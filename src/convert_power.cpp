/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "convert_power.h"
namespace power {

PowerHandler::PowerHandler(structures::PowerInput& power_input,
                           structures::PowerOutput& power_output,
                           structures::UserInput& user_input,
                           structures::TelemetryInput& telemetry_input) {

  PowerHandler::power_input = power_input;
  PowerHandler::power_output = power_output;
  PowerHandler::user_input = user_input;
  PowerHandler::telemetry_input = telemetry_input;
}

}