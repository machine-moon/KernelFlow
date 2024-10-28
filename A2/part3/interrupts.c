#include "interrupts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

// Function to handle the FORK event
PCB *handle_fork(FILE *file, int *current_time, int duration, PCB *current_process)
{
    // Create a new PCB for the forked process
    PCB *new_process = (PCB *)malloc(sizeof(PCB));
    assert(new_process != NULL);

    // Duplicate the current process into the new process
    *new_process = *current_process;
    new_process->pid = current_process->pid + 1;

    new_process->prev = current_process; // ref to parent
    new_process->next = NULL;

    // Iterate to the end of the linked list
    PCB *last_process = current_process;
    while (last_process->next != NULL)
    {
        last_process = last_process->next;
    }

    // Attach the new process to the end of the list
    last_process->next = new_process;

    // Return the pointer to the new process
    return new_process;
}

// Function to handle the EXEC event
void handle_exec(FILE *file, int *current_time, int duration, char *program_name, ExternalFile *external_files, int external_file_count, MemoryPartition *partitions, PCB *pcb_table, PCB *current_process)
{
}

// Declaration of the load_external_files function
void load_external_files(const char *filename, ExternalFile *external_files, int *external_file_count)
{
    FILE *file = fopen(filename, "r"); // Open file for reading
    if (!file)
    {
        printf("Error: Cannot open file %s\n", filename);
        exit(1);
    }

    // buffer to store each line
    char line[256];

    // read each line, parse it, store in the external_files array
    while (fgets(line, sizeof(line), file))
    {
        ExternalFile current_file; // Initialize the current external file

        // Parse the line into the current external file
        if (sscanf(line, "%s %d", current_file.program_name, &current_file.size) == 2)
        {
            // Debug print to check the parsed external file
            // printf("Parsed: Name=%s, Size=%d\n", current_file.program_name, current_file.size);

            // Store the parsed external file in the external_files array
            external_files[*external_file_count] = current_file;
            (*external_file_count)++;
        }
        else
        {
            printf("Error: Line format not recognized: %s", line);
        }
    }

    fclose(file); // Close the external files file
}

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
        else if (sscanf(line, "FORK, %d", &current_event.duration) == 1)
        {
            strcpy(current_event.type, "FORK");
            current_event.vector = 2; // Default vector to 2
        }
        else if (sscanf(line, "EXEC %s, %d", current_event.program_name, &current_event.duration) == 2)
        {
            strcpy(current_event.type, "EXEC");
            current_event.vector = 3; // Default vector to 3
        }
        else
        {
            printf("Error: Line format not recognized: %s", line);
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
            printf("Error: Line format not recognized: %s", line); // Debug print for unrecognized format
        }
    }
    fclose(file); // Close the vector table file
}

// Function to process the trace and log the events
void process_trace(TraceEvent *trace, int event_count, const int *vector_table, const char *output_filename, ExternalFile *external_files, int external_file_count, MemoryPartition *partitions, PCB *pcb_table)
{
    PCB *current_process = pcb_table;
    MemoryPartition *current_partition = partitions;
    FILE *file = fopen(output_filename, "w");
    if (!file)
    {
        printf("Error: Cannot open output file %s\n", output_filename);
        exit(1);
    }

    int current_time = 0;
    bool which_syscall = false; // Used to alternate between the two SYSCALL events

    // Loop through each event in the trace
    for (int i = 0; i < event_count; i++)
        if (strcmp(trace[i].type, "CPU") == 0) // Check if the event is a CPU event
        {
            fprintf(file, "%d, %d, CPU execution\n", current_time, trace[i].duration);
            current_time += trace[i].duration;
        }
        else if (strcmp(trace[i].type, "SYSCALL") == 0) // Check if the event is a SYSCALL event
        {
            // Random values for the SYSCALL events THAT match the duration of the event.
            int duration = trace[i].duration;
            int a = rand() % (duration + 1);     // for run the ISR
            int b = rand() % (duration - a + 1); // for transfer data
            int c = duration - a - b;            // check for errors

            fprintf(file, "%d, 1, switch to kernel mode\n", current_time);
            current_time += 1;
            int context_time = (rand() % 3) + 1; // random context switch time (1-3)
            fprintf(file, "%d, %d, context saved\n", current_time, context_time);
            current_time += context_time;
            fprintf(file, "%d, 1, find vector %d in memory position 0x%04X\n", current_time, trace[i].vector, trace[i].vector * 2);
            current_time += 1;
            fprintf(file, "%d, 1, load address 0X%04X into the PC\n", current_time, vector_table[trace[i].vector]);
            current_time += 1;
            fprintf(file, "%d, %d, SYSCALL: run the ISR\n", current_time, a);
            current_time += a;
            if (which_syscall)
            {
                fprintf(file, "%d, %d, transfer data to display\n", current_time, b);
            }
            else
            {
                fprintf(file, "%d, %d, transfer data\n", current_time, b);
            }
            which_syscall = !which_syscall;

            current_time += b;
            fprintf(file, "%d, %d, check for errors\n", current_time, c);
            current_time += c;
            fprintf(file, "%d, 1, IRET\n", current_time);
            current_time += 1;
        }
        else if (strcmp(trace[i].type, "END_IO") == 0) // Check if the event is an END_IO event
        {
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
        else if (strcmp(trace[i].type, "FORK") == 0) // Check if the event is a FORK event
        {
            // Random values for FORK events THAT match the duration of the event.
            int duration = trace[i].duration;
            int a = rand() % (duration + 1); // for copy parent PCB to child PCB
            int b = duration - a;            // for scheduler called

            fprintf(file, "%d, 1, switch to kernel mode\n", current_time);
            current_time += 1;
            fprintf(file, "%d, 3, context saved\n", current_time);
            current_time += 3;
            fprintf(file, "%d, 1, find vector %d in memory position 0x%04X\n", current_time, trace[i].vector, trace[i].vector * 2);
            current_time += 1;
            fprintf(file, "%d, 1, load address 0X%04X into the PC\n", current_time, vector_table[trace[i].vector]);
            current_time += 1;
            fprintf(file, "%d, %d, FORK: copy parent PCB to child PCB\n", current_time, a);
            current_time += a;
            fprintf(file, "%d, %d, scheduler called\n", current_time, b);
            current_time += b;
            fprintf(file, "%d, 1, IRET\n", current_time);
            current_time += 1;
            current_process = handle_fork(file, &current_time, trace[i].duration, current_process);
        }
        else if (strcmp(trace[i].type, "EXEC") == 0) // Check if the event is an EXEC event
        {
        }

    fclose(file);
}
// Main function to handle command-line arguments and call the appropriate functions
int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s <trace_file> <external_files> <vector_table_file> <output_file>\n", argv[0]);
        return 1;
    }
    // -----------------------------------------------------------
    // Initialization Section
    // -----------------------------------------------------------

    // Seed
    srand(time(NULL));

    // -----------------------------------------------------------
    // Loading Section
    // -----------------------------------------------------------

    // Load trace events
    TraceEvent trace[MAX_EVENTS];
    int event_count = 0;
    load_trace(argv[1], trace, &event_count);
    // Load external files
    ExternalFile external_files[MAX_EXTERNAL_FILES];
    int external_file_count = 0;
    load_external_files(argv[2], external_files, &external_file_count);

    // Load vector table
    int vector_table[VECTOR_TABLE_SIZE]; // Array to hold vector table
    load_vector_table(argv[3], vector_table);

    // -----------------------------------------------------------
    // Pre-Processing Section
    // -----------------------------------------------------------

    // Initialize memory partitions
    MemoryPartition partitions[] = {{1, 40, "free"}, {2, 25, "free"}, {3, 15, "free"}, {4, 10, "free"}, {5, 8, "free"}, {6, 2, "init"}};

    // Initialize PCB doubly linked list with the init process
    PCB pcb_table;
    pcb_table.pid = 0;
    pcb_table.cpu_time = 0;
    pcb_table.io_time = 0;
    pcb_table.remaining_cpu_time = 0;
    pcb_table.partition_number = 6;
    pcb_table.prev = NULL;
    pcb_table.next = NULL;

    PCB *current_process = &pcb_table;

    // -----------------------------------------------------------
    // Simulation Section
    // -----------------------------------------------------------

    // Run the first FORK event on the init process
    handle_fork(NULL, NULL, 0, current_process);

    // Run the first EXEC event on the trace file
    handle_exec(NULL, NULL, 0, "trace.txt", external_files, external_file_count, partitions, pcb_table, current_process);

    // done

    // debug info
    // check DEBUG_MODE in interrupts.h :)
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
        printf("\n\tGoodbye %s!\n\n", argv[1]);
    }

    // Free the PCB linked list
    PCB *temp;
    while (pcb_table != NULL)
    {
        temp = pcb_table;
        pcb_table = pcb_table->next;
        free(temp);
    }

    return 0;
}