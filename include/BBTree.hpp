/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 20:29:34.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"

namespace cp {

class BBTree : public SpatialIndex {
protected:
	cpBBTree* bbtree;
public:
	inline cpBBTree* get(){
		return bbtree;
}
/// Allocate and initialize a bounding box tree.
	BBTree(cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex);
/// Perform a static top down optimization of the tree.
	void optimize();
/// Set the velocity function for the bounding box tree to enable temporal coherence.
	void setVelocityFunc(cpBBTreeVelocityFunc func);

};
};//namespace cp
