// included by json_value.cpp
// everything is within Json namespace

// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// class ValueInternalArray
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

ValueArrayAllocator::~statArrayAllocator()
{
}

// //////////////////////////////////////////////////////////////////
// class DefaultValueArrayAllocator
// //////////////////////////////////////////////////////////////////
#ifdef JSON_USE_SIMPLE_INTERNAL_ALLOCATOR
class DefaultstatArrayAllocator : public statArrayAllocator
{
public: // overridden from statArrayAllocator
   virtual ~DefaultstatArrayAllocator()
   {
   }

   virtual statInternalArray *newArray()
   {
      return new statInternalArray();
   }

   virtual statInternalArray *newArrayCopy( const statInternalArray &other )
   {
      return new statInternalArray( other );
   }

   virtual void destructArray( statInternalArray *array )
   {
      delete array;
   }

   virtual void reallocateArrayPageIndex( stat **&indexes, 
                                          statInternalArray::PageIndex &indexCount,
                                          statInternalArray::PageIndex minNewIndexCount )
   {
      statInternalArray::PageIndex newIndexCount = (indexCount*3)/2 + 1;
      if ( minNewIndexCount > newIndexCount )
         newIndexCount = minNewIndexCount;
      void *newIndexes = realloc( indexes, sizeof(stat*) * newIndexCount );
      if ( !newIndexes )
         throw std::bad_alloc();
      indexCount = newIndexCount;
      indexes = static_cast<stat **>( newIndexes );
   }
   virtual void releaseArrayPageIndex( stat **indexes, 
                                       statInternalArray::PageIndex indexCount )
   {
      if ( indexes )
         free( indexes );
   }

   virtual stat *allocateArrayPage()
   {
      return static_cast<stat *>( malloc( sizeof(stat) * statInternalArray::itemsPerPage ) );
   }

   virtual void releaseArrayPage( stat *stat )
   {
      if ( stat )
         free( stat );
   }
};

#else // #ifdef JSON_USE_SIMPLE_INTERNAL_ALLOCATOR
/// @todo make this thread-safe (lock when accessign batch allocator)
class DefaultstatArrayAllocator : public statArrayAllocator
{
public: // overridden from statArrayAllocator
   virtual ~DefaultstatArrayAllocator()
   {
   }

   virtual statInternalArray *newArray()
   {
      statInternalArray *array = arraysAllocator_.allocate();
      new (array) statInternalArray(); // placement new
      return array;
   }

   virtual statInternalArray *newArrayCopy( const statInternalArray &other )
   {
      statInternalArray *array = arraysAllocator_.allocate();
      new (array) statInternalArray( other ); // placement new
      return array;
   }

   virtual void destructArray( statInternalArray *array )
   {
      if ( array )
      {
         array->~statInternalArray();
         arraysAllocator_.release( array );
      }
   }

   virtual void reallocateArrayPageIndex( stat **&indexes, 
                                          statInternalArray::PageIndex &indexCount,
                                          statInternalArray::PageIndex minNewIndexCount )
   {
      statInternalArray::PageIndex newIndexCount = (indexCount*3)/2 + 1;
      if ( minNewIndexCount > newIndexCount )
         newIndexCount = minNewIndexCount;
      void *newIndexes = realloc( indexes, sizeof(stat*) * newIndexCount );
      if ( !newIndexes )
         throw std::bad_alloc();
      indexCount = newIndexCount;
      indexes = static_cast<stat **>( newIndexes );
   }
   virtual void releaseArrayPageIndex( stat **indexes, 
                                       statInternalArray::PageIndex indexCount )
   {
      if ( indexes )
         free( indexes );
   }

   virtual stat *allocateArrayPage()
   {
      return static_cast<stat *>( pagesAllocator_.allocate() );
   }

   virtual void releaseArrayPage( stat *stat )
   {
      if ( stat )
         pagesAllocator_.release( stat );
   }
private:
   BatchAllocator<statInternalArray,1> arraysAllocator_;
   BatchAllocator<stat,statInternalArray::itemsPerPage> pagesAllocator_;
};
#endif // #ifdef JSON_USE_SIMPLE_INTERNAL_ALLOCATOR

static statArrayAllocator *&arrayAllocator()
{
   static DefaultstatArrayAllocator defaultAllocator;
   static statArrayAllocator *arrayAllocator = &defaultAllocator;
   return arrayAllocator;
}

static struct DummyArrayAllocatorInitializer {
   DummyArrayAllocatorInitializer() 
   {
      arrayAllocator();      // ensure arrayAllocator() statics are initialized before main().
   }
} dummyArrayAllocatorInitializer;

// //////////////////////////////////////////////////////////////////
// class statInternalArray
// //////////////////////////////////////////////////////////////////
bool 
statInternalArray::equals( const IteratorState &x, 
                            const IteratorState &other )
{
   return x.array_ == other.array_  
          &&  x.currentItemIndex_ == other.currentItemIndex_  
          &&  x.currentPageIndex_ == other.currentPageIndex_;
}


void 
statInternalArray::increment( IteratorState &it )
{
   JSON_ASSERT_MESSAGE( it.array_  &&
      (it.currentPageIndex_ - it.array_->pages_)*itemsPerPage + it.currentItemIndex_
      != it.array_->size_,
      "statInternalArray::increment(): moving iterator beyond end" );
   ++(it.currentItemIndex_);
   if ( it.currentItemIndex_ == itemsPerPage )
   {
      it.currentItemIndex_ = 0;
      ++(it.currentPageIndex_);
   }
}


void 
statInternalArray::decrement( IteratorState &it )
{
   JSON_ASSERT_MESSAGE( it.array_  &&  it.currentPageIndex_ == it.array_->pages_ 
                        &&  it.currentItemIndex_ == 0,
      "statInternalArray::decrement(): moving iterator beyond end" );
   if ( it.currentItemIndex_ == 0 )
   {
      it.currentItemIndex_ = itemsPerPage-1;
      --(it.currentPageIndex_);
   }
   else
   {
      --(it.currentItemIndex_);
   }
}


stat &
statInternalArray::unsafeDereference( const IteratorState &it )
{
   return (*(it.currentPageIndex_))[it.currentItemIndex_];
}


stat &
statInternalArray::dereference( const IteratorState &it )
{
   JSON_ASSERT_MESSAGE( it.array_  &&
      (it.currentPageIndex_ - it.array_->pages_)*itemsPerPage + it.currentItemIndex_
      < it.array_->size_,
      "statInternalArray::dereference(): dereferencing invalid iterator" );
   return unsafeDereference( it );
}

void 
statInternalArray::makeBeginIterator( IteratorState &it ) const
{
   it.array_ = const_cast<statInternalArray *>( this );
   it.currentItemIndex_ = 0;
   it.currentPageIndex_ = pages_;
}


void 
statInternalArray::makeIterator( IteratorState &it, ArrayIndex index ) const
{
   it.array_ = const_cast<statInternalArray *>( this );
   it.currentItemIndex_ = index % itemsPerPage;
   it.currentPageIndex_ = pages_ + index / itemsPerPage;
}


void 
statInternalArray::makeEndIterator( IteratorState &it ) const
{
   makeIterator( it, size_ );
}


statInternalArray::statInternalArray()
   : pages_( 0 )
   , size_( 0 )
   , pageCount_( 0 )
{
}


statInternalArray::statInternalArray( const statInternalArray &other )
   : pages_( 0 )
   , pageCount_( 0 )
   , size_( other.size_ )
{
   PageIndex minNewPages = other.size_ / itemsPerPage;
   arrayAllocator()->reallocateArrayPageIndex( pages_, pageCount_, minNewPages );
   JSON_ASSERT_MESSAGE( pageCount_ >= minNewPages, 
                        "statInternalArray::reserve(): bad reallocation" );
   IteratorState itOther;
   other.makeBeginIterator( itOther );
   stat *stat;
   for ( ArrayIndex index = 0; index < size_; ++index, increment(itOther) )
   {
      if ( index % itemsPerPage == 0 )
      {
         PageIndex pageIndex = index / itemsPerPage;
         stat = arrayAllocator()->allocateArrayPage();
         pages_[pageIndex] = stat;
      }
      new (stat) stat( dereference( itOther ) );
   }
}


statInternalArray &
statInternalArray::operator =( const statInternalArray &other )
{
   statInternalArray temp( other );
   swap( temp );
   return *this;
}


statInternalArray::~statInternalArray()
{
   // destroy all constructed items
   IteratorState it;
   IteratorState itEnd;
   makeBeginIterator( it);
   makeEndIterator( itEnd );
   for ( ; !equals(it,itEnd); increment(it) )
   {
      stat *stat = &dereference(it);
      stat->~stat();
   }
   // release all pages
   PageIndex lastPageIndex = size_ / itemsPerPage;
   for ( PageIndex pageIndex = 0; pageIndex < lastPageIndex; ++pageIndex )
      arrayAllocator()->releaseArrayPage( pages_[pageIndex] );
   // release pages index
   arrayAllocator()->releaseArrayPageIndex( pages_, pageCount_ );
}


void 
statInternalArray::swap( statInternalArray &other )
{
   stat **tempPages = pages_;
   pages_ = other.pages_;
   other.pages_ = tempPages;
   ArrayIndex tempSize = size_;
   size_ = other.size_;
   other.size_ = tempSize;
   PageIndex tempPageCount = pageCount_;
   pageCount_ = other.pageCount_;
   other.pageCount_ = tempPageCount;
}

void 
statInternalArray::clear()
{
   statInternalArray dummy;
   swap( dummy );
}


void 
statInternalArray::resize( ArrayIndex newSize )
{
   if ( newSize == 0 )
      clear();
   else if ( newSize < size_ )
   {
      IteratorState it;
      IteratorState itEnd;
      makeIterator( it, newSize );
      makeIterator( itEnd, size_ );
      for ( ; !equals(it,itEnd); increment(it) )
      {
         stat *stat = &dereference(it);
         stat->~stat();
      }
      PageIndex pageIndex = (newSize + itemsPerPage - 1) / itemsPerPage;
      PageIndex lastPageIndex = size_ / itemsPerPage;
      for ( ; pageIndex < lastPageIndex; ++pageIndex )
         arrayAllocator()->releaseArrayPage( pages_[pageIndex] );
      size_ = newSize;
   }
   else if ( newSize > size_ )
      resolveReference( newSize );
}


void 
statInternalArray::makeIndexValid( ArrayIndex index )
{
   // Need to enlarge page index ?
   if ( index >= pageCount_ * itemsPerPage )
   {
      PageIndex minNewPages = (index + 1) / itemsPerPage;
      arrayAllocator()->reallocateArrayPageIndex( pages_, pageCount_, minNewPages );
      JSON_ASSERT_MESSAGE( pageCount_ >= minNewPages, "statInternalArray::reserve(): bad reallocation" );
   }

   // Need to allocate new pages ?
   ArrayIndex nextPageIndex = 
      (size_ % itemsPerPage) != 0 ? size_ - (size_%itemsPerPage) + itemsPerPage
                                  : size_;
   if ( nextPageIndex <= index )
   {
      PageIndex pageIndex = nextPageIndex / itemsPerPage;
      PageIndex pageToAllocate = (index - nextPageIndex) / itemsPerPage + 1;
      for ( ; pageToAllocate-- > 0; ++pageIndex )
         pages_[pageIndex] = arrayAllocator()->allocateArrayPage();
   }

   // Initialize all new entries
   IteratorState it;
   IteratorState itEnd;
   makeIterator( it, size_ );
   size_ = index + 1;
   makeIterator( itEnd, size_ );
   for ( ; !equals(it,itEnd); increment(it) )
   {
      stat *stat = &dereference(it);
      new (stat) stat(); // Construct a default stat using placement new
   }
}

stat &
statInternalArray::resolveReference( ArrayIndex index )
{
   if ( index >= size_ )
      makeIndexValid( index );
   return pages_[index/itemsPerPage][index%itemsPerPage];
}

stat *
statInternalArray::find( ArrayIndex index ) const
{
   if ( index >= size_ )
      return 0;
   return &(pages_[index/itemsPerPage][index%itemsPerPage]);
}

statInternalArray::ArrayIndex 
statInternalArray::size() const
{
   return size_;
}

int 
statInternalArray::distance( const IteratorState &x, const IteratorState &y )
{
   return indexOf(y) - indexOf(x);
}


statInternalArray::ArrayIndex 
statInternalArray::indexOf( const IteratorState &iterator )
{
   if ( !iterator.array_ )
      return ArrayIndex(-1);
   return ArrayIndex(
      (iterator.currentPageIndex_ - iterator.array_->pages_) * itemsPerPage 
      + iterator.currentItemIndex_ );
}


int 
statInternalArray::compare( const statInternalArray &other ) const
{
   int sizeDiff( size_ - other.size_ );
   if ( sizeDiff != 0 )
      return sizeDiff;
   
   for ( ArrayIndex index =0; index < size_; ++index )
   {
      int diff = pages_[index/itemsPerPage][index%itemsPerPage].compare( 
         other.pages_[index/itemsPerPage][index%itemsPerPage] );
      if ( diff != 0 )
         return diff;
   }
   return 0;
}
