# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC = concurrent_processes.c process2.c
OBJ = concurrent_processes.o process2.o

# Header files
DEPS =

# Executable names
TARGET1 = concurrent_processes
TARGET2 = process2

# Default rule (build the programs)
all: $(TARGET1) $(TARGET2)

# Object file rule (dependencies for object file)
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Build the executables from object files
$(TARGET1): concurrent_processes.o
	$(CC) $(CFLAGS) -o $(TARGET1) concurrent_processes.o

$(TARGET2): process2.o
	$(CC) $(CFLAGS) -o $(TARGET2) process2.o

# Clean up
clean:
	rm -f $(TARGET1) $(TARGET2) $(OBJ)