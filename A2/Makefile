# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC_PART2 = concurrent_processes.c process2.c
OBJ_PART2 = concurrent_processes.o process2.o

SRC_PART3 = interrupts.c
OBJ_PART3 = interrupts.o

# Header files
DEPS_PART3 = interrupts.h

# Executable names
TARGET_PART2_1 = concurrent_processes
TARGET_PART2_2 = process2
TARGET_PART3 = sim

# Default rule (build everything)
all: part2 part3 rm-obj

# Build part2 executables
part2: $(TARGET_PART2_1) $(TARGET_PART2_2)

# Object file rule for part2
$(OBJ_PART2): $(SRC_PART2)
	concurrent_processes.o: concurrent_processes.c
		$(CC) $(CFLAGS) -c concurrent_processes.c -o concurrent_processes.o

	process2.o: process2.c
		$(CC) $(CFLAGS) -c process2.c -o process2.o

# Build the executables from object files for part2
$(TARGET_PART2_1): concurrent_processes.o
    $(CC) $(CFLAGS) -o $(TARGET_PART2_1) concurrent_processes.o

$(TARGET_PART2_2): process2.o
    $(CC) $(CFLAGS) -o $(TARGET_PART2_2) process2.o

# Build part3 executable
part3: $(TARGET_PART3)

# Object file rule for part3
$(OBJ_PART3): $(SRC_PART3) $(DEPS_PART3)
    $(CC) $(CFLAGS) -c interrupts.c -o interrupts.o

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
    ./$(TARGET_PART3) trace1.txt external_files.txt vector_table.txt execution1.txt

# Test 2: Run the program with different arguments 
test2: $(TARGET_PART3)
    ./$(TARGET_PART3) trace2.txt external_files.txt vector_table.txt execution2.txt

# Test 3: Run the program with different arguments 
test3: $(TARGET_PART3)
    ./$(TARGET_PART3) trace3.txt external_files.txt vector_table.txt execution3.txt

# Test 4: Run the program with different arguments 
test4: $(TARGET_PART3)
    ./$(TARGET_PART3) trace4.txt external_files.txt vector_table.txt execution4.txt

# Test 5: Run the program with different arguments 
test5: $(TARGET_PART3)
    ./$(TARGET_PART3) trace5.txt external_files.txt vector_table.txt execution5.txt