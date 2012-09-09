#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Arbiter.hpp"
#include "Constraint.hpp"
#include <functional>
#include "Space.hpp"
#include "Vect.hpp"
#include "Shape.hpp"
#include "Body.hpp"

namespace cp {
	typedef std::function<void (cp::Body *,cp::Shape *)> BodyShapeIteratorFunc ;
	typedef std::function<void (cp::Body *,cp::Constraint *)> BodyConstraintIteratorFunc ;
	typedef std::function<void (cp::Body *,cp::Arbiter *)> BodyArbiterIteratorFunc ;

class Body {
protected:
	cpBody* body;
	cpDataPointer data;
	friend class  cp::Space;
;
public:
	cpBody* get();
	Body(cpFloat m,cpFloat i);
	Body(void);
	~Body();
	void activate();
	void activateStatic(cp::Shape *filter);
	void sleep();
	void sleepWithGroup(cp::Body *group);
	cpBool isSleeping();
	cpBool isStatic();
	cpBool isRogue();
	void setMass(cpFloat m);
	void setMoment(cpFloat i);
	void setPos(cp::Vect pos);
	void setAngle(cpFloat a);
	void updateVelocity(cp::Vect gravity,cpFloat damping,cpFloat dt);
	void updatePosition(cpFloat dt);
	cp::Vect local2World(const cpVect v);
	cp::Vect world2Local(const cpVect v);
	void resetForces();
	void applyForce(const cpVect f,const cpVect r);
	void applyImpulse(const cpVect j,const cpVect r);
	cp::Vect getVelAtWorldPoint(cp::Vect point);
	cp::Vect getVelAtLocalPoint(cp::Vect point);
	cpFloat kineticEnergy();
	void eachShape(cpBodyShapeIteratorFunc func,void *data);
	void eachShape(BodyShapeIteratorFunc func);
	void eachConstraint(cpBodyConstraintIteratorFunc func,void *data);
	void eachConstraint(BodyConstraintIteratorFunc func);
	void eachArbiter(cpBodyArbiterIteratorFunc func,void *data);
	void eachArbiter(BodyArbiterIteratorFunc func);
	cp::Space* getSpace(void);
	cpFloat getMass(void);
	cpFloat getMoment(void);
	cp::Vect getPos(void);
	cp::Vect getVel(void);
	void setVel(cp::Vect value);
	cp::Vect getForce(void);
	void setForce(cp::Vect value);
	cpFloat getAngle(void);
	cpFloat getAngVel(void);
	void setAngVel(cpFloat value);
	cpFloat getTorque(void);
	void setTorque(cpFloat value);
	cp::Vect getRot(void);
	cpFloat getVelLimit(void);
	void setVelLimit(cpFloat value);
	cpFloat getAngVelLimit(void);
	void setAngVelLimit(cpFloat value);
	cpDataPointer getUserData(void);
	void setUserData(cpDataPointer value);
	Body(cpBody* v);

};
};//namespace cp
