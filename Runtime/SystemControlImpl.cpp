#include "SystemControlImpl.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


SystemControlImpl::SystemControlImpl(void)
{
}

SystemControlImpl::~SystemControlImpl(void)
{
}

// Implementation of the interface function retreiveDate.
// This function gets a current system time from the Operating System. Time is in
// a local timezone.
// Actual value is stored inside of OperationEvent Object. If event is not attached
// then the function returns an error code ERR_EVT_NO_EVNT_OBJECT.
// In a case of successfull retreival of the date, the function returns EVT_SUCCESS.
// Error codes are defined in errors.h file.
int SystemControlImpl::retreiveDate(void)
{
	if (!eventAttached()) 
		return ERR_EVT_NO_EVNT_OBJECT;

	int res;
	if ((res = opEvent->begin_operation()) != EVT_SUCCESS)
		return res;

	time_t t;
	struct tm* st;

	time(&t);
	st = localtime(&t);
	DateStruct ds;
	ds.DD = (byte)st->tm_mday;
	ds.MN = (byte)st->tm_mon + 1; //range: 0-11
	ds.WD = (byte)st->tm_wday + 1; //range: 0-6
	ds.MM = (byte)st->tm_min;
	ds.SS = (byte)st->tm_sec;
	ds.HH = (byte)st->tm_hour;
	ds.CC = (byte)20 + (st->tm_year / 100);
	ds.YY = (byte)st->tm_year;

	// Store the date and a status code inside of the OperationEvent object
	((SystemOperationEvent*)(this->opEvent))->setDate (ds);
	return opEvent->setSuccess();
}

int SystemControlImpl::retreiveDateEx(DateStruct *ds)
{
	time_t t;
	struct tm* st;

	time(&t);
	st = localtime(&t);
	
	ds->DD = (byte)st->tm_mday;
	ds->MN = (byte)st->tm_mon + 1; //range: 0-11
	ds->WD = (byte)st->tm_wday + 1; //range: 0-6
	ds->MM = (byte)st->tm_min;
	ds->SS = (byte)st->tm_sec;
	ds->HH = (byte)st->tm_hour;
	ds->CC = (byte)20 + (st->tm_year / 100);
	ds->YY = (byte)st->tm_year - 100;  //Year is number of years passed since
					   //1900. Thus year 2005 is 105.

	return SUCCESS;
}

// Open a file
int SystemControlImpl::openFile (const char* pathname, 
								 int flags, int *fd)
{
	int fl; // file decriptor
	int io_flags;

	// map SCS defined flags to the standard flags
	setIOflag (flags, &io_flags);
	
	// Open a file
	//fl = open (pathname, io_flags, S_IREAD | S_IWRITE);
	printf("FILE OPEN NOT IMPLEMENTED!!!!!!!\n FIX IT AS SOON AS POSSIBLE!!!!!!\n");
	exit(0);
	
	if (fl == -1)
		return mapError(errno);
	
	*fd = fl;
	return SUCCESS;
}

int SystemControlImpl::writeFile (int fd, const char* buf, 
								  UNINT count, int flags)
{
	int bytesWritten;
	if ((bytesWritten = write(fd, buf, count)) == -1)
		return mapError(errno);
	if (check_bit(flags, SCS_FILE_LN_MODE))
		write(fd, "\n", 1);
	return SUCCESS;
}

int SystemControlImpl::readFile (int fd, UNINT count, int flags)
{
	if (!eventAttached()) 
		return ERR_EVT_NO_EVNT_OBJECT;

	int res;
	if ((res = opEvent->begin_operation()) != EVT_SUCCESS)
		return res;

	// Cast the OperationEvent object to the appropriate type
	SystemOperationEventImpl *pEvent = 
		(SystemOperationEventImpl*) opEvent;
	
	//Reset event
	pEvent->resetEvent();
	
	if (check_bit(flags, SCS_FILE_LN_MODE))
	{
		// Read one line at a time
		return readOneLine(fd, pEvent);
	}
	else if (count == 0)
	{
		// read the entire file
		return readAllFile(fd, pEvent);
	}
	else
	{
		// read # of bytes specified
		return readBytes(fd, count, pEvent);
	}
}

int SystemControlImpl::closeFile (int fd)
{
/*
	if (close(fd) == 0)
		return SUCCESS;
	else
		return mapError(errno);
*/
	printf("FILE CLOSE NOT IMPLEMENTED!!!!!!!\n FIX IT AS SOON AS POSSIBLE!!!!!!\n");
	exit(0);
}

int SystemControlImpl::setIOflag (int scs_flag, int *std_flag)
{
	*std_flag = 0;
	if (check_bit(scs_flag, SCS_FILE_APPEND))
		*std_flag |= O_APPEND;
	if (check_bit(scs_flag, SCS_FILE_CREATE))
		*std_flag |= O_CREAT;
	if (check_bit(scs_flag, SCS_FILE_RW))
		*std_flag |= O_RDWR;
	else if (check_bit(scs_flag, SCS_FILE_RDONLY))
		*std_flag |= O_RDONLY;
	else if (check_bit(scs_flag, SCS_FILE_WRONLY))
		*std_flag |= O_WRONLY;
	return SUCCESS;
}

int SystemControlImpl::mapError(int err)
{
	switch (err)
	{
	case EACCES: return ERR_FILE_IO_EACCES;
	case EINVAL: return ERR_FILE_IO_EINVAL;
	case EMFILE: return ERR_FILE_IO_EMFILE;
	case ENOENT: return ERR_FILE_IO_ENOENT;
	case EBADF: return ERR_FILE_IO_EBADF;
	case ENOSPC: return ERR_FILE_IO_ENOSPC;
	default: return ERR_NO_INFO;
	}
}

int SystemControlImpl::readOneLine(int fd, 
								   SystemOperationEventImpl *pEvent)
{
	int res;
	UNINT buff_sz = 255; 
	int act_count = 1; 

	char *buff = new char [buff_sz];
	if (!buff)
		return pEvent->setError (ERR_MEMORY_ALLOC, RUNTIME_EXECUTION);
	
	if ((act_count = read(fd, buff, act_count)) == -1)
	{
		delete [] buff;
		return pEvent->setError (mapError(errno), RUNTIME_EXECUTION);
	}
	else if (act_count == 0)
	{
		delete [] buff;
		return pEvent->setError (ERR_FILE_IO_EOF, RUNTIME_EXECUTION);
	}
	
	UNINT curChar = 0;

	while (true)
	{
		if (buff[curChar] == '\n')
		{
			// New line is found
			res = pEvent->setText((byte*)buff, curChar);
			delete [] buff;
			return res;
		}
		curChar++;
		if (curChar >= buff_sz)
		{
			char *tmp = new char [buff_sz + 255];
			if (!tmp)
			{
				delete [] buff;
				return pEvent->setError (ERR_MEMORY_ALLOC, RUNTIME_EXECUTION);
			}
			memcpy (tmp, buff, buff_sz);
			delete [] buff;
			buff = tmp;
			buff_sz += 255;
		}
		if ((act_count = read(fd, buff + curChar, 1)) == -1)
		{
			delete [] buff;
			return pEvent->setError (mapError(errno), RUNTIME_EXECUTION);
		}
		else if (act_count == 0)
		{
			// EOF
			// return what was read so far
			res = pEvent->setText((byte*)buff, curChar);
			delete [] buff;
			return res;
		}
	}
	return pEvent->setSuccess();
}

int SystemControlImpl::readAllFile(int fd, 
								   SystemOperationEventImpl *pEvent)
{
	const int buff_size = 255;
	char read_buff[buff_size];
	
	int res;
	
	int act_count = 0;	
	char *buff = 0;
	UNINT buff_sz = 0; 

	while ((act_count = read(fd, read_buff, buff_size)) > 0)
	{
		char *tmp = new char [buff_sz + act_count];
		if (!tmp)
		{
			if (buff)
				delete [] buff;
			return pEvent->setError (ERR_MEMORY_ALLOC, RUNTIME_EXECUTION);
		}
		if (buff)
		{
			// copy previously stored text
			memcpy(tmp, buff, buff_sz);
			// copy just read text
			memcpy(tmp + buff_sz, read_buff, act_count);
			delete [] buff;
			buff = tmp;
			buff_sz = buff_sz + act_count;
		}
		else // (!buff)
		{
			memcpy(tmp, read_buff, act_count);
			buff = tmp;
			buff_sz = act_count;
		}
	}
	
	if (act_count < 0) // actually, the only valid value less than 0 is '-1'
	{
		// Error while reading the file
		res = mapError(errno);
		if (res == ERR_FILE_IO_EOF)
		{
			if (buff)
			{
				res = pEvent->setText ((byte*)buff, buff_sz);
			}
			else
			{
				res = pEvent->setError(res, RUNTIME_EXECUTION);
			}
		}
		else
			res = pEvent->setError(res, RUNTIME_EXECUTION);
	}
	else //if (act_count == 0)
	{
		// Nothing was read from the file
		if (buff)
		{
			res = pEvent->setText ((byte*)buff, buff_sz);
		}
		else
		{
			res = pEvent->setError(ERR_FILE_IO_EOF, RUNTIME_EXECUTION);
		}
	}
	if (buff)
		delete [] buff;

	return res;
}

int SystemControlImpl::readBytes(int fd, UNINT count, 
								 SystemOperationEventImpl *pEvent)
{
	int res;
	int act_count; 
	
	char *buff = new char [count];
	if (!buff)
		return pEvent->setError (ERR_MEMORY_ALLOC, RUNTIME_EXECUTION);
	
	if ((act_count = read(fd, buff, count)) == -1)
	{
		res = pEvent->setError (mapError(errno), RUNTIME_EXECUTION);
	}
	else if (act_count == 0)
	{
		res = pEvent->setError (ERR_FILE_IO_EOF, RUNTIME_EXECUTION);
	}
	else
	{
		res = pEvent->setText((byte*)buff, act_count);
	}

	delete [] buff;
	return res;
}
