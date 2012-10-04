/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 19:56:58.
 */
#include "Space.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include <unordered_map>
#include "Space.hpp"
#include "Shape.hpp"
#include "Arbiter.hpp"
#include <functional>
#include "Vect.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

class Space;
namespace {
	cpBool internal_cpCollisionBeginFunc (cpArbiter *arb,cpSpace *space,void *data);
	cpBool internal_cpCollisionPreSolveFunc (cpArbiter *arb,cpSpace *space,void *data);
	void internal_cpCollisionPostSolveFunc (cpArbiter *arb,cpSpace *space,void *data);
	void internal_cpCollisionSeparateFunc (cpArbiter *arb,cpSpace *space,void *data);
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

void Space::nearestPointQuery_b(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpSpaceNearestPointQueryBlock block)
{
		cpSpaceNearestPointQuery_b(space,point,maxDistance,layers,group,block);
}
void Space::segmentQuery_b(cpVect start,cpVect end,cpLayers layers,cpGroup group,cpSpaceSegmentQueryBlock block)
{
		cpSpaceSegmentQuery_b(space,start,end,layers,group,block);
}
void Space::BBQuery_b(cpBB bb,cpLayers layers,cpGroup group,cpSpaceBBQueryBlock block)
{
		cpSpaceBBQuery_b(space,bb,layers,group,block);
}
cpBool Space::shapeQuery_b(cpShape *shape,cpSpaceShapeQueryBlock block)
{
		return cpSpaceShapeQuery_b(space,shape ? shape->get() : 0,block);
}
Space::Space(void)
	: space(cpSpaceNew()),
	  data(0),
	  body(new cp::Body(cpSpaceGetStaticBody(space)))
{
		space->data = this;
		cpBodySetUserData(cpSpaceGetStaticBody(space), body);
}
Space::~Space()
{
		cpSpaceFree(space);
		body->body = 0;
		delete body;
}
void Space::setDefaultCollisionHandler(cpCollisionBeginFunc begin,cpCollisionPreSolveFunc preSolve,cpCollisionPostSolveFunc postSolve,cpCollisionSeparateFunc separate,void *data)
{
		cpSpaceSetDefaultCollisionHandler(space,begin,preSolve,postSolve,separate,data);
}
void Space::addCollisionHandler(cpCollisionType a,cpCollisionType b,const cpCollisionBeginFunc & begin,const cpCollisionPreSolveFunc & preSolve,const cpCollisionPostSolveFunc & postSolve,const cpCollisionSeparateFunc & separate,void *data)
{
		CollisionHandler& handler = collisionHandlers[std::make_pair(a,b)];
			handler.begin = begin;
			handler.preSolve = preSolve;
			handler.postSolve = postSolve;
			handler.separate = separate;
			handler.data = data;
			cpSpaceAddCollisionHandler(space, a, b, !begin ?  0 : internal_cpCollisionBeginFunc , !preSolve ?  0 : internal_cpCollisionPreSolveFunc , !postSolve ?  0 : internal_cpCollisionPostSolveFunc , !separate ?  0 : internal_cpCollisionSeparateFunc ,  &handler);
}
void Space::addCollisionHandler(cpCollisionType a,cpCollisionType b,cpCollisionBeginFunc begin,cpCollisionPreSolveFunc preSolve,cpCollisionPostSolveFunc postSolve,cpCollisionSeparateFunc separate,void *data)
{
		cpSpaceAddCollisionHandler(space,a,b,begin,preSolve,postSolve,separate,data);
}
void Space::removeCollisionHandler(cpCollisionType a,cpCollisionType b)
{
		collisionHandlers.erase(std::make_pair(a, b));
cpSpaceRemoveCollisionHandler(get(),a,b);
}
cpShape* Space::addShape(cpShape *shape)
{
		cpShape*  temp = cpSpaceAddShape(space,shape ? shape->get() : 0);
		return static_cast<cpShape* >(temp ? temp->data : 0);
}
cpShape* Space::addStaticShape(cpShape *shape)
{
		cpShape*  temp = cpSpaceAddStaticShape(space,shape ? shape->get() : 0);
		return static_cast<cpShape* >(temp ? temp->data : 0);
}
cpBody* Space::addBody(cpBody *body)
{
		cpBody*  temp = cpSpaceAddBody(space,body ? body->get() : 0);
		return static_cast<cpBody* >(temp ? temp->data : 0);
}
cpConstraint* Space::addConstraint(cpConstraint *constraint)
{
		cpConstraint*  temp = cpSpaceAddConstraint(space,constraint ? constraint->get() : 0);
		return static_cast<cpConstraint* >(temp ? temp->data : 0);
}
void Space::removeShape(cpShape *shape)
{
		cpSpaceRemoveShape(space,shape ? shape->get() : 0);
}
void Space::removeStaticShape(cpShape *shape)
{
		cpSpaceRemoveStaticShape(space,shape ? shape->get() : 0);
}
void Space::removeBody(cpBody *body)
{
		cpSpaceRemoveBody(space,body ? body->get() : 0);
}
void Space::removeConstraint(cpConstraint *constraint)
{
		cpSpaceRemoveConstraint(space,constraint ? constraint->get() : 0);
}
cpBool Space::containsShape(cpShape *shape)
{
		return cpSpaceContainsShape(space,shape ? shape->get() : 0);
}
cpBool Space::containsBody(cpBody *body)
{
		return cpSpaceContainsBody(space,body ? body->get() : 0);
}
cpBool Space::containsConstraint(cpConstraint *constraint)
{
		return cpSpaceContainsConstraint(space,constraint ? constraint->get() : 0);
}
cpBool Space::addPostStepCallback(cpPostStepFunc func,void *key,void *data)
{
		return cpSpaceAddPostStepCallback(space,func,key,data);
}
cpBool Space::addPostStepCallback(PostStepFunc func,void *key)
{
		return cpSpaceAddPostStepCallback(space,*SpaceAddPostStepCallback,key,&func);
}
void Space::pointQuery(cpVect point,cpLayers layers,cpGroup group,cpSpacePointQueryFunc func,void *data)
{
		cpSpacePointQuery(space,point,layers,group,func,data);
}
void Space::pointQuery(cpVect point,cpLayers layers,cpGroup group,SpacePointQueryFunc func)
{
		cpSpacePointQuery(space,point,layers,group,*SpacePointQuery,&func);
}
cpShape *Space::pointQueryFirst(cpVect point,cpLayers layers,cpGroup group)
{
		cpShape * temp = cpSpacePointQueryFirst(space,point,layers,group);
		return static_cast<cpShape *>(temp ? temp->data : 0);
}
void Space::nearestPointQuery(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpSpaceNearestPointQueryFunc func,void *data)
{
		cpSpaceNearestPointQuery(space,point,maxDistance,layers,group,func,data);
}
void Space::nearestPointQuery(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,SpaceNearestPointQueryFunc func)
{
		cpSpaceNearestPointQuery(space,point,maxDistance,layers,group,*SpaceNearestPointQuery,&func);
}
cpShape *Space::nearestPointQueryNearest(cpVect point,cpFloat maxDistance,cpLayers layers,cpGroup group,cpNearestPointQueryInfo *out)
{
		cpShape * temp = cpSpaceNearestPointQueryNearest(space,point,maxDistance,layers,group,out);
		return static_cast<cpShape *>(temp ? temp->data : 0);
}
void Space::segmentQuery(cpVect start,cpVect end,cpLayers layers,cpGroup group,cpSpaceSegmentQueryFunc func,void *data)
{
		cpSpaceSegmentQuery(space,start,end,layers,group,func,data);
}
void Space::segmentQuery(cpVect start,cpVect end,cpLayers layers,cpGroup group,SpaceSegmentQueryFunc func)
{
		cpSpaceSegmentQuery(space,start,end,layers,group,*SpaceSegmentQuery,&func);
}
cpShape *Space::segmentQueryFirst(cpVect start,cpVect end,cpLayers layers,cpGroup group,cpSegmentQueryInfo *out)
{
		cpShape * temp = cpSpaceSegmentQueryFirst(space,start,end,layers,group,out);
		return static_cast<cpShape *>(temp ? temp->data : 0);
}
void Space::BBQuery(cpBB bb,cpLayers layers,cpGroup group,cpSpaceBBQueryFunc func,void *data)
{
		cpSpaceBBQuery(space,bb,layers,group,func,data);
}
void Space::BBQuery(cpBB bb,cpLayers layers,cpGroup group,SpaceBBQueryFunc func)
{
		cpSpaceBBQuery(space,bb,layers,group,*SpaceBBQuery,&func);
}
cpBool Space::shapeQuery(cpShape *shape,cpSpaceShapeQueryFunc func,void *data)
{
		return cpSpaceShapeQuery(space,shape ? shape->get() : 0,func,data);
}
cpBool Space::shapeQuery(cpShape *shape,SpaceShapeQueryFunc func)
{
		return cpSpaceShapeQuery(space,shape,*SpaceShapeQuery,&func);
}
void Space::activateShapesTouchingShape(cpShape *shape)
{
		cpSpaceActivateShapesTouchingShape(space,shape ? shape->get() : 0);
}
void Space::eachBody(cpSpaceBodyIteratorFunc func,void *data)
{
		cpSpaceEachBody(space,func,data);
}
void Space::eachBody(SpaceBodyIteratorFunc func)
{
		cpSpaceEachBody(space,*SpaceEachBody,&func);
}
void Space::eachShape(cpSpaceShapeIteratorFunc func,void *data)
{
		cpSpaceEachShape(space,func,data);
}
void Space::eachShape(SpaceShapeIteratorFunc func)
{
		cpSpaceEachShape(space,*SpaceEachShape,&func);
}
void Space::eachConstraint(cpSpaceConstraintIteratorFunc func,void *data)
{
		cpSpaceEachConstraint(space,func,data);
}
void Space::eachConstraint(SpaceConstraintIteratorFunc func)
{
		cpSpaceEachConstraint(space,*SpaceEachConstraint,&func);
}
void Space::reindexStatic()
{
		cpSpaceReindexStatic(space);
}
void Space::reindexShape(cpShape *shape)
{
		cpSpaceReindexShape(space,shape ? shape->get() : 0);
}
void Space::reindexShapesForBody(cpBody *body)
{
		cpSpaceReindexShapesForBody(space,body ? body->get() : 0);
}
void Space::useSpatialHash(cpFloat dim,int count)
{
		cpSpaceUseSpatialHash(space,dim,count);
}
void Space::step(cpFloat dt)
{
		cpSpaceStep(space,dt);
}
int Space::getIterations(void)
{
		return cpSpaceGetIterations(space);
}
void Space::setIterations(int value)
{
		cpSpaceSetIterations(space,value);
}
cp::Vect Space::getGravity(void)
{
		return cpSpaceGetGravity(space);
}
void Space::setGravity(cp::Vect value)
{
		cpSpaceSetGravity(space,value);
}
cpFloat Space::getDamping(void)
{
		return cpSpaceGetDamping(space);
}
void Space::setDamping(cpFloat value)
{
		cpSpaceSetDamping(space,value);
}
cpFloat Space::getIdleSpeedThreshold(void)
{
		return cpSpaceGetIdleSpeedThreshold(space);
}
void Space::setIdleSpeedThreshold(cpFloat value)
{
		cpSpaceSetIdleSpeedThreshold(space,value);
}
cpFloat Space::getSleepTimeThreshold(void)
{
		return cpSpaceGetSleepTimeThreshold(space);
}
void Space::setSleepTimeThreshold(cpFloat value)
{
		cpSpaceSetSleepTimeThreshold(space,value);
}
cpFloat Space::getCollisionSlop(void)
{
		return cpSpaceGetCollisionSlop(space);
}
void Space::setCollisionSlop(cpFloat value)
{
		cpSpaceSetCollisionSlop(space,value);
}
cpFloat Space::getCollisionBias(void)
{
		return cpSpaceGetCollisionBias(space);
}
void Space::setCollisionBias(cpFloat value)
{
		cpSpaceSetCollisionBias(space,value);
}
cpTimestamp Space::getCollisionPersistence(void)
{
		return cpSpaceGetCollisionPersistence(space);
}
void Space::setCollisionPersistence(cpTimestamp value)
{
		cpSpaceSetCollisionPersistence(space,value);
}
cpBool Space::getEnableContactGraph(void)
{
		return cpSpaceGetEnableContactGraph(space);
}
void Space::setEnableContactGraph(cpBool value)
{
		cpSpaceSetEnableContactGraph(space,value);
}
cpDataPointer Space::getUserData(void)
{
		return data;
}
void Space::setUserData(cpDataPointer value)
{
		data = value;
}
cp::Body* Space::getStaticBody(void)
{
		cpBody *temp = cpSpaceGetStaticBody(space);
		return static_cast<cp::Body*>(temp ? temp->data : 0);
}
cpFloat Space::getCurrentTimeStep(void)
{
		return cpSpaceGetCurrentTimeStep(space);
}
Space::Space(cpSpace* v)
	: data(0)
{
		space = v;
		data = v->data;
		v->data = this;
}
};//namespace cp
namespace {
	cpBool internal_cpCollisionBeginFunc (cpArbiter *arb,cpSpace *space,void *data)
	{
		cp::CollisionHandler* handler = static_cast<cp::CollisionHandler*>(data);
		cp::Arbiter tempArbiter(arb);
		data = handler->data;
		return (handler->begin)(&tempArbiter,static_cast<cpSpace *>(space->data),data);
	}
	cpBool internal_cpCollisionPreSolveFunc (cpArbiter *arb,cpSpace *space,void *data)
	{
		cp::CollisionHandler* handler = static_cast<cp::CollisionHandler*>(data);
		cp::Arbiter tempArbiter(arb);
		data = handler->data;
		return (handler->preSolve)(&tempArbiter,static_cast<cpSpace *>(space->data),data);
	}
	void internal_cpCollisionPostSolveFunc (cpArbiter *arb,cpSpace *space,void *data)
	{
		cp::CollisionHandler* handler = static_cast<cp::CollisionHandler*>(data);
		cp::Arbiter tempArbiter(arb);
		data = handler->data;
		return (handler->postSolve)(&tempArbiter,static_cast<cpSpace *>(space->data),data);
	}
	void internal_cpCollisionSeparateFunc (cpArbiter *arb,cpSpace *space,void *data)
	{
		cp::CollisionHandler* handler = static_cast<cp::CollisionHandler*>(data);
		cp::Arbiter tempArbiter(arb);
		data = handler->data;
		return (handler->separate)(&tempArbiter,static_cast<cpSpace *>(space->data),data);
	}
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
				(*reinterpret_cast<std::function<void (cp::Shape *,cpFloat ,cp::Vect )> *>(data))((cp::Shape *)shape->data,distance,point);
	}

	void SpaceSegmentQuery(cpShape *shape,cpFloat t,cpVect n,void *data)
	{
				(*reinterpret_cast<std::function<void (cp::Shape *,cpFloat ,cp::Vect )> *>(data))((cp::Shape *)shape->data,t,n);
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

