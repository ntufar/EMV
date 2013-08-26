#ifndef SERVICECONTROL_CONSTANTS_H
#define SERVICECONTROL_CONSTANTS_H

// Service Status Codes
#define SERVICE_PATH_SET            0x00000001
#define SERVICE_OPENED              0x00000002
#define SERVICE_ERROR               0x80000000

// Service Return Codes
#define SERVICE_SUCCESS             0x00000000
#define SERVICE_ERR_OPEN_FAILED     0x80000001
#define SERVICE_BUSY                0x80000002
#define SERVICE_ERR_NOT_INITIALIZED 0x80000003

#endif