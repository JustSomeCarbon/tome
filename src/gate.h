

/**
 * prints usage information for the program
 */
void usage();

/**
 * prints information on how to use the program
 */
void help();

/**
 * lists all the gate endpoints within the gatefile to
 * the console.
 */
void list_gates();

/**
 * generate a random letter and return it
 */
char generate_letter();

/**
 * generate a random tag for a new gate. The tag
 * returned must be freed.
 */
char* generate_tag();

/**
 * check if the given tag is already in use.
 * return 0 if no collision is detected, 1 otherwise
 */
int check_tag_collision(char* tag);

/**
 * create a new gate
 */
int create_gate(char* path);
