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
        float cel_voltages[12];
        float state_of_charge;
        unsigned char error_number;
        unsigned char error_location;
        signed char max_temp;
        signed char min_temp;
        bool balance_state, contactor_ready, contactor_status;
    };
    
    struct SolarInput{
        float MPPT_power[10];
        float panel_power[10];
    };
    
    struct DriverInput{
        float motor_temp, driver_temp, driver_output_power, motor_speed;
        float driver_voltage_input, driver_current_input;
        bool driver_state;
    };
    
        
    BatteryInput battery;
    
    SolarInput solar_panels;
    
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
        PIDState PID_state;
        
        //Roll given by the pedals saved as an float
        float roll;
    };
    
    struct ButtonInput{
        bool battery_on;
        bool motor_on;    
    };
    
    struct SteeringInput{
    //raw value of the Throttle 0 till 255 (from the analog inputs)
        unsigned char raw_throttle;
        //values: NO_FLY, FLY, BRIDGE, SLALOM
        FlyMode fly_mode;

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
    bool solar_panel_states[10];
    float advised_speed; 
};

/*
 * structure for all the outputs which are send to Power data
 */
struct PowerOutput{
    bool solar_panel_states[10];
    // the throttle used by the Motor from -320000 to 320000
    signed short int throttle;
    bool motor_state;
    unsigned char contractor_control;
    unsigned char balancing_control;
};


/*
 Structure for the Control system, both all the inputs and all the outputs.
 */
struct ControlData{
        
    struct InputXSenseData{
        float raw_pitch, raw_roll;
        float filtered_pitch, filtered_roll;
        float raw_z_acceleration;
    };
    
    struct Vlotters{
        float angle_left, angle_right;
    };
    
    struct ComputedControlData{
        float force_roll, force_pitch, force_height;
        float angle_left, angle_right, angle_back;
    };
    
    InputXSenseData xsens;
    Vlotters vlotters;
    ComputedControlData computed;
    float real_height;
    float real_roll; 
};

#endif /* STRUCTURES_H */

