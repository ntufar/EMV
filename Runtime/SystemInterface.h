// SystemControl Service
// SystemControl Interface Declaration.
//
// Defines an interface to access Operating System specific commands.

#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H

#include "custom_types.h"
#include "ServiceInterface.h"

// Define File IO flags
#define SCS_FILE_APPEND  0x01
#define SCS_FILE_CREATE  0x02
#define SCS_FILE_RDONLY   0x04
#define SCS_FILE_WRONLY   0x08
#define SCS_FILE_RW (SCS_FILE_RDONLY | SCS_FILE_WRONLY)
#define SCS_FILE_LN_MODE 0x10

// Errors
//-------
// Tried to open read-only file for writing, or file's sharing 
// mode does not allow specified operations, 
// or given path is directory:
#define ERR_FILE_IO_EACCES 0xA7000001
//Invalid flags argument: 
#define ERR_FILE_IO_EINVAL 0xA7000002
//No more file handles available (too many open files):
#define ERR_FILE_IO_EMFILE 0xA7000003
//File or path not found:
#define ERR_FILE_IO_ENOENT 0xA7000004
//An invalid file-handle parameter:
#define ERR_FILE_IO_EBADF 0xA7000005
//There is not enough space left on the device for the operation:
#define ERR_FILE_IO_ENOSPC 0xA7000006
// Trying to read End-of-File
#define ERR_FILE_IO_EOF 0xA7000007

class SystemInterface: public ServiceInterface
{
public:
	SystemInterface(void);
	virtual ~SystemInterface(void);

public:
	virtual int retreiveDate(void) = 0;
	virtual int retreiveDateEx(DateStruct *date) = 0;

	// Purpose: Opens a file for reading or (and) writing.
	// Parameters:
	//  pathname - a path and thename of thefile to be opened
	//  flags - type of operations allowed (see IO flags above)
	//  fd - a pointer initialized to a file decriptor if operation
	//		succeeds.
	// Returns:
	//	SUCCESS (0) - if file is opened successfully (fd points to a 
	//				  file descriptor
	//  negative number - error code (see above for possible values)
	// Note:
	//	This function doesn't require an operation event object
	virtual int openFile (const char* pathname, int flags, int *fd) = 0;
	
	// Purpose: writes or appends to a file.
	// Parameters:
	//  fd - a file descriptor returned by openFile function
	//  buf - a buffer containg a text to be written to the file
	//  count - a number of bytes to write into the file (<= size of
	//			the buffer buf)
	//  flags - operation flags. Currently only one value is supported:
	//     SCS_FILE_LN_MODE - writes a text to the file and appends it
	//     with new line character.
	//	   If flags is 0, the new text is not appended with new line character
	// Returns:
	//	SUCCESS (0) - if text is successfully written to the file 
	//  negative number - error code (see above for possible values)
	// Note:
	//	This function doesn't require an operation event object
	virtual int writeFile (int fd, const char* buf, UNINT count,
		int flags) = 0;

	// Purpose: reads a text from a file.
	// Parameters:
	//  fd - a file descriptor returned by openFile function
	//  count - a number of bytes to read from the file.
	//		if count is 0 - the entier file is read
	//  flags - operation flags. Currently only one value is supported:
	//     SCS_FILE_LN_MODE - reads a text until a new line character
	//       is encountered. A new line character is disgarded (not 
	//       included in returned text).
	//	   If flags is set to SCS_FILE_LN_MODE, then the count argument
	//	     is ignored
	//	   Set flags to 0 to read the entire file or fixed number of
	//		 characters
	// Returns:
	//	SUCCESS (0) - text is successfully read from the file. Use
	//		the getText function of the SystemOperationEvent object
	//		to retrieve the actual value read from the file.
	//  EVT_ERROR - error condition. Use the getError function
	//		of the SystemOperationEvent object to retrieve an error code
	//		indicating the error (see above for possible values)
	// Note:
	//	This function requires an operation event object
	virtual int readFile (int fd, UNINT count, int flags) = 0;


	// Purpose: closes a file.
	// Parameters:
	//  fd - a file descriptor returned by openFile function
	// Returns:
	//	SUCCESS (0) - File is closed successfully
	//  Negative number - an error code indicating the error 
	//		(see above for possible values)
	// Note:
	//	This function does not require an operation event object
	virtual int closeFile (int fd) = 0;
};

#endif

