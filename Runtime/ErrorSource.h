#ifndef ERRORSOURCE_H
#define ERRORSOURCE_H

//Internal Source of errors

#define CnfgOperationEvent_setString__allocateResource       1
#define CnfgOperationEvent_setStringArray__allocateResource1 2
#define CnfgOperationEvent_setStringArray__allocateResource2 3
#define CnfgOperationEvent_setByteString__allocateResource   4
#define CnfgControlImpl_getValue__buildKey                   5
#define CnfgControlImpl_getValueFromRegistry                 6
#define CnfgControlImpl_setValueToRegistry                   7
#define CnfgControlImpl_packOperationEvent                   8
#define CnfgControlImpl_setValueLong                         9
#define CnfgControlImpl_setValueString                       10
#define CnfgControlImpl_setValueByteString                   11
#define CnfgControlImpl_deleteValue                          12
#define CnfgControlImpl_createValue                          13
#define CnfgControlImpl_enumKeys	                         14
#define CnfgControlImpl_checkInitialization                  15
#define CnfgControlImpl_enumRegKeys                          16
#define CnfgControlImpl_deleteRegValue                       17


#define UIControl_setString                                  18
#define UIControlImpl_checkInitialization                    19
#define UIControl_addString                                  20
#define UIControl_setAndReceiveString                        21
#define UIOperationEvent_setString                           22 
#define UIControl_getAnswer                                  23
#define UIControl_selectOption                               24

//External Source of errors
#define _RegOpenKeyEx                                        1
#define _RegQueryValueEx                                     2
#define _RegSetValueEx                                       3
#define _RegDeleteValue                                      4
#define _RegQueryInfoKey                                     5

#define _SetDlgItemText                                      6

#else
#endif