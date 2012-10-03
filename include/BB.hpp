/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:41:26.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"

namespace cp {

class BB : public cpBB {
protected:
public:
	BB(const cpBB v);
/// Convenience constructor for cpBB structs.
	BB(const cpFloat l,const cpFloat b,const cpFloat r,const cpFloat t);
/// Constructs a cpBB for a circle with the given position and radius.
	BB(const cpVect p,const cpFloat r);
/// Returns true if @c a and @c b intersect.
	cpBool intersects(const cpBB b);
/// Returns true if @c other lies completely within @c bb.
	cpBool containsBB(const cpBB other);
/// Returns true if @c bb contains @c v.
	cpBool containsVect(const cpVect v);
/// Returns a bounding box that holds both bounding boxes.
	cpBB merge(const cpBB b);
/// Returns a bounding box that holds both @c bb and @c v.
	cpBB expand(const cpVect v);
/// Returns the area of the bounding box.
	cpFloat area();
/// Merges @c a and @c b and returns the area of the merged bounding box.
	cpFloat mergedArea(cpBB b);
/// Returns the fraction along the segment query the cpBB is hit. Returns INFINITY if it doesn't hit.
	cpFloat segmentQuery(cpVect a,cpVect b);
/// Return true if the bounding box intersects the line segment with ends @c a and @c b.
	cpBool intersectsSegment(cpVect a,cpVect b);
// TODO edge case issue
/// Wrap a vector to a bounding box.
	cpVect wrapVect(const cpVect v);

};
};//namespace cp
