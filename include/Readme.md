Readme for structures.h
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
* `InputXSensData xsens`   
   See [Input Xsens data](###input-xsens-data)
* `InputXSensData xsens`   
   See [Input Xsens data](###input-xsens-data)
* `InputXSensData xsens`   
   See [Input Xsens data](###input-xsens-data)

Besides these 'raw' variable three nested structures are defined as follows:
#### 1.1. Input Xsens data 	( `structure::ControlData::InputXSensData` ) 
#### 1.2. Vlotters data
