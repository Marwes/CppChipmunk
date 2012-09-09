#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Space.hpp"
#include "BB.hpp"
#include "Shape.hpp"
#include <functional>
#include "Vect.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {
	typedef std::function<void (cp::Space *,void *)> PostStepFunc ;
	typedef std::function<void (cp::Shape *)> SpacePointQueryFunc ;
	typedef std::function<void (cp::Shape *,cpFloat ,cp::Vect )> SpaceNearestPointQueryFunc ;
	typedef std::function<void (cp::Shape *,cpFloat ,cp::Vect )> SpaceSegmentQueryFunc ;
	typedef std::function<void (cp::Shape *)> SpaceBBQueryFunc ;
	typedef std::function<void (cp::Shape *,cpContactPointSet *)> SpaceShapeQueryFunc ;
	typedef std::function<void (cp::Body *)> SpaceBodyIteratorFunc ;
	typedef std::function<void (cp::Shape *)> SpaceShapeIteratorFunc ;
	typedef std::function<void (cp::Constraint *)> SpaceConstraintIteratorFunc ;

class Space {
protected:
	cpSpace* space;
	cpDataPointer data;
	cp::Body* body;
public:
	cpSpace* get();
	Space(void);
	~Space();
	void setDefaultCollisionHandler(cpCollisionBeginFunc begin,cpCollisionPreSolveFunc preSolve,cpCollisionPostSolveFunc postSolve,cpCollisionSeparateFunc separate,void *data);
	void addCollisionHandler(cpCollisionType a,cpCollisionType b,cpCollisionBeginFunc begin,cpCollisionPreSolveFunc preSolve,cpCollisionPostSolveFunc postSolve,cpCollisionSeparateFunc separate,void *data);
	void removeCollisionHandler(cpCollisionType a,cpCollisionType b);
	cp::Shape* addShape(cp::Shape *shape);
	cp::Shape* addStaticShape(cp::Shape *shape);
	cp::Body* addBody(cp::Body *body);
	cp::Constraint* addConstraint(cp::Constraint *constraint);
	void removeShape(cp::Shape *shape);
	void removeStaticShape(cp::Shape *shape);
	void removeBody(cp::Body *body);
	void removeConstraint(cp::Constraint *constraint);
	cpBool containsShape(cp::Shape *shape);
	cpBool containsBody(cp::Body *body);
	cpBool containsConstraint(cp::Constraint *constraint);
	cpBool addPostStepCallback(cpPostStepFunc func,void *key,void *data);
	cpBool addPostStepCallback(PostStepFunc func,void *key);
	void pointQuery(cp::Vect point,cpLayers layers,cpGroup group,cpSpacePointQueryFunc func,void *data);
	void pointQuery(cpVect point,cpLayers layers,cpGroup group,SpacePointQueryFunc func);
	cp::Shape *pointQueryFirst(cp::Vect point,cpLayers layers,cpGroup group);
	void nearestPointQuery(cp::Vect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpSpaceNearestPointQueryFunc func,void *data);
	void nearestPointQuery(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,SpaceNearestPointQueryFunc func);
	cp::Shape *nearestPointQueryNearest(cp::Vect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpNearestPointQueryInfo *out);
	void segmentQuery(cp::Vect start,cp::Vect end,cpLayers layers,cpGroup group,cpSpaceSegmentQueryFunc func,void *data);
	void segmentQuery(cpVect start,cpVect end,cpLayers layers,cpGroup group,SpaceSegmentQueryFunc func);
	cp::Shape *segmentQueryFirst(cp::Vect start,cp::Vect end,cpLayers layers,cpGroup group,cpSegmentQueryInfo *out);
	void BBQuery(cp::BB bb,cpLayers layers,cpGroup group,cpSpaceBBQueryFunc func,void *data);
	void BBQuery(cpBB bb,cpLayers layers,cpGroup group,SpaceBBQueryFunc func);
	cpBool shapeQuery(cp::Shape *shape,cpSpaceShapeQueryFunc func,void *data);
	cpBool shapeQuery(cpShape *shape,SpaceShapeQueryFunc func);
	void activateShapesTouchingShape(cp::Shape *shape);
	void eachBody(cpSpaceBodyIteratorFunc func,void *data);
	void eachBody(SpaceBodyIteratorFunc func);
	void eachShape(cpSpaceShapeIteratorFunc func,void *data);
	void eachShape(SpaceShapeIteratorFunc func);
	void eachConstraint(cpSpaceConstraintIteratorFunc func,void *data);
	void eachConstraint(SpaceConstraintIteratorFunc func);
	void reindexStatic();
	void reindexShape(cp::Shape *shape);
	void reindexShapesForBody(cp::Body *body);
	void useSpatialHash(cpFloat dim,int count);
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
