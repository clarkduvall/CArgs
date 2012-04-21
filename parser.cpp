#include "parser.h"

#include <cstdlib>
#include <string.h>
#include <vector>
#include <map>

// static
bool Args::isNum(const char* str) {
   for (int i = 0; i < strlen(str); i++) {
      if (str[i] != '0' && str[i] != '.')
         return false;
   }
   return true;
}

void Args::ParseArgs(int argc, char* argv[]) {
   double val = 0;
   for (int i = 1; i < argc; i++) {
      switch (argv[i][0]) {
      case '-':
         if (strlen(argv[i]) > 2) {
            for (int j = 1; j < strlen(argv[i]); j++)
               map_.insert(ArgPair(argv[i][j], 0.0));
            break;
         }
         val = 0;
         if (i + 1 < argc)
            val = atof(argv[i + 1]);
         map_.erase(argv[i][1]);
         map_.insert(ArgPair(argv[i][1], val));
         if (val != 0.0 || (i + 1 < argc && val == 0.0 && isNum(argv[i + 1])))
            i++;
         break;
      default:
         vec_.push_back(argv[i]);
         break;
      }
   }
}

void Args::SetDefault(char c, double v) {
   map_.insert(ArgPair(c, v));
}

void Args::SetDefault(char c, int v) {
   SetDefault(c, (double)v);
}

bool Args::HasOption(char c) {
   return map_.find(c) != map_.end();
}

double Args::GetDouble(char c) {
   double val = 0.0;
   if (map_.find(c) == map_.end())
      return 0.0;
   return map_[c];
}

int Args::GetInt(char c) {
   return (int)GetDouble(c);
}

char* Args::GetArg(int i) {
   if (vec_.size() <= (size_t)i)
      return NULL;
   return vec_[i];
}

int Args::GetArgNum() {
   return (int)vec_.size();
}
