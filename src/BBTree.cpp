/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/04/12 20:19:55.
 */
#include "BBTree.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"
#include "SpatialIndex.hpp"

namespace cp {

BBTree::BBTree(cpSpatialIndexBBFunc bbfunc,cp::SpatialIndex *staticIndex)
	: SpatialIndex(cpBBTreeNew(bbfunc,staticIndex ? staticIndex->get() : 0))
{
		}
void BBTree::optimize()
{
		cpBBTreeOptimize(SpatialIndex::get());
}
void BBTree::setVelocityFunc(cpBBTreeVelocityFunc func)
{
		cpBBTreeSetVelocityFunc(SpatialIndex::get(),func);
}
};//namespace cp
