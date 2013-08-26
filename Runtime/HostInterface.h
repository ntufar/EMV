// HostControl Service
// HostControl Interface Declaration.
//
// HostControl is used to send online messages to the host, and 
// pass the response back from the host to the caller.

#ifndef HOSTINTERFACE_H
#define HOSTINTERFACE_H


#include "ServiceInterface.h"
#include "custom_types.h"
#include "errors.h"

enum ONLINE_RESULT {ON_RES_UNKNOWN, ONRES_DECLINE, ONRES_REFERRAL, 
					ONRES_APPROVE};

// Errors:
#define ERR_HOST_UNSPECIFIED_ERROR 0xC1000000
#define ERR_HOST_COMM_ERROR       0xC1000001
#define ERR_HOST_DISCONNECT       0xC1000002
#define ERR_INVALID_HOST		  0xC1000003
#define ERR_HOST_INVALID_PORT     0xC1000004
#define ERR_HOST_INVALID_RESPONSE 0xC1000005
#define ERR_HOST_NO_CONNECTION    0xC1000006
#define ERR_HOST_NO_RESPONSE      0xC1000007
#define ERR_HOST_PROCESSING_ERROR 0xC1000008
#define ERR_HOST_INVALID_AID      0xC1000009
#define ERR_HOST_BUFFER_OVERFLOW  0xC100000A
#define ERR_HOST_MSG_NOT_SUPPORTED 0xC100000B
#define ERR_HOST_UNKNOWN_AUTH_CODE 0xC100000C

#define HOST_INFINITE    0x7FFFFFFF

// Define online message types:
#define MSG_AUTHORIZATION_REQUEST 0x01
#define MSG_FINANCIAL_REQUEST     0x02
#define MSG_ONLINE_ADVICE         0x03
#define MSG_REVERSAL              0x04
#define MSG_DATA_BATCH            0x05

enum ONLINE_DATA_TAGS {AUTH_RQST_TAGS, RESP_TAGS, FINANC_RQST_TAGS,
					   ADVICE_TAGS, REVERSAL_TAGS};

#define AUTH_RQST_REG_KEY     "4000000A"
#define RESP_REG_KEY          "4000000C"
#define REVERSAL_REG_KEY      "4000000D"
#define FINANC_RQST_REG_KEY   "4000000E"
#define ADVICE_REG_KEY        "4000000F"
#define DATA_BATCH_KEY        "40000010"

class HostInterface :
	public ServiceInterface
{
public:
	HostInterface(void);
	virtual ~HostInterface(void);

	// Connects to a host.
	// Returns SUCCESS (0) if connection succeeded, or error code otherwise
	virtual int host_connect() = 0;

	// Returns an array of tags for data required for online message.
	virtual int getOnlineDataTags (ONLINE_DATA_TAGS tagType) = 0;

	// Analyzes a Response Code and returns ONLINE_RESULT indicating
	// whether the transaction is approved, declined, or referral is required
	virtual ONLINE_RESULT AnalyzeAuthResponse (const byte* const AuthRespCode) = 0;

	// Sends data to the host, waits for the response, and returns response data.
	// Parameters:
	// out_data - a buffer with data to be sent to the host
	// out_len - the size of the out_data in bytes
	// response_data - a buffer to be filled with the data received from the host.
	//				Data must be in TLV format
	// resp_len - the size of the response_buffer in bytes. On return, must be set to 
	//		     the actual size of data received from the host.
	// timeout - time im milliseconds to wait until response from the host is received.
	//			Default value is SCS_TO_INFINITE (0x7fffffff)
	// Returns:
	//		SUCCESS (0) - operation succeeds. The resp_len parameter has the actual
	//      size of the response data;
	//		ERR_BUFFER_OVERFLOW (0x80000017)- the size of the response_data buffer 
	//		is too small to keep the data. The resp_len parameter has the size 
	//      of the buffer required to fit response data
	//      error code - some other errors
	virtual int send_data(int msg_type, 
						  const byte *out_data, UNINT out_len,
				          UNINT timeout = SCS_TO_INFINITE) = 0;
	
	// Disconnects from the host
	virtual void host_disconnect() = 0;
};

#endif

