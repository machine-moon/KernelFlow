// interrupts.c - Main file for the interrupt simulator

#include "interrupts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to load trace events from a file
void load_trace(const char *filename, TraceEvent *trace, int *event_count)
{
    FILE *file = fopen(filename, "r"); // Open file for reading
    if (!file)
    {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }

    // buffer to store each line
    char line[256];

    // read each line, parse it, store in the trace array
    while (fgets(line, sizeof(line), file))
    {
        // printf("Read line: %s", line);
        TraceEvent current_event;  // Initialize the current trace event
        current_event.vector = -1; // Default vector to -1

        // Check if the line contains "CPU" OR "END_IO" OR "SYSCALL"
        if (sscanf(line, "CPU, %d", &current_event.duration) == 1)
        {
            strcpy(current_event.type, "CPU");
        }
        else if (sscanf(line, "END_IO %d, %d", &current_event.vector, &current_event.duration) == 2)
        {
            strcpy(current_event.type, "END_IO");
        }
        else if (sscanf(line, "SYSCALL %d, %d", &current_event.vector, &current_event.duration) == 2)
        {
            strcpy(current_event.type, "SYSCALL");
        }
        else
        {
            printf("Warning: Line format not recognized: %s", line);
            continue; // Skip to the end of the loop
        }

        // Debug print to check the parsed event
        // printf("Parsed: Type=%s, Vector=%d, Duration=%d\n", current_event.type, current_event.vector, current_event.duration);

        // Store the parsed event in the trace array
        trace[*event_count] = current_event;
        (*event_count)++;
    }

    fclose(file);
}

// Function to load the vector table from a file
void load_vector_table(const char *filename, int *vector_table)
{
    FILE *file = fopen(filename, "r"); // Open file for reading
    if (!file)
    {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }
    // buffer
    char line[256];
    int index = 0;
    // Read each line from the file and parse it into vector table array
    while (fgets(line, sizeof(line), file))
    {
        int is_success = (sscanf(line, "%X", &vector_table[index]) == 1);
        index += (is_success) ? 1 : 0;

        if (!is_success)
        {
            printf("Warning: Line format not recognized: %s", line); // Debug print for unrecognized format
        }
    }
    fclose(file); // Close the vector table file
}

// Function to process the trace and log the events
void process_trace(TraceEvent *trace, int event_count, const int *vector_table, const char *output_filename)
{
    FILE *file = fopen(output_filename, "w"); // Open output file for writing
    if (!file)
    {
        printf("Error: Cannot open output file %s\n", output_filename);
        exit(1);
    }

    int current_time = 0;

    // Loop through each event in the trace
    for (int i = 0; i < event_count; i++)
    {
        if (strcmp(trace[i].type, "CPU") == 0) // Check if the event is a CPU event
        {
            fprintf(file, "%d, %d, CPU execution\n", current_time, trace[i].duration);
            current_time += trace[i].duration;
        }
        else if (strcmp(trace[i].type, "SYSCALL") == 0) // Check if the event is a SYSCALL event
        {
            // Random values for the SYSCALL event
            // SYSCALL event times
            int duration = trace[i].duration;
            float r1 = (float)rand() / RAND_MAX, r2 = (float)rand() / RAND_MAX, r3 = (float)rand() / RAND_MAX;
            float total = r1 + r2 + r3;
            int a = (int)(duration * 0.50 * (r1 / total));
            int b = (int)(duration * 0.35 * (r2 / total));
            int c = duration - a - b; // Ensure sum equals duration

            fprintf(file, "%d, 1, switch to kernel mode\n", current_time);
            current_time += 1;
            int context_time = (rand() % 3) + 1; // random context switch time
            fprintf(file, "%d, %d, context saved\n", current_time, (context_time));
            current_time += context_time;
            fprintf(file, "%d, 1, find vector %d in memory position 0x%04X\n", current_time, trace[i].vector, trace[i].vector * 2);
            current_time += 1;
            fprintf(file, "%d, 1, load address 0X%04X into the PC\n", current_time, vector_table[trace[i].vector]);
            current_time += 1;
            fprintf(file, "%d, %d, SYSCALL: run the ISR\n", current_time, a);
            current_time += a;
            fprintf(file, "%d, %d, transfer data\n", current_time, b);
            current_time += b;
            fprintf(file, "%d, %d, check for errors\n", current_time, c);
            current_time += c;
            fprintf(file, "%d, 1, IRET\n", current_time);
            current_time += 1;
        }
        else if (strcmp(trace[i].type, "END_IO") == 0) // Check if the event is an END_IO event
        {
            // Log END_IO events
            fprintf(file, "%d, 1, check priority of interrupt\n", current_time);
            current_time += 1;
            fprintf(file, "%d, 1, check if masked\n", current_time);
            current_time += 1;
            fprintf(file, "%d, 1, switch to kernel mode\n", current_time);
            current_time += 1;
            fprintf(file, "%d, 3, context saved\n", current_time);
            current_time += 3;
            fprintf(file, "%d, 1, find vector %d in memory position 0x%04X\n", current_time, trace[i].vector, trace[i].vector * 2);
            current_time += 1;
            fprintf(file, "%d, 1, load address 0X%04X into the PC\n", current_time, vector_table[trace[i].vector]);
            current_time += 1;
            fprintf(file, "%d, %d, END_IO\n", current_time, trace[i].duration);
            current_time += trace[i].duration;
            fprintf(file, "%d, 1, IRET\n", current_time);
            current_time += 1;
        }
    }

    fclose(file);
}

// Main function to handle command-line arguments and call the appropriate functions
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <trace_file> <vector_table_file> <output_file>\n", argv[0]);
        return 1;
    }
    // Seed
    srand(time(NULL));

    TraceEvent trace[MAX_EVENTS];        // Array to hold trace events
    int vector_table[VECTOR_TABLE_SIZE]; // Array to hold vector table
    int event_count = 0;                 // Number of trace events

    // Load trace events
    load_trace(argv[1], trace, &event_count);
    // Load vector table
    load_vector_table(argv[2], vector_table);
    // Process trace events and generate output
    process_trace(trace, event_count, vector_table, argv[3]);
    // done

    // log the debug info
    if (DEBUG_MODE)
    {
        // Print the output trace
        char choice;
        printf("Execution trace saved to %s\n", argv[3]);
        printf("Would you like to print the execution trace? (y/n): ");
        scanf("%c", &choice);

        if ((choice == 'y') || (choice == 'Y'))
        {
            FILE *file = fopen(argv[3], "r"); // Open file for reading
            if (!file)
            {
                printf("Error: Cannot open file %s\n", argv[3]); // Print error if file can't be opened
            }

            int i = 0;
            char line[256];
            // Read each line from the file and print it
            while (fgets(line, sizeof(line), file))
            {
                printf("Execution Trace Line %d: ", i);
                printf("%s", line);
                i++;
            }
        }

        printf("Would you like to print the debug info? (y/n): ");
        while (getchar() != '\n')
            ;
        scanf("%c", &choice);

        if ((choice == 'y') || (choice == 'Y'))
        {

            FILE *file = fopen(argv[1], "r"); // Open file for reading
            if (!file)
            {
                printf("Error: Cannot open file %s\n", argv[1]); // Print error if file can't be opened
            }

            int i = 0;
            char line[256];
            // Read each line from the file and parse it into the trace array
            while (fgets(line, sizeof(line), file))
            {

                printf("\nOriginal Trace Line %d: ", i);
                printf("%s", line);

                printf("Captured in TraceEvent: Type=%s, Duration=%d, Vector=%d\n", trace[i].type, trace[i].duration, trace[i].vector);

                if (trace[i].vector != -1)
                {
                    printf("Vector Table Lookup: Vector=%d, Content=0x%04X\n", trace[i].vector, vector_table[trace[i].vector]);
                }

                i++;
            }
        }
    }
    else
    {
        printf("Goodbye!\n");
    }

    return 0;
}