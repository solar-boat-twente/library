/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Sander Oosterveld
 *
 * Created on February 28, 2019, 9:10 AM
 */
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "include/structures.h"
#include "src/convert_power.h"

#define DEBUG_POWERHANDLER 0

#define DEBUG 1

using namespace std;

void powerThread(PowerHandler pw);
void throttleThread(structures::UserInput* user_input);

void powerThread(PowerHandler pw){
  for(int i =0;i<10;i++){
    pw.run();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void throttleThread(structures::UserInput* user_input){
  for(int i = 0; i<100; i++){
    user_input->steer.raw_throttle+=1;
    if (user_input->steer.raw_throttle>100){
      user_input->steer.raw_throttle=1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(137));
  }
}

int main(int argc, char** argv) {
  std::cout<<"Starting mainloop"<<endl;
  
  structures::PowerInput *power_input_ptr, power_input;
  structures::PowerOutput* power_output_ptr, power_output;
  structures::UserInput* user_input_ptr, user_input;
  structures::TelemetryInput* telemetry_input_ptr, telemetry_input;
  
  power_input_ptr = &power_input;
  power_output_ptr = &power_output;
  user_input_ptr = &user_input;
  telemetry_input_ptr = &telemetry_input;
        
  std::cout<<"Starting initialization\n";
  
  user_input_ptr->steer.raw_throttle = 50;
  user_input_ptr->steer.reverse = true;
  
  for(int i=0;i<10;i++){
    telemetry_input_ptr->solar_panel_states[i] = true;
    power_output_ptr->solar_panel_states[i] = false;
  }
  
  power_output_ptr->contractor_control=0;
  
  user_input_ptr->buttons.battery_on=true;
  PowerHandler powerHandler = PowerHandler(power_input_ptr, power_output_ptr, user_input_ptr, telemetry_input_ptr);
  
  
  std::thread th1(powerThread, powerHandler);
  std::thread th2(throttleThread, user_input_ptr);
  th1.join();
  th2.join();
  return 0 ;
}

