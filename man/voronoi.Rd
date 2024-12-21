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
  \item{X}{a two-column matrix.}
  \item{sorted}{a logical: are the coordinates already sorted in
    increasing order first by y, then by x? (See
    \code{\link[base]{order}}.) If \code{TRUE}, this saves some running
    time.}
  \item{debug}{a logical: if \code{TRUE}, some details of the
    computation are printed.}
  \item{x}{an object of class \code{"voronoi"}.}
  \item{\dots}{(unused).}
}
\value{
  an object of class \code{"voronoi"} with four elements:

  \item{Triplets}{a three-column matrix of integers giving the triangles
  of the Delaunay triangulation (indices from the original data.}
  \item{Vertices}{a two-column matrix of reals giving the coordinates of
  the vertices of the Voronoi tessellation.}
  \item{Edges}{a two-column matrix of integers giving the edges of the
  tessellation (indices of the vertices from the previous matrix).}
  \item{Lines}{a description of the previous edges (some of them are
    semi-infinite indicated by a 0 in the matrix \code{Edges}).}
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
}
\keyword{models}
