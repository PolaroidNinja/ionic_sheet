// included by json_stat.cpp
// everything is within Json namespace

// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class statInternalMap
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

/** \internal MUST be safely initialized using memset( this, 0, sizeof(statInternalLink) );
   * This optimization is used by the fast allocator.
   */
statInternalLink::statInternalLink()
   : previous_( 0 )
   , next_( 0 )
{
}

statInternalLink::~statInternalLink()
{ 
   for ( int index =0; index < itemPerLink; ++index )
   {
      if ( !items_[index].isItemAvailable() )
      {
         if ( !items_[index].isMemberNameStatic() )
            free( keys_[index] );
      }
      else
         break;
   }
}



statMapAllocator::~statMapAllocator()
{
}

#ifdef JSON_USE_SIMPLE_INTERNAL_ALLOCATOR
class DefaultstatMapAllocator : public statMapAllocator
{
public: // overridden from statMapAllocator
   virtual statInternalMap *newMap()
   {
      return new statInternalMap();
   }

   virtual statInternalMap *newMapCopy( const statInternalMap &other )
   {
      return new statInternalMap( other );
   }

   virtual void destructMap( statInternalMap *map )
   {
      delete map;
   }

   virtual statInternalLink *allocateMapBuckets( unsigned int size )
   {
      return new statInternalLink[size];
   }

   virtual void releaseMapBuckets( statInternalLink *links )
   {
      delete [] links;
   }

   virtual statInternalLink *allocateMapLink()
   {
      return new statInternalLink();
   }

   virtual void releaseMapLink( statInternalLink *link )
   {
      delete link;
   }
};
#else
/// @todo make this thread-safe (lock when accessign batch allocator)
class DefaultstatMapAllocator : public statMapAllocator
{
public: // overridden from statMapAllocator
   virtual statInternalMap *newMap()
   {
      statInternalMap *map = mapsAllocator_.allocate();
      new (map) statInternalMap(); // placement new
      return map;
   }

   virtual statInternalMap *newMapCopy( const statInternalMap &other )
   {
      statInternalMap *map = mapsAllocator_.allocate();
      new (map) statInternalMap( other ); // placement new
      return map;
   }

   virtual void destructMap( statInternalMap *map )
   {
      if ( map )
      {
         map->~statInternalMap();
         mapsAllocator_.release( map );
      }
   }

   virtual statInternalLink *allocateMapBuckets( unsigned int size )
   {
      return new statInternalLink[size];
   }

   virtual void releaseMapBuckets( statInternalLink *links )
   {
      delete [] links;
   }

   virtual statInternalLink *allocateMapLink()
   {
      statInternalLink *link = linksAllocator_.allocate();
      memset( link, 0, sizeof(statInternalLink) );
      return link;
   }

   virtual void releaseMapLink( statInternalLink *link )
   {
      link->~statInternalLink();
      linksAllocator_.release( link );
   }
private:
   BatchAllocator<statInternalMap,1> mapsAllocator_;
   BatchAllocator<statInternalLink,1> linksAllocator_;
};
#endif

static statMapAllocator *&mapAllocator()
{
   static DefaultstatMapAllocator defaultAllocator;
   static statMapAllocator *mapAllocator = &defaultAllocator;
   return mapAllocator;
}

static struct DummyMapAllocatorInitializer {
   DummyMapAllocatorInitializer() 
   {
      mapAllocator();      // ensure mapAllocator() statics are initialized before main().
   }
} dummyMapAllocatorInitializer;



// h(K) = stat * K >> w ; with w = 32 & K prime w.r.t. 2^32.

/*
use linked list hash map. 
buckets array is a container.
linked list element contains 6 key/stats. (memory = (16+4) * 6 + 4 = 124)
stat have extra state: valid, available, deleted
*/


statInternalMap::statInternalMap()
   : buckets_( 0 )
   , tailLink_( 0 )
   , bucketsSize_( 0 )
   , itemCount_( 0 )
{
}


statInternalMap::statInternalMap( const statInternalMap &other )
   : buckets_( 0 )
   , tailLink_( 0 )
   , bucketsSize_( 0 )
   , itemCount_( 0 )
{
   reserve( other.itemCount_ );
   IteratorState it;
   IteratorState itEnd;
   other.makeBeginIterator( it );
   other.makeEndIterator( itEnd );
   for ( ; !equals(it,itEnd); increment(it) )
   {
      bool isStatic;
      const char *memberName = key( it, isStatic );
      const stat &astat = stat( it );
      resolveReference(memberName, isStatic) = astat;
   }
}


statInternalMap &
statInternalMap::operator =( const statInternalMap &other )
{
   statInternalMap dummy( other );
   swap( dummy );
   return *this;
}


statInternalMap::~statInternalMap()
{
   if ( buckets_ )
   {
      for ( BucketIndex bucketIndex =0; bucketIndex < bucketsSize_; ++bucketIndex )
      {
         statInternalLink *link = buckets_[bucketIndex].next_;
         while ( link )
         {
            statInternalLink *linkToRelease = link;
            link = link->next_;
            mapAllocator()->releaseMapLink( linkToRelease );
         }
      }
      mapAllocator()->releaseMapBuckets( buckets_ );
   }
}


void 
statInternalMap::swap( statInternalMap &other )
{
   statInternalLink *tempBuckets = buckets_;
   buckets_ = other.buckets_;
   other.buckets_ = tempBuckets;
   statInternalLink *tempTailLink = tailLink_;
   tailLink_ = other.tailLink_;
   other.tailLink_ = tempTailLink;
   BucketIndex tempBucketsSize = bucketsSize_;
   bucketsSize_ = other.bucketsSize_;
   other.bucketsSize_ = tempBucketsSize;
   BucketIndex tempItemCount = itemCount_;
   itemCount_ = other.itemCount_;
   other.itemCount_ = tempItemCount;
}


void 
statInternalMap::clear()
{
   statInternalMap dummy;
   swap( dummy );
}


statInternalMap::BucketIndex 
statInternalMap::size() const
{
   return itemCount_;
}

bool 
statInternalMap::reserveDelta( BucketIndex growth )
{
   return reserve( itemCount_ + growth );
}

bool 
statInternalMap::reserve( BucketIndex newItemCount )
{
   if ( !buckets_  &&  newItemCount > 0 )
   {
      buckets_ = mapAllocator()->allocateMapBuckets( 1 );
      bucketsSize_ = 1;
      tailLink_ = &buckets_[0];
   }
//   BucketIndex idealBucketCount = (newItemCount + statInternalLink::itemPerLink) / statInternalLink::itemPerLink;
   return true;
}


const stat *
statInternalMap::find( const char *key ) const
{
   if ( !bucketsSize_ )
      return 0;
   HashKey hashedKey = hash( key );
   BucketIndex bucketIndex = hashedKey % bucketsSize_;
   for ( const statInternalLink *current = &buckets_[bucketIndex]; 
         current != 0; 
         current = current->next_ )
   {
      for ( BucketIndex index=0; index < statInternalLink::itemPerLink; ++index )
      {
         if ( current->items_[index].isItemAvailable() )
            return 0;
         if ( strcmp( key, current->keys_[index] ) == 0 )
            return &current->items_[index];
      }
   }
   return 0;
}


stat *
statInternalMap::find( const char *key )
{
   const statInternalMap *constThis = this;
   return const_cast<stat *>( constThis->find( key ) );
}


stat &
statInternalMap::resolveReference( const char *key,
                                    bool isStatic )
{
   HashKey hashedKey = hash( key );
   if ( bucketsSize_ )
   {
      BucketIndex bucketIndex = hashedKey % bucketsSize_;
      statInternalLink **previous = 0;
      BucketIndex index;
      for ( statInternalLink *current = &buckets_[bucketIndex]; 
            current != 0; 
            previous = &current->next_, current = current->next_ )
      {
         for ( index=0; index < statInternalLink::itemPerLink; ++index )
         {
            if ( current->items_[index].isItemAvailable() )
               return setNewItem( key, isStatic, current, index );
            if ( strcmp( key, current->keys_[index] ) == 0 )
               return current->items_[index];
         }
      }
   }

   reserveDelta( 1 );
   return unsafeAdd( key, isStatic, hashedKey );
}


void 
statInternalMap::remove( const char *key )
{
   HashKey hashedKey = hash( key );
   if ( !bucketsSize_ )
      return;
   BucketIndex bucketIndex = hashedKey % bucketsSize_;
   for ( statInternalLink *link = &buckets_[bucketIndex]; 
         link != 0; 
         link = link->next_ )
   {
      BucketIndex index;
      for ( index =0; index < statInternalLink::itemPerLink; ++index )
      {
         if ( link->items_[index].isItemAvailable() )
            return;
         if ( strcmp( key, link->keys_[index] ) == 0 )
         {
            doActualRemove( link, index, bucketIndex );
            return;
         }
      }
   }
}

void 
statInternalMap::doActualRemove( statInternalLink *link, 
                                  BucketIndex index,
                                  BucketIndex bucketIndex )
{
   // find last item of the bucket and swap it with the 'removed' one.
   // set removed items flags to 'available'.
   // if last page only contains 'available' items, then desallocate it (it's empty)
   statInternalLink *&lastLink = getLastLinkInBucket( index );
   BucketIndex lastItemIndex = 1; // a link can never be empty, so start at 1
   for ( ;   
         lastItemIndex < statInternalLink::itemPerLink; 
         ++lastItemIndex ) // may be optimized with dicotomic search
   {
      if ( lastLink->items_[lastItemIndex].isItemAvailable() )
         break;
   }
   
   BucketIndex lastUsedIndex = lastItemIndex - 1;
   stat *statToDelete = &link->items_[index];
   stat *statToPreserve = &lastLink->items_[lastUsedIndex];
   if ( statToDelete != statToPreserve )
      statToDelete->swap( *statToPreserve );
   if ( lastUsedIndex == 0 )  // page is now empty
   {  // remove it from bucket linked list and delete it.
      statInternalLink *linkPreviousToLast = lastLink->previous_;
      if ( linkPreviousToLast != 0 )   // can not deleted bucket link.
      {
         mapAllocator()->releaseMapLink( lastLink );
         linkPreviousToLast->next_ = 0;
         lastLink = linkPreviousToLast;
      }
   }
   else
   {
      stat dummy;
      statToPreserve->swap( dummy ); // restore deleted to default stat.
      statToPreserve->setItemUsed( false );
   }
   --itemCount_;
}


statInternalLink *&
statInternalMap::getLastLinkInBucket( BucketIndex bucketIndex )
{
   if ( bucketIndex == bucketsSize_ - 1 )
      return tailLink_;
   statInternalLink *&previous = buckets_[bucketIndex+1].previous_;
   if ( !previous )
      previous = &buckets_[bucketIndex];
   return previous;
}


stat &
statInternalMap::setNewItem( const char *key, 
                              bool isStatic,
                              statInternalLink *link, 
                              BucketIndex index )
{
   char *duplicatedKey = statAllocator()->makeMemberName( key );
   ++itemCount_;
   link->keys_[index] = duplicatedKey;
   link->items_[index].setItemUsed();
   link->items_[index].setMemberNameIsStatic( isStatic );
   return link->items_[index]; // items already default constructed.
}


stat &
statInternalMap::unsafeAdd( const char *key, 
                             bool isStatic, 
                             HashKey hashedKey )
{
   JSON_ASSERT_MESSAGE( bucketsSize_ > 0, "statInternalMap::unsafeAdd(): internal logic error." );
   BucketIndex bucketIndex = hashedKey % bucketsSize_;
   statInternalLink *&previousLink = getLastLinkInBucket( bucketIndex );
   statInternalLink *link = previousLink;
   BucketIndex index;
   for ( index =0; index < statInternalLink::itemPerLink; ++index )
   {
      if ( link->items_[index].isItemAvailable() )
         break;
   }
   if ( index == statInternalLink::itemPerLink ) // need to add a new page
   {
      statInternalLink *newLink = mapAllocator()->allocateMapLink();
      index = 0;
      link->next_ = newLink;
      previousLink = newLink;
      link = newLink;
   }
   return setNewItem( key, isStatic, link, index );
}


statInternalMap::HashKey 
statInternalMap::hash( const char *key ) const
{
   HashKey hash = 0;
   while ( *key )
      hash += *key++ * 37;
   return hash;
}


int 
statInternalMap::compare( const statInternalMap &other ) const
{
   int sizeDiff( itemCount_ - other.itemCount_ );
   if ( sizeDiff != 0 )
      return sizeDiff;
   // Strict order guaranty is required. Compare all keys FIRST, then compare stats.
   IteratorState it;
   IteratorState itEnd;
   makeBeginIterator( it );
   makeEndIterator( itEnd );
   for ( ; !equals(it,itEnd); increment(it) )
   {
      if ( !other.find( key( it ) ) )
         return 1;
   }

   // All keys are equals, let's compare stats
   makeBeginIterator( it );
   for ( ; !equals(it,itEnd); increment(it) )
   {
      const stat *otherstat = other.find( key( it ) );
      int statDiff = stat(it).compare( *otherstat );
      if ( statDiff != 0 )
         return statDiff;
   }
   return 0;
}


void 
statInternalMap::makeBeginIterator( IteratorState &it ) const
{
   it.map_ = const_cast<statInternalMap *>( this );
   it.bucketIndex_ = 0;
   it.itemIndex_ = 0;
   it.link_ = buckets_;
}


void 
statInternalMap::makeEndIterator( IteratorState &it ) const
{
   it.map_ = const_cast<statInternalMap *>( this );
   it.bucketIndex_ = bucketsSize_;
   it.itemIndex_ = 0;
   it.link_ = 0;
}


bool 
statInternalMap::equals( const IteratorState &x, const IteratorState &other )
{
   return x.map_ == other.map_  
          &&  x.bucketIndex_ == other.bucketIndex_  
          &&  x.link_ == other.link_
          &&  x.itemIndex_ == other.itemIndex_;
}


void 
statInternalMap::incrementBucket( IteratorState &iterator )
{
   ++iterator.bucketIndex_;
   JSON_ASSERT_MESSAGE( iterator.bucketIndex_ <= iterator.map_->bucketsSize_,
      "statInternalMap::increment(): attempting to iterate beyond end." );
   if ( iterator.bucketIndex_ == iterator.map_->bucketsSize_ )
      iterator.link_ = 0;
   else
      iterator.link_ = &(iterator.map_->buckets_[iterator.bucketIndex_]);
   iterator.itemIndex_ = 0;
}


void 
statInternalMap::increment( IteratorState &iterator )
{
   JSON_ASSERT_MESSAGE( iterator.map_, "Attempting to iterator using invalid iterator." );
   ++iterator.itemIndex_;
   if ( iterator.itemIndex_ == statInternalLink::itemPerLink )
   {
      JSON_ASSERT_MESSAGE( iterator.link_ != 0,
         "statInternalMap::increment(): attempting to iterate beyond end." );
      iterator.link_ = iterator.link_->next_;
      if ( iterator.link_ == 0 )
         incrementBucket( iterator );
   }
   else if ( iterator.link_->items_[iterator.itemIndex_].isItemAvailable() )
   {
      incrementBucket( iterator );
   }
}


void 
statInternalMap::decrement( IteratorState &iterator )
{
   if ( iterator.itemIndex_ == 0 )
   {
      JSON_ASSERT_MESSAGE( iterator.map_, "Attempting to iterate using invalid iterator." );
      if ( iterator.link_ == &iterator.map_->buckets_[iterator.bucketIndex_] )
      {
         JSON_ASSERT_MESSAGE( iterator.bucketIndex_ > 0, "Attempting to iterate beyond beginning." );
         --(iterator.bucketIndex_);
      }
      iterator.link_ = iterator.link_->previous_;
      iterator.itemIndex_ = statInternalLink::itemPerLink - 1;
   }
}


const char *
statInternalMap::key( const IteratorState &iterator )
{
   JSON_ASSERT_MESSAGE( iterator.link_, "Attempting to iterate using invalid iterator." );
   return iterator.link_->keys_[iterator.itemIndex_];
}

const char *
statInternalMap::key( const IteratorState &iterator, bool &isStatic )
{
   JSON_ASSERT_MESSAGE( iterator.link_, "Attempting to iterate using invalid iterator." );
   isStatic = iterator.link_->items_[iterator.itemIndex_].isMemberNameStatic();
   return iterator.link_->keys_[iterator.itemIndex_];
}


stat &
statInternalMap::stat( const IteratorState &iterator )
{
   JSON_ASSERT_MESSAGE( iterator.link_, "Attempting to iterate using invalid iterator." );
   return iterator.link_->items_[iterator.itemIndex_];
}


int 
statInternalMap::distance( const IteratorState &x, const IteratorState &y )
{
   int offset = 0;
   IteratorState it = x;
   while ( !equals( it, y ) )
      increment( it );
   return offset;
}
