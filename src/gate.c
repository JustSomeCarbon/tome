/**
 * GATE ::
 * creates gate points within the file tree to enable quick movement
 * between different locations.
 */

#include <stdio.h>

#include "gate.h"

int main(int argc, char* argv[]) {
  for (int param = 1; param < argc; param++) {
    if (argv[param][0] == '-') {
      int n = 1;
      char cur = argv[param][n];
      while(cur) {
        switch (cur) {
          case 'h':
            help();
            break;
          default:
            printf("Error: unknown flag %c\n", cur);
            continue;
        }
        n++;
        cur = argv[param][n];
      }
    }
  }

  return 0;
}

void help() {
  printf("GATE::\n");
  printf(" Filesystem movement system\n");
  printf(" Create gates within file systems that allow you to maneuver between different gate points quickly\n");
  printf("\t$ gate -[flags] [filepath]\n\n");
}
