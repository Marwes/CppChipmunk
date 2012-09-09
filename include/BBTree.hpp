/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"
#include "SpatialIndex.hpp"

namespace cp {

class BBTree : public SpatialIndex {
protected:
	cpBBTree* bbtree;
public:
	cpBBTree* get();
	BBTree(cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex);
	void optimize();
	void setVelocityFunc(cpBBTreeVelocityFunc func);

};
};//namespace cp
