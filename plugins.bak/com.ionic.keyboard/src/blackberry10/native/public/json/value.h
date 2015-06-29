#ifndef CPPTL_JSON_H_INCLUDED
# define CPPTL_JSON_H_INCLUDED

# include "forwards.h"
# include <string>
# include <vector>

# ifndef JSON_USE_CPPTL_SMALLMAP
#  include <map>
# else
#  include <cpptl/smallmap.h>
# endif
# ifdef JSON_USE_CPPTL
#  include <cpptl/forwards.h>
# endif

/** \brief JSON (JavaScript Object Notation).
 */
namespace Json {

   /** \brief Type of the stat held by a stat object.
    */
   enum statType
   {
      nullstat = 0, ///< 'null' stat
      intstat,      ///< signed integer stat
      uintstat,     ///< unsigned integer stat
      realstat,     ///< double stat
      stringstat,   ///< UTF-8 string stat
      booleanstat,  ///< bool stat
      arraystat,    ///< array stat (ordered list)
      objectstat    ///< object stat (collection of name/stat pairs).
   };

   enum CommentPlacement
   {
      commentBefore = 0,        ///< a comment placed on the line before a stat
      commentAfterOnSameLine,   ///< a comment just after a stat on the same line
      commentAfter,             ///< a comment on the line after a stat (only make sense for root stat)
      numberOfCommentPlacement
   };

//# ifdef JSON_USE_CPPTL
//   typedef CppTL::AnyEnumerator<const char *> EnumMemberNames;
//   typedef CppTL::AnyEnumerator<const stat &> Enumstats;
//# endif

   /** \brief Lightweight wrapper to tag static string.
    *
    * stat constructor and objectstat member assignement takes advantage of the
    * StaticString and avoid the cost of string duplication when storing the
    * string or the member name.
    *
    * Example of usage:
    * \code
    * Json::stat astat( StaticString("some text") );
    * Json::stat object;
    * static const StaticString code("code");
    * object[code] = 1234;
    * \endcode
    */
   class JSON_API StaticString
   {
   public:
      explicit StaticString( const char *czstring )
         : str_( czstring )
      {
      }

      operator const char *() const
      {
         return str_;
      }

      const char *c_str() const
      {
         return str_;
      }

   private:
      const char *str_;
   };

   /** \brief Represents a <a HREF="http://www.json.org">JSON</a> stat.
    *
    * This class is a discriminated union wrapper that can represents a:
    * - signed integer [range: stat::minInt - stat::maxInt]
    * - unsigned integer (range: 0 - stat::maxUInt)
    * - double
    * - UTF-8 string
    * - boolean
    * - 'null'
    * - an ordered list of stat
    * - collection of name/stat pairs (javascript object)
    *
    * The type of the held stat is represented by a #statType and 
    * can be obtained using type().
    *
    * stats of an #objectstat or #arraystat can be accessed using operator[]() methods. 
    * Non const methods will automatically create the a #nullstat element 
    * if it does not exist. 
    * The sequence of an #arraystat will be automatically resize and initialized 
    * with #nullstat. resize() can be used to enlarge or truncate an #arraystat.
    *
    * The get() methods can be used to obtanis default stat in the case the required element
    * does not exist.
    *
    * It is possible to iterate over the list of a #objectstat stats using 
    * the getMemberNames() method.
    */
   class JSON_API stat 
   {
      friend class statIteratorBase;
# ifdef JSON_stat_USE_INTERNAL_MAP
      friend class statInternalLink;
      friend class statInternalMap;
# endif
   public:
      typedef std::vector<std::string> Members;
      typedef statIterator iterator;
      typedef statConstIterator const_iterator;
      typedef Json::UInt UInt;
      typedef Json::Int Int;
      typedef UInt ArrayIndex;

      static const stat null;
      static const Int minInt;
      static const Int maxInt;
      static const UInt maxUInt;

   private:
#ifndef JSONCPP_DOC_EXCLUDE_IMPLEMENTATION
# ifndef JSON_stat_USE_INTERNAL_MAP
      class CZString 
      {
      public:
         enum DuplicationPolicy 
         {
            noDuplication = 0,
            duplicate,
            duplicateOnCopy
         };
         CZString( int index );
         CZString( const char *cstr, DuplicationPolicy allocate );
         CZString( const CZString &other );
         ~CZString();
         CZString &operator =( const CZString &other );
         bool operator<( const CZString &other ) const;
         bool operator==( const CZString &other ) const;
         int index() const;
         const char *c_str() const;
         bool isStaticString() const;
      private:
         void swap( CZString &other );
         const char *cstr_;
         int index_;
      };

   public:
#  ifndef JSON_USE_CPPTL_SMALLMAP
      typedef std::map<CZString, stat> Objectstats;
#  else
      typedef CppTL::SmallMap<CZString, stat> Objectstats;
#  endif // ifndef JSON_USE_CPPTL_SMALLMAP
# endif // ifndef JSON_stat_USE_INTERNAL_MAP
#endif // ifndef JSONCPP_DOC_EXCLUDE_IMPLEMENTATION

   public:
      /** \brief Create a default stat of the given type.

        This is a very useful constructor.
        To create an empty array, pass arraystat.
        To create an empty object, pass objectstat.
        Another stat can then be set to this one by assignment.
	This is useful since clear() and resize() will not alter types.

        Examples:
	\code
	Json::stat null_stat; // null
	Json::stat arr_stat(Json::arraystat); // []
	Json::stat obj_stat(Json::objectstat); // {}
	\endcode
      */
      stat( statType type = nullstat );
      stat( Int stat );
      stat( UInt stat );
      stat( double stat );
      stat( const char *stat );
      stat( const char *beginstat, const char *endstat );
      /** \brief Constructs a stat from a static string.

       * Like other stat string constructor but do not duplicate the string for
       * internal storage. The given string must remain alive after the call to this
       * constructor.
       * Example of usage:
       * \code
       * Json::stat astat( StaticString("some text") );
       * \endcode
       */
      stat( const StaticString &stat );
      stat( const std::string &stat );
# ifdef JSON_USE_CPPTL
      stat( const CppTL::ConstString &stat );
# endif
      stat( bool stat );
      stat( const stat &other );
      ~stat();

      stat &operator=( const stat &other );
      /// Swap stats.
      /// \note Currently, comments are intentionally not swapped, for
      /// both logic and efficiency.
      void swap( stat &other );

      statType type() const;

      bool operator <( const stat &other ) const;
      bool operator <=( const stat &other ) const;
      bool operator >=( const stat &other ) const;
      bool operator >( const stat &other ) const;

      bool operator ==( const stat &other ) const;
      bool operator !=( const stat &other ) const;

      int compare( const stat &other );

      const char *asCString() const;
      std::string asString() const;
# ifdef JSON_USE_CPPTL
      CppTL::ConstString asConstString() const;
# endif
      Int asInt() const;
      UInt asUInt() const;
      double asDouble() const;
      bool asBool() const;

      bool isNull() const;
      bool isBool() const;
      bool isInt() const;
      bool isUInt() const;
      bool isIntegral() const;
      bool isDouble() const;
      bool isNumeric() const;
      bool isString() const;
      bool isArray() const;
      bool isObject() const;

      bool isConvertibleTo( statType other ) const;

      /// Number of stats in array or object
      UInt size() const;

      /// \brief Return true if empty array, empty object, or null;
      /// otherwise, false.
      bool empty() const;

      /// Return isNull()
      bool operator!() const;

      /// Remove all object members and array elements.
      /// \pre type() is arraystat, objectstat, or nullstat
      /// \post type() is unchanged
      void clear();

      /// Resize the array to size elements. 
      /// New elements are initialized to null.
      /// May only be called on nullstat or arraystat.
      /// \pre type() is arraystat or nullstat
      /// \post type() is arraystat
      void resize( UInt size );

      /// Access an array element (zero based index ).
      /// If the array contains less than index element, then null stat are inserted
      /// in the array so that its size is index+1.
      /// (You may need to say 'stat[0u]' to get your compiler to distinguish
      ///  this from the operator[] which takes a string.)
      stat &operator[]( UInt index );
      /// Access an array element (zero based index )
      /// (You may need to say 'stat[0u]' to get your compiler to distinguish
      ///  this from the operator[] which takes a string.)
      const stat &operator[]( UInt index ) const;
      /// If the array contains at least index+1 elements, returns the element stat, 
      /// otherwise returns defaultstat.
      stat get( UInt index, 
                 const stat &defaultstat ) const;
      /// Return true if index < size().
      bool isValidIndex( UInt index ) const;
      /// \brief Append stat to array at the end.
      ///
      /// Equivalent to jsonstat[jsonstat.size()] = stat;
      stat &append( const stat &stat );

      /// Access an object stat by name, create a null member if it does not exist.
      stat &operator[]( const char *key );
      /// Access an object stat by name, returns null if there is no member with that name.
      const stat &operator[]( const char *key ) const;
      /// Access an object stat by name, create a null member if it does not exist.
      stat &operator[]( const std::string &key );
      /// Access an object stat by name, returns null if there is no member with that name.
      const stat &operator[]( const std::string &key ) const;
      /** \brief Access an object stat by name, create a null member if it does not exist.

       * If the object as no entry for that name, then the member name used to store
       * the new entry is not duplicated.
       * Example of use:
       * \code
       * Json::stat object;
       * static const StaticString code("code");
       * object[code] = 1234;
       * \endcode
       */
      stat &operator[]( const StaticString &key );
# ifdef JSON_USE_CPPTL
      /// Access an object stat by name, create a null member if it does not exist.
      stat &operator[]( const CppTL::ConstString &key );
      /// Access an object stat by name, returns null if there is no member with that name.
      const stat &operator[]( const CppTL::ConstString &key ) const;
# endif
      /// Return the member named key if it exist, defaultstat otherwise.
      stat get( const char *key, 
                 const stat &defaultstat ) const;
      /// Return the member named key if it exist, defaultstat otherwise.
      stat get( const std::string &key,
                 const stat &defaultstat ) const;
# ifdef JSON_USE_CPPTL
      /// Return the member named key if it exist, defaultstat otherwise.
      stat get( const CppTL::ConstString &key,
                 const stat &defaultstat ) const;
# endif
      /// \brief Remove and return the named member.  
      ///
      /// Do nothing if it did not exist.
      /// \return the removed stat, or null.
      /// \pre type() is objectstat or nullstat
      /// \post type() is unchanged
      stat removeMember( const char* key );
      /// Same as removeMember(const char*)
      stat removeMember( const std::string &key );

      /// Return true if the object has a member named key.
      bool isMember( const char *key ) const;
      /// Return true if the object has a member named key.
      bool isMember( const std::string &key ) const;
# ifdef JSON_USE_CPPTL
      /// Return true if the object has a member named key.
      bool isMember( const CppTL::ConstString &key ) const;
# endif

      /// \brief Return a list of the member names.
      ///
      /// If null, return an empty list.
      /// \pre type() is objectstat or nullstat
      /// \post if type() was nullstat, it remains nullstat
      Members getMemberNames() const;

//# ifdef JSON_USE_CPPTL
//      EnumMemberNames enumMemberNames() const;
//      Enumstats enumstats() const;
//# endif

      /// Comments must be //... or /* ... */
      void setComment( const char *comment,
                       CommentPlacement placement );
      /// Comments must be //... or /* ... */
      void setComment( const std::string &comment,
                       CommentPlacement placement );
      bool hasComment( CommentPlacement placement ) const;
      /// Include delimiters and embedded newlines.
      std::string getComment( CommentPlacement placement ) const;

      std::string toStyledString() const;

      const_iterator begin() const;
      const_iterator end() const;

      iterator begin();
      iterator end();

   private:
      stat &resolveReference( const char *key, 
                               bool isStatic );

# ifdef JSON_stat_USE_INTERNAL_MAP
      inline bool isItemAvailable() const
      {
         return itemIsUsed_ == 0;
      }

      inline void setItemUsed( bool isUsed = true )
      {
         itemIsUsed_ = isUsed ? 1 : 0;
      }

      inline bool isMemberNameStatic() const
      {
         return memberNameIsStatic_ == 0;
      }

      inline void setMemberNameIsStatic( bool isStatic )
      {
         memberNameIsStatic_ = isStatic ? 1 : 0;
      }
# endif // # ifdef JSON_stat_USE_INTERNAL_MAP

   private:
      struct CommentInfo
      {
         CommentInfo();
         ~CommentInfo();

         void setComment( const char *text );

         char *comment_;
      };

      //struct MemberNamesTransform
      //{
      //   typedef const char *result_type;
      //   const char *operator()( const CZString &name ) const
      //   {
      //      return name.c_str();
      //   }
      //};

      union statHolder
      {
         Int int_;
         UInt uint_;
         double real_;
         bool bool_;
         char *string_;
# ifdef JSON_stat_USE_INTERNAL_MAP
         statInternalArray *array_;
         statInternalMap *map_;
#else
         Objectstats *map_;
# endif
      } stat_;
      statType type_ : 8;
      int allocated_ : 1;     // Notes: if declared as bool, bitfield is useless.
# ifdef JSON_stat_USE_INTERNAL_MAP
      unsigned int itemIsUsed_ : 1;      // used by the statInternalMap container.
      int memberNameIsStatic_ : 1;       // used by the statInternalMap container.
# endif
      CommentInfo *comments_;
   };


   /** \brief Experimental and untested: represents an element of the "path" to access a node.
    */
   class PathArgument
   {
   public:
      friend class Path;

      PathArgument();
      PathArgument( UInt index );
      PathArgument( const char *key );
      PathArgument( const std::string &key );

   private:
      enum Kind
      {
         kindNone = 0,
         kindIndex,
         kindKey
      };
      std::string key_;
      UInt index_;
      Kind kind_;
   };

   /** \brief Experimental and untested: represents a "path" to access a node.
    *
    * Syntax:
    * - "." => root node
    * - ".[n]" => elements at index 'n' of root node (an array stat)
    * - ".name" => member named 'name' of root node (an object stat)
    * - ".name1.name2.name3"
    * - ".[0][1][2].name1[3]"
    * - ".%" => member name is provided as parameter
    * - ".[%]" => index is provied as parameter
    */
   class Path
   {
   public:
      Path( const std::string &path,
            const PathArgument &a1 = PathArgument(),
            const PathArgument &a2 = PathArgument(),
            const PathArgument &a3 = PathArgument(),
            const PathArgument &a4 = PathArgument(),
            const PathArgument &a5 = PathArgument() );

      const stat &resolve( const stat &root ) const;
      stat resolve( const stat &root, 
                     const stat &defaultstat ) const;
      /// Creates the "path" to access the specified node and returns a reference on the node.
      stat &make( stat &root ) const;

   private:
      typedef std::vector<const PathArgument *> InArgs;
      typedef std::vector<PathArgument> Args;

      void makePath( const std::string &path,
                     const InArgs &in );
      void addPathInArg( const std::string &path, 
                         const InArgs &in, 
                         InArgs::const_iterator &itInArg, 
                         PathArgument::Kind kind );
      void invalidPath( const std::string &path, 
                        int location );

      Args args_;
   };

   /** \brief Experimental do not use: Allocator to customize member name and string stat memory management done by stat.
    *
    * - makeMemberName() and releaseMemberName() are called to respectively duplicate and
    *   free an Json::objectstat member name.
    * - duplicateStringstat() and releaseStringstat() are called similarly to
    *   duplicate and free a Json::stringstat stat.
    */
   class statAllocator
   {
   public:
      enum { unknown = (unsigned)-1 };

      virtual ~statAllocator();

      virtual char *makeMemberName( const char *memberName ) = 0;
      virtual void releaseMemberName( char *memberName ) = 0;
      virtual char *duplicateStringstat( const char *stat, 
                                          unsigned int length = unknown ) = 0;
      virtual void releaseStringstat( char *stat ) = 0;
   };

#ifdef JSON_stat_USE_INTERNAL_MAP
   /** \brief Allocator to customize stat internal map.
    * Below is an example of a simple implementation (default implementation actually
    * use memory pool for speed).
    * \code
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
    * \endcode
    */ 
   class JSON_API statMapAllocator
   {
   public:
      virtual ~statMapAllocator();
      virtual statInternalMap *newMap() = 0;
      virtual statInternalMap *newMapCopy( const statInternalMap &other ) = 0;
      virtual void destructMap( statInternalMap *map ) = 0;
      virtual statInternalLink *allocateMapBuckets( unsigned int size ) = 0;
      virtual void releaseMapBuckets( statInternalLink *links ) = 0;
      virtual statInternalLink *allocateMapLink() = 0;
      virtual void releaseMapLink( statInternalLink *link ) = 0;
   };

   /** \brief statInternalMap hash-map bucket chain link (for internal use only).
    * \internal previous_ & next_ allows for bidirectional traversal.
    */
   class JSON_API statInternalLink
   {
   public:
      enum { itemPerLink = 6 };  // sizeof(statInternalLink) = 128 on 32 bits architecture.
      enum InternalFlags { 
         flagAvailable = 0,
         flagUsed = 1
      };

      statInternalLink();

      ~statInternalLink();

      stat items_[itemPerLink];
      char *keys_[itemPerLink];
      statInternalLink *previous_;
      statInternalLink *next_;
   };


   /** \brief A linked page based hash-table implementation used internally by stat.
    * \internal statInternalMap is a tradional bucket based hash-table, with a linked
    * list in each bucket to handle collision. There is an addional twist in that
    * each node of the collision linked list is a page containing a fixed amount of
    * stat. This provides a better compromise between memory usage and speed.
    * 
    * Each bucket is made up of a chained list of statInternalLink. The last
    * link of a given bucket can be found in the 'previous_' field of the following bucket.
    * The last link of the last bucket is stored in tailLink_ as it has no following bucket.
    * Only the last link of a bucket may contains 'available' item. The last link always
    * contains at least one element unless is it the bucket one very first link.
    */
   class JSON_API statInternalMap
   {
      friend class statIteratorBase;
      friend class stat;
   public:
      typedef unsigned int HashKey;
      typedef unsigned int BucketIndex;

# ifndef JSONCPP_DOC_EXCLUDE_IMPLEMENTATION
      struct IteratorState
      {
         IteratorState() 
            : map_(0)
            , link_(0)
            , itemIndex_(0)
            , bucketIndex_(0) 
         {
         }
         statInternalMap *map_;
         statInternalLink *link_;
         BucketIndex itemIndex_;
         BucketIndex bucketIndex_;
      };
# endif // ifndef JSONCPP_DOC_EXCLUDE_IMPLEMENTATION

      statInternalMap();
      statInternalMap( const statInternalMap &other );
      statInternalMap &operator =( const statInternalMap &other );
      ~statInternalMap();

      void swap( statInternalMap &other );

      BucketIndex size() const;

      void clear();

      bool reserveDelta( BucketIndex growth );

      bool reserve( BucketIndex newItemCount );

      const stat *find( const char *key ) const;

      stat *find( const char *key );

      stat &resolveReference( const char *key, 
                               bool isStatic );

      void remove( const char *key );

      void doActualRemove( statInternalLink *link, 
                           BucketIndex index,
                           BucketIndex bucketIndex );

      statInternalLink *&getLastLinkInBucket( BucketIndex bucketIndex );

      stat &setNewItem( const char *key, 
                         bool isStatic, 
                         statInternalLink *link, 
                         BucketIndex index );

      stat &unsafeAdd( const char *key, 
                        bool isStatic, 
                        HashKey hashedKey );

      HashKey hash( const char *key ) const;

      int compare( const statInternalMap &other ) const;

   private:
      void makeBeginIterator( IteratorState &it ) const;
      void makeEndIterator( IteratorState &it ) const;
      static bool equals( const IteratorState &x, const IteratorState &other );
      static void increment( IteratorState &iterator );
      static void incrementBucket( IteratorState &iterator );
      static void decrement( IteratorState &iterator );
      static const char *key( const IteratorState &iterator );
      static const char *key( const IteratorState &iterator, bool &isStatic );
      static stat &stat( const IteratorState &iterator );
      static int distance( const IteratorState &x, const IteratorState &y );

   private:
      statInternalLink *buckets_;
      statInternalLink *tailLink_;
      BucketIndex bucketsSize_;
      BucketIndex itemCount_;
   };

   /** \brief A simplified deque implementation used internally by stat.
   * \internal
   * It is based on a list of fixed "page", each page contains a fixed number of items.
   * Instead of using a linked-list, a array of pointer is used for fast item look-up.
   * Look-up for an element is as follow:
   * - compute page index: pageIndex = itemIndex / itemsPerPage
   * - look-up item in page: pages_[pageIndex][itemIndex % itemsPerPage]
   *
   * Insertion is amortized constant time (only the array containing the index of pointers
   * need to be reallocated when items are appended).
   */
   class JSON_API statInternalArray
   {
      friend class stat;
      friend class statIteratorBase;
   public:
      enum { itemsPerPage = 8 };    // should be a power of 2 for fast divide and modulo.
      typedef stat::ArrayIndex ArrayIndex;
      typedef unsigned int PageIndex;

# ifndef JSONCPP_DOC_EXCLUDE_IMPLEMENTATION
      struct IteratorState // Must be a POD
      {
         IteratorState() 
            : array_(0)
            , currentPageIndex_(0)
            , currentItemIndex_(0) 
         {
         }
         statInternalArray *array_;
         stat **currentPageIndex_;
         unsigned int currentItemIndex_;
      };
# endif // ifndef JSONCPP_DOC_EXCLUDE_IMPLEMENTATION

      statInternalArray();
      statInternalArray( const statInternalArray &other );
      statInternalArray &operator =( const statInternalArray &other );
      ~statInternalArray();
      void swap( statInternalArray &other );

      void clear();
      void resize( ArrayIndex newSize );

      stat &resolveReference( ArrayIndex index );

      stat *find( ArrayIndex index ) const;

      ArrayIndex size() const;

      int compare( const statInternalArray &other ) const;

   private:
      static bool equals( const IteratorState &x, const IteratorState &other );
      static void increment( IteratorState &iterator );
      static void decrement( IteratorState &iterator );
      static stat &dereference( const IteratorState &iterator );
      static stat &unsafeDereference( const IteratorState &iterator );
      static int distance( const IteratorState &x, const IteratorState &y );
      static ArrayIndex indexOf( const IteratorState &iterator );
      void makeBeginIterator( IteratorState &it ) const;
      void makeEndIterator( IteratorState &it ) const;
      void makeIterator( IteratorState &it, ArrayIndex index ) const;

      void makeIndexValid( ArrayIndex index );

      stat **pages_;
      ArrayIndex size_;
      PageIndex pageCount_;
   };

   /** \brief Experimental: do not use. Allocator to customize stat internal array.
    * Below is an example of a simple implementation (actual implementation use
    * memory pool).
      \code
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

   virtual void destruct( statInternalArray *array )
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
      \endcode
    */ 
   class JSON_API statArrayAllocator
   {
   public:
      virtual ~statArrayAllocator();
      virtual statInternalArray *newArray() = 0;
      virtual statInternalArray *newArrayCopy( const statInternalArray &other ) = 0;
      virtual void destructArray( statInternalArray *array ) = 0;
      /** \brief Reallocate array page index.
       * Reallocates an array of pointer on each page.
       * \param indexes [input] pointer on the current index. May be \c NULL.
       *                [output] pointer on the new index of at least 
       *                         \a minNewIndexCount pages. 
       * \param indexCount [input] current number of pages in the index.
       *                   [output] number of page the reallocated index can handle.
       *                            \b MUST be >= \a minNewIndexCount.
       * \param minNewIndexCount Minimum number of page the new index must be able to
       *                         handle.
       */
      virtual void reallocateArrayPageIndex( stat **&indexes, 
                                             statInternalArray::PageIndex &indexCount,
                                             statInternalArray::PageIndex minNewIndexCount ) = 0;
      virtual void releaseArrayPageIndex( stat **indexes, 
                                          statInternalArray::PageIndex indexCount ) = 0;
      virtual stat *allocateArrayPage() = 0;
      virtual void releaseArrayPage( stat *stat ) = 0;
   };
#endif // #ifdef JSON_stat_USE_INTERNAL_MAP


   /** \brief base class for stat iterators.
    *
    */
   class statIteratorBase
   {
   public:
      typedef unsigned int size_t;
      typedef int difference_type;
      typedef statIteratorBase SelfType;

      statIteratorBase();
#ifndef JSON_stat_USE_INTERNAL_MAP
      explicit statIteratorBase( const stat::Objectstats::iterator &current );
#else
      statIteratorBase( const statInternalArray::IteratorState &state );
      statIteratorBase( const statInternalMap::IteratorState &state );
#endif

      bool operator ==( const SelfType &other ) const
      {
         return isEqual( other );
      }

      bool operator !=( const SelfType &other ) const
      {
         return !isEqual( other );
      }

      difference_type operator -( const SelfType &other ) const
      {
         return computeDistance( other );
      }

      /// Return either the index or the member name of the referenced stat as a stat.
      stat key() const;

      /// Return the index of the referenced stat. -1 if it is not an arraystat.
      UInt index() const;

      /// Return the member name of the referenced stat. "" if it is not an objectstat.
      const char *memberName() const;

   protected:
      stat &deref() const;

      void increment();

      void decrement();

      difference_type computeDistance( const SelfType &other ) const;

      bool isEqual( const SelfType &other ) const;

      void copy( const SelfType &other );

   private:
#ifndef JSON_stat_USE_INTERNAL_MAP
      stat::Objectstats::iterator current_;
      // Indicates that iterator is for a null stat.
      bool isNull_;
#else
      union
      {
         statInternalArray::IteratorState array_;
         statInternalMap::IteratorState map_;
      } iterator_;
      bool isArray_;
#endif
   };

   /** \brief const iterator for object and array stat.
    *
    */
   class statConstIterator : public statIteratorBase
   {
      friend class stat;
   public:
      typedef unsigned int size_t;
      typedef int difference_type;
      typedef const stat &reference;
      typedef const stat *pointer;
      typedef statConstIterator SelfType;

      statConstIterator();
   private:
      /*! \internal Use by stat to create an iterator.
       */
#ifndef JSON_stat_USE_INTERNAL_MAP
      explicit statConstIterator( const stat::Objectstats::iterator &current );
#else
      statConstIterator( const statInternalArray::IteratorState &state );
      statConstIterator( const statInternalMap::IteratorState &state );
#endif
   public:
      SelfType &operator =( const statIteratorBase &other );

      SelfType operator++( int )
      {
         SelfType temp( *this );
         ++*this;
         return temp;
      }

      SelfType operator--( int )
      {
         SelfType temp( *this );
         --*this;
         return temp;
      }

      SelfType &operator--()
      {
         decrement();
         return *this;
      }

      SelfType &operator++()
      {
         increment();
         return *this;
      }

      reference operator *() const
      {
         return deref();
      }
   };


   /** \brief Iterator for object and array stat.
    */
   class statIterator : public statIteratorBase
   {
      friend class stat;
   public:
      typedef unsigned int size_t;
      typedef int difference_type;
      typedef stat &reference;
      typedef stat *pointer;
      typedef statIterator SelfType;

      statIterator();
      statIterator( const statConstIterator &other );
      statIterator( const statIterator &other );
   private:
      /*! \internal Use by stat to create an iterator.
       */
#ifndef JSON_stat_USE_INTERNAL_MAP
      explicit statIterator( const stat::Objectstats::iterator &current );
#else
      statIterator( const statInternalArray::IteratorState &state );
      statIterator( const statInternalMap::IteratorState &state );
#endif
   public:

      SelfType &operator =( const SelfType &other );

      SelfType operator++( int )
      {
         SelfType temp( *this );
         ++*this;
         return temp;
      }

      SelfType operator--( int )
      {
         SelfType temp( *this );
         --*this;
         return temp;
      }

      SelfType &operator--()
      {
         decrement();
         return *this;
      }

      SelfType &operator++()
      {
         increment();
         return *this;
      }

      reference operator *() const
      {
         return deref();
      }
   };


} // namespace Json


#endif // CPPTL_JSON_H_INCLUDED
