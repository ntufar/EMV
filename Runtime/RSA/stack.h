/* $Id: stack.h,v 1.1 2005/06/15 11:53:33 ntufar Exp $ */
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
 * @file
 * This file provides information on the structures, defines and function
 * prototypes used in the manipulation of the #STACK structure used by the
 * library.
 */
#ifndef HEADER_COMMON_STACK_H
#define HEADER_COMMON_STACK_H


#ifdef  __cplusplus
extern "C" {
#endif

#ifndef HEADER_COMMON_STACK_H_TYPEDEF_DEF
#define HEADER_COMMON_STACK_H_TYPEDEF_DEF
/**
 * This structure is used to contain a generic data stack.
 */
typedef struct stack_st STACK;
#endif

#ifndef HEADER_COMMON_STACK_H_STRUCT_DEF
#define HEADER_COMMON_STACK_H_STRUCT_DEF

/**
 * This structure is used to contain a generic data stack.
 */
struct stack_st
    {
    int num;
    char **data;
    int sorted;

    int num_alloc;
#ifndef NOPROTO
    int (*comp)(char **d1, char **d2);
#else
    int (*comp)();
#endif
    };
#endif

#define sk_num(sk)      ((sk)->num)
#define sk_value(sk,n)  ((sk)->data[n])
#define sk_data(sk)     ((sk)->data)

#define sk_new_null()   sk_new(NULL)


#ifndef NOPROTO
STACK *sk_new(int (*cmp)(char **d1, char **d2));
void sk_pop_free(STACK *st, void (*func)(char *data));
int sk_delete_all(STACK *st, char *data, void (*free_func)(char *data));
void sk_clear(STACK *st, void (*free_func)(char *data));
void sk_set_cmp_func(STACK *sk, int (*c)(char **d1, char **d2));
#else
STACK *sk_new(int (*cmp)());
void sk_pop_free(STACK *st, void (*func)());
int sk_delete_all(STACK *st, char *data, void (*free_func)());
void sk_clear(STACK *st, void (*free_func)());
void sk_set_cmp_func(STACK *sk, int (*c)());
#endif

void sk_free(STACK *);
int sk_insert(STACK *sk,char *data,int where);
char *sk_delete(STACK *st,int loc);
char *sk_delete_ptr(STACK *st, char *p);
int sk_find(STACK *st,char *data);
int sk_lfind(STACK *st, char *data);
int sk_move(STACK *st, int loc, int dest);
int sk_push(STACK *st,char *data);
int sk_unshift(STACK *st,char *data);
char *sk_shift(STACK *st);
char *sk_pop(STACK *st);
void sk_zero(STACK *st);
STACK *sk_dup(STACK *st);
int sk_cat(STACK *d_st, STACK *s_st);
char *sk_set(STACK *st, int i, char *value);


#ifdef  __cplusplus
}
#endif

#endif /* HEADER_COMMON_STACK_H */
