/* 
 * Licensed under the MIT License (See the file LICENSE in the root directory).
 *
 * Chipmunk binding for C++ automatically generated on 10/03/12 22:41:26.
 */
#include "SpaceHash.hpp"
#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include "SpatialIndex.hpp"

namespace cp {

SpaceHash::SpaceHash(cpFloat celldim,int cells,cpSpatialIndexBBFunc bbfunc,cpSpatialIndex *staticIndex)
	: SpatialIndex(cpSpaceHashNew(celldim,cells,bbfunc,SpatialIndex::get()))
{
		}
void SpaceHash::resize(cpFloat celldim,int numcells)
{
		cpSpaceHashResize(hash,celldim,numcells);
}
};//namespace cp
