#pragma once

#include "chipmunk.h"
#include "Shape.hpp"

namespace cp {


class PolyShape : public Shape{
protected:
	cpPolyShape*polyshape;
public:

	cpPolyShape* get() const
	{
		return polyshape;
	}

	operator cpPolyShape*() const
	{
		return polyshape;
	}

	inline int getNumVerts()
	{
		return cpPolyShapeGetNumVerts(shape);
	}

	inline cpVect getVert(int idx)
	{
		return cpPolyShapeGetVert(shape,idx);
	}

	PolyShape(cpBody *body,int numVerts,cpVect *verts,cpVect offset)
	 : Shape(cpPolyShapeNew(body,numVerts,verts,offset))
	{
		shape->data = this;
	}

	PolyShape(cpBody *body,cpFloat width,cpFloat height)
	 : Shape(cpBoxShapeNew(body,width,height))
	{
		shape->data = this;
	}

	PolyShape(cpBody *body,cpBB box)
	 : Shape(cpBoxShapeNew2(body,box))
	{
		shape->data = this;
	}

};
}//namespace cp
