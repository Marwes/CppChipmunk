/* 
 * Chipmunk binding for c++ automatically generated on 09/09/12 16:29:46.
 */
#pragma once

#include "chipmunk.h"
#include "chipmunk_declarations.hpp"
#include <functional>
#include "Vect.hpp"
#include "BB.hpp"
#include "SpatialIndex.hpp"

namespace cp {
	typedef std::function<void (void *,void *)> SpatialIndexQueryFunc ;
	typedef std::function<void (void *)> SpatialIndexIteratorFunc ;
	typedef std::function<void (void *,void *)> SpatialIndexQueryFunc ;
	typedef std::function<cpFloat (void *,void *)> SpatialIndexSegmentQueryFunc ;
	typedef std::function<void (void *,void *)> SpatialIndexQueryFunc ;

class SpatialIndex {
protected:
	cpSpatialIndex* index;
public:
	cpSpatialIndex* get();
	~SpatialIndex();
	void collideStatic(cp::SpatialIndex *staticIndex,cpSpatialIndexQueryFunc func,void *data);
	void collideStatic(cpSpatialIndex *staticIndex,SpatialIndexQueryFunc func);
	int count();
	void each(cpSpatialIndexIteratorFunc func,void *data);
	void each(SpatialIndexIteratorFunc func);
	cpBool contains(void *obj,cpHashValue hashid);
	void insert(void *obj,cpHashValue hashid);
	void remove(void *obj,cpHashValue hashid);
	void reindex();
	void reindexObject(void *obj,cpHashValue hashid);
	void query(void *obj,cp::BB bb,cpSpatialIndexQueryFunc func,void *data);
	void query(void *obj,cpBB bb,SpatialIndexQueryFunc func);
	void segmentQuery(void *obj,cp::Vect a,cp::Vect b,cpFloat t_exit,cpSpatialIndexSegmentQueryFunc func,void *data);
	void segmentQuery(void *obj,cpVect a,cpVect b,cpFloat t_exit,SpatialIndexSegmentQueryFunc func);
	void reindexQuery(cpSpatialIndexQueryFunc func,void *data);
	void reindexQuery(SpatialIndexQueryFunc func);
	SpatialIndex(cpSpatialIndex* v);

};
};//namespace cp
