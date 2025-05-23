/* heap.c    2025-01-03 */

/* Copyright 2021 Plan 9 Foundation */

/* This file is part of the R-package `voronoifortune'. */
/* See the file ../../DESCRIPTION for licensing issues. */

#include <R.h>
#include <Rinternals.h>
#include "vdefs.h"

int PQmin, PQcount, PQhashsize ;
Halfedge * PQhash ;

void
PQinsert(Halfedge * he, Site * v, double offset)
    {
    Halfedge * last, * next ;

    he->vertex = v ;
    ref(v) ;
    he->ystar = v->coord.y + offset ;
    last = &PQhash[ PQbucket(he)] ;
    while ((next = last->PQnext) != (Halfedge *)NULL &&
      (he->ystar  > next->ystar  ||
      (he->ystar == next->ystar &&
      v->coord.x > next->vertex->coord.x)))
        {
        last = next ;
        }
    he->PQnext = last->PQnext ;
    last->PQnext = he ;
    PQcount++ ;
    }

void
PQdelete(Halfedge * he)
    {
    Halfedge * last;

    if(he ->  vertex != (Site *) NULL)
        {
        last = &PQhash[PQbucket(he)] ;
        while (last -> PQnext != he)
            {
            last = last->PQnext ;
            }
        last->PQnext = he->PQnext;
        PQcount-- ;
        deref(he->vertex) ;
        he->vertex = (Site *)NULL ;
        }
    }

int
PQbucket(Halfedge * he)
    {
    int bucket ;


    if	    (he->ystar < ymin)  bucket = 0;
    else if (he->ystar >= ymax) bucket = PQhashsize-1;
    else 			bucket = (he->ystar - ymin)/deltay * PQhashsize;
    if (bucket < 0)
        {
        bucket = 0 ;
        }
    if (bucket >= PQhashsize)
        {
        bucket = PQhashsize-1 ;
        }
    if (bucket < PQmin)
        {
        PQmin = bucket ;
        }
    return (bucket);
    }

int
PQempty(void)
    {
    return (PQcount == 0) ;
    }


Point
PQ_min(void)
    {
    Point answer ;

    while (PQhash[PQmin].PQnext == (Halfedge *)NULL)
        {
        ++PQmin ;
        }
    answer.x = PQhash[PQmin].PQnext->vertex->coord.x ;
    answer.y = PQhash[PQmin].PQnext->ystar ;
    return (answer) ;
    }

Halfedge *
PQextractmin(void)
    {
    Halfedge * curr ;

    curr = PQhash[PQmin].PQnext ;
    PQhash[PQmin].PQnext = curr->PQnext ;
    PQcount-- ;
    return (curr) ;
    }

void
PQinitialize(void)
    {
    int i ;

    PQcount = PQmin = 0 ;
    PQhashsize = 4 * sqrt_nsites ;
    PQhash = (Halfedge *)R_alloc(PQhashsize, sizeof *PQhash) ;
    for (i = 0 ; i < PQhashsize; i++)
        {
        PQhash[i].PQnext = (Halfedge *)NULL ;
        }
    }
