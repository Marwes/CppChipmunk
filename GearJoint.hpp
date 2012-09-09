#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Constraint.hpp"
#include "Body.hpp"

namespace cp {

class GearJoint : public Constraint {
protected:
	cpGearJoint* gearjoint;
public:
	cpGearJoint* get();
	const cpConstraintClass *getClass();
	GearJoint(cp::Body *a,cp::Body *b,cpFloat phase,cpFloat ratio);
	void setRatio(cpFloat value);
	cpFloat getPhase(void);
	void setPhase(cpFloat value);
	cpFloat getRatio(void);

};
};//namespace cp
