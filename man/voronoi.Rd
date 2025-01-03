\name{voronoi}
\alias{voronoi}
\alias{print.voronoi}
\title{Voronoi Tessellation and Delaunay Triangulation}
\description{
  Voronoi tessellation and Delaunay triangulation are performed
  simultaneously with the Fortune (1987) algorithm.
}
\usage{
voronoi(X, sorted = FALSE, debug = FALSE)
\method{print}{voronoi}(x, ...)
}
\arguments{
  \item{X}{a two-column matrix with the coordinates.}
  \item{sorted}{a logical: are the coordinates already sorted in
    increasing order first by y, then by x? (See
    \code{\link[base]{order}}.) If \code{TRUE}, this shortens running
    time.}
  \item{debug}{a logical: if \code{TRUE}, some details of the
    computation are printed for debugging.}
  \item{x}{an object of class \code{"voronoi"}.}
  \item{\dots}{(unused).}
}
\value{
  \code{voronoi()} returns an object of class \code{"voronoi"} with four
  elements:

  \item{Triplets}{a three-column matrix of integers giving the triangles
    of the Delaunay triangulation (indices from the original data);}
  \item{Vertices}{a two-column matrix of reals giving the coordinates of
    the vertices of the Voronoi tessellation;}
  \item{Edges}{a two-column matrix of integers giving the edges of the
    tessellation (indices of the vertices in the previous matrix);}
  \item{Lines}{a description of the previous edges (some of them are
    semi-infinite indicated by a 0 in the matrix \code{Edges}; this
    element is used to draw the dashed lines by
    \code{\link{plot.voronoi}}).}
}
\references{
  Fortune, S. (1987) A sweepline algorithm for Voronoi
  diagrams. \emph{Algorithmica}, \bold{2}, 153--174.
  \doi{10.1007/BF01840357}.
}
\author{Emmanuel Paradis, Steven Fortune}
\seealso{\code{\link{plot.voronoi}}}
\examples{
n <- 100L
xx <- runif(n)
yy <- runif(n)
X <- cbind(xx, yy)
(res <- voronoi(X))
str(res)

### show the circumcle of each Delaunay triangle ###

n <- 10L
X <- cbind(runif(n), runif(n))
res <- voronoi(X)

## if 12 windows not enough par(ask) is set to TRUE
op <- par(mfrow = c(3, 4), ask = interactive())
## to show the circle as disk:
col <- rgb(.5, .5, 1, .3)

## for each triangle:
for (i in 1:nrow(res$Triplets)) {
    plot(res, X = X, voronoi = FALSE, main = i)
    ## get the 3 vertices of the triangle:
    P <- res$Triplets[i, ]
    ## center the coordinates on the 1st vertex:
    ## (B and C are the new coordinates of the 2nd
    ## and 3rd vertices)
    A <- X[P[1], ]
    B <- X[P[2], ] - A
    C <- X[P[3], ] - A
    ## the coordinates of the center of the circumcircle are:
    ## (https://en.wikipedia.org/wiki/Circumcircle)
    cr <- c(C[2] * sum(B^2) - B[2] * sum(C^2),
            B[1] * sum(C^2) - C[1] * sum(B^2))
    cr <- cr / (2 * (B[1] * C[2] - B[2] * C[1]))
    ## since the circle intersects with the new origin,
    ## the radius is simply:
    r <- sqrt(sum(cr^2))
    ## translate back to the original coordinate system:
    cr <- cr + A
    ## draw the circumcircle:
    symbols(cr[1], cr[2], circles = r, inches = FALSE, add = TRUE,
            fg = col, bg = col)
    ## test numerically that no points are inside the circumcircle:
    ## 1/ build a matrix with the coordinates of the center
    ## and all the vertices:
    M <- rbind(cr, X)
    ## 2/ compute the Euclidean distances, we keep only the n first
    ## values which are the distances from the center to the n vertices:
    Dis <- dist(M)[1:n]
    ## 3/ all other points than the 3 in P should be farther
    ## to the center:
    stopifnot(all(Dis[-P] > r))
}

par(op)
}
\keyword{models}
