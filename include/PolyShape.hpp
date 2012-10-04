/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:40:05.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"

namespace cp {

class PolyShape : public Shape {
protected:
	cpPolyShape* polyshape;
public:
	cpPolyShape* get(){
		return polyshape;
}
/// Allocate and initialize a polygon shape.
/// A convex hull will be created from the vertexes.
	PolyShape(cp::Body *body,int numVerts,cpVect *verts,cpVect offset);
/// Allocate and initialize a box shaped polygon shape.
	PolyShape(cpBody *body,cpFloat width,cpFloat height);
/// Allocate and initialize an offset box shaped polygon shape.
	PolyShape(cpBody *body,cpBB box);
/// Get the number of verts in a polygon shape.
	int getNumVerts();
/// Get the @c ith vertex of a polygon shape.
	cpVect getVert(int idx);

};
};//namespace cp
