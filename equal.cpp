/**************************************************************************************************
 * File: equal.cpp
 * Author: Nolan Davenport
 * Procedures:
 * 
 * equal_partitioning   - Performs the experiment for the equal partitioning style. 
 *************************************************************************************************/

#include<iostream>
#include<random>
#include<queue>
#include<list>

#include"main.h"
#include"equal.h"

using namespace std;

/**************************************************************************************************
 * void equal_partitioning(Data data[NUMBER_OF_SAMPLES], int number_of_samples, Results* equal)
 * 
 * Author: Nolan Davenport
 * Description: Performs the experiment for the equal partitioning style. 
 * 
 * Parameters:
 *  data                I/P     Data[NUMBER_OF_SAMPLES]     The data to be used in this experiment.
 *  number_of_samples   I/P     int                         The number of samples in this experiment.
 *  equal               O/P     Results*                    Pointer to the structure that holds the 
 *                                                          results of this experiment.
 *************************************************************************************************/
void equal_partitioning(Data data[NUMBER_OF_SAMPLES], int number_of_samples, Results* equal){
    Data experiment_data[NUMBER_OF_SAMPLES];        // Create an array to copy the experiment data.
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++){     // Loop through each array element.
        experiment_data[i] = data[i];               // Copy the data[] array into the experiment_data[] array.
    }

    int number_of_failures = 0;                     // Initialize number of failures to zero.

    // Initially assign the first 7 tasks/data
    StaticPartition partitions[7];                          // Create the array of static partitions. 
    for(int i = 0; i < min(7, NUMBER_OF_SAMPLES); i++){     // Loop through the partitions.
        partitions[i].size = 8;                             // Set the size of the partition to 8MB.
        partitions[i].data_index = i;                       // Set the data index for the partition to the looping variable.
        experiment_data[i].time_start = 0;                  // Set the start time to zero.
        if(experiment_data[i].size > 8){                    // If the size of the data is greater than 8MB:
            experiment_data[i].failure = true;              // Count it as a failure.
            number_of_failures++;                           // Increment the number of failures.
        }
    }

    int num_data_members_in_partition_table =       // Set the number of data members in the partition table.
        min(7, NUMBER_OF_SAMPLES);

    int next_data = min(7, NUMBER_OF_SAMPLES);      // Set the next data element in the queue as the index into the data array.
    int curr_partition = 0;                         // Initialize the current partition to zero.

    int clock = 0;                                  // Initialize the clock to zero.

    float average_num_data_members_in_partition_table = 0;      // Initialize the average number of data members in the parition
                                                                // table to zero.
    for(;;){                                                    // Clock loop.
        if(partitions[curr_partition].data_index == -1){        // If the partition is empty:
            curr_partition = (curr_partition + 1) %             // Increment curr_partition, looping back to zero if it reaches 7.
                min(7, NUMBER_OF_SAMPLES);
            continue;
        }

        experiment_data[partitions[curr_partition].data_index].left -= 1;       // Decrement the time left for the partition that
                                                                                // the "processor" is one. This simulates work for 
                                                                                // one quantum. 
        if(experiment_data[partitions[curr_partition].data_index].left == 0){   // If left is zero, then the data is finished processing.

            experiment_data[partitions[curr_partition].data_index].time_end = clock;    // Set the end time to the clock value. 

            experiment_data[partitions[curr_partition].data_index].turn_around_time = clock -   // Calculate the turnaround time as the
                experiment_data[partitions[curr_partition].data_index].time_start;              // endtime - startime.

            equal->turn_around_time +=                                                  // Add the turnaround time to the cumulative
            experiment_data[partitions[curr_partition].data_index].turn_around_time;    // variable that is used for calculating the
                                                                                        // average turnaround time.
            equal->relative_turn_around_time +=       // Calculate the relative turnaround time and add to cumulative variable.
                (float)experiment_data[partitions[curr_partition].data_index].turn_around_time /    // This is used to calculate
                experiment_data[partitions[curr_partition].data_index].time;                        // the average later on.

            if(next_data != NUMBER_OF_SAMPLES){                         // If the queue isn't empty:
                partitions[curr_partition].data_index = next_data;      // Then add the item at the front of the queue to the
                                                                        // partition.
                next_data++;                                            // Increment the next_data variable to put the next
                                                                        // data member at the front of the queue.
                // TODO: do something with this.
                //experiment_data[partitions[curr_partition].data_index].time_start = clock+1;
                if(experiment_data[partitions[curr_partition].data_index].size > 8){    // If the data item size that was just added
                                                                                        // is greater that 8MB, count it as a failure.
                    number_of_failures++;                                               // Increment the number of failures.
                }
            }else{
                partitions[curr_partition].data_index = -1;     // If the queue is empty, then set the partition to empty.
                num_data_members_in_partition_table--;          // Decrement the number of data members in the partition table.
                if(num_data_members_in_partition_table == 0){   // If the number of data members is zero:
                    break;                                      // The experiment is done, break out of the loop.
                }
            }
        }
        curr_partition = (curr_partition + 1) %                 // Increment curr_partition, looping back to zero if it 
            min(7, NUMBER_OF_SAMPLES);                          // reaches min(7, NUMBER_OF_SAMPLES).

        clock++;                                                // Increment the clock.

        average_num_data_members_in_partition_table +=          // Add the number of data members in the partition to the cumulative
            num_data_members_in_partition_table;                // average variable. This will be used to get the average.
    }

    average_num_data_members_in_partition_table /= clock;   // Calculate the average number of data members in the partition table.

    equal->average_num_data_members_in_partition_table +=   // Add the number to the cumulative variable. Will be used to calculate
        average_num_data_members_in_partition_table;        // the average later on.

    equal->number_of_failures += number_of_failures;        // Add the number of failures to the cumulative number of failures. Will be
                                                            // used in calculating the average later on.
}