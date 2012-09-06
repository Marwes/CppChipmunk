#pragma once

#include "chipmunk.h"
#include "Shape.hpp"
#include <functional>
#include "Vect.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

class Space;
namespace {
	void SpaceAddPostStepCallback(cpSpace *space,void *obj,void *data);
	void SpacePointQuery(cpShape *shape,void *data);
	void SpaceNearestPointQuery(cpShape *shape,cpFloat distance,cpVect point,void *data);
	void SpaceSegmentQuery(cpShape *shape,cpFloat t,cpVect n,void *data);
	void SpaceBBQuery(cpShape *shape,void *data);
	void SpaceShapeQuery(cpShape *shape,cpContactPointSet *points,void *data);
	void SpaceEachBody(cpBody *body,void *data);
	void SpaceEachShape(cpShape *shape,void *data);
	void SpaceEachConstraint(cpConstraint *constraint,void *data);
}

namespace cp {

typedef std::function<void (cp::Space *,void *)> PostStepFunc ;
typedef std::function<void (cp::Shape *)> SpacePointQueryFunc ;
typedef std::function<void (cp::Shape *,cpFloat ,cpVect )> SpaceNearestPointQueryFunc ;
typedef std::function<void (cp::Shape *,cpFloat ,cpVect )> SpaceSegmentQueryFunc ;
typedef std::function<void (cp::Shape *)> SpaceBBQueryFunc ;
typedef std::function<void (cp::Shape *,cpContactPointSet *)> SpaceShapeQueryFunc ;
typedef std::function<void (cp::Body *)> SpaceBodyIteratorFunc ;
typedef std::function<void (cp::Shape *)> SpaceShapeIteratorFunc ;
typedef std::function<void (cp::Constraint *)> SpaceConstraintIteratorFunc ;

class Space{
protected:
	cpSpace*space;
private:
	cpDataPointer data;
	cp::Body* body;
public:

	cpSpace* get() const
	{
		return space;
	}

	operator cpSpace*() const
	{
		return space;
	}

	~Space()
	{
		cpSpaceFree(space);
		body->body = 0;
		delete body;
	}

	inline void setDefaultCollisionHandler(cpCollisionBeginFunc begin,cpCollisionPreSolveFunc preSolve,cpCollisionPostSolveFunc postSolve,cpCollisionSeparateFunc separate,void *data)
	{
		cpSpaceSetDefaultCollisionHandler(space,begin,preSolve,postSolve,separate,data);
	}

	inline void addCollisionHandler(cpCollisionType a,cpCollisionType b,cpCollisionBeginFunc begin,cpCollisionPreSolveFunc preSolve,cpCollisionPostSolveFunc postSolve,cpCollisionSeparateFunc separate,void *data)
	{
		cpSpaceAddCollisionHandler(space,a,b,begin,preSolve,postSolve,separate,data);
	}

	inline void removeCollisionHandler(cpCollisionType a,cpCollisionType b)
	{
		cpSpaceRemoveCollisionHandler(space,a,b);
	}

	inline cp::Shape* addShape(cpShape *shape)
	{
		cpShape*  temp = cpSpaceAddShape(space,shape);
		return static_cast<cp::Shape* >(temp ? temp->data : 0);
	}

	inline cp::Shape* addStaticShape(cpShape *shape)
	{
		cpShape*  temp = cpSpaceAddStaticShape(space,shape);
		return static_cast<cp::Shape* >(temp ? temp->data : 0);
	}

	inline cp::Body* addBody(cpBody *body)
	{
		cpBody*  temp = cpSpaceAddBody(space,body);
		return static_cast<cp::Body* >(temp ? temp->data : 0);
	}

	inline cp::Constraint* addConstraint(cpConstraint *constraint)
	{
		cpConstraint*  temp = cpSpaceAddConstraint(space,constraint);
		return static_cast<cp::Constraint* >(temp ? temp->data : 0);
	}

	inline void removeShape(cpShape *shape)
	{
		cpSpaceRemoveShape(space,shape);
	}

	inline void removeStaticShape(cpShape *shape)
	{
		cpSpaceRemoveStaticShape(space,shape);
	}

	inline void removeBody(cpBody *body)
	{
		cpSpaceRemoveBody(space,body);
	}

	inline void removeConstraint(cpConstraint *constraint)
	{
		cpSpaceRemoveConstraint(space,constraint);
	}

	inline cpBool containsShape(cpShape *shape)
	{
		return cpSpaceContainsShape(space,shape);
	}

	inline cpBool containsBody(cpBody *body)
	{
		return cpSpaceContainsBody(space,body);
	}

	inline cpBool containsConstraint(cpConstraint *constraint)
	{
		return cpSpaceContainsConstraint(space,constraint);
	}

	inline cpBool addPostStepCallback(PostStepFunc func,void *key)
	{
		return cpSpaceAddPostStepCallback(space,*SpaceAddPostStepCallback,key,&func);
	};

	inline cpBool addPostStepCallback(cpPostStepFunc func,void *key,void *data)
	{
		return cpSpaceAddPostStepCallback(space,func,key,data);
	}

	inline void pointQuery(cpVect point,cpLayers layers,cpGroup group,SpacePointQueryFunc func)
	{
		cpSpacePointQuery(space,point,layers,group,*SpacePointQuery,&func);
	};

	inline void pointQuery(cpVect point,cpLayers layers,cpGroup group,cpSpacePointQueryFunc func,void *data)
	{
		cpSpacePointQuery(space,point,layers,group,func,data);
	}

	inline cp::Shape *pointQueryFirst(cpVect point,cpLayers layers,cpGroup group)
	{
		cpShape * temp = cpSpacePointQueryFirst(space,point,layers,group);
		return static_cast<cp::Shape *>(temp ? temp->data : 0);
	}

	inline void nearestPointQuery(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,SpaceNearestPointQueryFunc func)
	{
		cpSpaceNearestPointQuery(space,point,maxDistance,layers,group,*SpaceNearestPointQuery,&func);
	};

	inline void nearestPointQuery(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpSpaceNearestPointQueryFunc func,void *data)
	{
		cpSpaceNearestPointQuery(space,point,maxDistance,layers,group,func,data);
	}

	inline cp::Shape *nearestPointQueryNearest(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpNearestPointQueryInfo *out)
	{
		cpShape * temp = cpSpaceNearestPointQueryNearest(space,point,maxDistance,layers,group,out);
		return static_cast<cp::Shape *>(temp ? temp->data : 0);
	}

	inline void segmentQuery(cpVect start,cpVect end,cpLayers layers,cpGroup group,SpaceSegmentQueryFunc func)
	{
		cpSpaceSegmentQuery(space,start,end,layers,group,*SpaceSegmentQuery,&func);
	};

	inline void segmentQuery(cpVect start,cpVect end,cpLayers layers,cpGroup group,cpSpaceSegmentQueryFunc func,void *data)
	{
		cpSpaceSegmentQuery(space,start,end,layers,group,func,data);
	}

	inline cp::Shape *segmentQueryFirst(cpVect start,cpVect end,cpLayers layers,cpGroup group,cpSegmentQueryInfo *out)
	{
		cpShape * temp = cpSpaceSegmentQueryFirst(space,start,end,layers,group,out);
		return static_cast<cp::Shape *>(temp ? temp->data : 0);
	}

	inline void BBQuery(cpBB bb,cpLayers layers,cpGroup group,SpaceBBQueryFunc func)
	{
		cpSpaceBBQuery(space,bb,layers,group,*SpaceBBQuery,&func);
	};

	inline void BBQuery(cpBB bb,cpLayers layers,cpGroup group,cpSpaceBBQueryFunc func,void *data)
	{
		cpSpaceBBQuery(space,bb,layers,group,func,data);
	}

	inline cpBool shapeQuery(cpShape *shape,SpaceShapeQueryFunc func)
	{
		return cpSpaceShapeQuery(space,shape,*SpaceShapeQuery,&func);
	};

	inline cpBool shapeQuery(cpShape *shape,cpSpaceShapeQueryFunc func,void *data)
	{
		return cpSpaceShapeQuery(space,shape,func,data);
	}

	inline void activateShapesTouchingShape(cpShape *shape)
	{
		cpSpaceActivateShapesTouchingShape(space,shape);
	}

	inline void eachBody(SpaceBodyIteratorFunc func)
	{
		cpSpaceEachBody(space,*SpaceEachBody,&func);
	};

	inline void eachBody(cpSpaceBodyIteratorFunc func,void *data)
	{
		cpSpaceEachBody(space,func,data);
	}

	inline void eachShape(SpaceShapeIteratorFunc func)
	{
		cpSpaceEachShape(space,*SpaceEachShape,&func);
	};

	inline void eachShape(cpSpaceShapeIteratorFunc func,void *data)
	{
		cpSpaceEachShape(space,func,data);
	}

	inline void eachConstraint(SpaceConstraintIteratorFunc func)
	{
		cpSpaceEachConstraint(space,*SpaceEachConstraint,&func);
	};

	inline void eachConstraint(cpSpaceConstraintIteratorFunc func,void *data)
	{
		cpSpaceEachConstraint(space,func,data);
	}

	inline void reindexStatic()
	{
		cpSpaceReindexStatic(space);
	}

	inline void reindexShape(cpShape *shape)
	{
		cpSpaceReindexShape(space,shape);
	}

	inline void reindexShapesForBody(cpBody *body)
	{
		cpSpaceReindexShapesForBody(space,body);
	}

	inline void useSpatialHash(cpFloat dim,int count)
	{
		cpSpaceUseSpatialHash(space,dim,count);
	}

	inline void step(cpFloat dt)
	{
		cpSpaceStep(space,dt);
	}

	inline int getIterations(void)
	{
		return cpSpaceGetIterations(space);
	}

	inline void setIterations(int value)
	{
		cpSpaceSetIterations(space,value);
	}

	inline cp::Vect getGravity(void)
	{
		return cpSpaceGetGravity(space);
	}

	inline void setGravity(cp::Vect& value)
	{
		cpSpaceSetGravity(space,value);
	}

	inline cpFloat getDamping(void)
	{
		return cpSpaceGetDamping(space);
	}

	inline void setDamping(cpFloat value)
	{
		cpSpaceSetDamping(space,value);
	}

	inline cpFloat getIdleSpeedThreshold(void)
	{
		return cpSpaceGetIdleSpeedThreshold(space);
	}

	inline void setIdleSpeedThreshold(cpFloat value)
	{
		cpSpaceSetIdleSpeedThreshold(space,value);
	}

	inline cpFloat getSleepTimeThreshold(void)
	{
		return cpSpaceGetSleepTimeThreshold(space);
	}

	inline void setSleepTimeThreshold(cpFloat value)
	{
		cpSpaceSetSleepTimeThreshold(space,value);
	}

	inline cpFloat getCollisionSlop(void)
	{
		return cpSpaceGetCollisionSlop(space);
	}

	inline void setCollisionSlop(cpFloat value)
	{
		cpSpaceSetCollisionSlop(space,value);
	}

	inline cpFloat getCollisionBias(void)
	{
		return cpSpaceGetCollisionBias(space);
	}

	inline void setCollisionBias(cpFloat value)
	{
		cpSpaceSetCollisionBias(space,value);
	}

	inline cpTimestamp getCollisionPersistence(void)
	{
		return cpSpaceGetCollisionPersistence(space);
	}

	inline void setCollisionPersistence(cpTimestamp value)
	{
		cpSpaceSetCollisionPersistence(space,value);
	}

	inline cpBool getEnableContactGraph(void)
	{
		return cpSpaceGetEnableContactGraph(space);
	}

	inline void setEnableContactGraph(cpBool value)
	{
		cpSpaceSetEnableContactGraph(space,value);
	}

	inline cpDataPointer getUserData(void)
	{
		return data;
	}

	inline void setUserData(cpDataPointer value)
	{
		data = value;
	}

	inline cp::Body* getStaticBody(void)
	{
		return static_cast<cp::Body*>(cpSpaceGetStaticBody(space) ? cpSpaceGetStaticBody(space)->data : 0);
	}

	inline cpFloat getCurrentTimeStep(void)
	{
		return cpSpaceGetCurrentTimeStep(space);
	}

	Space(cpSpace* v)
	{
		space = v;
		data = v->data;
		v->data = this;
	}

	Space(void)
	 : space(cpSpaceNew())
	, body(new cp::Body(cpSpaceGetStaticBody(space)))
	{
		space->data = this;
		cpBodySetUserData(cpSpaceGetStaticBody(space), body);
	}

};
}//namespace cp

namespace {
	void SpaceAddPostStepCallback(cpSpace *space,void *obj,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Space *,void *)> *>(data))((cp::Space *)space->data,obj);
	}

	void SpacePointQuery(cpShape *shape,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Shape *)> *>(data))((cp::Shape *)shape->data);
	}

	void SpaceNearestPointQuery(cpShape *shape,cpFloat distance,cpVect point,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Shape *,cpFloat ,cpVect )> *>(data))((cp::Shape *)shape->data,distance,point);
	}

	void SpaceSegmentQuery(cpShape *shape,cpFloat t,cpVect n,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Shape *,cpFloat ,cpVect )> *>(data))((cp::Shape *)shape->data,t,n);
	}

	void SpaceBBQuery(cpShape *shape,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Shape *)> *>(data))((cp::Shape *)shape->data);
	}

	void SpaceShapeQuery(cpShape *shape,cpContactPointSet *points,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Shape *,cpContactPointSet *)> *>(data))((cp::Shape *)shape->data,points);
	}

	void SpaceEachBody(cpBody *body,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Body *)> *>(data))((cp::Body *)body->data);
	}

	void SpaceEachShape(cpShape *shape,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Shape *)> *>(data))((cp::Shape *)shape->data);
	}

	void SpaceEachConstraint(cpConstraint *constraint,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Constraint *)> *>(data))((cp::Constraint *)constraint->data);
	}

}