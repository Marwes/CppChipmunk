#include "Constraint.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "Space.hpp"
#include "Body.hpp"

namespace cp {

cpConstraint* Constraint::get()
{
		return constraint;
}
Constraint::~Constraint()
{
		cpConstraintFree(constraint);
}
void Constraint::activateBodies()
{
		cpConstraintActivateBodies(constraint);
}
cpFloat Constraint::getImpulse()
{
		return cpConstraintGetImpulse(constraint);
}
cp::Space* Constraint::getSpace(void)
{
		cpSpace *temp = cpConstraintGetSpace(constraint);
		return static_cast<cp::Space*>(temp ? temp->data : 0);
}
cp::Body* Constraint::getA(void)
{
		cpBody *temp = cpConstraintGetA(constraint);
		return static_cast<cp::Body*>(temp ? temp->data : 0);
}
cp::Body* Constraint::getB(void)
{
		cpBody *temp = cpConstraintGetB(constraint);
		return static_cast<cp::Body*>(temp ? temp->data : 0);
}
cpFloat Constraint::getMaxForce(void)
{
		return cpConstraintGetMaxForce(constraint);
}
void Constraint::setMaxForce(cpFloat value)
{
		cpConstraintSetMaxForce(constraint,value);
}
cpFloat Constraint::getErrorBias(void)
{
		return cpConstraintGetErrorBias(constraint);
}
void Constraint::setErrorBias(cpFloat value)
{
		cpConstraintSetErrorBias(constraint,value);
}
cpFloat Constraint::getMaxBias(void)
{
		return cpConstraintGetMaxBias(constraint);
}
void Constraint::setMaxBias(cpFloat value)
{
		cpConstraintSetMaxBias(constraint,value);
}
cpConstraintPreSolveFunc Constraint::getPreSolveFunc(void)
{
		return cpConstraintGetPreSolveFunc(constraint);
}
void Constraint::setPreSolveFunc(cpConstraintPreSolveFunc value)
{
		cpConstraintSetPreSolveFunc(constraint,value);
}
cpConstraintPostSolveFunc Constraint::getPostSolveFunc(void)
{
		return cpConstraintGetPostSolveFunc(constraint);
}
void Constraint::setPostSolveFunc(cpConstraintPostSolveFunc value)
{
		cpConstraintSetPostSolveFunc(constraint,value);
}
cpDataPointer Constraint::getUserData(void)
{
		return data;
}
void Constraint::setUserData(cpDataPointer value)
{
		data = value;
}
Constraint::Constraint(cpConstraint* v)
	: data(0)
{
		constraint = v;
		data = v->data;
		v->data = this;
}
};//namespace cp