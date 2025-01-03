\name{plot.voronoi}
\alias{plot.voronoi}
\title{Plot Voronoi Tessellation and Delaunay Triangulation}
\description{
  Plot Voronoi tessellation (VT) and Delaunay triangulation (DT).
}
\usage{
\method{plot}{voronoi}(x, delaunay = TRUE, voronoi = TRUE,
     X = NULL, add = FALSE, asp = 1,
     col.delaunay = "red", col.voronoi = "blue", ...)
}
\arguments{
  \item{x}{an object of class \code{"voronoi"}.}
  \item{delaunay}{a logical value: draw the Delaunay triangulation?}
  \item{voronoi}{a logical value: draw the Voronoi tessellation?}
  \item{X}{a two-column matrix with the original data (sites).}
  \item{add}{a logical value. By default, a new plot is made. Setting
    \code{add = TRUE} is useful to add the tessellation and/or
    triangulation on, for instance, a map.}
  \item{asp}{a numeric value. By default, both axes are scaled
    similarly (isometry). Use \code{asp = NULL} to have independent
    scaling on both axes (like a standard plot).}
  \item{col.delaunay, col.voronoi}{the colours used for the segments.}
  \item{\dots}{other arguments passed to \code{\link{plot.default}}.}
}
\details{
  The \code{\dots} argument makes the plotting quite flexible.

  The plot procedure is to first draw the DT, setting the limits
  according to the data, and then to draw the VT. The Fortune algorithm
  often adds some vertices which are far from data points (sites); so if
  \code{delaunay = FALSE}, the scales are likely to extend much more
  than the default.

  The infinite edges are drawn as dashed lines.
}
\value{
  (NULL).
}
\author{Emmanuel Paradis}
\seealso{\code{\link{voronoi}}}
\examples{
example(voronoi)
plot(res)
plot(res, delaunay = FALSE)

## pass the data with the X argument:
dat <- matrix(runif(40), 20, 2)
tess.dat <- voronoi(dat)
op <- par(mar = rep(0, 4))
plot(tess.dat, X = dat, pch = ".", axes = FALSE, ann = FALSE,
     xlim = c(-1, 2), ylim = c(-1, 2))
legend("topleft", , c("Delaunay triangulation", "Voronoi tessellation"),
       lty = 1, col = c("red", "blue"), bty = "n")
par(op)
}
\keyword{hplot}
