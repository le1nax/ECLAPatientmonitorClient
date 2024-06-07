/*! \file smartECLA_IDs.h
 *  \brief Contains the global smartECLA enums
 *
 *   This file contains all of the 29-bit CAN/Measurement-IDs that
 *   are used in the SmartECLA project.

 *   It is used by all projects, by the CAN-Viewer and the Code-Gen.
 *
 *  \author		Florian Goebe
 *  \author		Lehrstuhl fuer Informatik 11 -  RWTH Aachen
 *  \date		20.04.2010
 *  \version	$Rev: 2690 $
 *
 * IMPORTANT: Please follow the described ID patterns when you insert or modify IDs!
 *
 *   Priority Blocks:
 * 
 * | ID Range     |    Usage
 * |--------------------------------------------------------------------------
 * | 0x000000--   |    Ultra-high priority (reserved for measurement issues)
 * |              |
 * | 0x00000100   |    Time (highest regular priority)
 * |              |
 * | 0x02------   |    Alerts (medical or safety-relevant)
 * | 0x03------   |    Alerts (lower prior)
 * |              |
 * | 0x05------   |    Commands for Translation Units and Devices
 * | 0x06------   |    Commands for Models (ASMO)
 * |              |
 * | 0x08------   |    Control Values (Stellwerte)
 * |              |
 * | 0x0A------   |    MMU-Notifications (medical measurement unit)
 * | 0x0B------   |    Model-Notifications
 * | 0x0C------   |    Network-Notifications (Card Disabled, Comment etc.)
 * |              |
 * | 0x10------   |    Measurements
 * |              |
 * | 0x11------   |    Flowprofiles
 * |              |
 * | 0x1FFFFFFFF  |    Last ID (reserved for measurement issues)
 * |--------------------------------------------------------------------------
 *
 * 
 *   Device Identifiers:
 *
 * | ID Pattern    |    Prefix      	(Device)
 * |--------------------------------------------------------------------------
 * | 0x--0-----    |                	(Medical Device)
 * | 0x--01----    |    CDI         	(Terumo CDI 500)
 * | 0x--02----    |    GAS         	(Gas Pump)
 * | 0x--03----    |    PRESSURE    	(Pressure Sensor)
 * | 0x--04----    |    AS3         	(Datex-Ohmeda AS/3)
 * | 0x--05----    |    Servo300    	(Servo Ventilator 300)
 * | 0x--06----    |    PGA	    		(Optimix Patient Gas Analyzer)
 * | 0x--07----    |    N560			(Nellcor N-560)
 * | 0x--08----    |    RECIRCULATION	(Recirculation Board)
 * | 0x--09----    |    PiCCO       	(Pulsion Monitor for Pulse Conture Cardiac Output)
 * | 0x--0A----    |    CombiM      	(Radiometer TCM CombiM)
 * | 0x--0B----    |    TEMPERATURE 	(Analogue Temperature Sensors - selfmade)
 * | 0x--0C----    |    BLOOD_FLOW  	(Transsonic HT 110 Analogue Blood Flow Sensors)
 * | 0x--0D----    |    PUMP        	(Blood Pump Control)
 * | 0x--0E----    |    Button      	(Experimental Button Sensor)
 * | 0x--0F----    |	Flow_Board		(Measurement with the help of Hall-Sensors)
 * | 0x--10----	   |	TOM				(InSpectra StO2 Tissue Oxygenation Monitor)
 * | 0x--1F----    |    DriverTests     (Driver Tests CAN IDs)
 * |               |
 * |               |
 * | 0x--20----    |    PV1000     		(Pandemic Ventilator)
 * |               |
 * | 0x--A-----    |    MODEL       	(Model, Simulink)
 * | 0x--A0----    |    MODEL_O2SAT		(Martin's O2-sat Model)
 * |               |
 * | 0x--FD----    |    DSPACEML		(dSpace MicroLabBox)
 * | 0x--FE----    |    DSPACE      	(dSpace MicroAutoBox)
 * | 0x--FF----    |    (no)        	(CAN-Viewer, others)
 * |--------------------------------------------------------------------------


 *
 * How to define groups
 * --------------------
 * A group definition holds until the next group definition
 * the end of the file. One group may occur several times, but the parameters should
 * stay consistent. A well-defined behaviour of inconsistent group definitions using
 * the same group name is not given yet. -> just keep it consistent.
 *
 * A group definition looks as follows (order of arguments matters!):
 *
 * <begin of line>// idGroup("MyGroupName", <count>, SHIFTER_DEFINE_NAME, ALARM)"<end of line>
 *
 * <count> stands for a simple int literal. Count and shifter can be ommitted (then 1 is used as count).
 * If a count is specified (even if it is 1), a shifter define has to be defined also.
 * ALARM is optional and can be left out. If something is left out, the comma before is
 * of course left out, too. // idGroup(none) sets the current group to none, thus the
 * following IDs are not assign to any group. The group definition must have an extra line.
 * Whitespaces (as indentation) before and after the group def. are ignored.
 * 
 * How to set up scaling, intervals and thresholds
 * ----------------------
 * 
 * values are optional in every  separate field (with separator "|") beginning from the right most value.
 * 
 *
 * Example: CAN_ID_GAS_ACTUAL_CO2			= 0x10020003, //Actual value for CO2 (Gasblender)	| 0.001 l/min | 10 100 0.005 0.01
 *                                                                                                |     |       |  |   |     |
 *                                                                                      scaling factor  |       |  |   |     |
 *                                                                                                    unit      |  |   |     |
 *                                                                                     interval for sending on CAN |   |     |
 *                                                                                           interval for saving on SD |     | 
 *                                                                                                threshold to send over CAN |
 *                                                                                                            threshold to save on SD
 */
#pragma once // Include this file only once!
#ifndef SMARTECLA_IDS_H_
#define SMARTECLA_IDS_H_
// Block IDs for filtering received messages
#define BLOCK_ID_MASK			(0xFF << 24)
#define BLOCK_ID_MEDICAL_ALERT  (0x02 << 24)
#define BLOCK_ID_LOW_PRIO_ALERT (0x03 << 24)
#define BLOCK_ID_DEVICE_COMAMND	(0x05 << 24)
#define BLOCK_ID_MODEL_COMMAND  (0x06 << 24)
#define BLOCK_ID_CONTROL_VALUES (0x08 << 24)
#define BLOCK_ID_MMU_NOTIFY		(0x0A << 24)
#define BLOCK_ID_MODEL_NOTIFY	(0x0B << 24)
#define BLOCK_ID_NETWORK_NOTIFY	(0x0C << 24)
#define BLOCK_ID_MEASUREMENTS	(0x10 << 24)
#define BLOCK_ID_FLOWPROFILES	(0x11 << 24)
// Device IDs for filtering received messages
#define DEVICE_ID_MASK			(0xFF << 16)
#define DEVICE_ID_CDI			(0x01 << 16)
#define DEVICE_ID_GAS			(0x02 << 16)
#define DEVICE_ID_PRESSURE		(0x03 << 16)
#define DEVICE_ID_AS3			(0x04 << 16)
#define DEVICE_ID_SERVO			(0x05 << 16)
#define DEVICE_ID_PGA			(0x06 << 16)
#define DEVICE_ID_N560			(0x07 << 16)
#define DEVICE_ID_RECIRCULATION	(0x08 << 16)
#define DEVICE_ID_PiCCO			(0x09 << 16)
#define DEVICE_ID_CombiM		(0x0A << 16)
#define DEVICE_ID_TEMPERATURE	(0x0B << 16)
#define DEVICE_ID_BLOOD_FLOW	(0x0C << 16)
#define DEVICE_ID_PUMP			(0x0D << 16)
#define DEVICE_ID_Button		(0x0E << 16)
#define DEVICE_ID_FLOW_BOARD	(0x0F << 16)
#define DEVICE_ID_TOM			(0x10 << 16)
#define DEVICE_ID_DriverTests	(0x1F << 16)
#define DEVICE_ID_PV1000    	(0x20 << 16)
#define DEVICE_ID_MODEL_O2SAT	(0xA0 << 16)
#define DEVICE_ID_DSPACEML		(0xFD << 16)
#define DEVICE_ID_DSPACE		(0xFE << 16)
#define DEVICE_ID_OTHERS		(0xFF << 16)
// one default shifter
#define CAN_DEFAULT_DEVNUMBER_SHIFT		12
//! Macro to read the device number out of an ID
#define getDeviceNumber(id,shifter)			((id >> shifter) & 0xF)
//! Macro to add the device number to an id. The preset bits at the device number's position in the IDs are discarded.
#define addDeviceNumber(devNum,id,shifter)	((id & ~(0xF << shifter)) | (devNum << shifter))
enum can_id { // Please do NOT change this line (for parsing by can viewer)
//####################################################################################################
// ULTRA-HIGH PRIORITY SECTION					0x0000000...
//####################################################################################################
// idGroup(none)
	CAN_ID_PERFORMANCE_COUNTER = 0x00000010, // Performance Messungen
//####################################################################################################
// TIME											0x00000100
//####################################################################################################
// idGroup("Time", ALARM)
	CAN_ID_TIME_BEACON = 0x00000100, // Beacon for time synchronizaion
// idGroup(none)
//####################################################################################################
// ALERTS (MEDICAL AND SAFETY)					0x02...
//####################################################################################################	
// idGroup("Models")
	CAN_ID_MODEL_O2SAT_ALARM = 0x02A00010, //Difference Oxy Sats. | 1 %
	CAN_ID_GAS_ACTUAL_CO2			= 0x10020003, //Actual value for CO2 (Gasblender)	| 0.001 l/min | 10 100 0.005 0.01
	CAN_ID_MODEL_PUMP_ALARM_CANNULA = 0x02B00001, //critical flow | 0.001 l/min
	CAN_ID_MODEL_PUMP_ALARM_CLOT = 0x02B00002, //difference | 1 %
	CAN_ID_MODEL_PUMP_ALARM_AIR = 0x02B00003, //difference | 1 %
	CAN_ID_MODEL_MEASUREMENT_TOO_LOW = 0x02B00100, //Given measurement is too low
	CAN_ID_MODEL_MEASUREMENT_TOO_HIGH = 0x02B00101, //Given measurement is too high
// idGroup("CDI Alarm", 2, CAN_CDI_SHIFT, ALARM)
	CAN_ID_CDI_X_ACQUIRE_MISSING = 0x02010F00, //Acquire define missing for CAN-ID
	CAN_ID_CDI_X_MEASUREMENT_TOO_LOW = 0x02010100, //Given measurement is too low
	CAN_ID_CDI_X_MEASUREMENT_TOO_HIGH = 0x02010101, //Given measurement is too high
// idGroup("Gasblender Alarm", ALARM)
	CAN_ID_GAS_ACQUIRE_MISSING = 0x02020F00, //Acquire define missing for CAN-ID
	CAN_ID_GAS_MEASUREMENT_TOO_LOW = 0x02020100, //Given measurement is too low
	CAN_ID_GAS_MEASUREMENT_TOO_HIGH = 0x02020101, //Given measurement is too high
// idGroup("Pressure Sensor Alarm", ALARM)
	CAN_ID_PRESSURE_ACQUIRE_MISSING = 0x02030F00, //Acquire define missing for CAN-ID
	CAN_ID_PRESSURE_MEASUREMENT_TOO_LOW = 0x02030100, //Given measurement is too low
	CAN_ID_PRESSURE_MEASUREMENT_TOO_HIGH = 0x02030101, //Given measurement is too high
// idGroup("AS3 Alarm", 2, CAN_AS3_SHIFT, ALARM)
	CAN_ID_AS3_X_ACQUIRE_MISSING = 0x02040F00, //Acquire define missing for CAN-ID
	CAN_ID_AS3_X_MEASUREMENT_TOO_LOW = 0x02040100, //Given measurement is too low
	CAN_ID_AS3_X_MEASUREMENT_TOO_HIGH = 0x02040101, //Given measurement is too high
// idGroup("SERVO Alarm", 2, CAN_SERVO_SHIFT, ALARM)
	CAN_ID_SERVO_X_ACQUIRE_MISSING = 0x02050F00, //Acquire define missing for CAN-ID
	CAN_ID_SERVO_X_MEASUREMENT_TOO_LOW = 0x02050100, //Given measurement is too low
	CAN_ID_SERVO_X_MEASUREMENT_TOO_HIGH = 0x02050101, //Given measurement is too high
// idGroup("PGA Alarm", 2, CAN_PGA_SHIFT, ALARM)
	CAN_ID_PGA_X_ACQUIRE_MISSING = 0x02060F00, //Acquire define missing for CAN-ID
	CAN_ID_PGA_X_MEASUREMENT_TOO_LOW = 0x02060100, //Given measurement is too low
	CAN_ID_PGA_X_MEASUREMENT_TOO_HIGH = 0x02060101, //Given measurement is too high
// idGroup("N560 Alarm", 2, CAN_N560_SHIFT, ALARM)
	CAN_ID_N560_X_ACQUIRE_MISSING = 0x02070F00, //Acquire define missing for CAN-ID
	CAN_ID_N560_X_MEASUREMENT_TOO_LOW = 0x02070100, //Given measurement is too low
	CAN_ID_N560_X_MEASUREMENT_TOO_HIGH = 0x02070101, //Given measurement is too high
// idGroup("RECIRCULATION Alarm", 2, CAN_RECIRCULATION_SHIFT, ALARM)
	CAN_ID_RECIRCULATION_X_ACQUIRE_MISSING = 0x02080F00, //Acquire define missing for CAN-ID
	CAN_ID_RECIRCULATION_X_MEASUREMENT_TOO_LOW = 0x02080100, //Given measurement is too low
	CAN_ID_RECIRCULATION_X_MEASUREMENT_TOO_HIGH = 0x02080101, //Given measurement is too high
// idGroup("PiCCO2 Alarm", ALARM)
	CAN_ID_PiCCO_ACQUIRE_MISSING = 0x02090F00, //Acquire define missing for CAN-ID
	CAN_ID_PiCCO_MEASUREMENT_TOO_LOW = 0x02090100, //Given measurement is too low
	CAN_ID_PiCCO_MEASUREMENT_TOO_HIGH = 0x02090101, //Given measurement is too high
// idGroup("TCM Alarm", ALARM)
	CAN_ID_CombiM_ACQUIRE_MISSING = 0x020A0F00, //Acquire define missing for CAN-ID
	CAN_ID_CombiM_MEASUREMENT_TOO_LOW = 0x020A0100, //Given measurement is too low
	CAN_ID_CombiM_MEASUREMENT_TOO_HIGH = 0x020A0101, //Given measurement is too high
// idGroup("Temperature Alarm", ALARM)
	CAN_ID_TEMPERATURE_ACQUIRE_MISSING = 0x020B0F00, //Acquire define missing for CAN-ID
	CAN_ID_TEMPERATURE_MEASUREMENT_TOO_LOW = 0x02B0F100, //Given measurement is too low
	CAN_ID_TEMPERATURE_MEASUREMENT_TOO_HIGH = 0x02B0F101, //Given measurement is too high
// idGroup("Blood Flow Alarm", 2, CAN_BLOOD_FLOW_SHIFT, ALARM)
	CAN_ID_BLOOD_FLOW_X_ACQUIRE_MISSING = 0x020C0F00, //Acquire define missing for CAN-ID
	CAN_ID_BLOOD_FLOW_X_MEASUREMENT_TOO_LOW = 0x020C0100, //Given measurement is too low
	CAN_ID_BLOOD_FLOW_X_MEASUREMENT_TOO_HIGH = 0x020C0101, //Given measurement is too high
// idGroup("Pump Control Alarm", ALARM)
	CAN_ID_PUMP_ACQUIRE_MISSING = 0x020D0F00, //Acquire define missing for CAN-ID
	CAN_ID_PUMP_MEASUREMENT_TOO_LOW = 0x020D0100, //Given measurement is too low
	CAN_ID_PUMP_MEASUREMENT_TOO_HIGH = 0x020D0101, //Given measurement is too high
// idGroup("Button Alarm", ALARM)
	CAN_ID_Button_ACQUIRE_MISSING = 0x020E0F00, //Acquire define missing for CAN-ID
	CAN_ID_Button_MEASUREMENT_TOO_LOW = 0x020E0100, //Given measurement is too low
	CAN_ID_Button_MEASUREMENT_TOO_HIGH = 0x020E0101, //Given measurement is too high
// idGroup("Flow_Board Alarm", ALARM)
	CAN_ID_FLOW_BOARD_ACQUIRE_MISSING = 0x020F0F00, //Acquire define missing for CAN-ID
	CAN_ID_FLOW_BOARD_MEASUREMENT_TOO_LOW = 0x020F0100, //Given measurement is too low
	CAN_ID_FLOW_BOARD_MEASUREMENT_TOO_HIGH = 0x020F0101, //Given measurement is too high
// idGroup("TOM Alarm", 2, CAN_TOM_SHIFT, ALARM)
	CAN_ID_TOM_X_ACQUIRE_MISSING = 0x02100F00, //Acquire define missing for CAN-ID
	CAN_ID_TOM_X__MEASUREMENT_TOO_LOW = 0x02100100, //Given measurement is too low
	CAN_ID_TOM_X__MEASUREMENT_TOO_HIGH = 0x02100101, //Given measurement is too high
// idGroup("DriverTests Alarm", 16, CAN_DRIVERTESTS_SHIFT, ALARM)
	CAN_ID_DriverTests_X_ACQUIRE_MISSING = 0x021F0F00, //Acquire define missing for CAN-ID
	CAN_ID_DriverTests_X_MEASUREMENT_TOO_LOW = 0x021F0100, //Given measurement is too low
	CAN_ID_DriverTests_X_MEASUREMENT_TOO_HIGH = 0x021F0101, //Given measurement is too high
// idGroup("Models", ALARM)
	CAN_ID_MODEL_O2SAT_ACQUIRE_MISSING = 0x02A00F00, //Acquire define missing for CAN-ID
	CAN_ID_MODEL_O2SAT_MEASUREMENT_TOO_LOW = 0x02A00100, //Given measurement is too low
	CAN_ID_MODEL_O2SAT_MEASUREMENT_TOO_HIGH = 0x02A00101, //Given measurement is too high

// idGroup("PV1000 Alarm")
	CAN_ID_PV1000_Alarm_Pmax = 0x02200000, // Pressure > Pmax
	

//####################################################################################################
// ALERTS (LOWER PRIOR)							0x03...
//####################################################################################################
//####################################################################################################
// Commands for Translation Units and Devices	0x05...
//####################################################################################################
// idGroup("Pump Control")
	CAN_ID_PUMP_CONTROL_TYPE = 0x050D0001, // type of control	|
	CAN_ID_PUMP_CONTROL_P = 0x050D0002, // P-factor		|
	CAN_ID_PUMP_CONTROL_I = 0x050D0003, // I-factor		|
	CAN_ID_PUMP_CONTROL_D = 0x050D0004, // D-factor		|
	CAN_ID_PUMP_CONTROL_T = 0x050D0005, // sampling time		|
	CAN_ID_PUMP_CONTROL_LIMIT_RPM = 0x050D0006, // maximum RPM		|
	CAN_ID_PUMP_CONTROL_LIMIT_I = 0x050D0007, // limit of integration	|
//####################################################################################################
// Commands for Models (ASMO)					0x06...
//####################################################################################################
// idGroup("Models")
	CAN_ID_MODEL_O2SAT_CALIBRATE = 0x06A00010, // Oxy Model Calibrate Command
//####################################################################################################
// Control Values (Stellwerte)					0x08...
//####################################################################################################
// idGroup("Gasblender Alarm", ALARM)
	CAN_ID_GAS_SET_POINT_CO2 = 0x08020000, //Set Point for CO2 (gasblender)	| 0.001 l/min
	CAN_ID_GAS_SET_POINT_O2 = 0x08020001, //Set Point for O2 (gasblender)	| 0.001 l/min
	CAN_ID_GAS_SET_POINT_N2 = 0x08020002, //Set Point for N2 (gasblender)	| 0.001 l/min
// idGroup("SERVO no Alarm", 2, CAN_SERVO_SHIFT)
	CAN_ID_SERVO_X_RR = 0x08050000, //Set Point for RR (ventilator)| 1 1/min
	CAN_ID_SERVO_X_FIO2 = 0x08050001, //Set Point for FiO2 (ventilator)| 1 %
	CAN_ID_SERVO_X_PEEP = 0x08050002, //Set Point for PEEP (ventilator)| 1 mbar
	CAN_ID_SERVO_X_VOL = 0x08050003, //Set Point for VOL (ventilator)| 1 L/min
	CAN_ID_SERVO_X_INSP_TIME = 0x08050004, //Set Point for InspTime (ventilator)| 1 %
	CAN_ID_SERVO_X_PAUSE_TIME = 0x08050005, //Set Point for PauseTime (ventilator)| 1 %
	CAN_ID_SERVO_X_RISE_TIME = 0x08050006, //Set Point for RiseTime (ventilator)| 1 %
	CAN_ID_SERVO_X_CMV = 0x08050007, //Set Point for CMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_TUP = 0x08050008, //Set Point for Trigger under PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_PCP = 0x08050009, //Set Point for Pressure controlled over PEEP (ventilator)| 1 mbar
	CAN_ID_SERVO_X_SIMV = 0x08050010, //Set Point for SIMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_PSP = 0x08050011, //Set Point for Pressure supported over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_CPAP = 0x08050012, //Set Point for CPAP Flow (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_RR_MIN = 0x08050020, //Set Min value for RR (ventilator)| 1 1/min
	CAN_ID_SERVO_X_FIO2_MIN = 0x08050021, //Set Min value for FIO2 (ventilator)| 1 %
	CAN_ID_SERVO_X_PEEP_MIN = 0x08050022, //Set Min value for PEEP (ventilator)| 1 mmH2O
	CAN_ID_SERVO_X_VOL_MIN = 0x08050023, //Set Min value for VOL (ventilator)| 0.001 l/min
	CAN_ID_SERVO_X_INSP_TIME_MIN = 0x08050024, //Set Min value for INSP_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_PAUSE_TIME_MIN = 0x08050025, //Set Min value for PAUSE_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_RISE_TIME_MIN = 0x08050026, //Set Min value for RISE_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_CMV_MIN = 0x08050027, //Set Min value for CMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_TUP_MIN = 0x08050028, //Set Min value for Trigger under PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_PCP_MIN = 0x08050029, //Set Min value for Pressure controlled over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_SIMV_MIN = 0x08050030, //Set Min value for SIMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_PSP_MIN = 0x08050031, //Set Min value for Pressure supported over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_CPAP_MIN = 0x08050032, //Set Min value for CPAP Flow (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_RR_MAX = 0x08050040, //Set Max value for RR (ventilator)| 1 l/min
	CAN_ID_SERVO_X_FIO2_MAX = 0x08050041, //Set Max value for FIO2 (ventilator)| 1 %
	CAN_ID_SERVO_X_PEEP_MAX = 0x08050042, //Set Max value for PEEP (ventilator)| 1 mmH2O
	CAN_ID_SERVO_X_VOL_MAX = 0x08050043, //Set Max value for VOL (ventilator)| 0.001 l/min
	CAN_ID_SERVO_X_INSP_TIME_MAX = 0x08050044, //Set Max value for INSP_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_PAUSE_TIME_MAX = 0x08050045, //Set Max value for PAUSE_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_RISE_TIME_MAX = 0x08050046, //Set Max value for RISE_TIME (ventilator)| 1%
	CAN_ID_SERVO_X_CMV_MAX = 0x08050047, //Set Max value for CMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_TUP_MAX = 0x08050048, //Set Max value for Trigger under PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_PCP_MAX = 0x08050049, //Set Max value for Pressure controlled over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_SIMV_MAX = 0x08050050, //Set Max value for SIMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_PSP_MAX = 0x08050051, //Set Max value for Pressure supported over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_CPAP_MAX = 0x08050052, //Set Max value for CPAP Flow (ventilator)| 1 cmH2O
// idGroup("PGA no Alarm", 2, CAN_PGA_SHIFT)
	CAN_ID_PGA_X_FUNCTION_NUMBER = 0x08060000, //Set Function of MCU
	CAN_ID_PGA_X_COMMAND = 0x08060001, //Send Command to PGA
	CAN_ID_PGA_X_SET_RT_O2 = 0x08060002, //Enable/Disable O2 RT channel | bool
	CAN_ID_PGA_X_SET_RT_CO2 = 0x08060003, //Enable/Disable CO2 RT channel | bool
	CAN_ID_PGA_X_SET_RT_PRESSURE = 0x08060004, //Enable/Disable Pressure RT channel | bool
// idGroup("DriverTests no Alarm")
	CAN_ID_DRIVERTESTS_CAN_SPEED = 0x081F0000, //Set CAN speed | 1 ms
	CAN_ID_DRIVERTESTS_TESTNR = 0x081F0001, //go to Test: (0:ADC 1:DAC 2:CAN 3:UART 4:Switch)
// idGroup("Pump Control")
	CAN_ID_PUMP_RPM_TARGET_MAN = 0x080D0000, // rpm | 1 rpm
	CAN_ID_PUMP_RPM_TARGET_CAN = 0x080D0001, // rpm | 1 rpm
	CAN_ID_PUMP_FLOW_TARGET_MAN = 0x080D0003, // flow | 1 ml/min
	CAN_ID_PUMP_FLOW_TARGET_CAN = 0x080D0004, // flow | 1 ml/min
	CAN_ID_PUMP_FLOW_TARGET_APPR = 0x080D0005, // flow | 1 ml/min
	CAN_ID_PUMP_FLOW_TARGET_MIN = 0x080D0006, // min. flow | 1 ml/min
	CAN_ID_PUMP_FLOW_TARGET_MAX = 0x080D0007, // max. flow | 1 ml/min
	CAN_ID_PUMP_FLOW_TARGET_CONT = 0x080D0008, // max. flow | 1 ml/min
	CAN_ID_PUMP_PROFILE_ACTIVE = 0x080D0010, // Aktives Profil
	CAN_ID_PUMP_PROFILE_ACTIVE_APPR = 0x080D0011, // Aktives Profil
	CAN_ID_PUMP_PROFILE_PERIODE = 0x080D0012, // Periodendauer
	CAN_ID_PUMP_PROFILE_PERIODE_APPR = 0x080D0013, // Periodendauer
	CAN_ID_PUMP_PROFILE_AMP = 0x080D0014, // Verstärkungsfaktor
	CAN_ID_PUMP_PROFILE_AMP_APPR = 0x080D0015, // Verstärkungsfaktor
	CAN_ID_PUMP_PROFILE_COMPLETE_A = 0x080D0016, // Profil komplett antwort
	CAN_ID_PUMP_PRESS_TARGET = 0x080D0020, // Target pressure difference over pump head | mmHg
	CAN_ID_PUMP_PRESS_BEFORE_OFFS = 0x080D0021, // Offset for pressure before pump head | mmHg
	CAN_ID_PUMP_PRESS_AFTER_OFFS = 0x080D0022, // Offset for pressure after pump head | mmHg
	CAN_ID_PUMP_PRESS_CONTROL_ACT = 0x080D0023, // Activate pressure control

// idGroup("PV1000 Control")
	CAN_ID_PV1000_RR 	= 0x08200000, //Set Point for RR (ventilator)| 1 1/min
	CAN_ID_PV1000_FIO2 	= 0x08200001, //Set Point for FiO2 (ventilator)| 1 %
	CAN_ID_PV1000_PEEP 	= 0x08200002, //Set Point for PEEP (ventilator)| 1 mbar
	CAN_ID_PV1000_Pinsp = 0x08200003, //Set Point for Pinsp (ventilator)| 1 mbar
	CAN_ID_PV1000_VOL 	= 0x08200004, //Set Point for VOL (ventilator)| 1 L/min

//####################################################################################################
// MMU-Notifications							0x0A...
//####################################################################################################
// idGroup("AS3 Alarm", 2, CAN_AS3_SHIFT, ALARM)
	CAN_ID_AS3_X_START_REQUESTS = 0x0A040010, // AS3 sent start requests.
	CAN_ID_AS3_X_STOP_REQUESTS = 0x0A040011, // AS3 sent stop requests.
// idGroup("Gasblender Alarm", ALARM)
	CAN_ID_GAS_ERROR_SET_POINT_CO2 = 0x0A020006, //Error in Set Point for CO2 (gasblender)	| 0.001 l/min
	CAN_ID_GAS_ERROR_SET_POINT_O2 = 0x0A020007, //Error in Set Point for O2 (gasblender)	| 0.001 l/min
	CAN_ID_GAS_ERROR_SET_POINT_N2 = 0x0A020008, //Error in Set Point for N2 (gasblender)	| 0.001 l/min
// idGroup("Pumpe", ALARM)
	CAN_ID_PUMP_WARNING_FLOW_TARGET_HIGH = 0x0A0D0001, // Received can flow-value is too high
	CAN_ID_PUMP_WARNING_FLOW_TARGET_LOW = 0x0A0D0002, // Received can flow-value is too low
	CAN_ID_PUMP_WARNING_AMPL_HIGH = 0x0A0D0010, // Amplitude zu hoch
	CAN_ID_PUMP_WARNING_PERIODE_LOW = 0x0A0D0011, // Periode zu niedrig
	CAN_ID_PUMP_WARNING_PERIODE_HIGH = 0x0A0D0012, // Periode zu hoch
	CAN_ID_PUMP_WARNING_PROFILE_EXISTS = 0x0A0D0013, // Profil existiert schon
	CAN_ID_PUMP_WARNING_NO_PROFILE = 0x0A0D0014, // Profil existiert nicht
	CAN_ID_PUMP_WARNING_PROFILE_UNDELETABLE = 0x0A0D0015, // Profil nicht löschbar
	//CAN_ID_PUMP_WARNING_PROFILE_SOLID = 0x0A0D0015, // Profil existiert nicht	
	CAN_ID_PUMP_WARNING_PROFILE_INCOMPLETE = 0x0A0D0016, // Profil nicht komplett
	CAN_ID_PUMP_WARNING_PROFILE_VAL_MISS = 0x0A0D0017, // Wert fehlt
	CAN_ID_PUMP_WARNING_MAX_VALUE_ID_HIGH = 0x0A0D0018, // Maximale Wert-ID zu hoch
	CAN_ID_PUMP_WARNING_MAX_VALUE_ID_LOW = 0x0A0D0019, // Maximale Wert-ID zu niedrig
	CAN_ID_PUMP_WARNING_ACCELERATION = 0x0A0D0020, // Beschleunigung zu hoch
	CAN_ID_PUMP_WARNING_PROFILE_CHECKSUM = 0x0A0D0021, // Checksumme stimmt nicht
// idGroup("SERVO Alarm", 2, CAN_SERVO_SHIFT, ALARM)
	CAN_ID_SERVO_X_COM_RESTART = 0x0A050000, // restart of communication to servo
	CAN_ID_SERVO_X_RCCO_GAIN_ERROR = 0x0A050001, // Gain is diffrent from the expected
	CAN_ID_SERVO_X_RCCO_GAIN_EXP_ERROR = 0x0A050002, // Gain exponent is diffrent from the expected
	CAN_ID_SERVO_X_RCCO_OFFSET_ERROR = 0x0A050003, // Offset is diffrent from the expected
	CAN_ID_SERVO_X_RCCO_OFFSET_EXP_ERROR = 0x0A050004, // Offset exponent is diffrent from the expected
	CAN_ID_SERVO_X_RCCO_UNIT_ERROR = 0x0A050005, // Unit  is diffrent from the expected
	CAN_ID_SERVO_X_WARNING_SET_HIGH = 0x0A050010, // letzter Set Wert ueber Controlvalue
	CAN_ID_SERVO_X_WARNING_SET_LOW = 0x0A050030, // letzter Set Wert unter Controlvalue
	CAN_ID_SERVO_X_WARNING_REAL = 0x0A050050, // Set Wert falsch uebernommen (Servo)
	CAN_ID_SERVO_X_WARNING_HIGH_SETFREQUENCY = 0x0A050060, // Setvalues frequency too high
	CAN_ID_SERVO_X_WARNING_VOLDIF = 0x0A050070, // in/expiratory Volume differs
// idGroup("Button")
	CAN_ID_Button = 0x0A0E0001, // Button State of experimental Button Sensor MCU
//####################################################################################################
// Model-Notifications							0x0B...
//####################################################################################################
// idGroup("Models")
	CAN_ID_MODEL_O2SAT_DELTA = 0x0BA00010, // O2SAT Delta		| 0.001 
	CAN_ID_MODEL_O2SAT_RELATIVE_ERROR = 0x0BA00000, // O2SAT Relative Error	| 0.1 %
//####################################################################################################
// Network-Notifications						0x0C...
//####################################################################################################
//----------------------------------------------------------------------------------------------------
// idGroup("Startup")
//----------------------------------------------------------------------------------------------------
#define CAN_STARTUP							0x0C000000  // indicates how the masked bits have to be set
#define CAN_DISABLED_CARDS					0x0C000010  // Needed for building the card disabled CAN ID in MCU code
#define CAN_STATUS_REPLY					0x0C000020  // Needed for building the status message CAN ID in MCU code
// the following concrete ids are only needed by the viewer, since the MCU-Software
// derives them using the device id, the startup pattern and the device number.
// idGroup("CDI no Alarm", 2, CAN_CDI_SHIFT)
	CAN_ID_CDI_X_STARTUP = 0x0C010000, // Startup sequence send out by CDI 500
	CAN_ID_CDI_X_CARD_DISABLED = 0x0C010010, // Card of CDI MCU full!
	CAN_ID_CDI_X_STATUS_REPLY = 0x0C010020, // Status message of CDI MCU in response of the time beacon
// idGroup("Gasblender no Alarm")
	CAN_ID_GAS_Startup = 0x0C020000, // Startup sequence send out by Gas blender
	CAN_ID_GAS_CARD_DISABLED = 0x0C020010, // Card of Gasblender MCU full!
	CAN_ID_GAS_STATUS_REPLY = 0x0C020020, // Status message of Gasblender MCU in response of the time beacon
// idGroup("Pressure Sensor no Alarm")
	CAN_ID_PRESSURE_Startup = 0x0C030000, // Startup sequence send out by Pressure Sensor
	CAN_ID_PRESSURE_CARD_DISABLED = 0x0C030010, // Card of Pressure Sensor MCU full!
	CAN_ID_PRESSURE_STATUS_REPLY = 0x0C030020, // Status message of Pressure Sensor MCU in response of the time beacon
// idGroup("AS3 no Alarm", 2, CAN_AS3_SHIFT)
	CAN_ID_AS3_X_STARTUP = 0x0C040000, // Startup sequence send out by Datex AS 3
	CAN_ID_AS3_X_CARD_DISABLED = 0x0C040010, // Card of AS3 MCU full!
	CAN_ID_AS3_X_STATUS_REPLY = 0x0C040020, // Status message of AS3 MCU in response of the time beacon
// idGroup("SERVO no Alarm", 2, CAN_SERVO_SHIFT)
	CAN_ID_SERVO_X_STARTUP = 0x0C050000, // Startup sequence send out by Servo Ventilator 300
	CAN_ID_SERVO_X_CARD_DISABLED = 0x0C050010, // Card of SERVO MCU full!
	CAN_ID_SERVO_X_STATUS_REPLY = 0x0C050020, // Status message of SERVO MCU in response of the time beacon
// idGroup("PGA no Alarm", 2, CAN_PGA_SHIFT)
	CAN_ID_PGA_X_STARTUP = 0x0C060000, // Startup sequence send out by PGA
	CAN_ID_PGA_X_CARD_DISABLED = 0x0C060010, // Card of PGA MCU full!
	CAN_ID_PGA_X_STATUS_REPLY = 0x0C060020, // Status message of SERVO MCU in response of the time beacon
// idGroup("N560 no Alarm", 2, CAN_N560_SHIFT)
	CAN_ID_N560_X_STARTUP = 0x0C070000, // Startup sequence send out by N560
	CAN_ID_N560_X_CARD_DISABLED = 0x0C070010, // Card of N560 MCU full!
	CAN_ID_N560_X_STATUS_REPLY = 0x0C070020, // Status message of SERVO MCU in response of the time beacon
// idGroup("RECIRCULATION no Alarm", 2, CAN_RECIRCULATION_SHIFT)
	CAN_ID_RECIRCULATION_X_STARTUP = 0x0C080000, // Startup sequence send out by RECIRCULATION
	CAN_ID_RECIRCULATION_X_CARD_DISABLED = 0x0C080010, // Card of Recirculation MCU full!
	CAN_ID_RECIRCULATION_X_STATUS_REPLY = 0x0C080020, // Status message of SERVO MCU in response of the time beacon
// idGroup("PiCCO2 no Alarm")
	CAN_ID_PiCCO_Startup = 0x0C090000, // Startup sequence send out by PiCCO
	CAN_ID_PiCCO_CARD_DISABLED = 0x0C090010, // Card of PiCCO MCU full!
	CAN_ID_PiCCO_STATUS_REPLY = 0x0C090020, // Status message of PiCCO MCU in response of the time beacon
// idGroup("TCM no Alarm")
	CAN_ID_CombiM_STARTUP = 0x0C0A0000, // Startup sequence send out by TCM CombiM
	CAN_ID_CombiM_CARD_DISABLED = 0x0C0A0010, // Card of CombiM MCU full!
	CAN_ID_CombiM_STATUS_REPLY = 0x0C0A0020, // Status message of CombiM MCU in response of the time beacon
// idGroup("Temperature no Alarm")
	CAN_ID_TEMPERATURE_Startup = 0x0C0B0000, // Startup sequence send out by Temperature Sensor
	CAN_ID_TEMPERATURE_CARD_DISABLED = 0x0C0B0010, // Card of Temperature Sensor MCU full!
	CAN_ID_TEMPERATURE_STATUS_REPLY = 0x0C0B0020, // Status message of Temperature Sensor MCU in response of the time beacon
// idGroup("Blood Flow no Alarm", 2, CAN_BLOOD_FLOW_SHIFT)
	CAN_ID_BLOOD_FLOW_X_Startup = 0x0C0C0000, // Startup sequence send out by BloodFlor Sensor 1
	CAN_ID_BLOOD_FLOW_X_CARD_DISABLED = 0x0C0C0010, // Card of BloodFlow Sensor 1 MCU full!
	CAN_ID_BLOOD_FLOW_X_STATUS_REPLY = 0x0C0C0020, // Status message of BloodFlow Sensor 1 MCU in response of the time beacon
// idGroup("Pump Control no Alarm")
	CAN_ID_PUMP_Startup = 0x0C0D0000, // Startup sequence send out by BloodFlor Sensor 1
// idGroup("Button no Alarm")
	CAN_ID_BUTTON_Startup = 0x0C0E0000, // Startup sequence send out by MCU for testing Purpose
	CAN_ID_Button_CARD_DISABLED = 0x0C0E0010, // Card of Button Sensor MCU full!
	CAN_ID_Button_STATUS_REPLY = 0x0C0E0020, // Status message of Button Sensor MCU in response of the time beacon
// idGroup("Flow_Board no Alarm")
	CAN_ID_FLOW_BOARD_Startup = 0x0C0F0000, // Startup sequence send out by MCU for testing Purpose
	CAN_ID_FLOW_BOARD_CARD_DISABLED = 0x0C0F0010, // Card of Button Sensor MCU full!
	CAN_ID_FLOW_BOARD_STATUS_REPLY = 0x0C0F0020, // Status message of Button Sensor MCU in response of the time beacon
// idGroup("TOM no Alarm", 2, CAN_TOM_SHIFT)
	CAN_ID_TOM_X_STARTUP = 0x0C100000, // Startup sequence send out by TOM
	CAN_ID_TOM_X_CARD_DISABLED = 0x0C100010, // Card of TOM MCU full!
	CAN_ID_TOM_X_STATUS_REPLY = 0x0C100020, // Status message of TOM MCU in response of the time beacon
// idGroup("DriverTests no Alarm", 16, CAN_DRIVERTESTS_SHIFT)
	CAN_ID_DRIVERTESTS_X_Startup = 0x0C1F0000, // Startup sequence send out by MCU for testing Purpose
	CAN_ID_DRIVERTESTS_X_CARD_DISABLED = 0x0C1F0010, // Card of DriverTests Sensor MCU full!
	CAN_ID_DRIVERTESTS_X_STATUS_REPLY = 0x0C1F0020, // Status message of DriverTests Sensor MCU in response of the time beacon
//----------------------------------------------------------------------------------------------------
// idGroup("Comments")
//----------------------------------------------------------------------------------------------------
	CAN_ID_DSPACE_CONTROL_COMMENT = 0x0CFE0000, // Kommentar vom Kontroll PC der dSpace Box
	CAN_ID_DSPACE_BGA_COMMENT = 0x0CFE0001, // COMMENT*10+BGA_ID 1=Art 2=OxyIn 3=OxyOut 4=gemVen 5=perVen 6=ACT
	CAN_ID_DSPACE_DRUG_TYPE_COMMENT = 0x0CFE0002, // COMMENT*1e4+DrugUnitDenominator_ID(0=none;1=s;2=min;3=h)*1000+DrugUnitNominator_ID(0=s;1=mL;2=mg;3=IE;4=IE/mL;5=mg/mL;6=Percent;7=ug;8=uL)*100+DrugID(1=ACT;2=Atropin;3=Bisprolol;4=Esmeron;5=Fentanyl;6=Heparin;7=Kalium;8=Magensium;9=Noradrenalin;10=Suprarenin;11=Propofol;12=Thiopental)
	CAN_ID_DSPACE_DRUG_VALUE_COMMENT = 0x0CFE0003, // Amount of given drug type  
	CAN_ID_DSPACE_DRIP_COMMENT = 0x0CFE0004, // COMMENT*1e5+Drip_value_mL*10+DripID(1=Sterofundin;2=Gelafundin 4%;3=NaCl 0.9% Lavage)

	CAN_ID_COMMENT = 0x0CFF0000, // Comment Log Message
//####################################################################################################
// Measurements									0x10...
//####################################################################################################
//----------------------------------------------------------------------------------------------------
// idGroup("CDI Alarm", 2, CAN_CDI_SHIFT, ALARM)
//----------------------------------------------------------------------------------------------------
#define CAN_CDI_SHIFT	12
	CAN_ID_CDI_X_APH = 0x10010000, //Arterieller pH			| 0.01
	CAN_ID_CDI_X_ACO2 = 0x10010001, //Arterieller CO2			| mmHg
	CAN_ID_CDI_X_AO2 = 0x10010002, //Arterieller O2			| mmHg
	CAN_ID_CDI_X_ATEMP = 0x10010003, //Arterielle Temperatur		| 0.1 celsius
	CAN_ID_CDI_X_ASO2 = 0x10010004, //Arterielle Saettigung O2		| %
	CAN_ID_CDI_X_AHCO3 = 0x10010005, //Arterieller HCO3		| meq/l
	CAN_ID_CDI_X_ABASE = 0x10010006, //Arterieller Basenueberschuss	| meq/l
	CAN_ID_CDI_X_KALIUM = 0x10010007, //K+	| 0.1 meq/l
	CAN_ID_CDI_X_UO2 = 0x10010008, //Verbrauch (Vo2)			|
	CAN_ID_CDI_X_VPH = 0x10010009, //Venoeser pH			| 0.01
	CAN_ID_CDI_X_VCO2 = 0x1001000A, //Venoeser CO2			| mmHg
	CAN_ID_CDI_X_VO2 = 0x1001000B, //Venoeser O2			| mmHg
	CAN_ID_CDI_X_VTEMP = 0x1001000C, //Venoese Temperatur		| 0.1 Celsius
	CAN_ID_CDI_X_VSO2 = 0x1001000D, //Venoeser Saettigung O2		| %
	CAN_ID_CDI_X_VHCO3 = 0x1001000E, //Venoeser HCO3			|
	CAN_ID_CDI_X_VBASE = 0x1001000F, //Venoeser Basenueberschuss		|
	CAN_ID_CDI_X_HCT = 0x10010010, //Haematokrit			| %
	CAN_ID_CDI_X_HGB = 0x10010011, //Haemoglobin			| 0.1 g/dL
	CAN_ID_CDI_X_AFLOW = 0x10010012, //Arterieller Fluss			|
	CAN_ID_CDI_X_BSA = 0x10010013, //Bereich der Koerperoberflaeche	| m sqr
//----------------------------------------------------------------------------------------------------
// idGroup("Gasblender Alarm", ALARM)
//----------------------------------------------------------------------------------------------------
	CAN_ID_GAS_ACTUAL_CO2 = 0x10020003, //Actual value for CO2 (Gasblender)	| 0.001 l/min
	CAN_ID_GAS_ACTUAL_O2 = 0x10020004, //Actual value for O2 (Gasblender)	| 0.001 l/min
	CAN_ID_GAS_ACTUAL_N2 = 0x10020005, //Actual value for N2 (Gasblender)	| 0.001 l/min
//----------------------------------------------------------------------------------------------------
// idGroup("Pressure Sensor Alarm", ALARM)
//----------------------------------------------------------------------------------------------------
	CAN_ID_PRESSURE_SIG1 = 0x10030000, //Pressure from Signal 1	| mmHg
	CAN_ID_PRESSURE_SIG2 = 0x10030001, //Pressure from Signal 2	| mmHg
	CAN_ID_PRESSURE_SIG3 = 0x10030002, //Pressure from Signal 3	| mmHg
	CAN_ID_PRESSURE_SIG4 = 0x10030003, //Pressure from Signal 4	| mmHg
//----------------------------------------------------------------------------------------------------
// idGroup("AS3 Alarm", 2, CAN_AS3_SHIFT, ALARM)
// Datex-Ohmeda AS3 Physioligical Data Basic part
//----------------------------------------------------------------------------------------------------
#define CAN_AS3_SHIFT	12
	CAN_ID_AS3_X_PD_BASIC_ECG_HR = 0x10040000, //Heart Rate | per minute
	CAN_ID_AS3_X_PD_BASIC_ECG_ST1 = 0x10040001, //ST level	| 0.01 mm
	CAN_ID_AS3_X_PD_BASIC_ECG_ST2 = 0x10040002, //ST level	| 0.01 mm
	CAN_ID_AS3_X_PD_BASIC_ECG_ST3 = 0x10040003, //ST level	| 0.01 mm
	CAN_ID_AS3_X_PD_BASIC_ECG_RR_IMPEDANCE = 0x10040004, //Respiration Rate based on ECG impedance measurement	| per minute
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_1_SYS = 0x10040010, //systolic pressure 1	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_1_DIA = 0x10040011, //diastolic pressure 1	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_1_MEAN = 0x10040012, //mean pressure 1	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_1_HR = 0x10040013, //Heart Rate 1	| per minute
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_2_SYS = 0x10040020, //systolic pressure 2	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_2_DIA = 0x10040021, //diastolic pressure 2	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_2_MEAN = 0x10040022, //mean pressure 2	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_2_HR = 0x10040023, //Heart Rate 2	| per minute
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_3_SYS = 0x10040030, //systolic pressure 3	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_3_DIA = 0x10040031, //diastolic pressure 3	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_3_MEAN = 0x10040032, //mean pressure 3	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_3_HR = 0x10040033, //Heart Rate 3	| per minute
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_4_SYS = 0x10040040, //systolic pressure 4	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_4_DIA = 0x10040041, //diastolic pressure 4	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_4_MEAN = 0x10040042, //mean pressure 4	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_INV_PRESSURE_4_HR = 0x10040043, //Heart Rate 4	| per minute
	CAN_ID_AS3_X_PD_BASIC_NONINV_PRESSURE_SYS = 0x10040050, //systolic pressure	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_NONINV_PRESSURE_DIA = 0x10040051, //diastolic pressure	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_NONINV_PRESSURE_MEAN = 0x10040052, //mean pressure	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_NONINV_PRESSURE_HR = 0x10040053, //Heart Rate 	| per minute
	CAN_ID_AS3_X_PD_BASIC_TEMP1 = 0x10040060, //Temperature 1 	| 0.01 Centigrade
	CAN_ID_AS3_X_PD_BASIC_TEMP2 = 0x10040061, //Temperature 2	| 0.01 Centigrade
	CAN_ID_AS3_X_PD_BASIC_TEMP3 = 0x10040062, //Temperature 3	| 0.01 Centigrade
	CAN_ID_AS3_X_PD_BASIC_TEMP4 = 0x10040063, //Temperature 4	| 0.01 Centigrade
	CAN_ID_AS3_X_PD_BASIC_SPO2_SPO2 = 0x10040070, //Peripheral Oxygen Saturation	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_SPO2_PR = 0x10040071, //Pulse Rate	| per minute
	CAN_ID_AS3_X_PD_BASIC_SPO2_MOD = 0x10040072, // Plethysmograph amplitude modulation	| %
	CAN_ID_AS3_X_PD_BASIC_SPO2_SVO2 = 0x10040073, //Saturation dependend on label	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_CO2_EXP = 0x10040080, //expiratory CO2 concentration	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_CO2_INSP = 0x10040081, //inspiratory CO2 Concentration	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_CO2_RR = 0x10040082, //Respiration Rate	| per minute
	CAN_ID_AS3_X_PD_BASIC_CO2_AMB_PRESS = 0x10040083, //Ambient pressure	| 0.1 mmHg
	CAN_ID_AS3_X_PD_BASIC_O2_EXP = 0x10040090, //expiratory O2 concentration	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_O2_INSP = 0x10040091, //inspiratory O2 concentration	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_N2O_EXP = 0x100400A0, //expiratory N2O concentration	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_N2O_INSP = 0x100400A1, //inspiratory N2O concentration	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_ANESTHESIA_EXP = 0x100400B0, //expiratory anesthesia agent concentration	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_ANESTHESIA_INSP = 0x100400B1, //inspiratory anesthesia agent concentration	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_ANESTHESIA_MAC = 0x100400B2, //total Minimum Alveolar Concentration of anesthesia agent	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_FLOW_RR = 0x100400C0, //Respiration Rate	| per minute
	CAN_ID_AS3_X_PD_BASIC_FLOW_PPEAK = 0x100400C1, //peak pressure	| 0.01 cmH20
	CAN_ID_AS3_X_PD_BASIC_FLOW_PEEP = 0x100400C2, //positive expiratory end pressure	| 0.01 cmH20	
	CAN_ID_AS3_X_PD_BASIC_FLOW_PPLAT = 0x100400C3, //plateu pressure	| 0.01 cmH20
	CAN_ID_AS3_X_PD_BASIC_FLOW_TV_INSP = 0x100400C4, //inspiratory tidal volume	| 0.1 ml
	CAN_ID_AS3_X_PD_BASIC_FLOW_TV_EXP = 0x100400C5, //expiratory tidal volume	| 0.1 ml
	CAN_ID_AS3_X_PD_BASIC_FLOW_COMPLIANCE = 0x100400C6, //Compliance	| 0.01 ml per cmH2O
	CAN_ID_AS3_X_PD_BASIC_FLOW_MV_EXP = 0x100400C7, //expiratory minute volume	| 0.01 l per minute
	CAN_ID_AS3_X_PD_BASIC_CARDIAC_OUTPUT = 0x100400D0, //Cardiac Output	| ml per minute
	CAN_ID_AS3_X_PD_BASIC_CARDIAC_TEMP = 0x100400D1, //blood temperature	| 0.01 centigrade
	CAN_ID_AS3_X_PD_BASIC_CARDIAC_REF = 0x100400D2, //right heart ejection fraction	| %
	CAN_ID_AS3_X_PD_BASIC_CARDIAC_WP = 0x100400D3, //Wedge Pressure	| 0.01 mmHg
	CAN_ID_AS3_X_PD_BASIC_NMT_T1 = 0x100400E0, //TOF Twich 1	| 0.1 %
	CAN_ID_AS3_X_PD_BASIC_NMT_TRATIO = 0x100400E1, //???	| 0.1 %	
	CAN_ID_AS3_X_PD_BASIC_NMT_PTC = 0x100400E2, //???	| 
	CAN_ID_AS3_X_PD_BASIC_ECG_EXTRA_HR_ECG = 0x100400F0, //Heart Rate derived from the ECG signal	|
	CAN_ID_AS3_X_PD_BASIC_ECG_EXTRA_HR_MAX = 0x100400F1, //Maximun Heart Rate derived from the ECG signal	|
	CAN_ID_AS3_X_PD_BASIC_ECG_EXTRA_HR_MIN = 0x100400F2, //Minimun Heart Rate derived from the ECG signal	|
	CAN_ID_AS3_X_PD_BASIC_SVO2 = 0x10040100, // SvO2	| 0.01 %
	CAN_ID_AS3_X_PD_BASIC_PRESSURE_5_SYS = 0x10040110, //systolic pressure 5	|
	CAN_ID_AS3_X_PD_BASIC_PRESSURE_5_DIA = 0x10040111, //diastolic pressure 5	|
	CAN_ID_AS3_X_PD_BASIC_PRESSURE_5_MEAN = 0x10040112, //mean pressure 5	|
	CAN_ID_AS3_X_PD_BASIC_PRESSURE_5_HR = 0x10040113, //Heart Rate 5	|
	CAN_ID_AS3_X_PD_BASIC_PRESSURE_6_SYS = 0x10040120, //systolic pressure 6	|
	CAN_ID_AS3_X_PD_BASIC_PRESSURE_6_DIA = 0x10040121, //diastolic pressure 6	|
	CAN_ID_AS3_X_PD_BASIC_PRESSURE_6_MEAN = 0x10040122, //mean pressure 6	|
	CAN_ID_AS3_X_PD_BASIC_PRESSURE_6_HR = 0x10040123, //Heart Rate 6	|
//----------------------------------------------------------------------------------------------------
// Datex-Ohmeda AS3 Physioligical Data Ext1 part
//----------------------------------------------------------------------------------------------------	
	CAN_ID_AS3_X_PD_EXT1_ARRH_ECG_HR = 0x10040200, //Heart Rate	| per minute
	CAN_ID_AS3_X_PD_EXT1_ARRH_ECG_RR_TIME = 0x10040201, //R-to-R time	| ms
	CAN_ID_AS3_X_PD_EXT1_ARRH_ECG_PVC = 0x10040202, //PVC rate	| per minute
	CAN_ID_AS3_X_PD_EXT1_ECG12_ST1 = 0x10040210, //ST level	| 0.01 mm
	CAN_ID_AS3_X_PD_EXT1_ECG12_ST2 = 0x10040211, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_ST3 = 0x10040212, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_AVL = 0x10040213, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_AVR = 0x10040214, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_AVF = 0x10040215, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_V1 = 0x10040216, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_V2 = 0x10040217, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_V3 = 0x10040218, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_V4 = 0x10040219, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_V5 = 0x1004021A, //ST level	|
	CAN_ID_AS3_X_PD_EXT1_ECG12_V6 = 0x1004021B, //ST level	|
//----------------------------------------------------------------------------------------------------
// Datex-Ohmeda AS3 Physioligical Data Ext2 part
//----------------------------------------------------------------------------------------------------	
	CAN_ID_AS3_X_PD_EXT2_NMT2_T1 = 0x10040300, //t1 absolute value	|
	CAN_ID_AS3_X_PD_EXT2_NMT2_T2 = 0x10040301, //t2 absolute value	|	
	CAN_ID_AS3_X_PD_EXT2_NMT2_T3 = 0x10040302, //t3 absolute value	|
	CAN_ID_AS3_X_PD_EXT2_NMT2_T4 = 0x10040303, //t4 absolute value	|
	CAN_ID_AS3_X_PD_EXT2_EEG_FEMG = 0x10040310, //frontal electromyography	| 0.01 microvolt
	CAN_ID_AS3_X_PD_EXT2_EEG_1_AMPL = 0x10040320, //RMS amplitude	| 0.01 microvolt
	CAN_ID_AS3_X_PD_EXT2_EEG_1_SEF = 0x10040321, //Spectral Edge Frequency		| 0.01 Hz
	CAN_ID_AS3_X_PD_EXT2_EEG_1_MF = 0x10040322, //median frequency	| 0.01 Hz
	CAN_ID_AS3_X_PD_EXT2_EEG_1_DELTA_PROC = 0x10040323, //relative power spectral content in delta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_1_THETA_PROC = 0x10040324, //relative power spectral content in theta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_1_ALPHA_PROC = 0x10040325, //relative power spectral content in alpha band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_1_BETA_PROC = 0x10040326, //relative power spectral content in beta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_1_BSR = 0x10040327, //Burst suppression ratio	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_2_AMPL = 0x10040330, //RMS amplitude	| 0.01 microvolt
	CAN_ID_AS3_X_PD_EXT2_EEG_2_SEF = 0x10040331, //Spectral Edge Frequency		| 0.01 Hz
	CAN_ID_AS3_X_PD_EXT2_EEG_2_MF = 0x10040332, //median frequency	| 0.01 Hz
	CAN_ID_AS3_X_PD_EXT2_EEG_2_DELTA_PROC = 0x10040333, //relative power spectral content in delta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_2_THETA_PROC = 0x10040334, //relative power spectral content in theta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_2_ALPHA_PROC = 0x10040335, //relative power spectral content in alpha band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_2_BETA_PROC = 0x10040336, //relative power spectral content in beta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_2_BSR = 0x10040337, //Burst suppression ratio	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_3_AMPL = 0x10040340, //RMS amplitude	| 0.01 microvolt
	CAN_ID_AS3_X_PD_EXT2_EEG_3_SEF = 0x10040341, //Spectral Edge Frequency		| 0.01 Hz
	CAN_ID_AS3_X_PD_EXT2_EEG_3_MF = 0x10040342, //median frequency	| 0.01 Hz
	CAN_ID_AS3_X_PD_EXT2_EEG_3_DELTA_PROC = 0x10040343, //relative power spectral content in delta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_3_THETA_PROC = 0x10040344, //relative power spectral content in theta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_3_ALPHA_PROC = 0x10040345, //relative power spectral content in alpha band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_3_BETA_PROC = 0x10040346, //relative power spectral content in beta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_3_BSR = 0x10040347, //Burst suppression ratio	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_4_AMPL = 0x10040350, //RMS amplitude	| 0.01 microvolt
	CAN_ID_AS3_X_PD_EXT2_EEG_4_SEF = 0x10040351, //Spectral Edge Frequency		| 0.01 Hz
	CAN_ID_AS3_X_PD_EXT2_EEG_4_MF = 0x10040352, //median frequency	| 0.01 Hz
	CAN_ID_AS3_X_PD_EXT2_EEG_4_DELTA_PROC = 0x10040353, //relative power spectral content in delta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_4_THETA_PROC = 0x10040354, //relative power spectral content in theta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_4_ALPHA_PROC = 0x10040355, //relative power spectral content in alpha band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_4_BETA_PROC = 0x10040356, //relative power spectral content in beta band	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_4_BSR = 0x10040357, //Burst suppression ratio	| %	
	CAN_ID_AS3_X_PD_EXT2_EEG_BIS_BIS = 0x10040360, //BIS bispektral Index	|
	CAN_ID_AS3_X_PD_EXT2_EEG_BIS_SQI = 0x10040361, //BIS Signal Quality Index	| %
	CAN_ID_AS3_X_PD_EXT2_EEG_BIS_EMG = 0x10040362, //BIS Electromyography	| dB
	CAN_ID_AS3_X_PD_EXT2_EEG_BIS_SR = 0x10040363, //BIS Suppression Ratio	| %
	CAN_ID_AS3_X_PD_EXT2_ENTROPY_EEG = 0x10040370, //state entropy	| N.A
	CAN_ID_AS3_X_PD_EXT2_ENTROPY_EMG = 0x10040371, //response entropy	| N.A
	CAN_ID_AS3_X_PD_EXT2_ENTROPY_BSR = 0x10040372, //entropy burst suppression ratio	| %
	CAN_ID_AS3_X_PD_EXT2_EEG2_COMMON = 0x10040380, //common reference electron label	| N.A
	CAN_ID_AS3_X_PD_EXT2_EEG2_CH_1_M = 0x10040381, //Negative electrode label for cahnnel 1	| N.A
	CAN_ID_AS3_X_PD_EXT2_EEG2_CH_1_P = 0x10040382, //Positive electrode label for cahnnel 1	| N.A
	CAN_ID_AS3_X_PD_EXT2_EEG2_CH_2_M = 0x10040383, //Negative electrode label for cahnnel 2	| N.A
	CAN_ID_AS3_X_PD_EXT2_EEG2_CH_2_P = 0x10040384, //Positive electrode label for cahnnel 2	| N.A
	CAN_ID_AS3_X_PD_EXT2_EEG2_CH_3_M = 0x10040385, //Negative electrode label for cahnnel 3	| N.A
	CAN_ID_AS3_X_PD_EXT2_EEG2_CH_3_P = 0x10040386, //Positive electrode label for cahnnel 3	| N.A
	CAN_ID_AS3_X_PD_EXT2_EEG2_CH_4_M = 0x10040387, //Negative electrode label for cahnnel 4	| N.A
	CAN_ID_AS3_X_PD_EXT2_EEG2_CH_4_P = 0x10040388, //Positive electrode label for cahnnel 4	| N.A
//----------------------------------------------------------------------------------------------------
// Datex-Ohmeda AS3 Physioligical Data Ext3 part
//----------------------------------------------------------------------------------------------------	
	CAN_ID_AS3_X_PD_EXT3_GASEXCH_VO2 = 0x10040400, //Oxygen Consumption	| 0.1 ml per minute
	CAN_ID_AS3_X_PD_EXT3_GASEXCH_VCO2 = 0x10040401, //Carbondioxide Consumption	| 0.1 ml per minute
	CAN_ID_AS3_X_PD_EXT3_GASEXCH_EE = 0x10040402, //energy expenditure		| 1 kcal per 24h
	CAN_ID_AS3_X_PD_EXT3_GASEXCH_RQ = 0x10040403, //Respiratory Quotient
	CAN_ID_AS3_X_PD_EXT3_FLOW_IPEEP = 0x10040410, //intrinsic PEEP	| 0.01 cmH2O
	CAN_ID_AS3_X_PD_EXT3_FLOW_PMEAN = 0x10040411, //mean pressure	| 0.01 cmH2O
	CAN_ID_AS3_X_PD_EXT3_FLOW_RAW = 0x10040412, //airway resistance	| 0.01 cmH2O/(L/s)
	CAN_ID_AS3_X_PD_EXT3_FLOW_MV_INSP = 0x10040413, //inspired minute volume	| 0.01 L per minute
	CAN_ID_AS3_X_PD_EXT3_FLOW_EPEEP = 0x10040414, //extrinsic PEEP	| 0.01 cmH2O 
	CAN_ID_AS3_X_PD_EXT3_FLOW_MV_EXP = 0x10040415, //spontaneous expired minute volume	| 0.01 L per minute
	CAN_ID_AS3_X_PD_EXT3_FLOW_IE_RATIO = 0x10040416, //inspiration time vs. expiration time ratio	|
	CAN_ID_AS3_X_PD_EXT3_FLOW_INSP_TIME = 0x10040417, //inspiration time	| 0.01 s
	CAN_ID_AS3_X_PD_EXT3_FLOW_EXP_TIME = 0x10040418, //expiration time	| 0.01 s
	CAN_ID_AS3_X_PD_EXT3_FLOW_STAT_COMPL = 0x10040419, //static complience	| 0.01 ml per cmH20
	CAN_ID_AS3_X_PD_EXT3_FLOW_STAT_PPLAT = 0x1004041A, //static plateau pressure	| 0.01 cmH2O
	CAN_ID_AS3_X_PD_EXT3_FLOW_STAT_PEEPE = 0x1004041B, //static extrinsic PEEP	| 0.01 cmH2O
	CAN_ID_AS3_X_PD_EXT3_FLOW_STAT_PEEPI = 0x1004041C, //static intrinsic PEEP	| 0.01 cmH2O
	CAN_ID_AS3_X_PD_EXT3_BALANCE_GAS_EC = 0x10040420, //expiratory concentration of balance gas	| 0.01 %
	CAN_ID_AS3_X_PD_EXT3_BALANCE_GAS_IC = 0x10040421, //inspiratory concentration of balance gas	| 0.01 %
	CAN_ID_AS3_X_PD_EXT3_TONOM_PRCO2 = 0x10040430, //PrCO2 concentration	| 0.01 kPa
	CAN_ID_AS3_X_PD_EXT3_TONOM_PR_ET = 0x10040431, //P(r-Et)CO2 gap	| 0.01 kPa
	CAN_ID_AS3_X_PD_EXT3_TONOM_PR_PA = 0x10040432, //P(r-Et)O2 gap	| 0.01 kPa
	CAN_ID_AS3_X_PD_EXT3_TONOM_PA_DELAY = 0x10040433, //PaCO2 delay	| min
	CAN_ID_AS3_X_PD_EXT3_TONOM_PHI = 0x10040434, //pHi value	| 0.01
	CAN_ID_AS3_X_PD_EXT3_TONOM_PHI_DELAY = 0x10040435, //pHi delay	| min
	CAN_ID_AS3_X_PD_EXT3_TONOM_AMB_PRESS = 0x10040436, //ambient pressure	| 0.1 mmHg
	CAN_ID_AS3_X_PD_EXT3_TONOM_CPMA = 0x10040437, //10 sec. minimum catheter pressure (research data??)	| 0.1 mbar
	CAN_ID_AS3_X_PD_EXT3_ANESTHESIA_MAC = 0x10040440, //age corrected MAC value	| index(0-2)
//----------------------------------------------------------------------------------------------------
// Datex-Ohmeda AS3 Waveform Data
//----------------------------------------------------------------------------------------------------	
	CAN_ID_AS3_X_WAVE_CMD = 0x10040500, //Waveform Command
	CAN_ID_AS3_X_WAVE_ECG1 = 0x10040501, //ECG channel 1
	CAN_ID_AS3_X_WAVE_ECG2 = 0x10040502, //ECG channel 2
	CAN_ID_AS3_X_WAVE_ECG3 = 0x10040503, //ECG channel 3
	CAN_ID_AS3_X_WAVE_INVP1 = 0x10040504, //invasive pressure channel 1	| 0.01 mmHg
	CAN_ID_AS3_X_WAVE_INVP2 = 0x10040505, //invasive pressure channel 2	| 0.01 mmHg
	CAN_ID_AS3_X_WAVE_INVP3 = 0x10040506, //invasive pressure channel 3	| 0.01 mmHg
	CAN_ID_AS3_X_WAVE_INVP4 = 0x10040507, //invasive pressure channel 4 | 0.01 mmHg
	CAN_ID_AS3_X_WAVE_PLETH = 0x10040508, //Plethysmograph
	CAN_ID_AS3_X_WAVE_CO2 = 0x10040509, //CO2
	CAN_ID_AS3_X_WAVE_O2 = 0x1004050A, //O2
	CAN_ID_AS3_X_WAVE_N2O = 0x1004050B, //N2O
	CAN_ID_AS3_X_WAVE_AA = 0x1004050C, //Anasthesia Agent
	CAN_ID_AS3_X_WAVE_AWP = 0x1004050D, //Airway Pressure
	CAN_ID_AS3_X_WAVE_FLOW = 0x1004050E, //Airway Flow
	CAN_ID_AS3_X_WAVE_RESP = 0x1004050F, //ECG respiratory waveform
	CAN_ID_AS3_X_WAVE_INVP5 = 0x10040510, //invasive pressure channel 5 | 0.01 mmHg
	CAN_ID_AS3_X_WAVE_INVP6 = 0x10040511, //invasive pressure channel 6 | 0.01 mmHg
	CAN_ID_AS3_X_WAVE_EEG1 = 0x10040512, //EEG channel 1
	CAN_ID_AS3_X_WAVE_EEG2 = 0x10040513, //EEG channel 2
	CAN_ID_AS3_X_WAVE_EEG3 = 0x10040514, //EEG channel 3
	CAN_ID_AS3_X_WAVE_EEG4 = 0x10040515, //EEG channel 4
	CAN_ID_AS3_X_WAVE_VOL = 0x10040516, //Airway Volume
	CAN_ID_AS3_X_WAVE_TONO_PRESS = 0x10040517, //Tonometry catheter pressure
	CAN_ID_AS3_X_WAVE_SPIRO = 0x10040518, //Spirometry loop bit pattern
	CAN_ID_AS3_X_WAVE_ENT = 0x10040519, //Entropy ??
	CAN_ID_AS3_X_WAVE_EEG_BIS = 0x1004051A, //BIS??
//----------------------------------------------------------------------------------------------------
// idGroup("SERVO Alarm", 2, CAN_SERVO_SHIFT, ALARM)
// Servo 300
//----------------------------------------------------------------------------------------------------
#define CAN_SERVO_SHIFT	12
	CAN_ID_SERVO_X_AIRWAY_FLOW = 0x10050000, //Airway flow | 0.000006 L per minute
	CAN_ID_SERVO_X_PHASE = 0x10050001, //Airway phase
	CAN_ID_SERVO_X_AIRWAY_PRESSURE_INSP = 0x10050002, //Airway Pressure insp. | 0.0000980665 mbar
	CAN_ID_SERVO_X_AIRWAY_PRESSURE_EXP = 0x10050003, //Airway Pressure exp.  | 0.0000980665 mbar
	CAN_ID_SERVO_X_PAUSE_PRESSURE = 0x10050004, //Pause Pressure | 0.0980638 mbar
	CAN_ID_SERVO_X_PEAK_PRESSURE = 0x10050005, //Peak Pressure | 0.0980638 mbar
	CAN_ID_SERVO_X_O2_CONCENTRATION = 0x10050006, //O2-concentration | 0.1 %
	CAN_ID_SERVO_X_CO2_CONCENTRATION = 0x10050007, //CO2-concentration | 0.01 %
	CAN_ID_SERVO_X_EXP_MINUTE_VOL = 0x10050008, //Exp. minute vol. | 0.1 L per minute
	CAN_ID_SERVO_X_RESP_RATE_CALC = 0x10050009, //Resp. rate calc  | 0.1 breaths per minute
	CAN_ID_SERVO_X_TIDAL_VOL_EXP = 0x10050010, //Exp. tidal volume  | 1 ml
	CAN_ID_SERVO_X_TIDAL_VOL_INSP = 0x10050011, //Insp. tidal volume | 1 ml
	CAN_ID_SERVO_X_END_EXP_PRESSURE = 0x10050012, //End exp. Pressure | 0.0980638 mbar
// idGroup("SERVO No Alarm", 2, CAN_SERVO_SHIFT)
	CAN_ID_SERVO_X_RR_IS_MIN = 0x10050020, //Is Min value for RR (ventilator)| 1 l/min
	CAN_ID_SERVO_X_FIO2_IS_MIN = 0x10050021, //Is Min value for FIO2 (ventilator)| 1 %
	CAN_ID_SERVO_X_PEEP_IS_MIN = 0x10050022, //Is Min value for PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_VOL_IS_MIN = 0x10050023, //Is Min value for VOL (ventilator)| 0.001 l/min
	CAN_ID_SERVO_X_INSP_TIME_IS_MIN = 0x10050024, //Is Min value for INSP_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_PAUSE_TIME_IS_MIN = 0x10050025, //Is Min value for PAUSE_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_RISE_TIME_IS_MIN = 0x10050026, //Is Min value for RISE_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_CMV_IS_MIN = 0x10050027, //Is Min value for CMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_TUP_IS_MIN = 0x10050028, //Is Min value for Trigger under PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_PCP_IS_MIN = 0x10050029, //Is Min value for Pressure controlled over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_SIMV_IS_MIN = 0x10050030, //Is Min value for SIMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_PSP_IS_MIN = 0x10050031, //Is Min value for Pressure supported over PEEP (ventilator)|  1 cmH2O
	CAN_ID_SERVO_X_CPAP_IS_MIN = 0x10050032, //Is Min value for CPAP Flow (ventilator)|  1 cmH2O
	CAN_ID_SERVO_X_RR_IS_MAX = 0x10050040, //Is Max value for RR (ventilator)| 1 l/min
	CAN_ID_SERVO_X_FIO2_IS_MAX = 0x10050041, //Is Max value for FIO2 (ventilator)| 1 %
	CAN_ID_SERVO_X_PEEP_IS_MAX = 0x10050042, //Is Max value for PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_VOL_IS_MAX = 0x10050043, //Is Max value for VOL (ventilator)| 0.001 l/min
	CAN_ID_SERVO_X_INSP_TIME_IS_MAX = 0x10050044, //Is Max value for INSP_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_PAUSE_TIME_IS_MAX = 0x10050045, //Is Max value for PAUSE_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_RISE_TIME_IS_MAX = 0x10050046, //Is Max value for RISE_TIME (ventilator)| 1 %
	CAN_ID_SERVO_X_CMV_IS_MAX = 0x10050047, //Is Max value for CMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_TUP_IS_MAX = 0x10050048, //Is Max value for Trigger under PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_PCP_IS_MAX = 0x10050049, //Is Max value for Pressure controlled over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_SIMV_IS_MAX = 0x10050050, //Is Max value for SIMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_PSP_IS_MAX = 0x10050051, //Is Max value for Pressure supported over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_CPAP_IS_MAX = 0x10050052, //Is Max value for CPAP Flow (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_RR_VALID = 0x10050060, //Validated Set Point for RR (ventilator) | 1 1/min
	CAN_ID_SERVO_X_FIO2_VALID = 0x10050061, //Validated Set Point for FiO2 (ventilator) | 1 %
	CAN_ID_SERVO_X_PEEP_VALID = 0x10050062, //Validated Set Point for PEEP (ventilator) | 1 mbar
	CAN_ID_SERVO_X_VOL_VALID = 0x10050063, //Validated Set Point for VOL (ventilator) | 0.001 l/min
	CAN_ID_SERVO_X_INSP_TIME_VALID = 0x10050064, //Validated Set Point for InspTime (ventilator) | 1 %
	CAN_ID_SERVO_X_PAUSE_TIME_VALID = 0x10050065, //Validated Set Point for PauseTime (ventilator) | 1 %
	CAN_ID_SERVO_X_RISE_TIME_VALID = 0x10050066, //Validated Set Point for RiseTime (ventilator) | 1 %
	CAN_ID_SERVO_X_CMV_VALID = 0x10050067, //Validated Set Point for CMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_TUP_VALID = 0x10050068, //Validated Set Point for Trigger under PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_PCP_VALID = 0x10050069, //Validated Set Point for Pressure controlled over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_SIMV_VALID = 0x10050070, //Validated Set Point for SIMV frequency (ventilator)| 1 breaths/min
	CAN_ID_SERVO_X_PSP_VALID = 0x10050071, //Validated Set Point for Pressure supported over PEEP (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_CPAP_VALID = 0x10050072, //Validated Set Point for CPAP Flow (ventilator)| 1 cmH2O
	CAN_ID_SERVO_X_FIO2_REAL = 0x10050081, //Real Value send by Servo for FiO2 (ventilator) | 0.01563 %
	CAN_ID_SERVO_X_PEEP_REAL = 0x10050082, //Real Value send by Servo for PEEP (ventilator) | 0.1 mbar
	CAN_ID_SERVO_X_VOL_REAL = 0x10050083, //Real Value send by Servo for VOL (ventilator) | 0.0001 l/min
	CAN_ID_SERVO_X_INSP_TIME_REAL = 0x10050084, //Real Value send by Servo for InspTime (ventilator) | 0.1 %
	CAN_ID_SERVO_X_PAUSE_TIME_REAL = 0x10050085, //Real Value send by Servo for PauseTime (ventilator) | 0.1 %
	CAN_ID_SERVO_X_RISE_TIME_REAL = 0x10050086, //Real Value send by Servo for RiseTime (ventilator) | 0.1 %
	CAN_ID_SERVO_X_CMV_REAL = 0x10050087, //Real Value send by Servo for CMV frequency (ventilator)| 0.1 breaths/min
	CAN_ID_SERVO_X_TUP_REAL = 0x10050088, //Real Value send by Servo for Trigger under PEEP (ventilator)| 0.1 cmH2O
	CAN_ID_SERVO_X_PCP_REAL = 0x10050089, //Real Value send by Servo for Pressure controlled over PEEP (ventilator)| 0.1 cmH2O
	CAN_ID_SERVO_X_SIMV_REAL = 0x10050090, //Real Value send by Servo for SIMV frequency (ventilator)| 0.1 breaths/min
	CAN_ID_SERVO_X_PSP_REAL = 0x10050091, //Real Value send by Servo for Pressure supported over PEEP (ventilator)| 0.1 cmH2O
	CAN_ID_SERVO_X_CPAP_REAL = 0x10050092, //Real Value send by Servo for CPAP Flow (ventilator)| 0.1 cmH2O
//----------------------------------------------------------------------------------------------------
// idGroup("PGA Alarm", 2, CAN_PGA_SHIFT, ALARM)
// PGA
//----------------------------------------------------------------------------------------------------
#define CAN_PGA_SHIFT	12
	CAN_ID_PGA_X_RT_O2 = 0x10060000, // O2 concentration | 0.01 Prozent | 100 100 0.01 0.01
	CAN_ID_PGA_X_RT_O2_VALID = 0x10060001, // O2 concentration valid | 1 bool | 100 100 1 1
	CAN_ID_PGA_X_RT_CO2 = 0x10060002, // CO2 concentration | 0.01 Prozent | 100 100 0.01 0.01
	CAN_ID_PGA_X_RT_CO2_VALID = 0x10060003, // CO2 concentration valid | 1 bool | 100 100 1 1
	CAN_ID_PGA_X_RT_PRESSURE = 0x10060004, // Pressure | 0.1 mbar | 100 100 0.01 0.01
	CAN_ID_PGA_X_RT_PRESSURE_VALID = 0x10060005, // Pressure valid | 1 bool | 100 100 1 1
	CAN_ID_PGA_X_IS_ZERO_REQUEST = 0x10060006, // Is Zero Request | 1 bool | 100 100 1 1
	CAN_ID_PGA_X_IS_OCCLUSION = 0x10060007, // Is Occlusion | 1 bool | 100 100 1 1
	CAN_ID_PGA_X_IS_WATERTRAP_FULL = 0x10060008, // Is Watertrap full | 1 bool | 100 100 1 1
	CAN_ID_PGA_X_IS_PARAMETER_IN_OP = 0x10060009, // Is Parameter in op | 1 bool | 100 100 1 1
	CAN_ID_PGA_X_IS_MODUL_IN_OP = 0x1006000A, // Is Module in op | 1 bool | 100 100 1 1
	CAN_ID_PGA_X_OP_MODE = 0x1006000B, // Operation Mode | | 100 100 1 1
	CAN_ID_PGA_X_COM_MODE = 0x1006000C, // Communication Mode | | 100 100 1 1
	CAN_ID_PGA_X_PUMP_STATUS = 0x1006000D, // Pump Status | | 100 100 1 1
	CAN_ID_PGA_X_ZEROS_SATUS_O2 = 0x1006000E, // Zero Status O2 | 1 bool | 100 100  1 1
	CAN_ID_PGA_X_STATUS_ACT_PGA = 0x1006000F, // Status Act PGA | | 100 100 1 1
	CAN_ID_PGA_X_STATUS_ACT_IS_OK = 0x10060010, // Status Act is ok | | 100 100 1 1
	CAN_ID_PGA_X_MCU_STATUS = 0x10060011, // MCU Status | | 100 100 1 1
//----------------------------------------------------------------------------------------------------
// idGroup("N560 Alarm", 2, CAN_N560_SHIFT, ALARM)
// N560
//----------------------------------------------------------------------------------------------------
#define CAN_N560_SHIFT	12
	CAN_ID_N560_X_SPO2 = 0x10070000, //SpO2 		| 1 %
	CAN_ID_N560_X_BPM = 0x10070001, //pulse rate 	| per minute
	CAN_ID_N560_X_PA = 0x10070002, //pulse amplitude
	CAN_ID_N560_X_STATUS = 0x10070003, //Status
//----------------------------------------------------------------------------------------------------
// idGroup("RECIRCULATION Alarm", 2, CAN_RECIRCULATION_SHIFT, ALARM)
// RECIRCULATION
//----------------------------------------------------------------------------------------------------
#define CAN_RECIRCULATION_SHIFT	12
	CAN_ID_RECIRCULATION_X_TEMP1 = 0x10080000, //Blood Temperature			| 0.00001 centigrade |	10 100 0 0.0001
	CAN_ID_RECIRCULATION_X_TEMP2 = 0x10080001, //Injection Temperature 		| 0.00001 centigrade |	10 100 0 0.0001
	CAN_ID_RECIRCULATION_X_OKOEX = 0x10080002, //Recirculation without Correction| 0.01 %
	CAN_ID_RECIRCULATION_X_INJECTION_VOL = 0x10080003, //Injection volume			| 0.1 ml
	CAN_ID_RECIRCULATION_X_K_FACTOR = 0x1008000C, //Factor K					| 0.01
	CAN_ID_RECIRCULATION_X_INJECTION_TEMP = 0x10080004, //Injection temperature		| 0.00001 centigrade
	CAN_ID_RECIRCULATION_X_PEAK_END = 0x10080006, //T_{intEnd}					| 0.00001 centigrade |	10 100 0 0.0001
	CAN_ID_RECIRCULATION_X_READY_FOR_INJECTION = 0x10080007, //Waiting for Injection(Bool) | 1 | 10 100 1 1
	CAN_ID_RECIRCULATION_X_PEAK_START = 0x10080008, //T_B							| 0.00001 centigrade |	10 100 0 0.0001
	CAN_ID_RECIRCULATION_X_OKEX = 0x10080009, //Extrapolated Recirculation	| 0.01 %
	CAN_ID_RECIRCULATION_X_ERROR = 0x1008000A, //Error						| 1 | 10 100 1 1
	CAN_ID_RECIRCULATION_X_STATUS = 0x1008000B, //State						| 1 | 10 100 1.1 1.1
	CAN_ID_RECIRCULATION_X_KOEX = 0x10080005, //Recirculation corrected T_inj	| 0.01 %
	CAN_ID_RECIRCULATION_X_KEX = 0x1008000D, // Recirculation with optimization	| 0.01 %
	CAN_ID_RECIRCULATION_X_INJECTION_TEMP_CORR = 0x1008000E, //Corrected Injection temperature		| 0.00001 centigrade
	CAN_ID_RECIRCULATION_X_A_FAKTOR = 0x1008000F, //A Faktor Integral		| 0.0000001
//----------------------------------------------------------------------------------------------------
// idGroup("PiCCO2 Alarm", ALARM)
//----------------------------------------------------------------------------------------------------
	CAN_ID_PiCCO_ALARMPCCO = 0x10090000, //PCCO alarm
	CAN_ID_PiCCO_ALARMSCVO2 = 0x10090001, //ScvO2 alarm
	CAN_ID_PiCCO_AP = 0x10090002, //Arterial blood pressure	| 0.1 mmHg
	CAN_ID_PiCCO_APDIA = 0x10090003, //Diastolic arterial blood pressure	| 0.1 mmHg
	CAN_ID_PiCCO_MAP = 0x10090004, //Mean arterial pressure	| 0.1 mmHg
	CAN_ID_PiCCO_APSYS = 0x10090005, //Arterial blood pressure systolic	| 0.1 mmHg
	CAN_ID_PiCCO_BSA = 0x10090006, //Body surface area	| 1 qm
	CAN_ID_PiCCO_CATHETER = 0x10090007, //ID of the connected Catheter
	CAN_ID_PiCCO_CATEGORY = 0x10090008, //Adult or pediatric
	CAN_ID_PiCCO_CFI = 0x10090009, //Cardiac function index | 0.1 1/min
	CAN_ID_PiCCO_CI = 0x1009000A, //Cardiac index	| 0.01 l/min/qm
	CAN_ID_PiCCO_CO = 0x1009000B, //Cardiac output	| 0.01 l/min
	CAN_ID_PiCCO_CPI = 0x1009000C, //Cardiac power index | 0.01 W/qm
	CAN_ID_PiCCO_CPO = 0x1009000D, //Cardiac power output | 0.01 W
	CAN_ID_PiCCO_CVP = 0x1009000E, //Central venous pressure	| 1 mmHg
	CAN_ID_PiCCO_DEL_ID_HIGH = 0x1009000F, //(Internal use only)
	CAN_ID_PiCCO_DEL_ID_LOW = 0x10090010, //(Internal use only)
	CAN_ID_PiCCO_DO2 = 0x10090011, //Oxygen delivery	| 1 ml/min
	CAN_ID_PiCCO_DO2I = 0x10090012, //Oxygen delivery index	| 1 ml/min/qm
	CAN_ID_PiCCO_DOT_ID_LOW = 0x10090013, //(Internal use only)
	CAN_ID_PiCCO_DPMX = 0x10090014, //Index of left ventricular contractility | 1 mmHg/s
	CAN_ID_PiCCO_DST = 0x10090015, //Down slope time	| 0.1 s
	CAN_ID_PiCCO_ERROR = 0x10090016, //TD measurement error; 0								= no err
	CAN_ID_PiCCO_ETVI = 0x10090017, //obsolete, use ELWI!
	CAN_ID_PiCCO_EVLW = 0x10090018, //Extravascular lung water	| 1 ml
	CAN_ID_PiCCO_ELWI = 0x10090019, //Extravascular lung water index	| 1 ml/kg
	CAN_ID_PiCCO_FLAGS = 0x1009001A, //(Internal Use only)
	CAN_ID_PiCCO_GEDV = 0x1009001B, //Global end-diastolic volume	| 1 ml
	CAN_ID_PiCCO_GEDI = 0x1009001C, //Global end-diastolic volume index	| 1 ml/qm
	CAN_ID_PiCCO_GEF = 0x1009001D, //Global ejection fraction	| 1 %
	CAN_ID_PiCCO_GENDER = 0x1009001E, //male or female; 0								= male, 1								= female
	CAN_ID_PiCCO_HCT = 0x1009001F, //Hematocrit	| 0.01 %
	CAN_ID_PiCCO_HEIGHT = 0x10090020, //Height of the patient	| 1 cm
	CAN_ID_PiCCO_HR = 0x10090021, //Heart rate	|	1 bpm
	CAN_ID_PiCCO_INJVOL = 0x10090022, //Injectate volume	| 0.1 ml
	CAN_ID_PiCCO_ITBV = 0x10090023, //Intrathoracic blood volume	| 1 ml
	CAN_ID_PiCCO_ITBI = 0x10090024, //Intrathoracic blood volume index	| 1 ml/qm
	CAN_ID_PiCCO_TD_CFI = 0x10090025, //Cardiac function index		| 0.1 1/min
	CAN_ID_PiCCO_TD_CI = 0x10090026, //Cardiac index	| 0.01
	CAN_ID_PiCCO_TD_CO = 0x10090027, //Cardiac output	| 0.01 l/min
	CAN_ID_PiCCO_TD_EVLW = 0x10090028, //Extravascular lung water	| 1 ml
	CAN_ID_PiCCO_TD_ELWI = 0x10090029, //Extravascular lung water index	| 1 ml/kg
	CAN_ID_PiCCO_TD_GEF = 0x1009002A, //Global ejection fraction	| 1 %
	CAN_ID_PiCCO_TD_GEDV = 0x1009002B, //Global end-diastolic volume	| 1 ml
	CAN_ID_PiCCO_TD_GEDI = 0x1009002C, //Global end-diastolic volume index	| 1 ml/qm
	CAN_ID_PiCCO_TD_ITBV = 0x1009002D, //Intrathoracic blood volume	| 1 ml
	CAN_ID_PiCCO_TD_ITBI = 0x1009002E, //Intrathoracic blood volume index	| 1 ml/qm
	CAN_ID_PiCCO_TD_PVPI = 0x1009002F, //Pulmonary vascular permeability index
	CAN_ID_PiCCO_MTT = 0x10090030, //Mean Transmit Time	| 0.1 s
	CAN_ID_PiCCO_PAT1 = 0x10090031, //number out of the patient name 1?
	CAN_ID_PiCCO_PAT2 = 0x10090032, //number out of the patient name 2?
	CAN_ID_PiCCO_PAT3 = 0x10090033, //number out of the patient name 3?
	CAN_ID_PiCCO_PAT4 = 0x10090034, //number out of the patient name 4?
	CAN_ID_PiCCO_PAT5 = 0x10090035, //number out of the patient name 5?
	CAN_ID_PiCCO_PATIENT_ID = 0x10090036, //Patient ID
	CAN_ID_PiCCO_PATIENT_NAME = 0x10090037, //Patient Name
	CAN_ID_PiCCO_PBSA = 0x10090038, //Predicted body surface area	| 0.0001 qm
	CAN_ID_PiCCO_PBW = 0x10090039, //Predicted body weight	| 0.1 kg
	CAN_ID_PiCCO_PCCI = 0x1009003A, //Pulse contour cardiac index	| 0.01 l/min/qm
	CAN_ID_PiCCO_PCCO = 0x1009003B, //Pulse contour cardiac output	| 0.01 l/min
	CAN_ID_PiCCO_PCCOFAC = 0x1009003C, //(Internal use only)
	CAN_ID_PiCCO_PPV = 0x1009003D, //Pulse pressure variation	| 1 %
	CAN_ID_PiCCO_PVPI = 0x1009003E, //Pulmonary vascular permeability index	| 0.1
	CAN_ID_PiCCO_RL_SHUNT = 0x1009003F, //Always INVALID
	CAN_ID_PiCCO_RELEASE_PICCO = 0x10090040, //Meaningless on PiCCO2
	CAN_ID_PiCCO_RELEASE_PICCO2 = 0x10090041, //Software version in hexadecimal number
	CAN_ID_PiCCO_SAO2 = 0x10090042, //Arterial oxygenation saturation	| 0.01 %
	CAN_ID_PiCCO_SCVO2 = 0x10090043, //Central venous oxygenation saturation	| 0.01 %
	CAN_ID_PiCCO_SCVO2CAL = 0x10090044, //ScvO2 Calibration input	| 0.01 %
	CAN_ID_PiCCO_STATUS = 0x10090045, //Status of the TD measurement
	CAN_ID_PiCCO_SV = 0x10090046, //Stroke volume	| 0.01 ml
	CAN_ID_PiCCO_SVI = 0x10090047, //Stroke volume index	| 0.01 ml/qm
	CAN_ID_PiCCO_SV_BEAT = 0x10090048, //Stroke volume; beat-to-beat	| 0.01 ml
	CAN_ID_PiCCO_SVMAX = 0x10090049, //Stroke volume maximum	| 0.01 ml
	CAN_ID_PiCCO_SVMIN = 0x1009004A, //Stroke volume minimum	| 0.01 ml
	CAN_ID_PiCCO_SVR = 0x1009004B, //Systemic vascular resistance	| 1 dyn*s*cm^-5
	CAN_ID_PiCCO_SVRI = 0x1009004C, //Systemic vascular resistance index	| 1 dyn*s*cm^-5*qm
	CAN_ID_PiCCO_SVV = 0x1009004D, //Stroke volume variation	| 1 %
	CAN_ID_PiCCO_TB = 0x1009004E, //Body Temperature	| 0.01 Centigrade
	CAN_ID_PiCCO_TD_COUNT = 0x1009004F, //Counter for signaling when all discontinuous parameters have been updated
	CAN_ID_PiCCO_TD_ID_HIGH = 0x10090050, //Higher part of timestamp of last TD measurement as bit field
	CAN_ID_PiCCO_TD_ID_LOW = 0x10090051, //Lower part of timestamp of last TD measurement as bit field
	CAN_ID_PiCCO_TDA_DTB = 0x10090052, //Temperature difference	| 0.01 Centigrade
	CAN_ID_PiCCO_TDA_TINJ = 0x10090053, //Injectate temperature of TD	| 0.1 Centigrade
	CAN_ID_PiCCO_TIME_YEAR = 0x10090054, //Current Date, YEAR
	CAN_ID_PiCCO_TIME_MONTH = 0x10090055, //Current Date, Month
	CAN_ID_PiCCO_TIME_DAY = 0x10090056, //Current Date, Day
	CAN_ID_PiCCO_TIME_HOUR = 0x10090057, //Current Time, Hours
	CAN_ID_PiCCO_TIME_MINUTE = 0x10090058, //Current Time, Minutes
	CAN_ID_PiCCO_TIME_SECOND = 0x10090059, //Current Time, Seconds
	CAN_ID_PiCCO_TINJ = 0x1009005A, //Injectate temperature of TD	| 0.01 Centigrade
	CAN_ID_PiCCO_UNDEL_ID_HIGH = 0x1009005B, //(Internal Use only)
	CAN_ID_PiCCO_UNDEL_ID_LOW = 0x1009005C, //(Internal Use only)
	CAN_ID_PiCCO_VO2 = 0x1009005D, //Oxygen consumption	| 1 ml/min
	CAN_ID_PiCCO_VO2I = 0x1009005E, //Oxygen consumption index	| 1 ml/min/qm
	CAN_ID_PiCCO_WEIGHT = 0x1009005F, //Weight of the patient in kg	| 0.1 kg
	CAN_ID_PiCCO_SPO2 = 0x10090060, //Arterial oxygenation saturation (pleth) | 0.01 %
	CAN_ID_PiCCO_ALARMSPO2 = 0x10090061, //Alarm of SpO2
	CAN_ID_PiCCO_ICG_ID_HIGH = 0x10090062, //Higher part of timestamp of last ICG measurement as bit field
	CAN_ID_PiCCO_ICG_ID_LOW = 0x10090063, //Lower part of timestamp of last ICG measurement as bit field
	CAN_ID_PiCCO_ICG_COUNT = 0x10090064, //Counter for signalizing update of ICG measurement
	CAN_ID_PiCCO_ERROR_ICG = 0x10090065, //ICG measurement error; if no error occurs 0 is transmitted
	CAN_ID_PiCCO_PDR = 0x10090066, //Plasma disappearance rate | 0.1 %/min
	CAN_ID_PiCCO_R15 = 0x10090067, //Retention Rate of ICG | 0.1 %
	CAN_ID_PiCCO_ASYNCSLOT = 0x100900E0, //Asynchron received slot
	CAN_ID_PiCCO_WRONGCHECKSUM = 0x100900E1, //Slot with wrong checksum received
	CAN_ID_PiCCO_EMPTYCELL = 0x100900FF, //ID for empty cell in slot (No CAN msg send).
//----------------------------------------------------------------------------------------------------
// idGroup("TCM Alarm", ALARM)
//----------------------------------------------------------------------------------------------------
	CAN_ID_CombiM_TIMESTAMP = 0x100A0000, // Seconds since last midnight
	CAN_ID_CombiM_CO2_PRESSURE = 0x100A0001, // CO2 Pressure	| 0.1 mmHG
	CAN_ID_CombiM_TEMPERATURE = 0x100A0002, // CombiM Temperature | 0.1 Celsius
	CAN_ID_CombiM_POWER = 0x100A0003, // Power	| 1 mW
	CAN_ID_CombiM_SP_O2 = 0x100A0004, // Oxygene Saturation	| 1 %
	CAN_ID_CombiM_HEARTRATE = 0x100A0005, // CombiM heart rate | 1 bpm
	CAN_ID_CombiM_SP_CO2 = 0x100A0006, // CO2 Saturation | 1 %
	CAN_ID_CombiM_O2_PRESSURE = 0x100A0007, // O2 Pressure | 0.1 mmHG
//----------------------------------------------------------------------------------------------------
// idGroup("Temperature Alarm", ALARM)
//----------------------------------------------------------------------------------------------------
	CAN_ID_TEMPERATURE = 0x100B0000, // Temperature Sensor | 1 ADC Einheiten
//----------------------------------------------------------------------------------------------------
// idGroup("Blood Flow Alarm", 2, CAN_BLOOD_FLOW_SHIFT, ALARM)
//----------------------------------------------------------------------------------------------------
#define CAN_BLOOD_FLOW_SHIFT	12
	CAN_ID_BLOOD_FLOW_X_AVERAGE = 0x100C0000, // average Blood Flow	|0.0024420024420024420024420024420024 L/min
	CAN_ID_BLOOD_FLOW_X_PULSATILE = 0x100C0001, // pulsatile Blood Flow	|0.0024420024420024420024420024420024 L/min | 100 10 0 0
	CAN_ID_BLOOD_FLOW_X_Channel_3 = 0x100C0002, // Blood Flow Channel 3	|0.0024420024420024420024420024420024 L/min
	CAN_ID_BLOOD_FLOW_X_Channel_4 = 0x100C0003, // Blood Flow Channel 4	|0.0024420024420024420024420024420024 L/min
//----------------------------------------------------------------------------------------------------
// idGroup("Pump Control")
//----------------------------------------------------------------------------------------------------
	CAN_ID_PUMP_CURRENT = 0x100D0000, // current | 1 mA
	CAN_ID_PUMP_RPM = 0x100D0001, // rpm | 1 rpm
	CAN_ID_PUMP_RPM2 = 0x100D0002, // rpm | 1 rpm
	CAN_ID_PUMP_FLOW_ACTIVE = 0x100D0003, // flow control active | 1
	CAN_ID_PUMP_PRESS_BEFORE = 0x100D0004, // Pressure before pump head | mmHg
	CAN_ID_PUMP_PRESS_AFTER = 0x100D0005, // Pressure after pump head | mmHg
	CAN_ID_PUMP_PRESS_DIFF = 0x100D0006, // Pressure difference | mmHg
//----------------------------------------------------------------------------------------------------
// idGroup("Flow Board")
//----------------------------------------------------------------------------------------------------
	CAN_ID_FLOW_BOARD_EXCORP = 0x100F0000, // Extracorporal Flow | 1 mL/min
	CAN_ID_FLOW_BOARD_ACTUAL_RECIRC = 0x100F0001, // Recirculation | 0.1 %
	CAN_ID_FLOW_BOARD_RECIRC = 0x100F0002, // Recirculation Flow | 1 mL/min
//----------------------------------------------------------------------------------------------------
// idGroup("TOM Alarm", 2, CAN_TOM_SHIFT, ALARM)
// TOM
//----------------------------------------------------------------------------------------------------
#define CAN_TOM_SHIFT	12
	CAN_ID_TOM_X_STO2 = 0x10100000, // StO2 		| 1 % | 2000 2000 1 1
	CAN_ID_TOM_X_THI = 0x10100001, // Tissue hemoglobin index 	| 0.1 | 2000 2000 1 1
	CAN_ID_TOM_X_STATUS = 0x10100002, // Status 	| | 2000 2000 1 1

//----------------------------------------------------------------------------------------------------
// idGroup("PV1000 Meas", ALARM)
// 0x -- --  00 nn --> Realtime Channels
// 0x -- --  01 nn --> Numeric Channels
//----------------------------------------------------------------------------------------------------
	CAN_ID_ PV1000_RT_INSP_FLOW = 0x10200000, //Inspiratory Flow 		| 1 l/min
	CAN_ID_ PV1000_RT_EXSP_FLOW = 0x10200001, //Exspiratory Flow 		| 1 l/min
	CAN_ID_ PV1000_RT_PINSP 	= 0x10200002, //Inspiratory pressure	| 0.1 mBar
	CAN_ID_ PV1000_RT_PEXSP		= 0x10200003, //exspiratory pressure	| 0.1 mBar
	CAN_ID_ PV1000_RT_Oxy		= 0x10200004, //inspiratory Oxygen		| 1 %
	CAN_ID_ PV1000_RT_Pleth		= 0x10200005, //PPG plethysmogram		| 1

	CAN_ID_ PV1000_NUM_VT		= 0x10200100, //Tidal Volume			| 1 ml
	CAN_ID_ PV1000_NUM_Pendinsp	= 0x10200101, //P_endinsp				| 0.1 mBar
	CAN_ID_ PV1000_NUM_Pendexsp	= 0x10200102, //P_endexsp				| 0.1 mBar
	CAN_ID_ PV1000_NUM_PPG-HR	= 0x10200103, //Heart Rate				| 1 /min
	CAN_ID_ PV1000_NUM_Pendexsp	= 0x10200104, //Saturation				| 1 %

	
//----------------------------------------------------------------------------------------------------
// idGroup("DriverTests  no Alarm", 16, CAN_DRIVERTESTS_SHIFT)
// DriverTests
//----------------------------------------------------------------------------------------------------
#define CAN_DRIVERTESTS_SHIFT	12
	CAN_ID_DRIVERTESTS_X_ADC_EXT_0 = 0x101F0010, //Value of (external) ADC Channel 0	| 0.001221 V
	CAN_ID_DRIVERTESTS_X_ADC_EXT_1 = 0x101F0011, //Value of (external) ADC Channel 1	| 0.001221 V
	CAN_ID_DRIVERTESTS_X_ADC_EXT_2 = 0x101F0012, //Value of (external) ADC Channel 2	| 0.001221 V
	CAN_ID_DRIVERTESTS_X_ADC_EXT_3 = 0x101F0013, //Value of (external) ADC Channel 3	| 0.001221 V
	CAN_ID_DRIVERTESTS_X_ADC_INT_1 = 0x101F0020, //Value of (internal) ADC Channel 1	| 0.0032258 V
	CAN_ID_DRIVERTESTS_X_ADC_INT_5 = 0x101F0021, //Value of (internal) ADC Channel 5	| 0.0032258 V
	CAN_ID_DRIVERTESTS_X_ADC_INT_6 = 0x101F0022, //Value of (internal) ADC Channel 6	| 0.0032258 V
	CAN_ID_DRIVERTESTS_X_ADC_INT_7 = 0x101F0023, //Value of (internal) ADC Channel 7	| 0.0032258 V
	CAN_ID_DRIVERTESTS_X_DAC_0 = 0x101F0030, //Value of DAC Channel 0 | 0.004887585532746823 V
	CAN_ID_DRIVERTESTS_X_DAC_1 = 0x101F0031, //Value of DAC Channel 1 | 0.004887585532746823 V
	CAN_ID_DRIVERTESTS_X_DAC_2 = 0x101F0032, //Value of DAC Channel 2 | 0.004887585532746823 V
	CAN_ID_DRIVERTESTS_X_DAC_3 = 0x101F0033, //Value of DAC Channel 3 | 0.004887585532746823 V
	CAN_ID_DRIVERTESTS_X_UART_ACK = 0x101F0040, //UART ACK | 1 bool
	CAN_ID_DRIVERTESTS_X_CAN_LOAD_0 = 0x101F0050, //CAN Message 0
	CAN_ID_DRIVERTESTS_X_CAN_LOAD_1 = 0x101F0051, //CAN Message 1
	CAN_ID_DRIVERTESTS_X_CAN_LOAD_2 = 0x101F0052, //CAN Message 2
	CAN_ID_DRIVERTESTS_X_CAN_LOAD_3 = 0x101F0053, //CAN Message 3
	CAN_ID_DRIVERTESTS_X_CAN_RX_ERR = 0x101F0054, //CAN Rx Error
	CAN_ID_DRIVERTESTS_X_CAN_TX_ERR = 0x101F0055, //CAN Tx Error
	CAN_ID_DRIVERTESTS_X_SWITCH_VALUE = 0x101F0060, // Switch value
	CAN_ID_DRIVERTESTS_X_BUTTON = 0x101F0070, // Button pressed (0: Next, 1: OK)
//----------------------------------------------------------------------------------------------------
// idGroup("dSpace Box Alarm", ALARM)
//----------------------------------------------------------------------------------------------------
// | ID Pattern    |    Period Time  |  
// |--------------------------------------------------------------------------
// | 0x10FE00--    |     506 ms      | Simulation, Evaluation and Control Data
// | 0x10FE01--    |     209 ms	     | PGA Measurement
// | 0x10FE02--    |    5000 ms	     | dSpace System Settings & Switchs
// | 0x10FE03--    |     100 ms	     | dSpace System Pressure Measurement
// | 0x10FE05--    |    5000 ms	     | Servo 300 Evaluation Values
// | 0x10FE06--    |     100 ms	     | Servo 300 Measurement
//----------------------------------------------------------------------------------------------------
	CAN_ID_DSPACE_D2Om = 0x10FE0000, // Diffusionskonstante O2 | 1 nL/s*mmHg
	CAN_ID_DSPACE_PoxyO2out = 0x10FE0001, // PoxyO2out simuliert | 0.1 mmHg 
	CAN_ID_DSPACE_PoxyCO2out = 0x10FE0002, // PoxyCO2out simuliert | 0.1 mmHg 
	CAN_ID_DSPACE_SoxyO2out = 0x10FE0003, // SoxyO2out simuliert | 0.1 % 
	CAN_ID_DSPACE_PvO2sim = 0x10FE0004, // PvO2sim | 0.1 mmHg  
	CAN_ID_DSPACE_PvCO2sim = 0x10FE0005, // PvCO2sim | 0.1 mmHg 
	CAN_ID_DSPACE_SvO2sim = 0x10FE0006, // SvO2sim | 0.1 %
	CAN_ID_DSPACE_PaO2sim = 0x10FE0007, // PaO2sim | 0.1 mmHg 
	CAN_ID_DSPACE_PaCO2sim = 0x10FE0008, // PaCO2sim | 0.1 mmHg  
	CAN_ID_DSPACE_SaO2sim = 0x10FE0009, // SaO2sim | 0.1 % 
	CAN_ID_DSPACE_O2TranferOxyGas = 0x10FE0010, // O2TranferOxyGas | 0.1 mL/min
	CAN_ID_DSPACE_CO2TranferOxyGas = 0x10FE0011, // CO2TranferOxyGas | 0.1 mL/min
	CAN_ID_DSPACE_O2TranferPat = 0x10FE0012, // O2TranferPat | 0.1 mL/min 
	CAN_ID_DSPACE_CO2TranferPat = 0x10FE0013, // CO2TranferPat | 0.1 mL/min
	CAN_ID_DSPACE_FgO2Set = 0x10FE0014, // FgO2Set | 0.1 %  
	CAN_ID_DSPACE_QbSet = 0x10FE0015, // QbSet | 0.1 mL/Min
	CAN_ID_DSPACE_QgSet = 0x10FE0016, // QgSet | 0.1 mL/Min
	CAN_ID_DSPACE_PoxyO2Soll = 0x10FE0017, // PoxyO2Soll | 0.1 mmHg
	CAN_ID_DSPACE_PoxyCO2Soll = 0x10FE0018, // PoxyCO2Soll | 0.1 mmHg
	CAN_ID_DSPACE_QbSoll = 0x10FE0019, // QbSoll | 0.1 mL/Min
	CAN_ID_DSPACE_SaO2invSoll = 0x10FE0020, // SaO2invSoll | 0.1 % 
	CAN_ID_DSPACE_CDIvCO2Soll = 0x10FE0021, // CDIvCO2Soll | 0.1 mmHg 
	CAN_ID_DSPACE_QbSollErr = 0x10FE0022, // QbSollErr | 0.1 ml/s
	CAN_ID_DSPACE_O2TranferOxyBlood = 0x10FE0023, // O2TranferOxyBlood | 0.1 mL/min
	CAN_ID_DSPACE_CO2TranferOxyBlood = 0x10FE0024, // CO2TranferOxyBlood | 0.1 mL/min
	CAN_ID_DSPACE_PGA1_concO2rt = 0x10FE0100, // PGA_concO2rt | 0.1 Prozent
	CAN_ID_DSPACE_PGA1_concO2valid = 0x10FE0101, // PGA_concO2valid | 1 bool
	CAN_ID_DSPACE_PGA1_concCO2rt = 0x10FE0102, // PGA_concCO2rt | 0.1 Prozent
	CAN_ID_DSPACE_PGA1_concCO2valid = 0x10FE0103, // PGA_concCO2valid | 1 bool
	CAN_ID_DSPACE_PGA1_pressRt = 0x10FE0104, // PGA_pressRt | 0.1 mbar
	CAN_ID_DSPACE_PGA1_pressValid = 0x10FE0105, // PGA_pressValid | 1 bool
	CAN_ID_DSPACE_PGA2_concO2rt = 0x10FE0110, // PGA_concO2rt | 0.1 Prozent
	CAN_ID_DSPACE_PGA2_concO2valid = 0x10FE0111, // PGA_concO2valid | 1 bool
	CAN_ID_DSPACE_PGA2_concCO2rt = 0x10FE0112, // PGA_concCO2rt | 0.1 Prozent
	CAN_ID_DSPACE_PGA2_concCO2valid = 0x10FE0113, // PGA_concCO2valid | 1 bool
	CAN_ID_DSPACE_PGA2_pressRt = 0x10FE0114, // PGA_pressRt | 0.1 mbar
	CAN_ID_DSPACE_PGA2_pressValid = 0x10FE0115, // PGA_pressValid | 1 bool
	CAN_ID_DSPACE_KnQb = 0x10FE0200, // KnQb |  0.1
	CAN_ID_DSPACE_TnQb = 0x10FE0201, // TnQb | 0.1 s
	CAN_ID_DSPACE_KnFgO2 = 0x10FE0202, // KnFgO2 | 0.01 e-3
	CAN_ID_DSPACE_TnFgO2 = 0x10FE0203, // TnFgO2 | 0.1 s
	CAN_ID_DSPACE_KnQg = 0x10FE0204, // KnQg | 0.01 e-3
	CAN_ID_DSPACE_TnQg = 0x10FE0205, // TnQg | 0.1 s
	CAN_ID_DSPACE_KnPoxyO2 = 0x10FE0206, // KnPoxyO2 | 0.1
	CAN_ID_DSPACE_TnPoxyO2 = 0x10FE0207, // TnPoxyO2 | 0.1 s
	CAN_ID_DSPACE_KnPoxyCO2 = 0x10FE0208, // KnPoxyCO2 | 0.1
	CAN_ID_DSPACE_TnPoxyCO2 = 0x10FE0209, // TnPoxyCO2 | 0.1 s
	CAN_ID_DSPACE_TnQbSoll = 0x10FE0210, // TnQbSoll  | 0.01 s
	CAN_ID_DSPACE_Oxy_Vg = 0x10FE0212, // Oxy Vg | 1 mL
	CAN_ID_DSPACE_Oxy_Vb = 0x10FE0213, // Oxy Vb | 1 mL
	CAN_ID_DSPACE_Oxy_VdO2m = 0x10FE0214, // Oxy VdO2m | 0.1
	CAN_ID_DSPACE_Oxy_dO2mControlOnline = 0x10FE0215, // Oxy dO2mControlOnline | 1 bool
	CAN_ID_DSPACE_Pat_mrO2 = 0x10FE0216, // Pat mrO2 | 1 mL/min
	CAN_ID_DSPACE_Pat_mrCalcOnline = 0x10FE0217, // Pat mrCalcOnline | 1 bool
	CAN_ID_DSPACE_Pat_recirculation = 0x10FE0218, // Pat recirculation | 1 mL/min
	CAN_ID_DSPACE_Pat_delataO2 = 0x10FE0219, // Pat delta O2 | 0.01 mmol/min
	CAN_ID_DSPACE_Pat_RQ = 0x10FE0220, // Pat RQ | 0.001 
	CAN_ID_DSPACE_P1 = 0x10FE0301, // dSpaceP1 | 1 mbar
	CAN_ID_DSPACE_P2 = 0x10FE0302, // dSpaceP2 | 1 mbar
	CAN_ID_DSPACE_VENT_SI = 0x10FE0500, // Stress Index | 0.001 
	CAN_ID_DSPACE_VENT_R_SI = 0x10FE0501, // SI R Value | 0.001 
	CAN_ID_DSPACE_VENT_PLATEAU_PRESSUE = 0x10FE0502, // Plateaue   | 0.001 mbar
	CAN_ID_DSPACE_VENT_C_RS = 0x10FE0503, // Compliance   | 0.001 L/mbar
//Auskommentierte IDs werden nicht über dSpace System ausgelesen
	CAN_ID_DSPACE_SERVO_X_AIRWAY_FLOW = 0x10FE0600, //Airway flow | 0.01 L per minute
//CAN_ID_DSPACE_SERVO_X_AIRWAY_FLOW_X10				= 0x10FE0601, //Airway flow *10 | 0.01 L per minute
	CAN_ID_DSPACE_SERVO_X_AIRWAY_PRESSURE_INSP = 0x10FE0602, //Airway Pressure Insp | 0.01 mbar
	CAN_ID_DSPACE_SERVO_X_AIRWAY_PRESSURE_EXP = 0x10FE0603, //Airway Pressure Exp | 0.01 mbar
//CAN_ID_DSPACE_SERVO_X_PAUSE_PRESSURE				= 0x10FE0604, //Pause Pressure | 0.01 mbar
//CAN_ID_DSPACE_SERVO_X_PEAK_PRESSURE				= 0x10FE0605, //Peak Pressure | 0.01 mbar
	CAN_ID_DSPACE_SERVO_X_O2_CONCENTRATION = 0x10FE0606, //O2-concentration | 0.01 %
	CAN_ID_DSPACE_SERVO_X_CO2_CONCENTRATION = 0x10FE0607, //CO2-concentration | 0.01 %
//CAN_ID_DSPACE_SERVO_X_EXP_MINUTE_VOL				= 0x10FE0608, //Exp. minute vol. | 0.01 L per minute
//CAN_ID_DSPACE_SERVO_X_RESP_RATE_CALC				= 0x10FE0609, //Resp. rate calc  | 0.01 breaths per minute
	CAN_ID_DSPACE_SERVO_X_END_TIDAL_CO2 = 0x10FE060A, //CO2-endtidal | 0.01 %
	CAN_ID_DSPACE_SERVO_X_EXP_BOOL = 0x10FE060B, //is expriation | 1 bool
	CAN_ID_DSPACE_SERVO_X_INSP_BOOL = 0x10FE060C, //is inspiration | 1 bool
	CAN_ID_DSPACE_SERVO_X_AIRWAY_PRESSURE = 0x10FE060D, //Airway Pressure | 0.01 mbar
	CAN_ID_DSPACE_SERVO_X_AIRWAY_FLOW_INSP = 0x10FE060E, //Airway flow Insp| 0.01 L per minute
	CAN_ID_DSPACE_SERVO_X_AIRWAY_FLOW_EXP = 0x10FE060F, //Airway flow Exp| 0.01 L per minute
	CAN_ID_DSPACE_SERVO_X_DELTA_V_LUNG = 0x10FE0610, //delta lung Volume | 0.001 L
//####################################################################################################
//----------------------------------------------------------------------------------------------------
// idGroup("dSpace MicroLabBox Measure", 1, CAN_ID_DSPACEML_SHIFT, ALARM)
//----------------------------------------------------------------------------------------------------
#define CAN_ID_DSPACEML_SHIFT	0
// Dspace MicroLabBox
	CAN_ID_DSPACEML_SERVO_I_AIRWAY_FLOW = 0x10FD0064, //Airway flow |0.001 L per second
	CAN_ID_DSPACEML_SERVO_I_AIRWAY_PRESSURE = 0x10FD0071, //Airway pressure |0.001 mbar
	CAN_ID_DSPACEML_SERVO_I_EDI = 0x10FD0076, //Electrical activity of diaphragm |0.01 uV 
//####################################################################################################
// Bloodflowprofile									0x11...
//####################################################################################################
//----------------------------------------------------------------------------------------------------
// idGroup("PUMP")
//----------------------------------------------------------------------------------------------------
	CAN_ID_PUMP_FLOW_PROF_VALUE = 0x110D0000, // add Values to Profile
	CAN_ID_PUMP_PROFILE_ADD = 0x110D0001, // Profil hinzufügen inkl. max. Anzahl an Werten
	CAN_ID_PUMP_PROFILE_DEL = 0x110D0002, // Profil löschen
	CAN_ID_PUMP_PROFILE_COMPLETE_Q = 0x110D0003, // Profil komplett anfrage
	CAN_ID_PUMP_PROFILE_SYNC = 0x110D0004, //
	CAN_ID_PUMP_PROFILE_ADDED = 0x110D0005, // Profil erfolgreich hinzugefügt
	CAN_ID_PUMP_PROFILE_DELETED = 0x110D0006, // Profil erfolgreich gelöscht
//####################################################################################################
// ID Testarea (Viewer, Device#, etc.)		0x1F...
//####################################################################################################
//####################################################################################################
// LAST IDs									0x1FFFFFFF
//####################################################################################################
// idGroup(none)
	CAN_ID_BEGIN_OF_END = 0x10FF0000, // 	| 1 
	CAN_ID_VERY_LAST_ID = 0x1FFFFFFF, // Last CAN ID. Should not be used.
};
// do NOT change this line too.
#endif /* SMARTECLA_IDS_H_ */
