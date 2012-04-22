#include "parser.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
   Args* args = new Args();
   args->ParseArgs(argc, argv);
   printf("%d\n", args->HasOption("bob"));
   exit(EXIT_SUCCESS);
}
