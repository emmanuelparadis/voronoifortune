## voronoi.R (2025-01-03)

## Copyright 2024-2025 Emmanuel Paradis

## This file is part of the R-package `voronoifortune'.
## See the file ../DESCRIPTION for licensing issues.

voronoi <- function(X, sorted = FALSE, debug = FALSE)
{
    if (ncol(X) != 2) stop("need 2 columns")
    if (nrow(X) < 3) stop("not enough rows")

    if (!sorted) {
        o <- order(X[, 2], X[, 1]) # sort sites on y, then x
        X <- X[o, ]
    }
    res <- .Call(voronoi_fortune, X, debug)
    names(res) <- c("Triplets", "Vertices", "Edges", "Lines")

    if (!sorted) { #delaunay &&
        trip <- res$Triplets
        d <- dim(trip)
        dim(trip) <- NULL
        trip <- o[trip]
        dim(trip) <- d
        res$Triplets <- trip
    }

    class(res) <- "voronoi"
    res
}

print.voronoi <- function(x, ...)
{
    cat('Object of class "voronoi" (package voronoi)\n')
    cat("Delaunay triangulation:\n")
    cat(sprintf("  %d triangles\n", nrow(x$Triplets)))
    cat("Voronoi tessellation:\n")
    cat(sprintf("  %d vertices\n", nrow(x$Vertices)))
    cat(sprintf("  %d edges\n", nrow(x$Edges)))
}

plot.voronoi <-
    function(x, delaunay = TRUE, voronoi = TRUE, X = NULL, add = FALSE,
             asp = 1, col.delaunay = "red", col.voronoi = "blue", ...)
{
    if (delaunay) {
        if (is.null(X)) {
            if (exists("X", envir = .GlobalEnv)) {
                X <- get("X", envir = .GlobalEnv)
                warning("no 'X' data given: using 'X' from the user's workspace")
            } else {
                stop("cannot find a matrix 'X'")
            }
        }
        if (!add) plot.default(X, col = col.delaunay, asp = asp, ...)

        ii <- rbind(x$Triplets[, -3L], x$Triplets[, -2L], x$Triplets[, -1L])
        ii <- unique.matrix(apply(ii, 1L, sort), MARGIN = 2L)
        i0 <- ii[1L, ]
        i1 <- ii[2L, ]
        x0 <- X[i0, 1L]
        y0 <- X[i0, 2L]
        x1 <- X[i1, 1L]
        y1 <- X[i1, 2L]
        segments(x0, y0, x1, y1, col = col.delaunay)
    }
    if (voronoi) {
        if (!delaunay && !add)
            plot.default(x$Vertices, type = "n", col = col.voronoi,
                         asp = asp, ...)

        ## 1. draw the finite edges
        s <- x$Edges[, 1L] > 0 & x$Edges[, 2L] > 0
        vtx0 <- x$Edges[s, 1L]
        vtx1 <- x$Edges[s, 2L]
        x0 <- x$Vertices[vtx0, 1L]
        y0 <- x$Vertices[vtx0, 2L]
        x1 <- x$Vertices[vtx1, 1L]
        y1 <- x$Vertices[vtx1, 2L]
        segments(x0, y0, x1, y1, col = col.voronoi)

        ## get the barycenter:
        bc.x <- median(x$Vertices[, 1L])
        bc.y <- median(x$Vertices[, 2L])

        ## 2. draw the infinite edges
        for (i in 1:nrow(x$Edges)) {
            flag <- TRUE
            for (j in 1:2) {
                if (x$Edges[i, j] == 0) {
                    ## V: vertex with an infinite edge
                    V <- x$Edges[i, (2:1)[j]]
                    flag <- FALSE
                }
            }
            if (flag) next

            k <- x$Edges[i, 3L]
            ## the 3 coeff. describing the line (ax + by = c):
            a <- x$Lines[k, 1L]
            b <- x$Lines[k, 2L]
            c <- x$Lines[k, 3L]
            x0 <- x$Vertices[V, 1]
            y0 <- x$Vertices[V, 2]
            ## points(x0, y0, pch = 2)
            Dx <- x0 - bc.x
            Dy <- y0 - bc.y
            if (abs(Dx) > abs(Dy)) {
                if (b) {
                    x1 <- if (Dx < 0) x0 - 1 else x0 + 1
                    y1 <- (c - a*x1)/b
                } else {
                    x1 <- x0
                    y1 <- y0 + sign(Dy)
                }
            } else {
                if (a) {
                    y1 <- if (Dy < 0) y0 - 1 else y0 + 1
                    x1 <- (c - b*y1)/a
                } else {
                    x1 <- x0 + sign(Dx)
                    y1 <- y0 + sign(Dy)
                }
            }
            segments(x0, y0, x1, y1, col = col.voronoi, lty = 2)
        }
    }
}
