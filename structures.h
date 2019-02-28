/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   library.h
 * Author: Sander Oosterveld
 *
 * Created on February 28, 2019, 9:13 AM
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

/*
 Declaring all the structures 
 */






/*
 * All the input structures and nested input structures for the power data.
 *
 *
 */
struct PowerInput{
    /*
     All the input gotten from the power electronics, this data is split as follows:
     * - battery (all the data from the battery)
     * - solarPanels (all the data from the solarPanels)
     * - driver (all the data from the motorController)
     */
    
    //The main structure for all of the power, this is subdivided into battery, solar and motor

    
    /*
     Nested structures used to order the PowerInput structure
     */
    struct BatteryInput{
        float celVoltages[12];
        float stateOfCharge;
        unsigned char errorNumber;
        unsigned char errorLocation;
        signed char maxTemp;
        signed char minTemp;
        bool balanceState, contactorReady, contactorStatus;
    };
    
    struct SolarInput{
        float MPPTPower[10];
        float panelPower[10];
    };
    
    struct DriverInput{
        float motorTemp, driverTemp, driverOutputPower, motorSpeed;
        float driverVoltageInput, driverCurrentInput;
        bool driverState;
    };
    
        
    BatteryInput battery;
    
    SolarInput solarPanels;
    
    DriverInput driver;
};

/*
 All the input structure from the user e.g. Steering Wheel and dashboard.
 */
enum FlyMode{
    NO_FLY,
    FLY,
    BRIDGE,
    SLALOM
};

enum PIDState{
    STATE1,
    STATE2,
    STATE3,
    STATE4,
    STATE5,
    STATE6,
    STATE7,
    STATE8    
};

struct UserInput{
    /*
     all user input nested into 3 sub parts: 
     * steer (for the steeringwheel)
     * buttons (for the buttons)
     * control (for the Control related inputs (also roll from pedals)
     */
    
    struct ControlUserInput{
        //Predefined PID states, using an enumerate
        PIDState PIDstate;
        
        //Roll given by the pedals saved as an float
        float roll;
    };
    
    struct ButtonInput{
        bool batteryOn;
        bool motorOn;    
    };
    
    struct SteeringInput{
    //raw value of the Throttle 0 till 255 (from the analog inputs)
        unsigned char rawThrottle;
        //values: NO_FLY, FLY, BRIDGE, SLALOM
        FlyMode flyMode;

        bool reverse;  
    };
    
    SteeringInput steer;
    
    ButtonInput buttons;
    
    ControlUserInput control;
};

/*
 All the data gotten from the Telemetry System
 */
struct TelemetryInput{
        
    struct TelemetryControlInput{
        struct TelemetryPID{
            // PID structure used in the telemetry system
            float P, I, D, N;
        };
        
        TelemetryPID PID_height;
        TelemetryPID PID_roll;
        TelemetryPID PID_pitch;
        bool overwrite;
    };
    
    TelemetryControlInput control;
    bool solarPanelStates[10];
    float advisedSpeed; 
};

/*
 * structure for all the outputs which are send to Power data
 */
struct PowerOutput{
    bool solarPanelStates[10];
    // the throttle used by the Motor from -320000 to 320000
    signed short int throttle;
    bool motorState;
    unsigned char contractorControl;
    unsigned char balancingControl;
};


/*
 Structure for the Control system, both all the inputs and all the outputs.
 */
struct ControlData{
        
    struct InputXSenseData{
        float rawPitch, rawRoll;
        float filteredPitch, filteredRoll;
        float rawZAcceleration;
    };
    
    struct Vlotters{
        float angleLeft, angleRight;
    };
    
    struct ComputedControlData{
        float forceRoll, forcePitch, forceHeight;
        float angleLeft, angleRight, angleBack;
    };
    
    InputXSenseData xsens;
    Vlotters vlotters;
    ComputedControlData computed;
    float realHeight;
    float realRoll; 
};

#endif /* STRUCTURES_H */

