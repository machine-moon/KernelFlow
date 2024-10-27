#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// configurations
#define MAX_EVENTS 300
#define VECTOR_TABLE_SIZE 256
#define DEBUG_MODE 0 // used for debugging at the end of main.c

typedef struct
{
    char type[10]; // CPU or SYSCALL or END_IO
    int duration;  // Duration of the event
    int vector;    // Vector number for interrupt events
} TraceEvent;

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
} PCB;

void load_trace(const char *filename, TraceEvent *trace, int *event_count);
void load_vector_table(const char *filename, int *vector_table);
void process_trace(TraceEvent *trace, int event_count, const int *vector_table, const char *output_filename);

#endif // INTERRUPTS_H