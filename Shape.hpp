#pragma once

#include "chipmunk.h"
#include "Space.hpp"
#include "Vect.hpp"
#include "BB.hpp"
#include "Body.hpp"

namespace cp {


class Shape{
protected:
	cpShape*shape;
private:
	cpDataPointer data;
public:

	cpShape* get() const
	{
		return shape;
	}

	operator cpShape*() const
	{
		return shape;
	}

	~Shape()
	{
		cpShapeFree(shape);
	}

	inline cp::BB cacheBB()
	{
		return cpShapeCacheBB(shape);
	}

	inline cp::BB update(cpVect pos,cpVect rot)
	{
		return cpShapeUpdate(shape,pos,rot);
	}

	inline cpBool pointQuery(cpVect p)
	{
		return cpShapePointQuery(shape,p);
	}

	inline cpFloat nearestPointQuery(cpVect p,cpNearestPointQueryInfo *out)
	{
		return cpShapeNearestPointQuery(shape,p,out);
	}

	inline cpBool segmentQuery(cpVect a,cpVect b,cpSegmentQueryInfo *info)
	{
		return cpShapeSegmentQuery(shape,a,b,info);
	}

	inline void setBody(cpBody *body)
	{
		cpShapeSetBody(shape,body);
	}

	inline cp::Space* getSpace(void)
	{
		return static_cast<cp::Space*>(cpShapeGetSpace(shape) ? cpShapeGetSpace(shape)->data : 0);
	}

	inline cp::Body* getBody(void)
	{
		return static_cast<cp::Body*>(cpShapeGetBody(shape) ? cpShapeGetBody(shape)->data : 0);
	}

	inline cp::BB getBB(void)
	{
		return cpShapeGetBB(shape);
	}

	inline cpBool getSensor(void)
	{
		return cpShapeGetSensor(shape);
	}

	inline void setSensor(cpBool value)
	{
		cpShapeSetSensor(shape,value);
	}

	inline cpFloat getElasticity(void)
	{
		return cpShapeGetElasticity(shape);
	}

	inline void setElasticity(cpFloat value)
	{
		cpShapeSetElasticity(shape,value);
	}

	inline cpFloat getFriction(void)
	{
		return cpShapeGetFriction(shape);
	}

	inline void setFriction(cpFloat value)
	{
		cpShapeSetFriction(shape,value);
	}

	inline cp::Vect getSurfaceVelocity(void)
	{
		return cpShapeGetSurfaceVelocity(shape);
	}

	inline void setSurfaceVelocity(cp::Vect& value)
	{
		cpShapeSetSurfaceVelocity(shape,value);
	}

	inline cpDataPointer getUserData(void)
	{
		return data;
	}

	inline void setUserData(cpDataPointer value)
	{
		data = value;
	}

	inline cpCollisionType getCollisionType(void)
	{
		return cpShapeGetCollisionType(shape);
	}

	inline void setCollisionType(cpCollisionType value)
	{
		cpShapeSetCollisionType(shape,value);
	}

	inline cpGroup getGroup(void)
	{
		return cpShapeGetGroup(shape);
	}

	inline void setGroup(cpGroup value)
	{
		cpShapeSetGroup(shape,value);
	}

	inline cpLayers getLayers(void)
	{
		return cpShapeGetLayers(shape);
	}

	inline void setLayers(cpLayers value)
	{
		cpShapeSetLayers(shape,value);
	}

	Shape(cpShape* v)
	{
		shape = v;
		data = v->data;
		v->data = this;
	}

};
}//namespace cp
