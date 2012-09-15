/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/15/12 09:00:46.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"

namespace cp {

class Shape {
protected:
	cpShape* shape;
	cpDataPointer data;
public:
	cpShape* get();
/// Destroy and Free a shape.
	~Shape();
/// Update, cache and return the bounding box of a shape based on the body it's attached to.
	cp::BB cacheBB();
/// Update, cache and return the bounding box of a shape with an explicit transformation.
	cp::BB update(cp::Vect pos,cp::Vect rot);
/// Test if a point lies within a shape.
	cpBool pointQuery(cp::Vect p);
/// Perform a nearest point query. It finds the closest point on the surface of shape to a specific point.
/// The value returned is the distance between the points. A negative distance means the point is inside the shape.
	cpFloat nearestPointQuery(cp::Vect p,cpNearestPointQueryInfo *out);
/// Perform a segment query against a shape. @c info must be a pointer to a valid cpSegmentQueryInfo structure.
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
