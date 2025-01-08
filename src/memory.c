/* memory.c    2025-01-03 */

/* Copyright 2021 Plan 9 Foundation */

/* This file is part of the R-package `voronoifortune'. */
/* See the file ../../DESCRIPTION for licensing issues. */

#include <R.h>
#include <Rinternals.h>
#include "vdefs.h"

extern int sqrt_nsites, siteidx ;

void
freeinit(Freelist * fl, int size)
    {
    fl->head = (Freenode *)NULL ;
    fl->nodesize = size ;
    }

char *
getfree(Freelist * fl)
    {
    int i ;
    Freenode * t ;
    if (fl->head == (Freenode *)NULL)
        {
        /* t =  (Freenode *) myalloc(sqrt_nsites * fl->nodesize) ; */
	    t =  (Freenode *) R_alloc(sqrt_nsites, fl->nodesize) ;
        for(i = 0 ; i < sqrt_nsites ; i++)
            {
            makefree((Freenode *)((char *)t+i*fl->nodesize), fl) ;
            }
        }
    t = fl->head ;
    fl->head = (fl->head)->nextfree ;
    return ((char *)t) ;
    }

void
makefree(Freenode * curr, Freelist * fl)
    {
    curr->nextfree = fl->head ;
    fl->head = curr ;
    }
