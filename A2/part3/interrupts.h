#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// configurations
#define MAX_EVENTS 300
#define MAX_PROCESSES 5 // doesnt account for the init process nor for child processes
#define MAX_EXTERNAL_FILES 100

#define VECTOR_TABLE_SIZE 256
#define DEBUG_MODE 0 // used for debugging at the end of main.c

typedef struct
{
    char type[10];         // CPU or SYSCALL or END_IO, FORK, EXEC
    int duration;          // Duration of the event
    char program_name[20]; // Optional, ProgramName for EXEC
    int vector;            // Optional, Vector number for SYSCALL, END_IO
} TraceEvent;
/*

17, 1, switch to kernel mode
18, 3, context saved
21, 1, find vector 3 in memory position 0x0006
22, 1, load address 0X042B into the PC
23, 30, EXEC: load program1 of size 10Mb

53, 10, found partition 4 with 10Mb of space
63, 6, partition 4 marked as occupied
69, 2, updating PCB with new information
71, 2, scheduler called
73, 1, IRET

*/
typedef struct
{
    unsigned int partition_number;
    unsigned int size;
    char code[20]; // "free", "init", or program name
} MemoryPartition;

typedef struct
{
    unsigned int pid;
    unsigned int cpu_time;
    unsigned int io_time;
    unsigned int remaining_cpu_time;
    unsigned int partition_number;
    struct PCB *prev;
    struct PCB *next;
} PCB;

typedef struct
{
    char program_name[20];
    unsigned int size;
} ExternalFile;

void load_external_files(const char *filename, ExternalFile *external_files, int *external_file_count);
void handle_fork(FILE *file, int *current_time, int duration, PCB *current_process);

void handle_exec(FILE *file, int *current_time, const char *program_name, ExternalFile *external_files, int external_file_count, MemoryPartition *partitions, PCB *pcb_table, PCB *current_process);

void load_trace(const char *filename, TraceEvent *trace, int *event_count);
void load_vector_table(const char *filename, int *vector_table);
void process_trace(TraceEvent *trace, int event_count, const int *vector_table, const char *output_filename, ExternalFile *external_files, int external_file_count, MemoryPartition *partitions, PCB *pcb_table);

#endif // INTERRUPTS_H