# Interrupt Simulator
## Description
A simple Interrupt Simulator for SYSC-4001 A1.

## Usage

To run the simulator, use the following command:
```sh
./sim <trace_file> <vector_table_file> <output_file>
```

## Makefile Instructions

### Default Rule
To build the program use:
```sh
make
```

### Running Specific Tests
To run specific tests, use the following commands:
```sh
make test1
make test2
make test3
make test4
make test5
# ... up to test20
```

### Running All Tests
To run all tests, use:
```sh
make test_all
```

### Running Tests by Groups
To run main tests (test1 and test2), use:
```sh
make test_main
```
To run other tests (test3 to test20), use:
```sh
make test_other
```

### Cleaning Up
To remove the executable, object file, and ALL test execution files in, use:
```sh
make clean
```

## Notes
- The `test1` and `test2` scripts are provided as part of the assignment instructions. However, using the `make test_main` and `make test_other` commands is more robust and easier to manage.
- Ensure you have `make` installed and properly configured.
- Running tests together may appear to repeat randomness due to fast execution; run tests individually to see true randomness.