# TOME

Tome is a collection of CLI tools built for fun. Each tool is named after some type
of spell that represents its behavior.

### Building the Project

Run the following to build the project:
```
$ ./make.sh
```
This will run the make file and build the executables of the tools. There is not yet
functionality to fully install the executables on the host system and will be built
in later.

### Scry

Scry is a vision tool used to list information about a specific file or directory. It
can also be used to display directories in a tree like manner.

### Gate

Gate is a movement tool used to create gate points in specified directories. Gate points
are stored in a gate file and are specified with a three letter tag. Gate works in
tandom with the Blink tool.

### Blink

Blink is a movement tool used in tandem with Gate. Blink accepts a tag and moves the current
working directory to the specified gate location.
