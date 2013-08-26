/* $Id: r_platf.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
/*
 * Copyright (C) 1998-2001 RSA Security Inc. All rights reserved. This
 * work contains proprietary information of RSA Security Inc. Distribution
 * is limited to authorised licensees of RSA Security Inc. Any unauthorised
 * reproduction or distribution of this work is strictly prohibited. 
 */
 
#ifndef HEADER_COMMON_R_PLATF_H
#define HEADER_COMMON_R_PLATF_H
 
#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @file 
 * This file contains the common definitions and mapping of platform
 * to specific operating system feature availability.
 */

/* 
 * There is a mixture of library feature, operating system name, 
 * operating system version, processor family, processor version, 
 * processor feature, compiler, compiler version, cpu feature
 * in various defines in RSA products. This header file blends the
 * usage from each product into a consistant single model.
 */

/*
 * Aims:
 *	- single identifier for each set of 'build' options
 *	  (i.e. only one thing that must be set in the compiler flags)
 *	- feature tests rather than 'platform' tests for interfaces
 *	  (reduced usage of 'platform' defines in the code)
 *	- explicit identification of 'arch' (CPU family + CPU version)
 *	- precise specification of compiler and O/S version dependencies
 *	  (where these are actually required)
 *	- independant values and define names for everything for all
 *	  output (i.e. one central set of names and values) which should
 *	  increase consistancy
 *	- reduce clashes with existing 3rd party usage
 *
 * R_OS=R_OS_${NAME}
 * R_OS_VER=${VALUE}
 *
 * R_COMPILER=R_COMPILER_${NAME}
 * R_COMPILER_VER=${VALUE}
 *
 * R_LIBC_VER=${VALUE}
 *
 * R_FEATURE_${NAME}=1
 *
 * R_CPU=R_CPU_${NAME} 
 * or
 * R_CPU_FAMILY=R_CPU_FAMILY_${NAME} 
 * R_CPU_VERSION=${VALUE}
 * or both
 * R_CPU=R_CPU_FAMILY_${R_CPU_VERSION}
 *
 * If needed at compile-time (unclear) then 
 * R_CPU_HAS_${FEATURE}=1 (currently this is only used at runtime)
 * 
 *
 * The defines for each of these are unique values which are constant
 * between products and product releases.
 */

/*----------------------------------------------------------------------------*/

#if 0
/* VENDOR */
/* VxWorks: CPU=ARM7TDMI,MIPS32,I80486,PPC603,SH7700,SIMSPARCSOLARIS,SIMNT */
#endif

/*----------------------------------------------------------------------------*/

#if 0

/* RCOM 
 *
 * build system sets the values in CFLAGS
 * all products end up with r_com.h included
 * 
 * INCLUDE:   r_com.h
 * 	      HEADER_COMMON_R_COM_H 
 *	      r_cpuid.h
 *
 * PLATFORM:  PLATFORM_${NAME} 
 *            R_PLATFORM_${NAME} 
 *
 * CPU:       CPU_${NAME} 
 *
 */

/* values used for identifying platforms in the code */

PLATFORM_IMODE
PLATFORM_LINUX 
SOLARIS
R_PLATFORM_IRIX			/* need to rename to PLATFORM_IRIX */
R_PLATFORM_PSOS			/* need to rename to PLATFORM_PSOS */
HPUX_IA64_32

WINDOWS
WIN32
MSDOS

_HPUX_SOURCE

/* legacy usage in the code */
__sgi
__ultrix
linux
sun
__i386__

UNDER_PALMOS
UNDER_CE			/* this is version number of WinCE OS */

R_OS_HPUX11

/* build system - these have values - which are used */
CPU_X86
CPU_POWERPC
CPU_ALPHA
CPU_IA64
CPU_PA8000
CPU_PARISC
CPU_X86
CPU_SPARC_V8
CPU_SPARC_V8PLUS
CPU_SPARC_V9
CPU_ARM4L

/* r_cpuid.h */
R_CPU_UNDEF
R_CPU_UNKNOWN
R_CPU_SPARC
R_CPU_SPARC64
R_CPU_X86
R_CPU_IA64
R_CPU_ALPHA
R_CPU_MIPS
R_CPU_MIPS64
R_CPU_SHx
R_CPU_M68K
R_CPU_ARM
R_CPU_ARM4L
R_CPU_PARISC
R_CPU_PARISC64
R_CPU_POWERPC

/* Attributes */
R_CPU_DEFAULT    0

/* flags */
R_CPU_SPARC_HAS_MUL
R_CPU_SPARC_HAS_MULD
R_CPU_SPARC_HAS_V9
R_CPU_SPARC_HAS_VIS
R_CPU_SPARC_HAS_FMULADD

/* flags */
R_CPU_X86_HAS_386
R_CPU_X86_HAS_486
R_CPU_X86_HAS_PENTIUM
R_CPU_X86_HAS_PENTIUM_PRO
R_CPU_X86_HAS_PENTIUM_IV
R_CPU_X86_HAS_MMX
R_CPU_X86_HAS_SSE
R_CPU_X86_HAS_SSE2

/* flags */
R_CPU_IA64_HAS_ITANIUM
R_CPU_IA64_HAS_ITANIUM2

#endif

/*----------------------------------------------------------------------------*/

#if 0

/* Crypto-C [+Cert-C] */
/* bsafe.h -> bsfplat.h */

/* Crypto-C
 *
 * INCLUDE:   bsafe.h 
 *	      _BSAFE_H_
 *
 * PLATFORM:  RSA_PLATFORM=RSA_${NAME} 
 *
 * CPU:       CPU_${NAME} 
 *
 */

/* bsfplatf.h */
RSA_I386_486
RSA_WINTEL_IA64
RSA_HP_PA1
RSA_HP_PA2
RSA_HP_64
RSA_HP_IA64
RSA_HP_IA64_32
RSA_LINUX
RSA_LINUX_IA64
RSA_SPARC_SUN_SOLARIS25
RSA_SPARC_SUN_SOLARISV8
RSA_SPARC_SUN_SOLARISV9
RSA_MAC_PPC_CODE_WARRIOR

RSA_MODERN_PLATFORM

/* bsfmacro.h */

RSA_INTEL_MSVC15_16_BIT     10
RSA_INTEL_MSVC20_32_BIT     12
RSA_INTEL_MSVC40_32_BIT     14
RSA_INTEL_BORLAND45_16_BIT  20
RSA_INTEL_BORLAND45_32_BIT  22
RSA_LINUX                   30
RSA_INTEL_LINUX21_32_BIT    31
RSA_INTEL_LINUX30_32_BIT    32
RSA_INTEL_LINUX_GLIBC5      33
RSA_INTEL_LINUX_GLIBC6      34
RSA_INTEL_SCO50_32_BIT      40
RSA_SPARC_SUN_OS_412        100
RSA_SPARC_SUN_SOLARIS       101
RSA_SPARC_SUN_SOLARIS25     102
RSA_SPARC_SUN_SOLARISV8     103
RSA_SPARC_SUN_SOLARISV9     104
RSA_SPARC_SUN_SOLARIS26     RSA_SPARC_SUN_SOLARISV8
RSA_SPARC_SUN_SOLARIS28     RSA_SPARC_SUN_SOLARISV9
RSA_MAC_68K_CODE_WARRIOR    120
RSA_MAC_68K_SYMANTEC        122
RSA_MAC_PPC_CODE_WARRIOR    130
RSA_MAC_PPC_SYMANTEC        132
RSA_ALPHA_DEC_OSF_UNIX      140
RSA_ALPHA_DEC_NT_MSVC40     142
RSA_ALPHA_DEC_VMS           144
RSA_MIPS_R2000_IRIX53       160
RSA_MIPS_R4000_IRIX60       162
RSA_HP_PA                   180
RSA_HP_PA1                  181
RSA_HP_PA2                  182
RSA_HP_64                   183
RSA_HP_IA64                 184
RSA_HP_IA64_32              185
RSA_AIX_414                 200
RSA_RS6000_PPC_AIX414       202
RSA_RS6000_PWR_AIX414       204
RSA_IBM_AIX32               205
RSA_IBM_AIX64               206
RSA_I386_486                210
RSA_WINTEL_IA64             211
RSA_LINUX_IA64              212
RSA_S390_OS390R13           220

/* rsashlib.h */
RSA_SHARED_LIBRARY_X86_WINDOWS   10
RSA_SHARED_LIBRARY_UNIX          30
RSA_SHARED_LIBRARY_HP_32         80
RSA_SHARED_LIBRARY_MACOS9        90
RSA_SHARED_LIBRARY_UNKNOWN       1000

/* rsap11.h */
RSA_PKCS11_X86_WINDOWS   RSA_SHARED_LIBRARY_X86_WINDOWS
RSA_PKCS11_UNIX          RSA_SHARED_LIBRARY_UNIX
RSA_PKCS11_HP_32         RSA_SHARED_LIBRARY_HP_32
RSA_PKCS11_MACOS9        RSA_SHARED_LIBRARY_MACOS9
RSA_PKCS11_UNKNOWN       RSA_SHARED_LIBRARY_UNKNOWN

#endif

/*----------------------------------------------------------------------------*/

/* operating systems */
#define R_OS_LINUX		0x0001
#define R_OS_WINDOWS		0x0002
#define R_OS_SUNOS		0x0003
#define R_OS_SOLARIS		0x0004
#define R_OS_HPUX		0x0005
#define R_OS_MACOS		0x0006
#define R_OS_DEC_OSF		0x0007
#define R_OS_DEC_UNIX		0x0008
#define R_OS_MSDOS		0x0009
#define R_OS_AIX		0x000a
#define R_OS_IRIX		0x000b
#define R_OS_PALMOS		0x000c
#define R_OS_EPOC		0x000d
#define R_OS_SYMBIANOS		R_OS_EPOC
#define R_OS_QNX		0x000e
#define R_OS_NETBSD		0x000f
#define R_OS_FREEBSD		0x0010
#define R_OS_PSOS		0x0011
#define R_OS_WINCE		0x0012
#define R_OS_VXWORKS		0x0013
#define R_OS_SCO_UNIX		0x0014
#define R_OS_UNIXWARE		0x0015
#define R_OS_RIM		0x0016

#define R_OS_VMS		0x0100
#define R_OS_MVS		0x0101
#define R_OS_OS390		0x0102
#define R_OS_OS400		0x0103

/* mask for vendor specific value (will not clash for R_OS_ usage) */
#define R_OS_VENDOR_DEFINED	0xf000

/* compilers */
#define R_COMPILER_VENDOR	0x0000
#define R_COMPILER_GCC		0x0001
#define R_COMPILER_MSVC		0x0002
#define R_COMPILER_INTEL	0x0003
#define R_COMPILER_BORLAND	0x0004
#define R_COMPILER_GREENHILL	0x0005
#define R_COMPILER_IAR		0x0006
#define R_COMPILER_WATCOM	0x0007
#define R_COMPILER_CODEWARRIOR	0x0008

/* CPU and CPU family values */
#define R_CPU_FAMILY(X)		(X & 0xff00)

/* Intel x86/ia32 series */
#define R_CPU_FAMILY_X86	0x0100
#define R_CPU_X86		(R_CPU_FAMILY_X86|0x0001)
#define R_CPU_IA32		R_CPU_X86

/* Intel ia64 Itanium series */
#define R_CPU_FAMILY_IA64	0x0200
#define R_CPU_IA64		(R_CPU_FAMILY_IA64|0x0001)

/* Sun SPARC series */
#define R_CPU_FAMILY_SPARC	0x0300
#define R_CPU_SPARCV8		(R_CPU_FAMILY_SPARC|0x0001)
#define R_CPU_SPARCV8PLUS	(R_CPU_FAMILY_SPARC|0x0002)
#define R_CPU_SPARCV9		(R_CPU_FAMILY_SPARC|0x0003)
#define R_CPU_SPARC_IS_32(X)	(((X)==R_CPU_SPARCV8)||((X)==R_CPU_SPARCV8PLUS))
#define R_CPU_SPARC_IS_64(X)	((X)==R_CPU_SPARCV9)

/* Hewlett Packard PA-RISC series */
#define R_CPU_FAMILY_PARISC	0x0400
#define R_CPU_PARISC1		(R_CPU_FAMILY_PARISC|0x0001)
#define R_CPU_PARISC2		(R_CPU_FAMILY_PARISC|0x0002)
#define R_CPU_PARISC_IS_32(X)	((X)==R_CPU_PARISC1)
#define R_CPU_PARISC_IS_64(X)	((X)==R_CPU_PARISC2)

/* Mororola PowerPC series */
#define R_CPU_FAMILY_POWERPC	0x0500
#define R_CPU_POWERPC		(R_CPU_FAMILY_POWERPC|0x0001)

/* MIPS mips series */
#define R_CPU_FAMILY_MIPS	0x0600
#define R_CPU_R2000		(R_CPU_FAMILY_MIPS|0x0001)
#define R_CPU_R3000		(R_CPU_FAMILY_MIPS|0x0002)
#define R_CPU_R4000		(R_CPU_FAMILY_MIPS|0x0003)
#define R_CPU_MIPS_IS_32(X)	(((X)==R_CPU_R2000)||((X)==R_CPU_R3000))
#define R_CPU_MIPS_IS_64(X)	((X)==R_CPU_R4000)

/* Digital/Compaq alpha series */
#define R_CPU_FAMILY_ALPHA	0x0700
#define R_CPU_ALPHA		(R_CPU_FAMILY_ALPHA|0x0001)

/* Motorala 68k series */
#define R_CPU_FAMILY_M68K	0x0800
#define R_CPU_M68K		(R_CPU_FAMILY_M68K|0x0001)

/* ARM arm series */
#define R_CPU_FAMILY_ARM	0x0900
#define R_CPU_ARM		(R_CPU_FAMILY_ARM|0x0001)
#define R_CPU_ARM4L		(R_CPU_FAMILY_ARM|0x0002)

/* Hitachi SuperH series */
#define R_CPU_FAMILY_SH		0x0a00
#define R_CPU_SH2		(R_CPU_FAMILY_SH|0x00001)
#define R_CPU_SH3		(R_CPU_FAMILY_SH|0x00002)
#define R_CPU_SH		R_CPU_SH2

/* Matsushita MN series */
#define R_CPU_FAMILY_MN		0x0b00
#define R_CPU_MN102L		(R_CPU_FAMILY_MN|0x0001)
#define R_CPU_MN103L		(R_CPU_FAMILY_MN|0x0002)
#define R_CPU_MN		R_CPU_MN102L

/*----------------------------------------------------------------------------*/

/* features are interfaces or properties of platforms */
#define R_FEATURE_NOT_SUPPORTED 0x0000

#define R_FEATURE_BITSIZE_32	0x0001
#define R_FEATURE_BITSIZE_64	0x0002

#define R_FEATURE_SHLIB_DL	0x0001
/** svr4,unix - dlopen, dlsym, dlclose */

#define R_FEATURE_SHLIB_WIN	0x0002
/** win{16,32,64} - LoadLibrary, GetProcAddress, FreeLibrary */

#define R_FEATURE_SHLIB_SHL	0x0003
/** hpux{10,11} - shl_load, shl_findsym, shl_unload */

#define R_FEATURE_SHLIB_MAC	0x0004
/** macos - GetSharedLibrary, FindSymbol, CloseConnection */

#define R_FEATURE_SHLIB_POS	0x0005
/** palmos - SysLibLoad, SysLibTblEntry, SysLibClose */

#define R_FEATURE_SHLIB_VXW	0x0006
/** vxworks - loadModule, symFindByName, unld */

#define R_FEATURE_SHLIB_WCE	0x0007
/** wince - (Converts to Unicode) LoadLibrary, GetProcAddress, FreeLibrary */

#define R_FEATURE_SHLIB_EPC	0x0008
/** epoc - RLibrary: Load, Lookup, Close */

/*----------------------------------------------------------------------------*/

/* now map from RCOM and Crypto-C platform defines */

/* if we have not been provided with an explicit value for R_OS then we 
 * attempt to guess the right value from the existing flags used in 
 * building products
 */

#if !defined(R_OS)

#if defined(_BSAFE_MACRO_H_)

/* if we have included bsfmacro.h then we are working with Crypto-C */
#if RSA_PLATFORM == RSA_I386_486
#define R_OS 	R_OS_WINDOWS
#define R_CPU 	R_CPU_X86
#endif
#if RSA_PLATFORM == RSA_WINTEL_IA64
#define R_OS 	R_OS_WINDOWS
#define R_CPU 	R_CPU_IA64
#endif
#if RSA_PLATFORM == RSA_LINUX
#define R_OS 	R_OS_LINUX
#define R_CPU 	R_CPU_X86
#endif
#if RSA_PLATFORM == RSA_LINUX_IA64
#define R_OS 	R_OS_LINUX
#define R_CPU 	R_CPU_IA64
#endif
#if RSA_PLATFORM == RSA_SPARC_SUN_SOLARISV8
#define R_OS    R_OS_SOLARIS
#define R_CPU   R_CPU_SPARCV8
#endif
#if RSA_PLATFORM == RSA_SPARC_SUN_SOLARISV9
#define R_OS    R_OS_SOLARIS
#define R_CPU   R_CPU_SPARCV9
#endif

#else /* !defined(_BSAFE_MACRO_H_) */

/* otherwise we are working with an RCOM 'build' based setup */

#if defined(WINDOWS) || defined(WIN32) || defined(WIN64)
#define R_OS R_OS_WINDOWS
#if defined(CPU_X86)
#define R_CPU R_CPU_X86
#endif
#if defined(CPU_IA64)
#define R_CPU R_CPU_IA64
#endif
#endif

#if defined(PLATFORM_LINUX)
#define R_OS R_OS_LINUX
#if defined(CPU_X86)
#define R_CPU R_CPU_X86
#endif
#if defined(CPU_IA64)
#define R_CPU R_CPU_IA64
#endif /* CPU_IA64 */
#endif /* PLATFORM_LINUX */

#if defined(PLATFORM_SOLARIS)
#define R_OS  R_OS_SOLARIS
#if defined(CPU_SPARC_V8)
#define R_CPU R_CPU_SPARCV8
#endif
#if defined(CPU_SPARC_V8PLUS)
#define R_CPU R_CPU_SPARCV8PLUS
#endif
#if defined(CPU_SPARC_V9)
#define R_CPU R_CPU_SPARCV9
#endif
#endif /* PLATFORM_SOLARIS */

#if defined(PLATFORM_HPUX_32)
#define R_OS	R_OS_HPUX
#define R_FEATURE_BITSIZE	R_FEATURE_BITSIZE_32
#endif

#if defined(PLATFORM_HPUX_64)
#define R_OS	R_OS_HPUX
#define R_FEATURE_BITSIZE	R_FEATURE_BITSIZE_64
#endif

#if defined(PLATFORM_MACOS)
#define R_OS	R_OS_MACOS
#endif

#if defined(PLATFORM_PALMOS)
#define R_OS	R_OS_PALMOS
#endif

#if defined(PLATFORM_VXWORKS)
#define R_OS	R_OS_VXWORKS
#endif

#if defined(PLATFORM_WINCE)
#define R_OS	R_OS_WINCE
#endif

#if defined(PLATFORM_EPOC)
#define R_OS	R_OS_EPOC
#endif

#if defined(PLATFORM_AIX)
#define R_OS	R_OS_AIX
#endif

#endif /*  defined(_BSAFE_MACRO_H_) */

#endif /* !defined(R_OS) */

/*----------------------------------------------------------------------------*/

/* this code switches based on R_OS ... it really should switch based 
 * on a unique build setup but I haven't done that yet
 */

#if R_OS == R_OS_WINDOWS

/* Win32 - MSVC 6.0 */

#if !defined(R_CPU)
#define R_CPU 			R_CPU_X86
#endif

#if !defined(R_COMPILER)
#define R_COMPILER 		R_COMPILER_MSVC
#endif
#if !defined(R_COMPILER_VER)
#define R_COMPILER_VER 		0x0C00			/* 12.00 (MSVC6) */
#endif

#define R_FEATURE_BITSIZE	R_FEATURE_BITSIZE_32

#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_WIN

#endif /* R_OS == R_OS_WINDOWS */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_LINUX

/* Linux 2.2, gcc2.96, libc6 (glibc)  32bit build */

#if !defined(R_OS_VER)
#define R_OS_VER 		0x0202			/* 2.2 kernel */
#endif

#if !defined(R_CPU)
#define R_CPU 			R_CPU_X86
#endif

#if !defined(R_COMPILER)
#define R_COMPILER 		R_COMPILER_GCC
#endif
#if !defined(R_COMPILER_VER)
#define R_COMPILER_VER 		0x0260			/* 2.96 */
#endif
#if !defined(R_LIBC_VER)
#define R_LIBC_VER 		0x0600			/* libc6 (glibc2) */
#endif

#define R_FEATURE_BITSIZE	R_FEATURE_BITSIZE_32

#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_DL

#endif /* R_OS == R_OS_LINUX */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_SOLARIS
#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_DL
#if !defined(R_COMPILER)
#ifdef __GNUC__
#define R_COMPILER              R_COMPILER_GCC
#else /* !__GNUC__ */
#define R_COMPILER              R_COMPILER_VENDOR
#endif /* __GNUC__ */
#endif /* !R_COMPILER */
#endif /* R_OS == R_OS_SOLARIS */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_MACOS
#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_MAC
#endif /* R_OS == R_OS_MACOS */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_PALMOS
#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_POS
#define R_SHLIB_E_MALLOC_MEM_SIZE (20 * 1024)
#ifndef NO_ENV_VARS
#define NO_ENV_VARS
#endif
#endif /* R_OS == R_OS_PALMOS */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_VXWORKS
#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_VXW
#define R_SHLIB_E_MALLOC_MEM_SIZE (20 * 1024)
#ifdef __GNUC__
#define R_COMPILER              R_COMPILER_GCC
#else /* !__GNUC__ */
#define R_COMPILER              R_COMPILER_VENDOR
#endif /* __GNUC__ */
#endif /* R_OS == R_OS_VXWORKS */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_WINCE
#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_WCE
#define R_SHLIB_E_MALLOC_MEM_SIZE (20 * 1024)
#ifndef NO_ENV_VARS
#define NO_ENV_VARS
#endif
#endif /* R_OS == R_OS_WINCE */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_EPOC
#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_EPC
#define R_SHLIB_E_MALLOC_MEM_SIZE (20 * 1024)
#endif /* R_OS == R_OS_EPOC */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_AIX
#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_DL
#endif /* R_OS == R_OS_AIX */

/*----------------------------------------------------------------------------*/

#if R_OS == R_OS_HPUX
#if defined(PLATFORM_HPUX_64)
#define R_FEATURE_SHLIB		R_FEATURE_SHLIB_SHL
#endif
#if defined(PLATFORM_HPUX_32)
#define R_FEATURE_SHLIB         R_FEATURE_SHLIB_SHL
#endif
#endif /* R_OS == R_OS_HPUX */

/*----------------------------------------------------------------------------*/

/* set a default shared library e_malloc memory size */
#if !defined(R_SHLIB_E_MALLOC_MEM_SIZE)
#define R_SHLIB_E_MALLOC_MEM_SIZE (32 * 1024)
#endif

/* all features are set in terms of specific values - those features that
 * we want to have a boolean flag for are handled here explicitly 
 */

#if R_FEATURE_BITSIZE == R_FEATURE_BITSIZE_32
#define R_FEATURE_IS_32BIT		1	
#endif

#if R_FEATURE_BITSIZE == R_FEATURE_BITSIZE_64
#define R_FEATURE_IS_64BIT		1	
#endif

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_PLATF_H */


