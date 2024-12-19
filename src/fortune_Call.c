/* fortune_Call.c    2024-12-19 */

/* Copyright 2021 Plan 9 Foundation, 2024 Emmanuel Paradis */

/* This file is part of the R-package `voronoi'. */
/* See the file ../../COPYING for licensing issues. */

#include <R.h>
#include <Rinternals.h>
#include "vdefs.h"

/* Site * nextone(void) ; */
/* Site * readone(void), * nextone(void) ; */
/* void readsites(void) ; */

int /* tessellate, triangulate, plot,  */debug, nsites, siteidx ;
double xmin, xmax, ymin, ymax ;
Site * sites ;
Freelist sfl ;

int *ptr_res_1, *ptr_res_2, *ptr_res_3, i_out, ie, i_vtx, il;
double *coord_vertex_x, *coord_vertex_y, *line_a, *line_b, *line_c;
int *edge_vtx1, *edge_vtx2, *edge_nbr;

Site *
nextone(void)
    {
    Site * s ;

    if (siteidx < nsites)
        {
        s = &sites[siteidx++];
        return (s) ;
        }
    else
        {
        return ((Site *)NULL) ;
        }
    }

SEXP voronoi_fortune(SEXP X, SEXP DEBUG)
{
    Site *(*next)() ;
    SEXP res, mat0, mat1, mat2, mat3;
    int N, i, *ptr_int;
    double *xy, *ptr_dbl;

    PROTECT(X = coerceVector(X, REALSXP));
    PROTECT(DEBUG = coerceVector(DEBUG, INTSXP));
    debug = INTEGER(DEBUG)[0];

    nsites = nrows(X);
    N = 2 * nsites - 2;
    xy = REAL(X);

    /* tessellate = triangulate = debug = plot = 0 ; */

    /* switch(INTEGER(OPTION)[0]) */
    /* 	{ */
    /* 	case 1: */
    /* 	    debug = 1; */
    /* 	    break; */
    /* 	case 2: */
    /* 	    triangulate = 1; */
    /* 	    break; */
    /* 	case 3: */
    /* 	    tessellate = 1; */
    /* 	    break; */
    /* 	case 4: */
    /* 	    triangulate = 1; */
    /* 	    tessellate = 1; */
    /* 	    break; */
    /* 	} */

    sites = (Site *)R_alloc(nsites, sizeof(Site));
    for (i = 0; i < nsites; i++) {
	sites[i].coord.x = xy[i];
	sites[i].coord.y = xy[i + nsites];
	sites[i].sitenbr = i;
	sites[i].refcnt = 0;
    }

    freeinit(&sfl, sizeof(Site)) ;

    /* sort sites on y, then x, coord
       NEW: the data are sorted in R */

    xmin = sites[0].coord.x ;
    xmax = sites[0].coord.x ;
    for (i = 1 ; i < nsites ; ++i) {
        if (sites[i].coord.x < xmin) xmin = sites[i].coord.x ;
        if (sites[i].coord.x > xmax) xmax = sites[i].coord.x ;
    }
    ymin = sites[0].coord.y ;
    ymax = sites[nsites - 1].coord.y ;

    next = nextone ;
    ie = i_vtx = i_out = il = siteidx = 0 ;
    geominit() ;
    /* if (plot) */
    /*     { */
    /*     plotinit() ; */
    /*     } */

    /* if (triangulate) { */
    ptr_res_1 = (int*)R_alloc(N, sizeof(int));
    ptr_res_2 = (int*)R_alloc(N, sizeof(int));
    ptr_res_3 = (int*)R_alloc(N, sizeof(int));
    /* } */
    /* if (tessellate) { */

    N *= 3;
    coord_vertex_x = (double*)R_alloc(N, sizeof(double));
    coord_vertex_y = (double*)R_alloc(N, sizeof(double));
    edge_nbr = (int*)R_alloc(N, sizeof(int));
    edge_vtx1 = (int*)R_alloc(N, sizeof(int));
    edge_vtx2 = (int*)R_alloc(N, sizeof(int));;
    /* } */
    line_a = (double*)R_alloc(N, sizeof(double));
    line_b = (double*)R_alloc(N, sizeof(double));
    line_c = (double*)R_alloc(N, sizeof(double));

    voronoi(next) ;

    /* output */

    PROTECT(res = allocVector(VECSXP, 4/* triangulate + 2*tessellate */));

    /* if (triangulate) { */

    /* increment the indices of the triples */
    for (i = 0; i < i_out; i++) {
	++(ptr_res_1[i]);
	++(ptr_res_2[i]);
	++(ptr_res_3[i]);
    }
    PROTECT(mat0 = allocMatrix(INTSXP, i_out, 3));

    N = i_out * sizeof(int);
    ptr_int = INTEGER(mat0);
    memcpy(ptr_int, ptr_res_1, N);
    ptr_int += i_out;
    memcpy(ptr_int, ptr_res_2, N);
    ptr_int += i_out;
    memcpy(ptr_int, ptr_res_3, N);

    SET_VECTOR_ELT(res, 0, mat0);
    /* } */
    /* if (tessellate) { */

    /* increment the indices of the vertices and lines */
    for (i = 0; i < ie; i++) {
	++(edge_vtx1[i]);
	++(edge_vtx2[i]);
	++(edge_nbr[i]);
    }

    PROTECT(mat1 = allocMatrix(REALSXP, i_vtx, 2));
    N = i_vtx * sizeof(double);
    ptr_dbl = REAL(mat1);
    memcpy(ptr_dbl, coord_vertex_x, N);
    ptr_dbl += i_vtx;
    memcpy(ptr_dbl, coord_vertex_y, N);
    SET_VECTOR_ELT(res, 1/* triangulate */, mat1);

    PROTECT(mat2 = allocMatrix(INTSXP, ie, 3));
    N = ie * sizeof(int);
    ptr_int = INTEGER(mat2);
    memcpy(ptr_int, edge_vtx1, N);
    ptr_int += ie;
    memcpy(ptr_int, edge_vtx2, N);
    ptr_int += ie;
    memcpy(ptr_int, edge_nbr, N);
    SET_VECTOR_ELT(res, 2/* triangulate + 1 */, mat2);
    /* } */

    PROTECT(mat3 = allocMatrix(REALSXP, il, 3));
    N = il * sizeof(double);
    ptr_dbl = REAL(mat3);
    memcpy(ptr_dbl, line_a, N);
    ptr_dbl += il;
    memcpy(ptr_dbl, line_b, N);
    ptr_dbl += il;
    memcpy(ptr_dbl, line_c, N);
    SET_VECTOR_ELT(res, 3, mat3);

    UNPROTECT(7);
    return res;
}
