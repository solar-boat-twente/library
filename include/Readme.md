 (Readme for structures.h
=====
## goal:
Have one file contain all the _global_ structures. The global data has been split into 5 data types:
* Control Data
* Power System Input
* Power System Output
* User Input
* Telemetry Input

In between these structures all the global data in the boat is represented. These structures are used for logging, telemetry and controlling the boat.
## Different Structures
Section describing the five structures defined in [Goal](##goal)
### 1. Control Data ( `structure::ControlData` )
Control Data stores all the data produced by the control system and is usefull for different sub systems such as the display and the telemetry system. the variables stored in this structure are:
* `float real_height`.   
	Stores the real height of the boat after a complementary filter taking both the flotter and the XSens into account   
* `float real_roll`   
   Stores the real roll after it has been filtered from the roll taken from the XSens roll data
* `InputXSensData xsens`      See [Input Xsens data](###input-xsens-data)
* `Vlotters vlotter`   
   See [Vlotters data](###input-xsens-data)
* `ComputedControlData computed`   
   See [Computed Control Data](###input-xsens-data)

Besides these 'raw' variable three nested structures are defined as follows:
#### 1.1. Input Xsens data 	( `structure::ControlData::InputXSensData` ) 
Input Xsens data stores all the (raw) data gotten from the XSens they are stored as follows:
* `float raw_pitch, raw_roll`   
   Stores the raw pitch and roll gotten directly from the XSens(before filtering)
* `float filtered_pitch, filtered_roll`   
   Stores the filted Pitch an roll --> helps to see if the filters are working well
* `float raw_z_acceleration`   
   Stores the z_acceleration according to the XSens this is used to compute `float real_height`

#### 1.2. Vlotters data (`structure::ControlData::InputXSensData`)
Just to order the data from the vlotters -> Makes getting the data a bit simpeler. It also only has two variables:
* `float angle_left, angle_right`   
   Stores the angles of the vlotters which is used to calculate both the roll and the height of the Solar Boat
   
#### 1.3. Computed Control Data (`structure::ControlData::ComputedControlData`)
Keeps all the computed data which is nice for past processing in one place. The data in this structures is:
* `float force_roll, force_pitch, force_height`   
   The computed required forces to keep the boat in place both for the roll (used to check the PID controller)
* `float angle_left, angle_right, angle_back`   
   The computed angles of the different wings, used to test the MMA

### 2. Power Output (`structure::PowerOutput`)
Simple structure for all the data which the power system requires, using this data the solar panels can be turned on, the throttle can be set, the motor can be turned on and the battery can be set to on value and balancing can be turned off/on.

The values in the structure are:
* `bool solar_panel_states[10]`   
   The set states of the 10 solar panels stored as an list of booleans
* `signed short int throttle`    
   The throttle in a value between -32000 and +32000 mapping -300 to 300 Amps input into the driver.
* `bool motor_state`   
   Stores whether the motor should be in freewheel mode.
* `unsigned char contractor_control`   
   Stores the stat of the contractor in 3 possible int values:   
   0 -> do not engage   
   1 -> engage if BMS wants to   
   2 -> force engage   
* `unsigned char balancing_control`   
   Stores the balencing state:   
   0 -> Normal balancing   
   1 -> Force balancing off (race mode)
   
   ### 3.
