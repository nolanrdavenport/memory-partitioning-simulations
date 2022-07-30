/**************************************************************************************************
 * File: one_queue_unequal.cpp
 * Author: Nolan Davenport
 * Procedures:
 * 
 * one_queue_fill_unequal_partitions    - Fills the next available partition with the data member 
 *                                        at the front of the queue if there is an available 
 *                                        partition. 
 * 
 * one_queue_unequal_partitioning       - Performs the experiment for a single queue using an 
 *                                        unequal partitioning style. 
 *************************************************************************************************/

#include<iostream>
#include<random>
#include<queue>
#include<list>

#include"main.h"

/**************************************************************************************************
 * void one_queue_fill_unequal_partitions(Data (&data)[NUMBER_OF_SAMPLES], int &next_data, 
 *                                        int &number_of_failures, StaticPartition (&partitions)[7], 
 *                                        int &num_data_members_in_partition_table, int clock){
 * 
 * Author: Nolan Davenport
 * Description: Fills the next available partition with the data member at the front of the queue 
 *              if there is an available partition.
 * 
 * Parameters:
 *  data                                    I/P     Data (&)[NUMBER_OF_SAMPLES]     The array of data that 
 *                                                                                  is being processed.
 *  next_data                               I/O     int (&)                         The index of the next 
 *                                                                                  piece of data at the
 *                                                                                  head of the queue. 
 *  number_of_failures                      O/P     int (&)                         The number of failures 
 *                                                                                  in this experiment.
 *  partitions                              I/O     StaticPartition (&)[7]          The partition table with
 *                                                                                  unequal sizes.
 *  num_data_members_in_partition_table     O/P     int (&)                         The number of data
 *                                                                                  members in the partition
 *                                                                                  table.
 *  clock                                   I/P     int                             The clock value.
 *************************************************************************************************/
void one_queue_fill_unequal_partitions(Data (&data)[NUMBER_OF_SAMPLES], int &next_data, int &number_of_failures, 
                        StaticPartition (&partitions)[7], int &num_data_members_in_partition_table, int clock){

    for(;;){                                                                    // Start the loop to fill as much partitions as it can.
        int next_data_size = data[next_data].size;                              // Get the size of the next element in the queue.

        if(next_data_size <= 2 && partitions[0].data_index == -1){              // If the next data size is <= 2 and the partition is empty.
            partitions[0].data_index = next_data;                               // Set the 2MB partition to the index of the next item in the queue.
        }else if(next_data_size <= 4 && partitions[1].data_index == -1){        // If the next data size is <= 4 and the partition is empty.
            partitions[1].data_index = next_data;                               // Set the 4MB partition to the index of the next item in the queue.
        }else if(next_data_size <= 6 && partitions[2].data_index == -1){        // If the next data size is <= 6 and the partition is empty.
            partitions[2].data_index = next_data;                               // Set the 6MB partition to the index of the next item in the queue.
        }else if(next_data_size <= 8 &&
        (partitions[3].data_index == -1 || partitions[4].data_index == -1)){    // If the next data size is <= 8 and either of the 8MB partitions is empty.
            if(partitions[3].data_index == -1){                                 // If the first 8MB partition is empty:
                partitions[3].data_index = next_data;                           // Set it to the index of the next item in the queue.
            }else{                                                              // Otherwise:
                partitions[4].data_index = next_data;                           // Set the second 8MB partition to the next item in the queue.
            }
        }else if(next_data_size <= 12 && partitions[5].data_index == -1){       // If the next data size is <= 12 and the partition is empty.
            partitions[5].data_index = next_data;                               // Set the 12MB partition to the index of the next item in the queue.
        }else if(partitions[6].data_index == -1){                               // Anything greater than 12 and if the 16MB partition is empty.
            partitions[6].data_index = next_data;                               // Set the 16MB partition to the index of the next item in the queue.

            if(next_data_size > 16){                                            // If the size of the item just inserter is greater than 16MB,
                number_of_failures++;                                           // Then increment the number of failures. 
            }
        }else{
            break;                                                              // The next data member is blocked from entering a StaticPartition. 
        }
        // TODO: figure this out
        //data[next_data].time_start = clock;

        num_data_members_in_partition_table++;  // Increment the number of data members in the partition table
                                                // Because an item was added if it got to this point. 
        next_data++;                            // Increment the index to show the next data item in the queue.
    }
}

/**************************************************************************************************
 * void one_queue_unequal_partitioning(Data data[NUMBER_OF_SAMPLES], int number_of_samples, 
 *                                     Results* one_queue_unequal)
 * 
 * Author: Nolan Davenport
 * Description: Performs the experiment for a single queue using an unequal partitioning style. 
 * 
 * Parameters:
 *  data                    I/P     Data[NUMBER_OF_SAMPLES]     The data to be used in this experiment.
 *  number_of_samples       I/P     int                         The number of samples in this experiment.
 *  one_queue_unequal       O/P     Results*                    Pointer to the structure that holds
 *                                                              the results of this experiment. 
 *************************************************************************************************/
void one_queue_unequal_partitioning(Data data[NUMBER_OF_SAMPLES], int number_of_samples, 
                                    Results* one_queue_unequal){

    Data experiment_data[NUMBER_OF_SAMPLES];        // Create an array to copy the experiment data.
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++){     // Loop through each array element.
        experiment_data[i] = data[i];               // Copy the data[] array into the experiment_data[] array.
    }

    int number_of_failures = 0;                     // Initialize the number of failures to zero.

    // Setup StaticPartition table
    StaticPartition partitions[7];                  // Create the array of partitions. 
    setup_unequal_static_partitions(partitions);    // Call setup_unequal_static_partitions in order to set it up.
                                                    // partitions is passed as reference. 

    // Put intitial data into the StaticPartition table. 
    int next_data = 0;                                  // Initialize the index that shows the next data item into the queue to zero.
    int num_data_members_in_partition_table = 0;        // Initialize the number of data members in the partition table to zero. 
    one_queue_fill_unequal_partitions(experiment_data,  // Call the one_queue_fill_unequal_partitions function to fill the unequal
        next_data, number_of_failures, partitions,      // partitions.
        num_data_members_in_partition_table, 0);

    int curr_partition = 0;     // Initialize the current partition to zero. For use in looping through partitions as the process runs.

    int clock = 0;              // Initialize the clock to zero. Used to track time. 

    float average_num_data_members_in_partition_table = 0;  // Initialize the average number of data members in the partition
                                                            // table to zero.

    for(;;){                                                // Start the clock loop.
        if(partitions[curr_partition].data_index == -1){    // If the current partition is empty, then just skip it without incrementing clock.
            curr_partition = (curr_partition + 1) % 7;      // Increments the current position, looping back around to 0 if it reaches 7. 
            continue;                                       // Continue to the next loop cycle, skipping everything below.
        }

        experiment_data[partitions[curr_partition].data_index].left -= 1;               // Decrement the time left for the partition that
                                                                                        // the "processor" is one. This simulates work for 
                                                                                        // one quantum. 

        if(experiment_data[partitions[curr_partition].data_index].left == 0){           // The case if there is no time left anymore.
            experiment_data[partitions[curr_partition].data_index].time_end = clock;    // Set the end time to the clock value. 

            experiment_data[partitions[curr_partition].data_index].turn_around_time = clock -   // Calculate the turnaround time as the
                experiment_data[partitions[curr_partition].data_index].time_start;              // endtime - startime.

            one_queue_unequal->turn_around_time +=                                      // Add the calculated turnaround time for this
            experiment_data[partitions[curr_partition].data_index].turn_around_time;    // sample to the cumulative turnaround time for
                                                                                        // this experiment.

            one_queue_unequal->relative_turn_around_time +=                                         // Calculate the relative turnaround
                (float)experiment_data[partitions[curr_partition].data_index].turn_around_time /    // time and add it to the cumulative
                experiment_data[partitions[curr_partition].data_index].time;                        // turnaround time for this experiment.

            partitions[curr_partition].data_index = -1; // Clear this partition by setting the data index to -1.
            num_data_members_in_partition_table--;      // Decrement the number of data members in the partition table.
            
            if(next_data != NUMBER_OF_SAMPLES){                     // As long as there exists more data items in the queue:
                one_queue_fill_unequal_partitions(experiment_data,  // Perform the algorithm to fill the unequal partitions
                    next_data, number_of_failures, partitions,      // using only one queue.
                    num_data_members_in_partition_table, clock+1);
            }else{                                                  // Otherwise, there's no more data items in the queue.
                if(num_data_members_in_partition_table == 0){       // If there's no items left in the queue and no data members in
                                                                    // the partition:
                    break;                                          // Break out of the loop to end this experiment.
                }
            }
        }

        curr_partition = (curr_partition + 1) % 7;                  // Increments the current partition, looping back around to 0 if it reaches 7. 
        clock++;                                                    // Increments the clock after each quantum.
        average_num_data_members_in_partition_table += 
            num_data_members_in_partition_table;                    // Add the number of data items to the variable that will be used
                                                                    // to calculate the average number of data members in the partition table.
    }

    average_num_data_members_in_partition_table /= clock;               // Calculate the average number of data members in the partition table.

    one_queue_unequal->average_num_data_members_in_partition_table +=   // Add the previously calculated value to the cumulative value.
        average_num_data_members_in_partition_table;                    // This will be used in the future to get the final average.

    one_queue_unequal->number_of_failures += number_of_failures;        // Add the number of failures for this experiment to the cumulative value.
                                                                        // For use in calculating average.
}