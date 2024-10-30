#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// configurations
#define MAX_EVENTS 300
#define MAX_PARTITIONS 5 // 0-5 is 6 partitions
#define MAX_EXTERNAL_FILES 100

#define VECTOR_TABLE_SIZE 256
#define DEBUG_MODE 0 // used for debugging at the end of main.c
#include <stdio.h>
typedef struct
{
    char type[10];         // CPU or SYSCALL or END_IO, FORK, EXEC
    int duration;          // Duration of the event
    char program_name[20]; // Optional, ProgramName for EXEC
    int vector;            // Optional, Vector number for SYSCALL, END_IO
} TraceEvent;

typedef struct
{
    unsigned int partition_number;
    unsigned int size;
    char code[20]; // "free", "init", or program name
} MemoryPartition;

// struct PCB;
typedef struct PCB
{
    unsigned int pid;
    unsigned int cpu_time;
    unsigned int io_time;
    unsigned int remaining_cpu_time;
    unsigned int partition_number;
    char program_name[20];
    unsigned int program_size;
    struct PCB *parent;
    struct PCB *next;
} PCB;

typedef struct
{
    char program_name[20];
    unsigned int size;
} ExternalFile;
// -----------------------------------------------------------
void run_fork(FILE *file, unsigned int *current_time, int duration, PCB **current_process);
void run_exec(const char *program_name, const int *vector_table, const char *output_filename, ExternalFile *external_files, int external_file_count, MemoryPartition *memory_partitions, PCB **current_process, unsigned int *current_time, int duration);
// -----------------------------------------------------------
PCB *init_pcb(PCB *pcb);

void save_system_status(unsigned int current_time, PCB *pcb_table);

void load_external_files(const char *filename, ExternalFile *external_files, int *external_file_count);
// -----------------------------------------------------------
void load_trace(const char *filename, TraceEvent *trace, int *event_count);
void load_vector_table(const char *filename, int *vector_table);
void process_trace(TraceEvent *trace, int event_count, const int *vector_table, const char *output_filename, ExternalFile *external_files, int external_file_count, MemoryPartition *partitions, PCB *pcb_table);

#endif // INTERRUPTS_H