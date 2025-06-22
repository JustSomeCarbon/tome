/**
 * GATE ::
 * creates gate points within the file tree to enable quick movement
 * between different locations.
 */

#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
							create_gate(cwd);
              printf("%s\n", cwd);
            } else if (argv[param+1][0] == '-') {
              // create gate with cwd
              char cwd[PATH_MAX];
              if (getcwd(cwd, sizeof(cwd)) == NULL) {
                printf("Error: Unable to obtain current working directory\n\n");
                return 1;
              }
							create_gate(cwd);
              printf("%s\n", cwd);
            } else {
              // create gate with given path
              create_gate(argv[param+1]);
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
		return;
  }

	char* line = NULL;
	size_t line_len = 0;

	while (getline(&line, &line_len, file) != -1) {
		printf("%s\n", line);
		printf("----\n");
	}
	
	free(line);
  fclose(file);
}

char generate_letter() {
  int letter_index = rand() % 26;
  return (char)(letter_index + 97);
}

char* generate_tag() {
  char* tag = (char*)malloc(sizeof(char) * 4);

  for (int t = 0; t < 3; t++) {
    tag[t] = generate_letter();
  }
  
  return tag;
}

int check_tag_collision(char *tag) {
	FILE* file = fopen(gate_file, "r");
	if (!file) {
		printf("Error: unable to open gatefile to read\n\n");
		exit(-1);
	}

	char* line = (char*)malloc(PATH_MAX + 6);
	size_t line_len = 0;

	while (getline(&line, &line_len, file) != -1) {
		char obtained_tag[4];
		if (!strncpy(obtained_tag, line, 3)) {
			printf("Error, unable to obtain tag from line: %s\n\n", line);
			exit(-1);
		}
		obtained_tag[3] = '\0';

		if (strcmp(tag, obtained_tag) == 0) {
			// tag cllision
			fclose(file);
			free(line);
			return 1;
		}
	}

	// no collision
	fclose(file);
	free(line);
	return 0;
}

int create_gate(char *path) {
	FILE* file = fopen(gate_file, "a+");
	if (!file) {
		printf("Error: unable to create and open the gatefile\n\n");
		exit(1);
	}

	srand(time(NULL));
	char* tag = generate_tag();
	while (check_tag_collision(tag)) {
		free(tag);
		tag = generate_tag();
	}
	
	// append the path and tag to the gatefile
	fputs(tag, file);
	fputs(",", file);
	fputs(path, file);
	fputs("\n", file);

	fclose(file);
	free(tag);
	return 0;
}

int delete_gate(char *tag) {
	FILE* old_file = fopen(gate_file, "r");
	if (!old_file) {
		printf("Error: Unable to open gatefile\n");
		printf("\tEnsure gate file exists\n\n");
		return 1;
	}
	FILE* new_file = fopen(".new_gates", "w");
	if (!new_file) {
		printf("Error: unable to create new gate file\n");
		return 1;
	}

	char* line;
	size_t line_len = 0;

	while(getline(&line, &line_len, old_file) != -1) {
		char obtained_tag[4];
		if (!strncpy(obtained_tag, line, 3)) {
			// something went wrong, remove artifacts
			free(line);
			fclose(old_file);
			fclose(new_file);
			remove(".new_gates");
			printf("Error: cannot obtain tag from: %s\n", line);
			printf("\tEnsure data of gate file has not been altered or corrupted\n\n");
			exit(-1);
		}
		obtained_tag[3] = '\0';
		if (strcmp(obtained_tag, tag) != 0) {
			fputs(line, new_file);
		}
	}
	free(line);
	fclose(old_file);
	fclose(new_file);

	// overwrite the gate file
	rename(".new_gates", gate_file);

	return 0;
}
