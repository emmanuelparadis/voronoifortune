\name{voronoifortune-package}
\alias{voronoifortune-package}
\docType{package}
\title{Fortune Algorithm for Voronoi Diagrams}
\description{
  \pkg{voronoifortune} is a port to \R of Fortune's algorithm, a very
  fast method to compute simultaneously the Delaunay triangulaton and
  the Voronoi tessellation for a set of sites (points). The algorithm
  scales linearly with the number of points whereas most other
  algorithms scale polynomially.

  A Voronoi tessellation defines for each site a cell (or region) so
  that all points included in the cell are not nearer to any other sites
  (distances are meant to be Euclidean distances).

  A Delaunay triangulaton defines a set of triangles with vertices at
  the sites so that the circle circumscribed to a given triangle does
  not include any other site; see an annotated example in
  \code{\link{voronoi}} including a test of this property.

  See the GitHub repository of the present package (link in the
  DESCRIPTION file) for some notes on porting this code to \R.
}
\author{
  Emmanuel Paradis, Steven Fortune

  Maintainer: Emmanuel Paradis <Emmanuel.Paradis@ird.fr>
}
\references{
  \url{https://en.wikipedia.org/wiki/Delaunay_triangulation}

  \url{https://en.wikipedia.org/wiki/Voronoi_diagram}
}
\keyword{package}
