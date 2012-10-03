/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:41:26.
 */
#include "BBTree.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"

namespace cp {

BBTree::BBTree(cpSpatialIndexBBFunc bbfunc,cpSpatialIndex *staticIndex)
	: SpatialIndex(cpBBTreeNew(bbfunc,SpatialIndex::get()))
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
