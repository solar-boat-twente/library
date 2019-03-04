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
#include "structures.h"


void printStructure(ControlData &powerInput){
  std::cout<<powerInput.real_height;
}
void printStructure(ControlData &powerInput);
/*
 * 
 */
int main(int argc, char** argv) {
  ControlData control_data;
  control_data.real_height = 10;
  //printStructure(control_data);
  unsigned char hello = 11;
  std::cout<<~hello;
  return 0 ;
}

