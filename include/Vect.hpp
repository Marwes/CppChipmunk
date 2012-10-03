/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/19/12 14:10:01.
 */
#pragma once

#include "chipmunk.h"

namespace cp {

class Vect : public cpVect {
protected:
public:
	Vect(cpVect cv);
/// Convenience constructor for cpVect structs.
	Vect(const cpFloat x = 0,const cpFloat y = 0);
/// Spherical linearly interpolate between v1 and v2.
	cp::Vect slerp(Vect& v2,const cpFloat t);
/// Spherical linearly interpolate between v1 towards v2 by no more than angle a radians
	cp::Vect slerpconst(Vect& v2,const cpFloat a);
///	Returns a string representation of v. Intended mostly for debugging purposes and not production use.
///	@attention The string points to a static local and is reset every time the function is called.
///	If you want to print more than one vector you will have to split up your printing onto separate lines.
	char* str();
/// Check if two vectors are equal. (Be careful when comparing floating point numbers!)
	cpBool eql(Vect& v2);
/// Add two vectors
	cp::Vect add(Vect& v2);
/// Subtract two vectors.
	cp::Vect sub(Vect& v2);
/// Negate a vector.
	cp::Vect neg();
/// Scalar multiplication.
	cp::Vect mult(const cpFloat s);
/// Vector dot product.
	cpFloat dot(Vect& v2);
/// 2D vector cross product analog.
/// The cross product of 2D vectors results in a 3D vector with only a z component.
/// This function returns the magnitude of the z value.
	cpFloat cross(Vect& v2);
/// Returns a perpendicular vector. (90 degree rotation)
	cp::Vect perp();
/// Returns a perpendicular vector. (-90 degree rotation)
	cp::Vect rperp();
/// Returns the vector projection of v1 onto v2.
	cp::Vect project(Vect& v2);
/// Returns the unit length vector for the given angle (in radians).
	cp::Vect forangle(const cpFloat a);
/// Returns the angular direction v is pointing in (in radians).
	cpFloat toangle();
/// Uses complex number multiplication to rotate v1 by v2. Scaling will occur if v1 is not a unit vector.
	cp::Vect rotate(Vect& v2);
/// Inverse of cpvrotate().
	cp::Vect unrotate(Vect& v2);
/// Returns the squared length of v. Faster than cpvlength() when you only need to compare lengths.
	cpFloat lengthsq();
/// Returns the length of v.
	cpFloat length();
/// Linearly interpolate between v1 and v2.
	cp::Vect lerp(Vect& v2,const cpFloat t);
/// Returns a normalized copy of v.
	cp::Vect normalize();
/// Returns a normalized copy of v or cpvzero if v was already cpvzero. Protects against divide by zero errors.
	cp::Vect normalize_safe();
/// Clamp v to length len.
	cp::Vect clamp(const cpFloat len);
/// Linearly interpolate between v1 towards v2 by distance d.
	cp::Vect lerpconst(Vect& v2,cpFloat d);
/// Returns the distance between v1 and v2.
	cpFloat dist(Vect& v2);
/// Returns the squared distance between v1 and v2. Faster than cpvdist() when you only need to compare distances.
	cpFloat distsq(Vect& v2);
/// Returns true if the distance between v1 and v2 is less than dist.
	cpBool near(Vect& v2,const cpFloat dist);

};
};//namespace cp
