/* voronoi_regis.c    2024-12-19 */

/* Copyright 2024 Emmanuel Paradis */

/* This file is part of the R-package `voronoi'. */
/* See the file ../../LICENSE for licensing issues. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP voronoi_fortune(SEXP X, SEXP DEBUG);

static R_CallMethodDef Call_entries[] = {
    {"voronoi_fortune", (DL_FUNC) &voronoi_fortune, 2},
    {NULL, NULL, 0}
};

void R_init_voronoi(DllInfo *info)
{
    R_registerRoutines(info, NULL, Call_entries, NULL, NULL);
    R_useDynamicSymbols(info, FALSE);
}

