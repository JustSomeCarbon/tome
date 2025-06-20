/**
 * GATE ::
 * creates gate points within the file tree to enable quick movement
 * between different locations.
 */

#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "gate.h"

char* gate_file = ".gatefile";

int main(int argc, char* argv[]) {
  if (argc == 1) {
    usage();
    return 0;
  }

  for (int param = 1; param < argc; param++) {
    if (argv[param][0] == '-') {
      int n = 1;
      char cur = argv[param][n];
      int break_flag = 0;
      while(cur && !break_flag) {
        switch (cur) {
          case 'h':
            help();
            return 0;
          case 'l':
            list_gates();
            break;
          case 'c':
            if ((param+1) >= argc) {
              // crate gate with cwd
              char cwd[PATH_MAX];
              if (getcwd(cwd, sizeof(cwd)) == NULL) {
                printf("Error: Unable to obtain current working directory\n\n");
                return 1;
              }
              printf("%s\n", cwd);
            } else if (argv[param+1][0] == '-') {
              // create gate with cwd
              char cwd[PATH_MAX];
              if (getcwd(cwd, sizeof(cwd)) == NULL) {
                printf("Error: Unable to obtain current working directory\n\n");
                return 1;
              }
              printf("%s\n", cwd);
            } else {
              // create gate with given path
              //create_gate(argv[param+1]);
              printf("path given: %s\n", argv[param+1]);
              break_flag = 1;
            }
            break;
          case 'd':
            break_flag = 1;
            break;
          case 'x':
            break_flag = 1;
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

void usage() {
  printf("GATE::\n");
  printf(" Filesystem movement system\n");
  printf(" Create gates within file systems that allow you to maneuver between different gate points quickly\n");
  printf("\t$ gate -[flags] [filepath]\n\n");
}

void help() {
  printf("GATE::\n");
  printf("\tDictates gate points within the file system.\n");
  printf(" Flags::\n");
  printf("\t-h : prints help information for gate\n");
  printf("\t-l : lists all gate endpoints within the gate file\n");
  printf("\t-c : creates a new gate point in the specified directory\n");
  printf("\t-d : takes a gate tag and deletes it from the gate list\n");
  printf("\t-x : delete all gate tags from the gate list\n");
  
  printf("\n\n");
}

void list_gates() {
  FILE* file = fopen(gate_file, "r");
  if (!file) {
    printf("Error: no gatefile exists\n");
    printf("\tAdd a gate using the -c flag");
  }

  fclose(file);
}

char generate_letter() {
  int letter_index = rand() % 27;
  return (char)(letter_index + 97);
}

char* generate_tag() {
  char* tag = (char*)malloc(sizeof(char) * 4);

  for (int t = 0; t < 3; t++) {
    tag[t] = generate_letter();
  }
  
  return tag;
}
