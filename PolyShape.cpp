#include "PolyShape.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Shape.hpp"
#include "Vect.hpp"
#include "BB.hpp"
#include "Body.hpp"

namespace cp {

cpPolyShape* PolyShape::get()
{
		return polyshape;
}
PolyShape::PolyShape(cp::Body *body,int numVerts,cp::Vect *verts,cp::Vect offset)
	: Shape(cpPolyShapeNew(body ? body->get() : 0,numVerts,verts,offset))
{
		shape->data = this;
}
PolyShape::PolyShape(cp::Body *body,cpFloat width,cpFloat height)
	: Shape(cpBoxShapeNew(body ? body->get() : 0,width,height))
{
		shape->data = this;
}
PolyShape::PolyShape(cp::Body *body,cp::BB box)
	: Shape(cpBoxShapeNew2(body ? body->get() : 0,box))
{
		shape->data = this;
}
int PolyShape::getNumVerts()
{
		return cpPolyShapeGetNumVerts(Shape::get());
}
cp::Vect PolyShape::getVert(int idx)
{
		return cpPolyShapeGetVert(Shape::get(),idx);
}
};//namespace cp
