\name{voronoi}
\alias{voronoi}
\alias{print.voronoi}
\title{Voronoi Tessellation and Delaunay Triangulation}
\description{
  Voronoi tessellation and Delaunay triangulation and performed
  simultaneously with the Fortune algorithm.
}
\usage{
voronoi(X, sorted = FALSE, debug = FALSE)
\method{print}{voronoi}(x, \dots)
}
\arguments{
  \item{X}{a two-column matrix.}
  \item{sorted}{a logical.}
  \item{debug}{a logical.}
  \item{x}{an object of class \code{"voronoi"}.}
  \item{\dots}{(unused).}
}
\value{
  an object of class \code{"voronoi"}.
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
