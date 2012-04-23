#include "cargs.h"

#include <cstdlib>
#include <string.h>
#include <vector>
#include <map>
#include <string>

// static
bool CArgs::isNum(const char* str) {
   for (int i = 0; i < strlen(str); i++) {
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
   for (int i = 1; i < argc; i++) {
      switch (argv[i][0]) {
      case '-':
         val = 0;
         if (argv[i][1] == '-') {
            to_insert = &argv[i][2];
         }
         else if (strlen(argv[i]) > 2) {
            for (int j = 1; j < strlen(argv[i]); j++) {
               to_insert = argv[i][j];
               map_.insert(ArgPair(to_insert, 0.0));
            }
            break;
         }
         else {
            to_insert = argv[i][1];
         }
         if (i + 1 < argc)
            val = atof(argv[i + 1]);
         map_.erase(to_insert);
         map_.insert(ArgPair(to_insert, val));
         if (val != 0.0 || (i + 1 < argc && val == 0.0 && isNum(argv[i + 1])))
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
   double val = 0.0;
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
