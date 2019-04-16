#include "Clipping.hpp"

#include <SDL2/SDL.h> // Uint8

// Note: Unless explicitly stated, all clipping algorithms are performed
//       in World space. CANIMPROVE: Avoid this bug-prone dependency!

enum Outcodes2D
{
   INSIDE = 0, // 0000
   LEFT = 1,   // 0001
   RIGHT = 2,  // 0010
   BOTTOM = 4, // 0100
   TOP = 8     // 1000
};

Uint8 ComputeOutcode (Point2F point, Rectangle2F surface)
{
   Uint8 result = Outcodes2D::INSIDE;

   // Top/Bottom
   if (point.y > surface.y)
   {
      result |= Outcodes2D::TOP;
   }
   else if (point.y < surface.y - surface.height)
   {
      result |= Outcodes2D::BOTTOM;
   }

   // Left/Right
   if (point.x > surface.x + surface.width)
   {
      result |= Outcodes2D::RIGHT;
   }
   else if (point.x < surface.x)
   {
      result |= Outcodes2D::LEFT;
   }

   // Note that it can't be both top + bottom or both left + right

   return result;
}

ClippingTestResult CohenSutherlandLineClipper::ClipLine (LineSegment2F & line, Rectangle2F const& clipRect) const
{
   // Until we have a trivial accept or reject,
   // 1. Compute outcodes for start and end points
   // 2. If start | end is 0, trivial accept
   //    Else if start & end is not 0, trivial reject
   //    Else,
   //    a) Find the outcode of the "out" point (the one whose outcode is non-zero),
   //    b) Update this to the intersection of the line and the appropriate clip rectangle border edge...take advantage of outcode when computing

   auto result = ClippingTestResult::NON_TRIVIAL;

   while (result == ClippingTestResult::NON_TRIVIAL)
   {
      auto outcode_start = ComputeOutcode(line.start, clipRect);
      auto outcode_end   = ComputeOutcode(line.end  , clipRect);

      if ((outcode_start | outcode_end) == 0) // both points are within clip rectangle
      {
         result = ClippingTestResult::TRIVIAL_ACCEPT;
      }
      else if ((outcode_start & outcode_end) != 0) // both points are outside of clip rectangle
      {
         result = ClippingTestResult::TRIVIAL_REJECT;
      }
      else // at least one point is within the clip rectangle
      {
         // Given two points (x0, y0), (x1, y1):
         // Slope `m` = (y1 - y0) / (x1 - x0)
         // Equation for `x` = x0 + (y - y0)/m
         // Equation for `y` = y0 + (x - x0)*m

         float x0 = line.start.x, x1 = line.end.x;
         float y0 = line.start.y, y1 = line.end.y;
         float m = (y1 - y0) / (x1 - x0);

         float xmin = clipRect.x, xmax = clipRect.x + clipRect.width;
         float ymin = clipRect.y - clipRect.height, ymax = clipRect.y;

         auto IsStartOutside = [=](void){ return outcode_start != 0; };         
         auto outcode_out = IsStartOutside() ? outcode_start : outcode_end;
         Point2F & updated = IsStartOutside() ? line.start : line.end;

         // Update the point that we determined is outside the clip rect
         if (outcode_out & LEFT) // set x = xmin, solve for y
         {
            updated.x = xmin;
            updated.y = y0 + (updated.x - x0) * m;
         }
         else if (outcode_out & RIGHT) // set x = xmax, solve for y
         {
            updated.x = xmax;
            updated.y = y0 + (updated.x - x0) * m;
         }
         else if (outcode_out & TOP) // set y = ymax, solve for x
         {
            updated.y = ymax;
            updated.x = x0 + (updated.y - y0) / m;
         }
         else if (outcode_out & BOTTOM) // set y = ymin, solve for x
         {
            updated.y = ymin;
            updated.x = x0 + (updated.y - y0) / m;
         }
      }
   }

   return result;
}