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

# Test 1: Run the program with trace1.txt, vector.txt, and execution1.txt
test1: $(TARGET)
	./$(TARGET) trace1.txt additionalFiles/vector_table.txt execution1.txt

# Test 2: Run the program with different arguments (trace2.txt, vector2.txt, execution2.txt)
test2: $(TARGET)
	./$(TARGET) trace2.txt additionalFiles/vector_table.txt execution2.txt




# Test all: run all tests
#test_all: test_main test_other

# Test_main: run tests 1-2 (test1, test2)
#test_main: test1 test2

# Test_other: run tests 3-20 (otherTests)
#test_other: test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test16 test17 test18 test19 test20


