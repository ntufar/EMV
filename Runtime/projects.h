#ifndef PROJECTS_H
#define PROJECTS_H

//Define macros to set and extract error information
#define seterror(project, module, function, error_type, error) \
	(int)(((project << 24) & 0xff000000) | \
	((module << 16) & 0x00ff0000) | \
	((function << 8) & 0x0000ff00) | \
	((error_type << 7) & 0x00000080) | (error & 0x0000007f))
#define getproject(error_val) (int)((error_val >> 24) & 0x000000ff)
#define getmodule(error_val)  (int)((error_val >> 16) & 0x000000ff)
#define getfunction(error_val) (int)((error_val >> 8) & 0x000000ff)
#define geterrortype(error_val) (int)((error_val >> 7) & 0x00000001)
#define geterror(error_val) (int)(error_val & 0x0000007f)

#define MODULE_SPECIFIC_ERROR 1
#define COMMON_ERROR          0

// This file defines all projects involved in SmartPOS
// reserved by SCS in a range 0x00 - 0x7F
#define PRJ_ACCESSMANAGER           0x01
#define PRJ_SERVICECONTROL          0x02
#define PRJ_SERVICEINTERFACE        0x03
#define PRJ_SYSTEMCONTROL           0x04
#define PRJ_CNFGCONTROL             0x05
#define PRJ_UICONTROL               0x06
#define PRJ_CLCCONTROL              0x07
#define PRJ_POSCONTROL              0x08
#define PRJ_CRYPTOCONTROL           0x09

// Developers defined, in a range 0x80 - 0xFF
#define PRJ_SYSTEMCONTROLINTERFACE  0x80
#define PRJ_SYSTEMCONTROLSEREVER    0x81
#define PRJ_CNFGCONTROLINTERFACE    0x82
#define PRJ_CNFGCONTROLSERVER       0x83
#define PRJ_UICONTROLINTERFACE      0x84
#define PRJ_UICONTROLSERVER         0x85
#define PRJ_CLCCONTROLINTERFACE     0x86
#define PRJ_POSCONTROLINTERFACE     0x87
#define PRJ_CRYPTOCONTROLINTERFACE  0x88
#define PRJ_CRYPTOCONTROLSERVER     0x89


#define PRJ_CLC_TIMESAVER       0xFF
#define PRJ_POS_TIMESAVER       0xFE

#endif

