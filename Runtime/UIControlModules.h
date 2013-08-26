#ifndef UICONTROLMODULES_H
#define UICONTROLMODULES_H

#define MOD_UIInterface 0x01
#define MOD_UIOperationEvent 0x02
#define MOD_UIControl_Server 0x03
#define MOD_UIControl_Interface 0x04

//Interface functions
#define UI_setString		    0x01
#define UI_setAndReceiveString  0x02
#define UI_getAnswer            0x03
#define UI_selectOption		    0x04
#define UI_addString		    0x05

#define UI_openService          0x06
#define UI_connectedServices    0x07
#define UI_addOperationEvent    0x08

#endif

