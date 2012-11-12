/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 11/12/12 01:09:09.
 */
#pragma once

#include <utility>
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
	BB(const cp::Vect p,const cpFloat r);
/// Returns true if @c a and @c b intersect.
	cpBool intersects(const cp::BB b);
/// Returns true if @c other lies completely within @c bb.
	cpBool containsBB(const cp::BB other);
/// Returns true if @c bb contains @c v.
	cpBool containsVect(const cp::Vect v);
/// Returns a bounding box that holds both bounding boxes.
	cp::BB merge(const cp::BB b);
/// Returns a bounding box that holds both @c bb and @c v.
	cp::BB expand(const cp::Vect v);
/// Returns the area of the bounding box.
	cpFloat area();
/// Merges @c a and @c b and returns the area of the merged bounding box.
	cpFloat mergedArea(cp::BB b);
/// Returns the fraction along the segment query the cpBB is hit. Returns INFINITY if it doesn't hit.
	cpFloat segmentQuery(cp::Vect a,cp::Vect b);
/// Return true if the bounding box intersects the line segment with ends @c a and @c b.
	cpBool intersectsSegment(cp::Vect a,cp::Vect b);
// TODO edge case issue
/// Wrap a vector to a bounding box.
	cp::Vect wrapVect(const cp::Vect v);
	BB(BB&&o);
private:
//Hiding copy constructor and assignment
};
};//namespace cp
