/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:41:26.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include <unordered_map>
#include <functional>

namespace cp {
	struct CollisionHandler {
		std::function<cpBool (cp::Arbiter *arb, cp::Space *space, void *data)> begin;
		std::function<cpBool (cp::Arbiter *arb, cp::Space *space, void *data)> preSolve;
		std::function<void (cp::Arbiter *arb, cp::Space *space, void *data)> postSolve;
		std::function<void (cp::Arbiter *arb, cp::Space *space, void *data)> separate;
		cpDataPointer data;
	};

	struct HashFunctor {
		size_t operator()(const std::pair<cpCollisionType, cpCollisionType> p) const
		{
			return (size_t)(p.first)*3344921057ul ^ (size_t)(p.second)*3344921057ul;
		}
	};
	typedef std::function<cpBool (cp::Arbiter *,cp::Space *,void *)> cpCollisionBeginFunc ;
	typedef std::function<cpBool (cp::Arbiter *,cp::Space *,void *)> cpCollisionPreSolveFunc ;
	typedef std::function<void (cp::Arbiter *,cp::Space *,void *)> cpCollisionPostSolveFunc ;
	typedef std::function<void (cp::Arbiter *,cp::Space *,void *)> cpCollisionSeparateFunc ;
/// Post Step callback function type.
	typedef std::function<void (cp::Space *,void *)> PostStepFunc ;
/// Point query callback function type.
	typedef std::function<void (cp::Shape *)> SpacePointQueryFunc ;
/// Nearest point query callback function type.
	typedef std::function<void (cp::Shape *,cpFloat ,cpVect )> SpaceNearestPointQueryFunc ;
/// Segment query callback function type.
	typedef std::function<void (cp::Shape *,cpFloat ,cpVect )> SpaceSegmentQueryFunc ;
/// Rectangle Query callback function type.
	typedef std::function<void (cp::Shape *)> SpaceBBQueryFunc ;
/// Shape query callback function type.
	typedef std::function<void (cp::Shape *,cpContactPointSet *)> SpaceShapeQueryFunc ;
/// Space/body iterator callback function type.
	typedef std::function<void (cp::Body *)> SpaceBodyIteratorFunc ;
/// Space/body iterator callback function type.
	typedef std::function<void (cp::Shape *)> SpaceShapeIteratorFunc ;
/// Space/constraint iterator callback function type.
	typedef std::function<void (cpConstraint *)> SpaceConstraintIteratorFunc ;

class Space {
protected:
	cpSpace* space;
	cpDataPointer data;
	cp::Body* body;
	std::unordered_map<std::pair<cpCollisionType, cpCollisionType>,CollisionHandler, HashFunctor>  collisionHandlers;;
public:
	cpSpace* get(){
		return space;
}
	void nearestPointQuery_b(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpSpaceNearestPointQueryBlock block);
	void segmentQuery_b(cpVect start,cpVect end,cpLayers layers,cpGroup group,cpSpaceSegmentQueryBlock block);
	void BBQuery_b(cpBB bb,cpLayers layers,cpGroup group,cpSpaceBBQueryBlock block);
	cpBool shapeQuery_b(cpShape *shape,cpSpaceShapeQueryBlock block);
	void processComponents(cpFloat dt);
	void pushFreshContactBuffer();
	void pushContacts(int count);
	cpPostStepCallback *getPostStepCallback(void *key);
	cpBool arbiterSetFilter(cpSpace *space);
	void filterArbiters(cpBody *body,cpShape *filter);
	void activateBody(cpBody *body);
	void lock();
	void unlock(cpBool runPostStep);
	void collideShapes(cpShape *b,cpSpace *space);
/// Allocate and initialize a cpSpace.
	Space(void);
/// Destroy and free a cpSpace.
	~Space();
/// Set a default collision handler for this space.
/// The default collision handler is invoked for each colliding pair of shapes
/// that isn't explicitly handled by a specific collision handler.
/// You can pass NULL for any function you don't want to implement.
	void setDefaultCollisionHandler(cpCollisionBeginFunc begin,cpCollisionPreSolveFunc preSolve,cpCollisionPostSolveFunc postSolve,cpCollisionSeparateFunc separate,void *data);
	void addCollisionHandler(cpCollisionType a,cpCollisionType b,const cpCollisionBeginFunc & begin = cpCollisionBeginFunc (),const cpCollisionPreSolveFunc & preSolve = cpCollisionPreSolveFunc (),const cpCollisionPostSolveFunc & postSolve = cpCollisionPostSolveFunc (),const cpCollisionSeparateFunc & separate = cpCollisionSeparateFunc (),void *data = 0);
/// Set a collision handler to be used whenever the two shapes with the given collision types collide.
/// You can pass NULL for any function you don't want to implement.
	void addCollisionHandler(cpCollisionType a,cpCollisionType b,cpCollisionBeginFunc begin,cpCollisionPreSolveFunc preSolve,cpCollisionPostSolveFunc postSolve,cpCollisionSeparateFunc separate,void *data);
/// Unset a collision handler.
	void removeCollisionHandler(cpCollisionType a,cpCollisionType b);
/// Add a collision shape to the simulation.
/// If the shape is attached to a static body, it will be added as a static shape.
	cpShape* addShape(cpShape *shape);
/// Explicity add a shape as a static shape to the simulation.
	cpShape* addStaticShape(cpShape *shape);
/// Add a rigid body to the simulation.
	cpBody* addBody(cpBody *body);
/// Add a constraint to the simulation.
	cpConstraint* addConstraint(cpConstraint *constraint);
/// Remove a collision shape from the simulation.
	void removeShape(cpShape *shape);
/// Remove a collision shape added using cpSpaceAddStaticShape() from the simulation.
	void removeStaticShape(cpShape *shape);
/// Remove a rigid body from the simulation.
	void removeBody(cpBody *body);
/// Remove a constraint from the simulation.
	void removeConstraint(cpConstraint *constraint);
/// Test if a collision shape has been added to the space.
	cpBool containsShape(cpShape *shape);
/// Test if a rigid body has been added to the space.
	cpBool containsBody(cpBody *body);
/// Test if a constraint has been added to the space.
	cpBool containsConstraint(cpConstraint *constraint);
	cpBool addPostStepCallback(cpPostStepFunc func,void *key,void *data);
/// Schedule a post-step callback to be called when cpSpaceStep() finishes.
/// You can only register one callback per unique value for @c key.
/// Returns true only if @c key has never been scheduled before.
/// It's possible to pass @c NULL for @c func if you only want to mark @c key as being used.
	cpBool addPostStepCallback(PostStepFunc func,void *key);
	void pointQuery(cpVect point,cpLayers layers,cpGroup group,cpSpacePointQueryFunc func,void *data);
/// Query the space at a point and call @c func for each shape found.
	void pointQuery(cpVect point,cpLayers layers,cpGroup group,SpacePointQueryFunc func);
/// Query the space at a point and return the first shape found. Returns NULL if no shapes were found.
	cpShape *pointQueryFirst(cpVect point,cpLayers layers,cpGroup group);
	void nearestPointQuery(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpSpaceNearestPointQueryFunc func,void *data);
/// Query the space at a point and call @c func for each shape found.
	void nearestPointQuery(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,SpaceNearestPointQueryFunc func);
/// Query the space at a point and return the nearest shape found. Returns NULL if no shapes were found.
	cpShape *nearestPointQueryNearest(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpNearestPointQueryInfo *out);
	void segmentQuery(cpVect start,cpVect end,cpLayers layers,cpGroup group,cpSpaceSegmentQueryFunc func,void *data);
/// Perform a directed line segment query (like a raycast) against the space calling @c func for each shape intersected.
	void segmentQuery(cpVect start,cpVect end,cpLayers layers,cpGroup group,SpaceSegmentQueryFunc func);
/// Perform a directed line segment query (like a raycast) against the space and return the first shape hit. Returns NULL if no shapes were hit.
	cpShape *segmentQueryFirst(cpVect start,cpVect end,cpLayers layers,cpGroup group,cpSegmentQueryInfo *out);
	void BBQuery(cpBB bb,cpLayers layers,cpGroup group,cpSpaceBBQueryFunc func,void *data);
/// Perform a fast rectangle query on the space calling @c func for each shape found.
/// Only the shape's bounding boxes are checked for overlap, not their full shape.
	void BBQuery(cpBB bb,cpLayers layers,cpGroup group,SpaceBBQueryFunc func);
	cpBool shapeQuery(cpShape *shape,cpSpaceShapeQueryFunc func,void *data);
/// Query a space for any shapes overlapping the given shape and call @c func for each shape found.
	cpBool shapeQuery(cpShape *shape,SpaceShapeQueryFunc func);
/// Call cpBodyActivate() for any shape that is overlaps the given shape.
	void activateShapesTouchingShape(cpShape *shape);
	void eachBody(cpSpaceBodyIteratorFunc func,void *data);
/// Call @c func for each body in the space.
	void eachBody(SpaceBodyIteratorFunc func);
	void eachShape(cpSpaceShapeIteratorFunc func,void *data);
/// Call @c func for each shape in the space.
	void eachShape(SpaceShapeIteratorFunc func);
	void eachConstraint(cpSpaceConstraintIteratorFunc func,void *data);
/// Call @c func for each shape in the space.
	void eachConstraint(SpaceConstraintIteratorFunc func);
/// Update the collision detection info for the static shapes in the space.
	void reindexStatic();
/// Update the collision detection data for a specific shape in the space.
	void reindexShape(cpShape *shape);
/// Update the collision detection data for all shapes attached to a body.
	void reindexShapesForBody(cpBody *body);
/// Switch the space to use a spatial has as it's spatial index.
	void useSpatialHash(cpFloat dim,int count);
/// Step the space forward in time by @c dt.
	void step(cpFloat dt);
	int getIterations(void);
	void setIterations(int value);
	cp::Vect getGravity(void);
	void setGravity(cp::Vect value);
	cpFloat getDamping(void);
	void setDamping(cpFloat value);
	cpFloat getIdleSpeedThreshold(void);
	void setIdleSpeedThreshold(cpFloat value);
	cpFloat getSleepTimeThreshold(void);
	void setSleepTimeThreshold(cpFloat value);
	cpFloat getCollisionSlop(void);
	void setCollisionSlop(cpFloat value);
	cpFloat getCollisionBias(void);
	void setCollisionBias(cpFloat value);
	cpTimestamp getCollisionPersistence(void);
	void setCollisionPersistence(cpTimestamp value);
	cpBool getEnableContactGraph(void);
	void setEnableContactGraph(cpBool value);
	cpDataPointer getUserData(void);
	void setUserData(cpDataPointer value);
	cp::Body* getStaticBody(void);
	cpFloat getCurrentTimeStep(void);
	Space(cpSpace* v);

};
};//namespace cp
