/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/19/12 14:10:01.
 */
#include "Arbiter.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Vect.hpp"
#include "Shape.hpp"
#include "Body.hpp"

namespace cp {

cpArbiter* Arbiter::get()
{
		return arb;
}
cp::Vect Arbiter::totalImpulse()
{
		return cpArbiterTotalImpulse(arb);
}
cp::Vect Arbiter::totalImpulseWithFriction()
{
		return cpArbiterTotalImpulseWithFriction(arb);
}
cpFloat Arbiter::totalKE()
{
		return cpArbiterTotalKE(arb);
}
void Arbiter::ignore()
{
		cpArbiterIgnore(arb);
}
void Arbiter::getShapes(cp::Shape *&a,cp::Shape *&b)
{
		cpShape *a_, *b_;
		cpArbiterGetShapes(arb, &a_, &b_);
		a = static_cast<cp::Shape*>(a_->data);
		b = static_cast<cp::Shape*>(b_->data);
}
void Arbiter::getBodies(cp::Body *&a,cp::Body *&b)
{
		cpBody *a_, *b_;
		cpArbiterGetBodies(arb, &a_, &b_);
		a = static_cast<cp::Body*>(a_->data);
		b = static_cast<cp::Body*>(b_->data);
}
cpContactPointSet Arbiter::getContactPointSet()
{
		return cpArbiterGetContactPointSet(arb);
}
cpBool Arbiter::isFirstContact()
{
		return cpArbiterIsFirstContact(arb);
}
int Arbiter::getCount()
{
		return cpArbiterGetCount(arb);
}
cp::Vect Arbiter::getNormal(int i)
{
		return cpArbiterGetNormal(arb,i);
}
cp::Vect Arbiter::getPoint(int i)
{
		return cpArbiterGetPoint(arb,i);
}
cpFloat Arbiter::getDepth(int i)
{
		return cpArbiterGetDepth(arb,i);
}
cpFloat Arbiter::getElasticity(void)
{
		return cpArbiterGetElasticity(arb);
}
void Arbiter::setElasticity(cpFloat value)
{
		cpArbiterSetElasticity(arb,value);
}
cpFloat Arbiter::getFriction(void)
{
		return cpArbiterGetFriction(arb);
}
void Arbiter::setFriction(cpFloat value)
{
		cpArbiterSetFriction(arb,value);
}
cp::Vect Arbiter::getSurfaceVelocity(void)
{
		return cpArbiterGetSurfaceVelocity(arb);
}
void Arbiter::setSurfaceVelocity(cp::Vect value)
{
		cpArbiterSetSurfaceVelocity(arb,value);
}
Arbiter::Arbiter(cpArbiter* v)
{
		arb = v;
}
};//namespace cp
