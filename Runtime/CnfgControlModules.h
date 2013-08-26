#ifndef CNFGCONTROLMODULES_H
#define CNFGCONTROLMODULES_H

//cpp files
#define MOD_CnfgControl_Interface 0x01
#define MOD_CnfgControlServer     0x02
#define MOD_CnfgInterface         0x03
#define MOD_CnfgOperationEvent    0x04

//interface functions
#define CNFG_openService        0x01
#define CNFG_connectedServices  0x02
#define CNFG_addOperationEvent  0x03
#define CNFG_getValue           0x04
#define CNFG_setValueLong       0x05
#define CNFG_setValueString     0x06
#define CNFG_setValueByteString 0x07
#define CNFG_deleteValue        0x08
#define CNFG_createValue        0x09
#define CNFG_enumKeys           0x0A
#define CNFG_enumValues         0x0B
#define CNFG_open               0x0C
#define CNFG_close              0x0D


#endif