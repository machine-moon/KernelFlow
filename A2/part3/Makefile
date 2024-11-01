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
TARGET = sim

# Default rule (build the program)
all: $(TARGET) rm-obj

# Object file rule (dependencies for object file)
$(OBJ): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) -c interrupts.c

# Build the executable from object file
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)


# Clean up
clean:
	rm -f $(TARGET) execution*.txt  

# rm-obj rule to remove object files
rm-obj:
	rm -f $(OBJ)


################## TESTS ##################

# Test 1: Run the program with different arguments
test1: $(TARGET)
	./$(TARGET) trace1.txt external_files.txt vector_table.txt execution1.txt

# Test 2: Run the program with different arguments 
test2: $(TARGET)
	./$(TARGET) trace2.txt external_files.txt vector_table.txt execution2.txt





