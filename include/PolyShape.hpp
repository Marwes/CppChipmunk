/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
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
