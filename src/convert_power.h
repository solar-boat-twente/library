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

namespace PowerStream{
   
    class PowerHandler{
        
    public:
        void PowerHandler();
        void run();
    private:
        
        bool turnRelayOff(PowerOutput &power_output);
        bool setThrottle(PowerOutput &power_output, UserInput &user_input);
        bool 
        
        
    
        
    }
    
    
    
    
    
    
}


#endif /* CONVERT_POWER_H */

