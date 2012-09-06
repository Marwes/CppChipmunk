#pragma once

#include "chipmunk.h"
#include <functional>
#include "Space.hpp"
#include "Arbiter.hpp"
#include "Vect.hpp"
#include "Constraint.hpp"
#include "Shape.hpp"

class Body;
namespace {
	void BodyEachShape(cpBody *body,cpShape *shape,void *data);
	void BodyEachConstraint(cpBody *body,cpConstraint *constraint,void *data);
	void BodyEachArbiter(cpBody *body,cpArbiter *arbiter,void *data);
}

namespace cp {

typedef std::function<void (cp::Body *,cp::Shape *)> BodyShapeIteratorFunc ;
typedef std::function<void (cp::Body *,cp::Constraint *)> BodyConstraintIteratorFunc ;
typedef std::function<void (cp::Body *,cp::Arbiter *)> BodyArbiterIteratorFunc ;

class Body{
protected:
	cpBody*body;
private:
	cpDataPointer data;
	friend class cp::Space;
public:

	cpBody* get() const
	{
		return body;
	}

	operator cpBody*() const
	{
		return body;
	}

	~Body()
	{
		cpBodyFree(body);
	}

	inline void sanityCheck()
	{
		cpBodySanityCheck(body);
	}

	inline void activate()
	{
		cpBodyActivate(body);
	}

	inline void activateStatic(cpShape *filter)
	{
		cpBodyActivateStatic(body,filter);
	}

	inline void sleep()
	{
		cpBodySleep(body);
	}

	inline void sleepWithGroup(cpBody *group)
	{
		cpBodySleepWithGroup(body,group);
	}

	inline cpBool isSleeping()
	{
		return cpBodyIsSleeping(body);
	}

	inline cpBool isStatic()
	{
		return cpBodyIsStatic(body);
	}

	inline cpBool isRogue()
	{
		return cpBodyIsRogue(body);
	}

	inline void setMass(cpFloat m)
	{
		cpBodySetMass(body,m);
	}

	inline void setMoment(cpFloat i)
	{
		cpBodySetMoment(body,i);
	}

	inline void setPos(cpVect pos)
	{
		cpBodySetPos(body,pos);
	}

	inline void setAngle(cpFloat a)
	{
		cpBodySetAngle(body,a);
	}

	inline void updateVelocity(cpVect gravity,cpFloat damping,cpFloat dt)
	{
		cpBodyUpdateVelocity(body,gravity,damping,dt);
	}

	inline void updatePosition(cpFloat dt)
	{
		cpBodyUpdatePosition(body,dt);
	}

	inline cpVect local2World(const cpVect v)
	{
		return cpBodyLocal2World(body,v);
	}

	inline cpVect world2Local(const cpVect v)
	{
		return cpBodyWorld2Local(body,v);
	}

	inline void resetForces()
	{
		cpBodyResetForces(body);
	}

	inline void applyForce(const cpVect f,const cpVect r)
	{
		cpBodyApplyForce(body,f,r);
	}

	inline void applyImpulse(const cpVect j,const cpVect r)
	{
		cpBodyApplyImpulse(body,j,r);
	}

	inline cpVect getVelAtWorldPoint(cpVect point)
	{
		return cpBodyGetVelAtWorldPoint(body,point);
	}

	inline cpVect getVelAtLocalPoint(cpVect point)
	{
		return cpBodyGetVelAtLocalPoint(body,point);
	}

	inline cpFloat kineticEnergy()
	{
		return cpBodyKineticEnergy(body);
	}

	inline void eachShape(BodyShapeIteratorFunc func)
	{
		cpBodyEachShape(body,*BodyEachShape,&func);
	};

	inline void eachShape(cpBodyShapeIteratorFunc func,void *data)
	{
		cpBodyEachShape(body,func,data);
	}

	inline void eachConstraint(BodyConstraintIteratorFunc func)
	{
		cpBodyEachConstraint(body,*BodyEachConstraint,&func);
	};

	inline void eachConstraint(cpBodyConstraintIteratorFunc func,void *data)
	{
		cpBodyEachConstraint(body,func,data);
	}

	inline void eachArbiter(BodyArbiterIteratorFunc func)
	{
		cpBodyEachArbiter(body,*BodyEachArbiter,&func);
	};

	inline void eachArbiter(cpBodyArbiterIteratorFunc func,void *data)
	{
		cpBodyEachArbiter(body,func,data);
	}

	inline cp::Space* getSpace(void)
	{
		return static_cast<cp::Space*>(cpBodyGetSpace(body) ? cpBodyGetSpace(body)->data : 0);
	}

	inline cpFloat getMass(void)
	{
		return cpBodyGetMass(body);
	}

	inline cpFloat getMoment(void)
	{
		return cpBodyGetMoment(body);
	}

	inline cp::Vect getPos(void)
	{
		return cpBodyGetPos(body);
	}

	inline cp::Vect getVel(void)
	{
		return cpBodyGetVel(body);
	}

	inline void setVel(cp::Vect& value)
	{
		cpBodySetVel(body,value);
	}

	inline cp::Vect getForce(void)
	{
		return cpBodyGetForce(body);
	}

	inline void setForce(cp::Vect& value)
	{
		cpBodySetForce(body,value);
	}

	inline cpFloat getAngle(void)
	{
		return cpBodyGetAngle(body);
	}

	inline cpFloat getAngVel(void)
	{
		return cpBodyGetAngVel(body);
	}

	inline void setAngVel(cpFloat value)
	{
		cpBodySetAngVel(body,value);
	}

	inline cpFloat getTorque(void)
	{
		return cpBodyGetTorque(body);
	}

	inline void setTorque(cpFloat value)
	{
		cpBodySetTorque(body,value);
	}

	inline cp::Vect getRot(void)
	{
		return cpBodyGetRot(body);
	}

	inline cpFloat getVelLimit(void)
	{
		return cpBodyGetVelLimit(body);
	}

	inline void setVelLimit(cpFloat value)
	{
		cpBodySetVelLimit(body,value);
	}

	inline cpFloat getAngVelLimit(void)
	{
		return cpBodyGetAngVelLimit(body);
	}

	inline void setAngVelLimit(cpFloat value)
	{
		cpBodySetAngVelLimit(body,value);
	}

	inline cpDataPointer getUserData(void)
	{
		return data;
	}

	inline void setUserData(cpDataPointer value)
	{
		data = value;
	}

	Body(cpBody* v)
	{
		body = v;
		data = v->data;
		v->data = this;
	}

	Body(cpFloat m,cpFloat i)
	 : body(cpBodyNew(m,i))
	{
		body->data = this;
	}

	Body(void)
	 : body(cpBodyNewStatic())
	{
		body->data = this;
	}

};
}//namespace cp

namespace {
	void BodyEachShape(cpBody *body,cpShape *shape,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Body *,cp::Shape *)> *>(data))((cp::Body *)body->data,(cp::Shape *)shape->data);
	}

	void BodyEachConstraint(cpBody *body,cpConstraint *constraint,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Body *,cp::Constraint *)> *>(data))((cp::Body *)body->data,(cp::Constraint *)constraint->data);
	}

	void BodyEachArbiter(cpBody *body,cpArbiter *arbiter,void *data)
	{
		(*reinterpret_cast<std::function<void (cp::Body *,cp::Arbiter *)> *>(data))((cp::Body *)body->data,&cp::Arbiter(arbiter));
	}

}