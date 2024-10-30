#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// configurations
#define MAX_EVENTS 300
#define MAX_PARTITIONS 6
#define MAX_EXTERNAL_FILES 100

#define VECTOR_TABLE_SIZE 256
#define DEBUG_MODE 0 // used for debugging at the end of main.c
#include <stdio.h>   // for FILE
#include <stdint.h>  // for uint16_t

typedef struct
{
    char type[10];         // CPU or SYSCALL or END_IO, FORK, EXEC
    uint16_t duration;     // Duration of the event
    char program_name[20]; // Optional, ProgramName for EXEC
    int16_t vector;        // Optional, Vector number for SYSCALL, END_IO
} TraceEvent;

typedef struct
{
    uint16_t partition_number;
    uint16_t size;
    char code[20]; // "free", "init", or program name
} MemoryPartition;

// struct PCB;
typedef struct PCB
{
    uint16_t pid;
    uint16_t cpu_time;
    uint16_t io_time;
    uint16_t remaining_cpu_time;
    uint16_t partition_number;
    char program_name[20];
    uint16_t program_size;
    struct PCB *parent;
    struct PCB *next;
} PCB;

typedef struct
{
    char program_name[20];
    uint16_t size;
} ExternalFile;
// -----------------------------------------------------------
void run_fork(FILE *file, uint16_t *current_time, int duration, PCB **current_process);
void run_exec(const char *program_name, const int *vector_table, const char *output_filename, ExternalFile *external_files, int external_file_count, MemoryPartition *memory_partitions, PCB **current_process, uint16_t *current_time, int duration);
// -----------------------------------------------------------

PCB *init_pcb(PCB *pcb);

void save_system_status(uint16_t current_time, PCB *pcb_table);

void load_external_files(const char *filename, ExternalFile *external_files, int *external_file_count);
// -----------------------------------------------------------
void load_trace(const char *filename, TraceEvent *trace, int *event_count);
void load_vector_table(const char *filename, int *vector_table);
void process_trace(TraceEvent *trace, int event_count, const int *vector_table, const char *output_filename, ExternalFile *external_files, int external_file_count, MemoryPartition *partitions, PCB *current_process, uint16_t *current_time);
// -----------------------------------------------------------

#endif // INTERRUPTS_H