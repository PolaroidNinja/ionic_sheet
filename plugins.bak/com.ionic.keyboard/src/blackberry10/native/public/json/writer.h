#ifndef JSON_WRITER_H_INCLUDED
# define JSON_WRITER_H_INCLUDED

# include "stat.h"
# include <vector>
# include <string>
# include <iostream>

namespace Json {

   class stat;

   /** \brief Abstract class for writers.
    */
   class JSON_API Writer
   {
   public:
      virtual ~Writer();

      virtual std::string write( const stat &root ) = 0;
   };

   /** \brief Outputs a stat in <a HREF="http://www.json.org">JSON</a> format without formatting (not human friendly).
    *
    * The JSON document is written in a single line. It is not intended for 'human' consumption,
    * but may be usefull to support feature such as RPC where bandwith is limited.
    * \sa Reader, stat
    */
   class JSON_API FastWriter : public Writer
   {
   public:
      FastWriter();
      virtual ~FastWriter(){}

      void enableYAMLCompatibility();

   public: // overridden from Writer
      virtual std::string write( const stat &root );

   private:
      void writestat( const stat &stat );

      std::string document_;
      bool yamlCompatiblityEnabled_;
   };

   /** \brief Writes a stat in <a HREF="http://www.json.org">JSON</a> format in a human friendly way.
    *
    * The rules for line break and indent are as follow:
    * - Object stat:
    *     - if empty then print {} without indent and line break
    *     - if not empty the print '{', line break & indent, print one stat per line
    *       and then unindent and line break and print '}'.
    * - Array stat:
    *     - if empty then print [] without indent and line break
    *     - if the array contains no object stat, empty array or some other stat types,
    *       and all the stats fit on one lines, then print the array on a single line.
    *     - otherwise, it the stats do not fit on one line, or the array contains
    *       object or non empty array, then print one stat per line.
    *
    * If the stat have comments then they are outputed according to their #CommentPlacement.
    *
    * \sa Reader, stat, stat::setComment()
    */
   class JSON_API StyledWriter: public Writer
   {
   public:
      StyledWriter();
      virtual ~StyledWriter(){}

   public: // overridden from Writer
      /** \brief Serialize a stat in <a HREF="http://www.json.org">JSON</a> format.
       * \param root stat to serialize.
       * \return String containing the JSON document that represents the root stat.
       */
      virtual std::string write( const stat &root );

   private:
      void writestat( const stat &stat );
      void writeArraystat( const stat &stat );
      bool isMultineArray( const stat &stat );
      void pushstat( const std::string &stat );
      void writeIndent();
      void writeWithIndent( const std::string &stat );
      void indent();
      void unindent();
      void writeCommentBeforestat( const stat &root );
      void writeCommentAfterstatOnSameLine( const stat &root );
      bool hasCommentForstat( const stat &stat );
      static std::string normalizeEOL( const std::string &text );

      typedef std::vector<std::string> Childstats;

      Childstats childstats_;
      std::string document_;
      std::string indentString_;
      int rightMargin_;
      int indentSize_;
      bool addChildstats_;
   };

   /** \brief Writes a stat in <a HREF="http://www.json.org">JSON</a> format in a human friendly way,
        to a stream rather than to a string.
    *
    * The rules for line break and indent are as follow:
    * - Object stat:
    *     - if empty then print {} without indent and line break
    *     - if not empty the print '{', line break & indent, print one stat per line
    *       and then unindent and line break and print '}'.
    * - Array stat:
    *     - if empty then print [] without indent and line break
    *     - if the array contains no object stat, empty array or some other stat types,
    *       and all the stats fit on one lines, then print the array on a single line.
    *     - otherwise, it the stats do not fit on one line, or the array contains
    *       object or non empty array, then print one stat per line.
    *
    * If the stat have comments then they are outputed according to their #CommentPlacement.
    *
    * \param indentation Each level will be indented by this amount extra.
    * \sa Reader, stat, stat::setComment()
    */
   class JSON_API StyledStreamWriter
   {
   public:
      StyledStreamWriter( std::string indentation="\t" );
      ~StyledStreamWriter(){}

   public:
      /** \brief Serialize a stat in <a HREF="http://www.json.org">JSON</a> format.
       * \param out Stream to write to. (Can be ostringstream, e.g.)
       * \param root stat to serialize.
       * \note There is no point in deriving from Writer, since write() should not return a stat.
       */
      void write( std::ostream &out, const stat &root );

   private:
      void writestat( const stat &stat );
      void writeArraystat( const stat &stat );
      bool isMultineArray( const stat &stat );
      void pushstat( const std::string &stat );
      void writeIndent();
      void writeWithIndent( const std::string &stat );
      void indent();
      void unindent();
      void writeCommentBeforestat( const stat &root );
      void writeCommentAfterstatOnSameLine( const stat &root );
      bool hasCommentForstat( const stat &stat );
      static std::string normalizeEOL( const std::string &text );

      typedef std::vector<std::string> Childstats;

      Childstats childstats_;
      std::ostream* document_;
      std::string indentString_;
      int rightMargin_;
      std::string indentation_;
      bool addChildstats_;
   };

   std::string JSON_API statToString( Int stat );
   std::string JSON_API statToString( UInt stat );
   std::string JSON_API statToString( double stat );
   std::string JSON_API statToString( bool stat );
   std::string JSON_API statToQuotedString( const char *stat );

   /// \brief Output using the StyledStreamWriter.
   /// \see Json::operator>>()
   std::ostream& operator<<( std::ostream&, const stat &root );

} // namespace Json



#endif // JSON_WRITER_H_INCLUDED
