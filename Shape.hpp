#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Space.hpp"
#include "Vect.hpp"
#include "BB.hpp"
#include "Body.hpp"

namespace cp {

class Shape {
protected:
	cpShape* shape;
	cpDataPointer data;
public:
	cpShape* get();
	~Shape();
	cp::BB cacheBB();
	cp::BB update(cp::Vect pos,cp::Vect rot);
	cpBool pointQuery(cp::Vect p);
	cpFloat nearestPointQuery(cp::Vect p,cpNearestPointQueryInfo *out);
	cpBool segmentQuery(cp::Vect a,cp::Vect b,cpSegmentQueryInfo *info);
	void setBody(cp::Body *body);
	cp::Space* getSpace(void);
	cp::Body* getBody(void);
	cp::BB getBB(void);
	cpBool getSensor(void);
	void setSensor(cpBool value);
	cpFloat getElasticity(void);
	void setElasticity(cpFloat value);
	cpFloat getFriction(void);
	void setFriction(cpFloat value);
	cp::Vect getSurfaceVelocity(void);
	void setSurfaceVelocity(cp::Vect value);
	cpDataPointer getUserData(void);
	void setUserData(cpDataPointer value);
	cpCollisionType getCollisionType(void);
	void setCollisionType(cpCollisionType value);
	cpGroup getGroup(void);
	void setGroup(cpGroup value);
	cpLayers getLayers(void);
	void setLayers(cpLayers value);
	Shape(cpShape* v);

};
};//namespace cp
