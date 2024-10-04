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
all: $(TARGET) test_all

# Object file rule (dependencies for object file)
$(OBJ): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) -c interrupts.c

# Build the executable from object file
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)


# Clean up
clean:
	rm -f $(TARGET) $(OBJ) otherTests/test*/execution*.txt execution*.txt  

# Test all: run all tests
test_all: test_main test_other

# Test_main: run tests 1-2 (test1, test2)
test_main: test1 test2

# Test_other: run tests 3-20 (otherTests)
test_other: test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14 test15 test16 test17 test18 test19 test20



# main tests


# Test 1: Run the program with trace1.txt, vector.txt, and execution1.txt
test1: $(TARGET)
	./$(TARGET) trace1.txt otherTests/vector.txt execution1.txt

# Test 2: Run the program with different arguments (trace2.txt, vector2.txt, execution2.txt)
test2: $(TARGET)
	./$(TARGET) trace2.txt otherTests/vector.txt execution2.txt


# otherTests tests


# Test 3: Run the program with different arguments (trace3.txt, vector3.txt, execution3.txt)
test3: $(TARGET)
	./$(TARGET) otherTests/test3/trace3.txt otherTests/vector.txt otherTests/test3/execution3.txt

# Test 4: Run the program with different arguments (trace4.txt, vector4.txt, execution4.txt)
test4: $(TARGET)
	./$(TARGET) otherTests/test4/trace4.txt otherTests/vector.txt otherTests/test4/execution4.txt

# Test 5: Run the program with different arguments (trace5.txt, vector5.txt, execution5.txt)
test5: $(TARGET)
	./$(TARGET) otherTests/test5/trace5.txt otherTests/vector.txt otherTests/test5/execution5.txt

# Test 6: Run the program with different arguments (trace6.txt, vector6.txt, execution6.txt)
test6: $(TARGET)
	./$(TARGET) otherTests/test6/trace6.txt otherTests/vector.txt otherTests/test6/execution6.txt

# Test 7: Run the program with different arguments (trace7.txt, vector7.txt, execution7.txt)
test7: $(TARGET)
	./$(TARGET) otherTests/test7/trace7.txt otherTests/vector.txt otherTests/test7/execution7.txt

# Test 8: Run the program with different arguments (trace8.txt, vector8.txt, execution8.txt)
test8: $(TARGET)
	./$(TARGET) otherTests/test8/trace8.txt otherTests/vector.txt otherTests/test8/execution8.txt

# Test 9: Run the program with different arguments (trace9.txt, vector9.txt, execution9.txt)
test9: $(TARGET)
	./$(TARGET) otherTests/test9/trace9.txt otherTests/vector.txt otherTests/test9/execution9.txt

# Test 10: Run the program with different arguments (trace10.txt, vector10.txt, execution10.txt)
test10: $(TARGET)
	./$(TARGET) otherTests/test10/trace10.txt otherTests/vector.txt otherTests/test10/execution10.txt

# Test 11: Run the program with different arguments (trace11.txt, vector11.txt, execution11.txt)
test11: $(TARGET)
	./$(TARGET) otherTests/test11/trace11.txt otherTests/vector.txt otherTests/test11/execution11.txt

# Test 12: Run the program with different arguments (trace12.txt, vector12.txt, execution12.txt)
test12: $(TARGET)
	./$(TARGET) otherTests/test12/trace12.txt otherTests/vector.txt otherTests/test12/execution12.txt

# Test 13: Run the program with different arguments (trace13.txt, vector13.txt, execution13.txt)
test13: $(TARGET)
	./$(TARGET) otherTests/test13/trace13.txt otherTests/vector.txt otherTests/test13/execution13.txt

# Test 14: Run the program with different arguments (trace14.txt, vector14.txt, execution14.txt)
test14: $(TARGET)
	./$(TARGET) otherTests/test14/trace14.txt otherTests/vector.txt otherTests/test14/execution14.txt

# Test 15: Run the program with different arguments (trace15.txt, vector15.txt, execution15.txt)
test15: $(TARGET)
	./$(TARGET) otherTests/test15/trace15.txt otherTests/vector.txt otherTests/test15/execution15.txt

# Test 16: Run the program with different arguments (trace16.txt, vector16.txt, execution16.txt)
test16: $(TARGET)
	./$(TARGET) otherTests/test16/trace16.txt otherTests/vector.txt otherTests/test16/execution16.txt

# Test 17: Run the program with different arguments (trace17.txt, vector17.txt, execution17.txt)
test17: $(TARGET)
	./$(TARGET) otherTests/test17/trace17.txt otherTests/vector.txt otherTests/test17/execution17.txt

# Test 18: Run the program with different arguments (trace18.txt, vector18.txt, execution18.txt)
test18: $(TARGET)
	./$(TARGET) otherTests/test18/trace18.txt otherTests/vector.txt otherTests/test18/execution18.txt

# Test 19: Run the program with different arguments (trace19.txt, vector19.txt, execution19.txt)
test19: $(TARGET)
	./$(TARGET) otherTests/test19/trace19.txt otherTests/vector.txt otherTests/test19/execution19.txt

# Test 20: Run the program with different arguments (trace20.txt, vector20.txt, execution20.txt)
test20: $(TARGET)
	./$(TARGET) otherTests/test20/trace20.txt otherTests/vector.txt otherTests/test20/execution20.txt

