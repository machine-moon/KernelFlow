#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#define MAX_EVENTS 100
#define VECTOR_TABLE_SIZE 256
#define DO_LOGGING 1

typedef struct
{
    char type[10]; // CPU or SYSCALL or END_IO
    int duration;  // Duration of the event
    int vector;    // Vector number for interrupt events
} TraceEvent;

void load_trace(const char *filename, TraceEvent *trace, int *event_count);
void load_vector_table(const char *filename, int *vector_table);
void process_trace(TraceEvent *trace, int event_count, const int *vector_table, const char *output_filename);

#endif // INTERRUPTS_H