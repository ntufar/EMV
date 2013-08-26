#ifndef POSCONTROLMODULES_H
#define POSCONTROLMODULES_H

#define MOD_POSControl_Interface 0x01
#define MOD_POSControl_Server    0x02
#define MOD_POSInterface         0x03

// Interface Functions
#define POS_execute           0x01
#define POS_init              0x02
#define POS_addOperationEvent 0x03
#define POS_removeEvent       0x04
#define POS_open              0x05

#endif