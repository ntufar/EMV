/* $Id: r_vararg.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_vararg.h
 * This file contains the set of macros used to enable the differences between
 * K&R and ANSI-C handling of variadic functions to be unified so portable code
 * can be more easily maintained.
 */

#ifndef HEADER_COMMON_R_VARARG_H
#define HEADER_COMMON_R_VARARG_H

#ifdef  __cplusplus
extern "C" {
#endif

/* Select ANSI-C version by default unless NOPROTO is set */
#ifndef NOPROTO
#define VAR_ANSI
#endif /* !NOPROTO */

#ifdef VAR_ANSI

/* ANSI version of a "portable" macro set for variable number of args */
#ifndef __STDARG_H__
#include <stdarg.h>
#endif /* !__STDARG_H__ */

#define VAR_PLIST(arg1type,arg1)    arg1type arg1, ...
#define VAR_PLIST2(arg1type,arg1,arg2type,arg2) arg1type arg1,arg2type arg2,...
#define VAR_ALIST
#define VAR_BDEFN(args,arg1type,arg1)   va_list args
#define VAR_BDEFN2(args,arg1type,arg1,arg2type,arg2)    va_list args
#define VAR_INIT(args,arg1type,arg1)    va_start(args,arg1);
#define VAR_INIT2(args,arg1type,arg1,arg2type,arg2) va_start(args,arg2);
#define VAR_ARG(args,type,arg)  arg=va_arg(args,type)
#define VAR_END(args)           va_end(args);

#else /* !VAR_ANSI */

/* K&R version of a "portable" macro set for variable number of args */

#ifndef __VARARGS_H__
#include <varargs.h>
#endif /* !__VARARGS_H__ */

#define VAR_PLIST(arg1type,arg1)        va_alist
#define VAR_PLIST2(arg1type,arg1,arg2type,arg2) va_alist
#define VAR_ALIST               va_dcl
#define VAR_BDEFN(args,arg1type,arg1)   va_list args; arg1type arg1
#define VAR_BDEFN2(args,arg1type,arg1,arg2type,arg2)    va_list args; \
        arg1type arg1; arg2type arg2
#define VAR_INIT(args,arg1type,arg1)    va_start(args); \
        arg1=va_arg(args,arg1type);
#define VAR_INIT2(args,arg1type,arg1,arg2type,arg2) va_start(args); \
        arg1=va_arg(args,arg1type);     arg2=va_arg(args,arg2type);
#define VAR_ARG(args,type,arg)          arg=va_arg(args,type)
#define VAR_END(args)                   va_end(args);

#endif /* !VAR_ANSI */

#ifdef  __cplusplus
}
#endif

#endif /*  HEADER_COMMON_R_VARARG_H */

