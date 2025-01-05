/* vdefs.h    2025-01-03 */

/* Copyright 2021 Plan 9 Foundation, 2024-2025 Emmanuel Paradis */

/* This file is part of the R-package `voronoifortune'. */
/* See the file ../../COPYING for licensing issues. */

#ifndef __VDEFS_H
#define __VDEFS_H

#ifndef NULL
#define NULL 0
#endif

#define DELETED -2

typedef struct Freenode
    {
    struct Freenode * nextfree;
    } Freenode ;


typedef struct Freelist
    {
    Freenode * head;
    int nodesize;
    } Freelist ;

typedef struct Point
    {
    double x ;
    double y ;
    } Point ;

/* structure used both for sites and for vertices */

typedef struct Site
    {
    Point coord ;
    int sitenbr ;
    int refcnt ;
    } Site ;


typedef struct Edge
    {
    double a, b, c ;
    Site * ep[2] ;
    Site * reg[2] ;
    int edgenbr ;
    } Edge ;

#define le 0
#define re 1

typedef struct Halfedge
    {
    struct Halfedge * ELleft ;
    struct Halfedge * ELright ;
    Edge * ELedge ;
    int ELrefcnt ;
    char ELpm ;
    Site * vertex ;
    double ystar ;
    struct Halfedge * PQnext ;
    } Halfedge ;

/* edgelist.c */
void ELinitialize(void) ;
Halfedge * HEcreate(Edge *, int) ;
void ELinsert(Halfedge *, Halfedge *) ;
Halfedge * ELgethash(int) ;
Halfedge * ELleftbnd(Point *) ;
void ELdelete(Halfedge *) ;
Halfedge * ELright(Halfedge *) ;
Halfedge * ELleft(Halfedge *) ;
Site * leftreg(Halfedge *) ;
Site * rightreg(Halfedge *) ;
extern int ELhashsize ;
extern Site * bottomsite ;
extern Freelist hfl ;
extern Halfedge * ELleftend, * ELrightend, **ELhash ;

/* geometry.c */
void geominit(void) ;
Edge * bisect(Site *, Site *) ;
Site * intersect(Halfedge *, Halfedge *) ;
int right_of(Halfedge *, Point *) ;
void endpoint(Edge *, int, Site *) ;
double dist(Site *, Site *) ;
void makevertex(Site *) ;
void deref(Site *) ;
void ref(Site *) ;
extern double deltax, deltay ;
extern int nsites, nedges, sqrt_nsites, nvertices ;
extern Freelist sfl, efl ;

/* heap.c */
void PQinsert(Halfedge *, Site *, double) ;
void PQdelete(Halfedge *) ;
int PQbucket(Halfedge *) ;
int PQempty(void) ;
Point PQ_min(void) ;
Halfedge * PQextractmin(void) ;
void PQinitialize(void) ;
extern int PQmin, PQcount, PQhashsize ;
extern Halfedge * PQhash ;

/* main.c */
extern int /* tessellate, triangulate, plot,  */debug, nsites, siteidx ;
extern double xmin, xmax, ymin, ymax ;
extern Site * sites ;
extern Freelist sfl ;
extern int *ptr_res_1, *ptr_res_2, *ptr_res_3, i_out, ie, i_vtx, il;
extern double *coord_vertex_x, *coord_vertex_y, *line_a, *line_b, *line_c;
extern int *edge_vtx1, *edge_vtx2, *edge_nbr;

/* getopt.c */
extern int getopt(int, char *const *, const char *);

/* memory.c */
void freeinit(Freelist *, int) ;
char *getfree(Freelist *) ;
void makefree(Freenode *, Freelist *) ;
/* char *myalloc(unsigned) ; */

/* output.c */
/* void openpl(void) ; */
/* void line(float, float, float, float) ; */
/* void circle(float, float, float) ; */
/* void range(float, float, float, float) ; */
void out_bisector(Edge *) ;
void out_ep(Edge *) ;
void out_vertex(Site *) ;
void out_site(Site *) ;
void out_triple(Site *, Site *, Site *) ;
/* void plotinit(void) ; */
/* void clip_line(Edge *) ; */

/* voronoi.c */
/* void voronoi(Site *(*)()) ; */
void voronoi(Site *(*nextsite)(void));

#endif


