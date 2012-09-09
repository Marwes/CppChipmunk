/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:52:11.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "BB.hpp"
#include "Vect.hpp"

namespace cp {

class BB : public cpBB {
protected:
public:
	BB(const cpBB v);
	BB(const cpFloat l,const cpFloat b,const cpFloat r,const cpFloat t);
	BB(const cpVect p,const cpFloat r);
	cpBool intersects(const cpBB b);
	cpBool containsBB(const cpBB other);
	cpBool containsVect(const cpVect v);
	cp::BB merge(const cpBB b);
	cp::BB expand(const cpVect v);
	cpFloat area();
	cpFloat mergedArea(cp::BB b);
	cpFloat segmentQuery(cp::Vect a,cp::Vect b);
	cpBool intersectsSegment(cp::Vect a,cp::Vect b);
	cp::Vect wrapVect(const cpVect v);

};
};//namespace cp
