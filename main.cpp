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
    std::cout<<powerInput.realHeight;
    
}
void printStructure(ControlData &powerInput);
/*
 * 
 */
int main(int argc, char** argv) {
    ControlData powerInput;
    powerInput.realHeight = 10;
    printStructure(powerInput);
    return 0;
}

