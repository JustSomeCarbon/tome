/**
 * BLINK::
 * enables the movement of the current working 
 * directory to registered gate endpoints.
 */

#include <stdio.h>

#include "blink.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    usage();
    return 0;
  }

  return 0;
}

void usage() {
  printf("BLINK::\n");
  printf(" Filesystem movement tool\n");
  printf(" Maneuver between different registered gates\n");
  printf("\t$blnk -[flags] [gate tag]\n\n");
}
