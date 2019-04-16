#ifndef CLIPPING_H
#define CLIPPING_H

#include "Geometry.hpp"

class ILineClipper
{
public:
   virtual ~ILineClipper () {}

   virtual ClippingTestResult ClipLine (LineSegment2F & line, Rectangle2F const& clipSurface) const = 0;
};

/// https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
class CohenSutherlandLineClipper
   : public virtual ILineClipper
{
public:
   virtual ~CohenSutherlandLineClipper () {}

   virtual ClippingTestResult ClipLine (LineSegment2F & line, Rectangle2F const& clipSurface) const;
};

#endif