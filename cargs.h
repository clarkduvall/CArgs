#ifndef _PARSER_H
#define _PARSER_H

#include <map>
#include <vector>
#include <string>

typedef std::map<std::string, double> ArgMap;
typedef std::pair<std::string, double> ArgPair;
typedef std::vector<const char*> ArgVec;

class CArgs {
  public:
   CArgs() {}
   ~CArgs() {}

   // Parses command line arguments.
   // |map| a mapping of characters to doubles which is used to determine
   // if a -x option is specified. If the option has a value after it then
   // this is stored in the map. Default values can be put in before |Parse|
   // is called.
   // |vec| a vector of the options that do not begin with a '-'
   void Parse(int argc, char** argv);
   void Parse(int argc, const char** argv);

   // Set default arguments.
   void SetDefault(const std::string& c, double v);
   void SetDefault(const std::string& c, int v);

   // Determines if a '-' or '--' option was specified.
   bool HasOption(const std::string& c);

   // Get '-' or '--' option values, or 0 if they don't have a value set.
   double GetDouble(const std::string& c);
   int GetInt(const std::string& c);

   // Get an arg that does not start with a '-' at the specified index.
   const char* GetArg(int i);

   // Get how many non '-' args there were.
   int GetArgNum();

  private:
   // Check if an arg is a num. Needed because |atof()| returns 0.0 if it
   // cannot parse the argument.
   static bool isNum(const char* str);
   ArgMap map_;
   ArgVec vec_;
};

#endif
