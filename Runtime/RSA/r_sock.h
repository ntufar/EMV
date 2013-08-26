/* $Id: r_sock.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2002 RSA Security Inc. All rights reserved.
 *
 * This work contains proprietary information of RSA Security.
 * Distribution is limited to authorized licensees of RSA
 * Security. Any unauthorized reproduction, distribution or
 * modification of this work is strictly prohibited.
 *
 */
/**
 * @file r_sock.h
 * This file provides defines used for enabling platform-independent socket
 * code.
 */
#ifndef HEADER_COMMON_R_SOCK_H
#define HEADER_COMMON_R_SOCK_H

#ifdef  __cplusplus
extern "C" {
#endif

#if defined(WINDOWS) || defined(WIN32)

#define get_last_socket_error()       WSAGetLastError()
#define clear_socket_error()          WSASetLastError(0)
#define readsocket(s,b,n)             recv((s),(b),(n),0)
#define writesocket(s,b,n)            send((s),(b),(n),0)
#define EADDRINUSE                    WSAEADDRINUSE

#else /* !WINDOWS */

#define get_last_socket_error()       errno
#define clear_socket_error()          errno=0
#ifdef VXWORKS
/*
 * Vxworks ioctl prototype expects an int
 */
#define ioctlsocket(a,b,c)            ioctl(a,b,(int)c)
#else /* !VXWORKS */
#define ioctlsocket(a,b,c)            ioctl(a,b,c)
#endif /* VXWORKS */
#define closesocket(s)                close(s)
/*
 * Epoc read function waits for passed in buffer to
 * fill completely before returning so use recv instead
 */
#ifdef PLATFORM_EPOC
#define readsocket(s,b,n)             recv((s),(b),(n),0)
#define writesocket(s,b,n)            send((s),(b),(n),0)
#else  /* !PLATFORM_EPOC */
#define readsocket(s,b,n)             read((s),(b),(n))
#define writesocket(s,b,n)            write((s),(b),(n))
#endif /* PLATFORM_EPOC */

#endif /* WINDOWS || WIN32 */

/* the return type from lseek varies across platforms - the R_LSEEK_RET_CAST
 * macro is used to allow for this difference without adding platform
 * testing logic in the code that uses lseek
 */
#if (defined (WINDOWS) || defined(MSDOS) || defined(WIN32)) && !defined(UNDER_CE)
#define R_LSEEK_RET_CAST(offset) ((long)(offset))
#else  /* !WINDOWS || MSDOS ||WIN32 && !UNDER_CE */
#define R_LSEEK_RET_CAST(offset) ((off_t)(offset))
#endif  /* !WINDOWS || MSDOS ||WIN32 && !UNDER_CE */

#if defined(WINDOWS) || defined(MSDOS) || defined(WIN32)

#ifdef NO_SOCK
#define SHUTDOWN(fd)            close(fd)
#define SHUTDOWN2(fd)           close(fd)
#else /* !NO_SOCK */
#include <winsock.h>
#define SHUTDOWN(fd)            { shutdown((fd),0); closesocket(fd); }
#define SHUTDOWN2(fd)           { shutdown((fd),2); closesocket(fd); }
#endif /* NO_SOCK */

#else /* !(WINDOWS || MSDOS || WIN32) */

#if !defined(VMS)

/* Unix or Unix-like platforms */
#ifndef NO_GETHOSTBYNAME
#include <netdb.h>
#else /* !NO_GETHOSTBYNAME */
#define NO_NETDB_H
#endif /* !NO_GETHOSTBYNAME */

#ifdef UNDER_PALMOS

#include <sys_types.h>
#include <sys_socket.h>

#ifndef FIONBIO
#define FIONBIO FNDELAY
#endif /* FIONBIO */

#else /* !UNDER_PALMOS */

#include <sys/types.h>
#include <sys/socket.h>

#endif /* !UNDER_PALMOS */

#ifdef __EPOC32__
/*
 * EPOC uses bzero() in the FD_ZERO macro.
 * We don't want to use this function (NON-ANSI),
 * so we redefie the FD_ZERO macro
 */
#ifdef FD_ZERO
#undef FD_ZERO
#define FD_ZERO(p) 	Memset( (caddr_t)(p), 0, sizeof (*(p)) )
#endif
#endif /* __EPOC32__ */

#ifdef FILIO_H
#include <sys/filio.h>        /* Added for FIONBIO under unixware */
#endif /* FILIO_H */

#if !defined(VXWORKS) && !defined(R_PLATFORM_PSOS)
#ifdef UNDER_PALMOS
#include <sys_time.h>         /* for FD_XXX macros */
#else /* !UNDER_PALMOS */
#ifndef MACOS
#include <sys/param.h>
#endif /* !MACOS */
#include <sys/time.h>         /* for FD_XXX macros */
#endif /* !UNDER_PALMOS */
#endif /* !VXWORKS */

#ifdef UNDER_PALMOS
#include <netinet_in.h>
#else /* !UNDER_PALMOS */
#include <netinet/in.h>
#endif /* !UNDER_PALMOS */

#endif /* !VMS */

#if defined(NeXT) || defined(_NEXT_SOURCE)
#include <sys/fcntl.h>
#include <sys/types.h>
#endif /* NeXT || _NEXT_SOURCE */

#ifdef VXWORKS
#include <ioLib.h>     /* Includes the ioctl command values */
#include <sockLib.h>
#include <selectLib.h>
#endif /* VXWORKS */

#if defined(AIX) || defined(QNX)
#include <sys/select.h>
#endif /* AIX || QNX */

#if defined(sun) || defined(linux)
#include <netinet/tcp.h>
#endif /* sun || linux */

#if defined(sun)
#include <sys/filio.h>
#else /* !sun */
#if !defined(UNDER_PALMOS) && !defined(R_PLATFORM_PSOS)
#include <sys/ioctl.h>
#endif /* !UNDER_PALMOS && !R_PLATFORM_PSOS */
#endif /* !sun */

#ifdef VMS
#include <unixio.h>
#endif /* VMS */

#define SHUTDOWN(fd)    { shutdown((fd),0); close((fd)); }
#define SHUTDOWN2(fd)   { shutdown((fd),2); close((fd)); }
#define INVALID_SOCKET    (-1)

#endif /* !(WINDOWS || MSDOS || WIN32) */

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_SOCK_H */


