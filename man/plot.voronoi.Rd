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
  \item{X}{a two-column matrix with the original data (site
    coordinates).}
  \item{add}{a logical value. By default, a new plot is made. Setting
    \code{add = TRUE} is useful to add the tessellation and/or the
    triangulation on, e.g., a map.}
  \item{asp}{a numeric value. By default, both axes are scaled
    similarly (isometry). Use \code{asp = NULL} to have independent
    scaling on both axes (like a standard plot in \R).}
  \item{col.delaunay, col.voronoi}{the colours used for the segments.}
  \item{\dots}{other arguments passed to \code{\link{plot.default}}.}
}
\details{
  The \code{\dots} argument makes plotting very flexible.

  The default procedure is to first draw the DT, setting the limits of
  the axes according to the data, and then to draw the VT. Playing with
  the different options can change the order these two are drawn.

  The Fortune algorithm often adds some vertices which are far from the
  data points (sites); so if \code{delaunay = FALSE}, the scales are
  likely to extend much more than the default.

  The infinite edges of the VT are drawn as dashed lines.
}
\value{(NULL).}
\author{Emmanuel Paradis}
\seealso{\code{\link{voronoi}}}
\examples{
X <- matrix(runif(200), 100, 2)
res <- voronoi(X)
plot(res)
plot(res, delaunay = FALSE)

dat <- matrix(runif(40), 20, 2)
tess.dat <- voronoi(dat)
op <- par(mar = rep(0, 4))
## pass the data with the X argument:
plot(tess.dat, X = dat, pch = ".", axes = FALSE, ann = FALSE,
     xlim = c(-1, 2), ylim = c(-1, 2))
legend("topleft", , c("Delaunay triangulation", "Voronoi tessellation"),
       lty = 1, col = c("red", "blue"), bty = "n")
par(op)
}
\keyword{hplot}
