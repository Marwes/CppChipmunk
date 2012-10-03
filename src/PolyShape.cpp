/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:41:26.
 */
#include "PolyShape.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Body.hpp"

namespace cp {

void PolyShape::setVerts(int numVerts,cpVect *verts,cpVect offset)
{
		cpPolyShapeSetVerts(Shape::get(),numVerts,verts,offset);
}
PolyShape::PolyShape(cp::Body *body,int numVerts,cpVect *verts,cpVect offset)
	: Shape(cpPolyShapeNew(body ? body->get() : 0,numVerts,verts,offset))
{
		}
PolyShape::PolyShape(cpBody *body,cpFloat width,cpFloat height)
	: Shape(cpBoxShapeNew(body ? body->get() : 0,width,height))
{
		shape->data = this;
}
PolyShape::PolyShape(cpBody *body,cpBB box)
	: Shape(cpBoxShapeNew2(body ? body->get() : 0,box))
{
		shape->data = this;
}
int PolyShape::getNumVerts()
{
		return cpPolyShapeGetNumVerts(Shape::get());
}
cpVect PolyShape::getVert(int idx)
{
		return cpPolyShapeGetVert(Shape::get(),idx);
}
};//namespace cp
