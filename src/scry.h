
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// FLAGS
extern short short_fl;
extern short tree_fl;

/**
 * Print basic usage message to console
 */
void usage();

/**
 * help flag function. Prints help information for using scry
 */
void help();

/**
 * handles scry functionality for a file
 */
void handle_file(char* filename, struct stat stats);

/**
 * handles scry functionality for a directory
 */
void handle_dir(char* filename);

/**
 * prints the entries of a directory as a tree up to
 * given branch levels.
 */
void print_dir_tree(char* filename, DIR* dir, int branch);

/**
 * print file information to console
 */
void print_file_props(char* filename, struct stat stats);

/**
 * print file information to console. Less information than
 * print_file_props.
 */
void print_file_props_short(char* filename, struct stat stats);

/**
 * prints the owner and the group of the file
 */
void print_owner_group(struct stat stats);

/**
 * prints the permissions of a given file
 */
void permissions(mode_t mode);

/**
 * prints the time a file type was created.
 */
void datetime_info(time_t ctime, time_t mtime);

/**
 * print the file size
 */
void print_file_size(struct stat stats);
