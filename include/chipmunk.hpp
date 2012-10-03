/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:46:42.
 */
#pragma once
#include "chipmunk_declarations.hpp"
#include "Vect.hpp"
#include "BB.hpp"
#include "Arbiter.hpp"
#include "BBTree.hpp"
#include "Array.hpp"
#include "HashSet.hpp"
#include "Space.hpp"
#include "Contact.hpp"
#include "Body.hpp"
#include "SpatialIndex.hpp"
#include "SpaceHash.hpp"
#include "BB.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "SegmentShape.hpp"
#include "PolyShape.hpp"
#include "CircleShape.hpp"
#include "Sweep1D.hpp"
namespace cp {
/// Calculate the moment of inertia for a circle.
/// @c r1 and @c r2 are the inner and outer diameters. A solid circle has an inner diameter of 0.
	cpFloat momentForCircle(cpFloat m,cpFloat r1,cpFloat r2,cpVect offset){
		return cpMomentForCircle(m,r1,r2,offset);
}

/// Calculate area of a hollow circle.
/// @c r1 and @c r2 are the inner and outer diameters. A solid circle has an inner diameter of 0.
	cpFloat areaForCircle(cpFloat r1,cpFloat r2){
		return cpAreaForCircle(r1,r2);
}

/// Calculate the moment of inertia for a line segment.
/// Beveling radius is not supported.
	cpFloat momentForSegment(cpFloat m,cpVect a,cpVect b){
		return cpMomentForSegment(m,a,b);
}

/// Calculate the area of a fattened (capsule shaped) line segment.
	cpFloat areaForSegment(cpVect a,cpVect b,cpFloat r){
		return cpAreaForSegment(a,b,r);
}

/// Calculate the moment of inertia for a solid polygon shape assuming it's center of gravity is at it's centroid. The offset is added to each vertex.
	cpFloat momentForPoly(cpFloat m,int numVerts,const cpVect *verts,cpVect offset){
		return cpMomentForPoly(m,numVerts,verts,offset);
}

/// Calculate the signed area of a polygon. A Clockwise winding gives positive area.
/// This is probably backwards from what you expect, but matches Chipmunk's the winding for poly shapes.
	cpFloat areaForPoly(const int numVerts,const cpVect *verts){
		return cpAreaForPoly(numVerts,verts);
}

/// Calculate the natural centroid of a polygon.
	cpVect centroidForPoly(const int numVerts,const cpVect *verts){
		return cpCentroidForPoly(numVerts,verts);
}

/// Center the polygon on the origin. (Subtracts the centroid of the polygon from each vertex)
	void recenterPoly(const int numVerts,cpVect *verts){
		cpRecenterPoly(numVerts,verts);
}

/// Calculate the moment of inertia for a solid box.
	cpFloat momentForBox(cpFloat m,cpFloat width,cpFloat height){
		return cpMomentForBox(m,width,height);
}

/// Calculate the moment of inertia for a solid box.
	cpFloat momentForBox2(cpFloat m,cpBB box){
		return cpMomentForBox2(m,box);
}

/// Calculate the convex hull of a given set of points. Returns the count of points in the hull.
/// @c result must be a pointer to a @c cpVect array with at least @c count elements. If @c result is @c NULL, then @c verts will be reduced instead.
/// @c first is an optional pointer to an integer to store where the first vertex in the hull came from (i.e. verts[first] == result[0])
/// @c tol is the allowed amount to shrink the hull when simplifying it. A tolerance of 0.0 creates an exact hull.
	int convexHull(int count,cpVect *verts,cpVect *result,int *first,cpFloat tol){
		return cpConvexHull(count,verts,result,first,tol);
}

	int collideShapes(const cpShape *a,const cpShape *b,cpContact *arr){
		return cpCollideShapes(a,b,arr);
}

	void loopIndexes(cpVect *verts,int count,int *start,int *end){
		cpLoopIndexes(verts,count,start,end);
}

/// Return the max of two cpFloats.
	cpFloat fmax(cpFloat a,cpFloat b){
		return cpfmax(a,b);
}

/// Return the min of two cpFloats.
	cpFloat fmin(cpFloat a,cpFloat b){
		return cpfmin(a,b);
}

/// Return the absolute value of a cpFloat.
	cpFloat fabs(cpFloat f){
		return cpfabs(f);
}

/// Clamp @c f to be between @c min and @c max.
	cpFloat fclamp(cpFloat f,cpFloat min,cpFloat max){
		return cpfclamp(f,min,max);
}

/// Clamp @c f to be between 0 and 1.
	cpFloat fclamp01(cpFloat f){
		return cpfclamp01(f);
}

/// Linearly interpolate (or extrapolate) between @c f1 and @c f2 by @c t percent.
	cpFloat flerp(cpFloat f1,cpFloat f2,cpFloat t){
		return cpflerp(f1,f2,t);
}

/// Linearly interpolate from @c f1 to @c f2 by no more than @c d.
	cpFloat flerpconst(cpFloat f1,cpFloat f2,cpFloat d){
		return cpflerpconst(f1,f2,d);
}

/// Check that a set of vertexes is convex and has a clockwise winding.
/// NOTE: Due to floating point precision issues, hulls created with cpQuickHull() are not guaranteed to validate!
	cpBool polyValidate(const cpVect *verts,const int numVerts){
		return cpPolyValidate(verts,numVerts);
}

/// Get the hit point for a segment query.
	cpVect segmentQueryHitPoint(const cpVect start,const cpVect end,const cpSegmentQueryInfo info){
		return cpSegmentQueryHitPoint(start,end,info);
}

/// Get the hit distance for a segment query.
	cpFloat segmentQueryHitDist(const cpVect start,const cpVect end,const cpSegmentQueryInfo info){
		return cpSegmentQueryHitDist(start,end,info);
}

/// When initializing a shape, it's hash value comes from a counter.
/// Because the hash value may affect iteration order, you can reset the shape ID counter
/// when recreating a space. This will make the simulation be deterministic.
	void resetShapeIdCounter(void){
		cpResetShapeIdCounter();
}

}//namespace cp
