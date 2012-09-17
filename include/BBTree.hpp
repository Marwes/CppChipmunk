/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 09/15/12 09:55:02.
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
	cpBBTree* get();
/// Allocate and initialize a bounding box tree.
	BBTree(cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex);
/// Perform a static top down optimization of the tree.
	void optimize();
/// Set the velocity function for the bounding box tree to enable temporal coherence.
	void setVelocityFunc(cpBBTreeVelocityFunc func);

};
};//namespace cp
