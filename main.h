/**************************************************************************************************
 * File: main.h
 * Author: Nolan Davenport
 * Procedures:
 * 
 * setup_unequal_static_partitions  - Sets up the sizes for the unequal partitions and initializes 
 *                                    each partition. 
 * 
 * report_results                   - Repots the results after completing each experiment. 
 * 
 * main                             - Entry point for this program. Initializes the data and 
 *                                    initiates the experiments. 
 *************************************************************************************************/

#pragma once

#define NUMBER_OF_EXPERIMENTS 1000
#define NUMBER_OF_SAMPLES 1000

// Structure that holds the results for the experiments. 
typedef struct {
    float turn_around_time = 0;
    float relative_turn_around_time = 0;
    float number_of_failures = 0;
    float average_num_data_members_in_partition_table = 0;
} Results;

// Structure that holds the information for a single member of data.
typedef struct {
    int index;
    int size;
    int time;
    int left;
    int time_start = 0;
    int time_end;
    int turn_around_time;
    bool failure;
} Data;

// Structure that holds information for one static partition. 
typedef struct{
    int size;
    int data_index;
} StaticPartition;

// Structure that holds information for one dynamic partition. 
typedef struct{
    int size;
    int start_location;
    int data_index;
}DynamicPartition;

#define MEMORY_END 55

// Function prototypes
void setup_unequal_static_partitions(StaticPartition (&partitions)[7]);
void report_results(Results* equal, Results* one_queue_unequal, Results* multiple_queues_unequal, Results* first_fit);
int main(int argc, char* argv[]);