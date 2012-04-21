#include "parser.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
   Args* args = new Args();
   args->ParseArgs(argc, argv);
   exit(EXIT_SUCCESS);
}
