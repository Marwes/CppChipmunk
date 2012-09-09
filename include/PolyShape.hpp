/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:52:11.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "BB.hpp"
#include "Body.hpp"

namespace cp {

class PolyShape : public Shape {
protected:
	cpPolyShape* polyshape;
public:
	cpPolyShape* get();
	PolyShape(cp::Body *body,int numVerts,cpVect *verts,cpVect offset);
	PolyShape(cp::Body *body,cpFloat width,cpFloat height);
	PolyShape(cp::Body *body,cp::BB box);
	int getNumVerts();
	cp::Vect getVert(int idx);

};
};//namespace cp
