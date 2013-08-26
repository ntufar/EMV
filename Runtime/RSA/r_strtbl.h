/* $Id: r_strtbl.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file r_strtbl.h
 * This file provides information on the defines, structures and function
 * prototypes used in the manipulation of indexed string tables.
 */
#ifndef HEADER_COMMON_R_STRTBL_H
#define HEADER_COMMON_R_STRTBL_H

#ifdef  __cplusplus
extern "C" {
#endif

/* Description type defines */
#define R_STRTBL_SHORT_DESCRIPTION                      1
#define R_STRTBL_LONG_DESCRIPTION                       2

/* The code definition and string structure */
typedef struct r_strtbl_st
        {
        int code;
        char *short_desc;
        char *long_desc;
        } R_STRTBL;

char *R_STRTBL_code_to_description(R_STRTBL *table, int code, int desc_type);
char *R_STRTBL_code_to_description_x(R_STRTBL *table, int code, int desc_type,
    char *default_desc);

int R_STRTBL_description_to_code(R_STRTBL *table, char *desc, int desc_type);
int R_STRTBL_description_to_code_x(R_STRTBL *table, char *desc, int desc_type,
    int default_code);

#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_R_STRTBL_H */

