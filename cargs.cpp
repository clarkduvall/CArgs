#include "cargs.h"

#include <cstdlib>
#include <string.h>
#include <vector>
#include <map>
#include <string>

// static
bool CArgs::isNum(const char* str) {
   for (size_t i = 0; i < strlen(str); i++) {
      if (str[i] != '0' && str[i] != '.')
         return false;
   }
   return true;
}

void CArgs::Parse(int argc, char* argv[]) {
   Parse(argc, (const char**)argv);
}

void CArgs::Parse(int argc, const char* argv[]) {
   double val = 0;
   std::string to_insert;
   size_t pos = to_insert.npos;
   for (int i = 1; i < argc; i++) {
      switch (argv[i][0]) {
      case '-':
         val = 0;
         if (argv[i][1] == '-') {
            // Argument of long form (--example).
            to_insert = &argv[i][2];
         }
         else if (strlen(argv[i]) > 2) {
            // Multiple arguments of short form (-abc).
            for (size_t j = 1; j < strlen(argv[i]); j++) {
               to_insert = argv[i][j];
               map_.insert(ArgPair(to_insert, 0.0));
            }
            break;
         }
         else {
            // Single argument of short form (-a).
            to_insert = argv[i][1];
         }
         // Get value of arg if provided.
         if ((pos = to_insert.find("=")) != to_insert.npos) {
            std::string num = to_insert.substr(pos + 1);
            val = atof(num.c_str());
            to_insert.erase(pos);
         }
         else if (i + 1 < argc) {
            val = atof(argv[i + 1]);
         }
         map_.erase(to_insert);
         map_.insert(ArgPair(to_insert, val));
         // If value is found, increment argument index.
         if (pos == to_insert.npos && (val != 0.0 ||
             (i + 1 < argc && val == 0.0 && isNum(argv[i + 1]))))
            i++;
         break;
      default:
         vec_.push_back(argv[i]);
         break;
      }
   }
}

void CArgs::SetDefault(const std::string& c, double v) {
   map_.insert(ArgPair(c, v));
}

void CArgs::SetDefault(const std::string& c, int v) {
   SetDefault(c, (double)v);
}

bool CArgs::HasOption(const std::string& c) {
   return map_.find(c) != map_.end();
}

double CArgs::GetDouble(const std::string& c) {
   if (map_.find(c) == map_.end())
      return 0.0;
   return map_[c];
}

int CArgs::GetInt(const std::string& c) {
   return (int)GetDouble(c);
}

const char* CArgs::GetArg(int i) {
   if (vec_.size() <= (size_t)i)
      return NULL;
   return vec_[i];
}

int CArgs::GetArgNum() {
   return (int)vec_.size();
}
