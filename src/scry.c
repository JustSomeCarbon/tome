/**
 * Takes a file name as an argument and gives
 * some information back.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include "scry.h"


int main(int argc, char* argv[]) {
  if (argc < 2) {
    usage();
  }

  for (int param = 1; param < argc; param++) {
    if (argv[param][0] == '-') {
      int n = 1;
      char cur = argv[param][n];
      while (cur) {
        switch (cur) {
          case 'h':
            help();
            return 0;
          case 's':
            short_fl = 1;
            break;
          default:
            printf("Unknown flag: %c\n", cur);
            break;
        }
        n++;
        cur = argv[param][n];
      }
    }
  }

  if (argv[argc-1][0] == '-') {
    usage();
    return -1;
  }

  struct stat stats;

  if (stat(argv[argc-1], &stats) != 0) {
    // file does not exist or something
    // went wrong
    printf("Error: unable to obtain file properties\n  Ensure %s exitst\n\n", argv[1]);
    return -1;
  }

  if (stats.st_mode & S_IFDIR) // DIRECTORY
  {
		handle_dir(argv[argc-1]);
  } else if (stats.st_mode & S_IFREG) // FILE
  {
    handle_file(argv[argc-1], stats);
  } else
  {
    printf("TODO: something else\n");
  }

  return 0;
}

void usage() {
  printf("Scry::\n\tInformational system");
  printf(" usage: $ scry -[flags] [filepath]\n\n");
}

void help() {
  printf("SCRY::\n");
  printf("\tPrints file information to the console. ");
  printf("Describes information for files and directories.\n");
  printf(" Flags::\n");
  printf("\t-s : prints file information in short format\n");

  printf("\n\n");
}

void handle_file(char *filename, struct stat stats) {
  if (short_fl) {
    print_file_props_short(filename, stats);
  } else {
    print_file_props(filename, stats);
  }
}

void handle_dir(char *filename) {
	// open the directory to read contents
	DIR* dir = opendir(filename);

	if (!dir) {
		printf("Error: unable to open directory %s\n", filename);
		printf("\tMake sure path to directory exists\n\n");
		return;
	}

	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL)
	{
		struct stat buf;
		char name[strlen(filename) + strlen(entry->d_name) + 1];
		name[0] = '\0';
		strcat(name, filename);
		strcat(name, "/");
		strcat(name, entry->d_name);
		if (stat(name, &buf) != 0) {
			// unable to obtain file stat
			printf("Error: unable to obtain file properties\n");
			printf("\tEnsure file %s exists\n", entry->d_name);
		} else {
			printf("----------------------------------\n");
			print_file_props_short(entry->d_name, buf);
			//printf("----------------------------------\n");
		}
	}
	
	// close the directory
	closedir(dir);
}

void print_file_props(char* filename, struct stat stats) {
  printf("%s:: ", filename);
  
  print_owner_group(stats);
  printf("\n");

  permissions(stats.st_mode);
  print_file_size(stats);
  printf("\n");
  
  datetime_info(stats.st_atime, stats.st_mtime);
}

void print_file_props_short(char *filename, struct stat stats) {
  printf("%s:: ", filename);

  print_owner_group(stats);
  printf("  ");

  permissions(stats.st_mode);
  print_file_size(stats);
  printf("\n");
}

void print_owner_group(struct stat stats) {
  struct passwd *owner = getpwuid(stats.st_uid);
  struct group *grp = getgrgid(stats.st_gid);
  
  if (!owner) {
    printf("NO OWNR  ");
  } else {
    printf("%s  ", owner->pw_name);
  }
  if (!grp) {
    printf("NO GRP");
  } else {
    printf("%s",  grp->gr_name);
  }
}

void permissions(mode_t mode) {
  printf(" ");

  printf("%c", (mode & S_IRUSR) ? 'r':'-');
  printf("%c", (mode & S_IWUSR) ? 'w':'-');
  printf("%c ", (mode & S_IXUSR) ? 'x':'-');

  printf("%c", (mode & S_IRGRP) ? 'r':'-');
  printf("%c", (mode & S_IWGRP) ? 'w':'-');
  printf("%c ", (mode & S_IXGRP) ? 'x':'-');

  printf("%c", (mode & S_IROTH) ? 'r':'-');
  printf("%c", (mode & S_IWOTH) ? 'w':'-');
  printf("%c", (mode & S_IXOTH) ? 'x':'-');
}

void datetime_info(time_t ctime, time_t mtime) {
 struct tm dat = *(gmtime(&ctime));

 printf(" ");
 printf("ACC: %d-%d-%d  %d:%d:%d\n", dat.tm_mday, dat.tm_mon, dat.tm_year + 1900, dat.tm_hour, dat.tm_min, dat.tm_sec);

 dat = *(gmtime(&mtime));
 printf(" ");
 printf("MOD: %d-%d-%d  %d:%d:%d\n", dat.tm_mday, dat.tm_mon, dat.tm_year + 1900, dat.tm_hour, dat.tm_min, dat.tm_sec);
}

void print_file_size(struct stat stats) {
  printf("  ");
  printf("%lldb", (long long)stats.st_size);
}
