# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC = interrupts.c
OBJ = interrupts.o

# Header files
DEPS = interrupts.h

# Executable name
TARGET = interrupts

# Default rule (build the program)
all: $(TARGET)

# Object file rule (dependencies for object file)
$(OBJ): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) -c interrupts.c

# Build the executable from object file
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Test 1: Run the program with trace.txt, vector.txt, and execution.txt
test1: $(TARGET)
	./$(TARGET) trace.txt vector.txt execution.txt

# Test 2: Run the program with different arguments (trace2.txt, vector2.txt, execution2.txt)
test2: $(TARGET)
	./$(TARGET) trace2.txt vector2.txt execution2.txt

# Clean up
clean:
	rm -f $(TARGET) $(OBJ)
