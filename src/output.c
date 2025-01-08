/* output.c    2024-12-19 */

/* Copyright 2021 Plan 9 Foundation, 2024 Emmanuel Paradis */

/* This file is part of the R-package `voronoifortune'. */
/* See the file ../../DESCRIPTION for licensing issues. */

#include <R.h>
#include <Rinternals.h>
#include "vdefs.h"

extern int debug ;
extern double ymax, ymin, xmax, xmin ;

double pxmin, pxmax, pymin, pymax, cradius;

void
out_bisector(Edge * e)
    {
    if (!debug)
        {
	line_a[il] = e->a;
	line_b[il] = e->b;
	line_c[il] = e->c;
	il++;
        }
    if (debug)
        {
        Rprintf("line(%d) %gx+%gy=%g, bisecting %d %d\n", e->edgenbr,
        e->a, e->b, e->c, e->reg[le]->sitenbr, e->reg[re]->sitenbr) ;
        }
    }

void
out_ep(Edge * e)
    {
	edge_nbr[ie] = e->edgenbr;
        edge_vtx1[ie] = e->ep[le] != (Site *)NULL ? e->ep[le]->sitenbr : -1;
        edge_vtx2[ie] = e->ep[re] != (Site *)NULL ? e->ep[re]->sitenbr : -1;
	ie++;
    }

void
out_vertex(Site * v)
    {
    if (!debug)
        {
	coord_vertex_x[i_vtx] = v->coord.x;
	coord_vertex_y[i_vtx] = v->coord.y;
	i_vtx++;
        } else
        {
        Rprintf("vertex(%d) at %f %f\n", v->sitenbr, v->coord.x, v->coord.y) ;
        }
    }

void
out_site(Site * s)
    {
    if (debug)
        {
        Rprintf("site (%d) at %f %f\n", s->sitenbr, s->coord.x, s->coord.y) ;
        }
    }

void
out_triple(Site * s1, Site * s2, Site * s3)
    {
    if (!debug)
        {
	    ptr_res_1[i_out] = s1->sitenbr;
	    ptr_res_2[i_out] = s2->sitenbr;
	    ptr_res_3[i_out] = s3->sitenbr;
	    i_out++;
        }
    if (debug)
        {
        Rprintf("circle through left=%d right=%d bottom=%d\n",
        s1->sitenbr, s2->sitenbr, s3->sitenbr) ;
        }
    }
