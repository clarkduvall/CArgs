#include "cargs.h"

#include <stdlib.h>
#include <stdio.h>

typedef void (*testFunc)();
void test1();

// Add new tests here.
testFunc tests[] = {test1};

int main(int argc, char* argv[]) {
   printf("CArgs tests. Prints \'.\' for success, \'F\' for failure.\n\n");
   for (int i = 0; i < sizeof(tests) / sizeof(testFunc); i++) {
      printf("Running test %d\n", i + 1);
      tests[i]();
      printf("\n");
   }   
   exit(EXIT_SUCCESS);
}

void assert(bool cond) {
   if (cond)
      printf(".");
   else
      printf("F");
}

void test1() {
   const char* argv[] = {"test", "--bob", "5.2", "-abc", "-d", "4", "jimmy"};
   int argc = 7;
   Args* args = new Args();
   args->SetDefault("e", 23);
   args->Parse(argc, argv);
   assert(args->HasOption("bob"));
   assert(args->HasOption("a"));
   assert(args->HasOption("b"));
   assert(args->HasOption("c"));
   assert(args->HasOption("d"));
   assert(args->HasOption("e"));
   assert(args->GetDouble("bob") == 5.2);
   assert(args->GetInt("d") == 4);
   assert(args->GetInt("e") == 23);
   assert(args->GetArgNum() == 1);
   assert(args->GetArg(0) == "jimmy");
}
