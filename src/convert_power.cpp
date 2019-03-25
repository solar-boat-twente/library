/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "convert_power.h"
#include "../include/structures.h"
#include <iostream>
#include <stdio.h>

#define DEBUG

#define DEBUG_POWERHANDLER

//inline namespace power {
using namespace std;
    
PowerHandler::PowerHandler(structures::PowerInput* power_input,
                           structures::PowerOutput* power_output,
                           structures::UserInput* user_input,
                           structures::TelemetryInput* telemetry_input) {


  PowerHandler::power_input = power_input;
  PowerHandler::power_output = power_output;
  PowerHandler::user_input = user_input;
  PowerHandler::telemetry_input = telemetry_input;
  
#ifdef DEBUG_POWERHANDLER
  std::cout<<"PowerHandler: Power Handler initialized"<<endl;
#endif
}

void PowerHandler::run(){
  //runs all the functions in side this class, this function should be run in a while loop
  setRelay();
  calculateThrottle();
  setMotorState();
  setContactor();
  setBalancing();
}


bool PowerHandler::setRelay(){
  //Helper variable, later 
  bool solar_panel_state[10]={0};
  
#ifdef DEBUG_POWERHANDLER
  std::cout<<"\nPowerHandler: Starting setRelay() with following states: ";
  for(char i=0; i<sizeof(solar_panel_state); i++){
    std::cout<<power_output->solar_panel_states[i]<<" ";
  }
  cout<<endl;
#endif
  
  //Test if the solar panels on button is pressed
  if (user_input->buttons.solar_on){
    for(char i=0;i<10;i++){
      solar_panel_state[i]=true;
    }
    //Handling the input from the telemetry system
    for(char i =0; i<10; i++){
      if(telemetry_input->solar_panel_states[i]){
        solar_panel_state[i] = true;
      } else{
        solar_panel_state[i] = false;
      }
    }
  }
 
#ifdef DEBUG_POWERHANDLER
  cout<<"PowerHandler: solar_panel_states: ";
  for(char i=0; i<sizeof(solar_panel_state); i++){
    cout<<solar_panel_state[i]<<" ";
  }
  cout<<endl;
#endif
  
  //Set the values in the structures equal to our temporary panel states array
  for(char i = 0; i<sizeof(solar_panel_state);i++){
    power_output->solar_panel_states[i]=solar_panel_state[i];
  }
  
#ifdef DEBUG_POWERHANDLER
  cout<<"PowerHandler: power_output -> solar_panel_states set to: ";
  for(char i=0; i<sizeof(solar_panel_state); i++){
    cout<<power_output->solar_panel_states[i]<<" ";
  }
  cout<<endl;
#endif
  
  return true;
}


bool PowerHandler::calculateThrottle(){
  
#ifdef DEBUG_POWERHANDLER
  cout<<"\nPowerHandler: Starting calculateThrottle() with current throttle: "<<power_output->throttle<<endl;
#endif
  
  signed short int real_throttle = mapThrottle(user_input->steer.raw_throttle); 
  if(user_input->steer.reverse){
    power_output->throttle = -1*real_throttle;
  }else{
    power_output->throttle = real_throttle;
  }
  
#ifdef DEBUG_POWERHANDLER
  printf("PowerHandler: Throttle set to: %i using raw_throttle: %i\n",power_output->throttle, user_input->steer.raw_throttle);
#endif

  if(power_output->throttle == real_throttle or power_output->throttle == -real_throttle){
    return true;
  }else{
    return false;
  }
}

signed short int PowerHandler::mapThrottle(unsigned char raw_power){
  signed short int short_power = (signed short)raw_power;
  if (short_power < 75){
    return short_power*110;
  }else{
    return 75*110 + (short_power-75)*975;
  }
}

bool PowerHandler::setMotorState(){
#ifdef DEBUG_POWERHANDLER
  printf("\nPowerHandler: Starting setMotorState() with value: %s\n", power_output->motor_state ? "true":"false");
#endif
  
  power_output->motor_state = user_input->buttons.motor_on;
    
#ifdef DEBUG_POWERHANDLER
  printf("PowerHandler: Motor state set to: %s\n", power_output->motor_state ? "true":"false");
#endif
  
  return true;
}

bool PowerHandler::setContactor(){
#ifdef DEBUG_POWERHANDLER
  printf("\nPowerHandler: Starting setContactor() with value: %i\n", power_output->contractor_control);
#endif
  
  if (user_input->buttons.battery_on){
    power_output->contractor_control=1;
  } else{
    power_output->contractor_control=0;
  }
  
  //If the battery is forced than the contactor should be forced on (2)
  if (user_input->buttons.force_battery){
    power_output->contractor_control=2;
  }
  
#ifdef DEBUG_POWERHANDLER
  printf("PowerHandler: Contactor state set to: %i\n", power_output->contractor_control);
#endif
  
  return true;
}

bool PowerHandler::setBalancing(){
#ifdef DEBUG_POWERHANDLER
  printf("\nPowerHandler: Starting setBalancing() with value: %i\n", power_output->balancing_control);
#endif
  
  if(user_input->buttons.battery_on){
    power_output->balancing_control = 1;
  }else{
    power_output->balancing_control = 0;
  }
  
#ifdef DEBUG_POWERHANDLER
  printf("PowerHandler: Balancing state set to: %i\n", power_output->balancing_control);
#endif
  
  return true;
}
//} /*power*/