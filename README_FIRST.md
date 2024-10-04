# Interrupt Simulator

## Description
A simple Interrupt Simulator for SYSC-4001 A1

## Usage

`./sim <trace_file> <vector_table_file> <output_file>`

### Running Specific Tests
To run specific tests, use the following commands:
```sh
make test1
make test2
make test3
make test4
make test5
```

### Running All Tests
To run all tests from both groups (tests 1 & 2) and other tests (3-20), use:
```sh
make
```

### Running Tests by Groups
To run tests by groups, use:
```sh
make test_main
make test_other
```

### Recompiling
To recompile and run all tests, use:
```sh
make
```

### Cleaning Up
To clean all execution*.txt files in both groups and remake everything by running `make`, use:
```sh
make clean
```

## Notes
- Ensure you have `make` installed and properly configured.
- Modify the `Makefile` as needed to suit your project's requirements.