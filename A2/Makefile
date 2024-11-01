# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC_PART2 = Part_II_101262467_101258978.c Part_II_101262467_101258978_program2.c
OBJ_PART2 = Part_II_101262467_101258978.o Part_II_101262467_101258978_program2.o

SRC_PART3 = interrupts_101262467_101258978.c
OBJ_PART3 = interrupts_101262467_101258978.o

# Header files
DEPS_PART3 = interrupts_101262467_101258978.h

# Executable names
TARGET_PART2_1 = concurrent_processes
TARGET_PART2_2 = process2
TARGET_PART3 = sim

# Default rule (build everything)
all: part2 part3 rm-obj

# Build part2 executables
part2: $(TARGET_PART2_1) $(TARGET_PART2_2)

# Build the executables from object files for part2
$(TARGET_PART2_1): Part_II_101262467_101258978.o
	$(CC) $(CFLAGS) -o $(TARGET_PART2_1) Part_II_101262467_101258978.o

$(TARGET_PART2_2): Part_II_101262467_101258978_program2.o
	$(CC) $(CFLAGS) -o $(TARGET_PART2_2) Part_II_101262467_101258978_program2.o

# Object file rule for part2
Part_II_101262467_101258978.o: Part_II_101262467_101258978.c
	$(CC) $(CFLAGS) -c Part_II_101262467_101258978.c -o Part_II_101262467_101258978.o

Part_II_101262467_101258978_program2.o: Part_II_101262467_101258978_program2.c
	$(CC) $(CFLAGS) -c Part_II_101262467_101258978_program2.c -o Part_II_101262467_101258978_program2.o

# Build part3 executable
part3: $(TARGET_PART3)

# Object file rule for part3
$(OBJ_PART3): $(SRC_PART3) $(DEPS_PART3)
	$(CC) $(CFLAGS) -c interrupts_101262467_101258978.c -o interrupts_101262467_101258978.o

# Build the executable from object file for part3
$(TARGET_PART3): $(OBJ_PART3)
	$(CC) $(CFLAGS) -o $(TARGET_PART3) $(OBJ_PART3)

# Clean up
clean:
	rm -f $(TARGET_PART2_1) $(TARGET_PART2_2) $(TARGET_PART3) $(OBJ_PART2) $(OBJ_PART3) execution*.txt

# Remove object files
rm-obj:
	rm -f $(OBJ_PART2) $(OBJ_PART3)

################## TESTS ##################

# Test 1: Run the program with different arguments
test1: $(TARGET_PART3)
	./$(TARGET_PART3) trace_1_101262467_101258978.txt external_files_101262467_101258978.txt vector_table_101262467_101258978.txt execution1.txt

# Test 2: Run the program with different arguments 
test2: $(TARGET_PART3)
	./$(TARGET_PART3) trace_2_101262467_101258978.txt external_files_101262467_101258978.txt vector_table_101262467_101258978.txt execution2.txt

# Test 3: Run the program with different arguments 
test3: $(TARGET_PART3)
	./$(TARGET_PART3) trace_3_101262467_101258978.txt external_files_101262467_101258978.txt vector_table_101262467_101258978.txt execution3.txt

# Test 4: Run the program with different arguments 
test4: $(TARGET_PART3)
	./$(TARGET_PART3) trace_4_101262467_101258978.txt external_files_101262467_101258978.txt vector_table_101262467_101258978.txt execution4.txt

# Test 5: Run the program with different arguments 
test5: $(TARGET_PART3)
	./$(TARGET_PART3) trace_5_101262467_101258978.txt external_files_101262467_101258978.txt vector_table_101262467_101258978.txt execution5.txt

testall: test1 test2 test3 test4 test5