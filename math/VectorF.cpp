#include "VectorF.hpp"

#include "MatrixF.hpp"

Vector2F Vector2F::Rotate (float const theta) const
{
   // Compute the rotation matrix
   float cos_theta = std::cos(theta);
   float sin_theta = std::sin(theta);
   Matrix2F rot{{cos_theta, -sin_theta,
                 sin_theta, cos_theta}};
   
   // Apply rotation matrix and return the resultant vector
   ColMatrix2F result = rot * ColMatrix2F(*this);
   return Vector2F(result[0], result[1]);
}