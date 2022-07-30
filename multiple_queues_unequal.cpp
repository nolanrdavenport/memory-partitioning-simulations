/**************************************************************************************************
 * File: multiple_queues_unequal.cpp
 * Author: Nolan Davenport
 * Procedures:
 * 
 * preprocess_multiple_queues           - Places the experiment data into the multiple queues based 
 *                                        on their sizes. 
 * 
 * multiple_queues_unequal_partitioning - Performs the experiment for multiple queues using an 
 *                                        unequal partitioning style. 
 *************************************************************************************************/

#include<iostream>
#include<random>
#include<queue>
#include<list>

#include"main.h"
#include"multiple_queues_unequal.h"

using namespace std;

/**************************************************************************************************
 * void preprocess_multiple_queues(queue<Data> (&queues)[7], Data(&data)[NUMBER_OF_SAMPLES], 
 *                                 int &number_of_failures)
 * 
 * Author: Nolan Davenport
 * Description: Places the experiment data into the multiple queues based on their sizes. 
 * 
 * Parameters:
 *  queues                  I/O     queue<Data> (&)[7]              The queues that will hold the data 
 *                                                                  before it gets processed.
 *  data                    I/P     Data (&)[NUMBER_OF_SAMPLES]     The data for this experiment.
 *  number_of_failures      O/P     int (&)                         The number of failures for this
 *                                                                  experiment. 
 *************************************************************************************************/
void preprocess_multiple_queues(queue<Data> (&queues)[7], Data(&data)[NUMBER_OF_SAMPLES], 
                                int &number_of_failures){

    enum LAST_8MB_USED{         // An enumeration that is used to handle the fact that there's two 8MB partitions.
        FIRST,                  // First 8MB partition.
        SECOND                  // Second 8MB partition.
    } last_8mb_used;            // Create the variable.
    last_8mb_used = SECOND;     // Initialize it to SECOND so that the first is used.

    for(int i = 0; i < NUMBER_OF_SAMPLES; i++){     // Loop through all samples.
        if(data[i].size <= 2){              // If the size of the data is <= 2MB:
            queues[0].push(data[i]);        // Put it in the first queue.
        }else if(data[i].size <= 4){        // If the size of the data is <= 4MB:
            queues[1].push(data[i]);        // Put it in the second queue.
        }else if(data[i].size <= 6){        // If the size of the data is <= 6MB:
            queues[2].push(data[i]);        // Put it in the third queue.
        }else if(data[i].size <= 8){        // If the size of the data is <= 8MB:
            if(last_8mb_used == SECOND){    // If the last queue used was the 2nd 8MB queue:
                last_8mb_used = FIRST;      // Set the last 8MB used to the FIRST 8MB queue.
                queues[3].push(data[i]);    // Put it in the fourth queue.    
            }else{                          // Otherwise:
                last_8mb_used = SECOND;     // Set the last 8MB used to the SECOND 8MB queue.
                queues[4].push(data[i]);    // Put it in the fifth queue.
            }
        }else if(data[i].size <= 12){       // If the size of the data is <= 12MB:
            queues[5].push(data[i]);        // Put it in the sixth queue.
        }else{                              // If the size is > 12MB:
            queues[6].push(data[i]);        // Put it in the seventh queue.
            
            if(data[i].size > 16){          // If the size of the data is > 16MB:
                number_of_failures++;       // Increment the number of failures.
            }
        }
    }
}

/**************************************************************************************************
 * void multiple_queues_unequal_partitioning(Data data[NUMBER_OF_SAMPLES], int number_of_samples, 
 *                                           Results* multiple_queues_unequal)
 * 
 * Author: Nolan Davenport
 * Description: Performs the experiment for multiple queues using an unequal partitioning style.
 * 
 * Parameters:
 *  data                        I/P     Data[NUMBER_OF_SAMPLES]     The data to be used in this
 *                                                                  experiment.
 *  number_of_samples           I/P     int                         The number of samples in this
 *                                                                  experiment.
 *  multiple_queues_unequal     O/P     Results*                    Pointer to the structure that holds
 *                                                                  the results of this experiment. 
 *************************************************************************************************/
void multiple_queues_unequal_partitioning(Data data[NUMBER_OF_SAMPLES], int number_of_samples, 
                                          Results* multiple_queues_unequal){

    Data experiment_data[NUMBER_OF_SAMPLES];        // Create an array to copy the experiment data.
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++){     // Loop through each array element.
        experiment_data[i] = data[i];               // Copy the data[] array into the experiment_data[] array.
    }

    int number_of_failures = 0;                     // Initialize the number of failures to zero.

    queue<Data> queues[7];                          // Create an array of queues of type Data. These are the multiple queues.
    preprocess_multiple_queues(queues, experiment_data, number_of_failures);    // Preprocess the data array into the multiple queues.


    // Setup StaticPartition table
    StaticPartition partitions[7];                  // Create an array of static partitions. These are the partitions in memory.
    setup_unequal_static_partitions(partitions);    // Setup the partitions to have the correct unequal values.

    int num_data_members_in_partition_table = 0;    // Initialize the number of data members in the partition table to zero.

    for(int i = 0; i < 7; i++){                     // Loop through the partitions.
        if(!queues[i].empty()){                     // As long as the queue for the partition isn't empty:
            Data data = queues[i].front();          // Store the value of the front of the queue in a temp variable.
            queues[i].pop();                        // Pop off the front of the queue and discard.
            partitions[i].data_index = data.index;  // Set the index of the data member at the front of the queue in
                                                    // the partition.
            num_data_members_in_partition_table++;  // Increment the number of data items in the partition table.
        }
    }

    int curr_partition = 0;                         // Initialize the current partition to zero. Start at zero.

    int clock = 0;                                  // Initialize the clock to zero. Start at time zero.

    float average_num_data_members_in_partition_table = 0;      // Initialize the average number of data members in the partition
                                                                // table to zero. This is used to find the average later on.

    for(;;){                                                    // Clock loop.
        if(partitions[curr_partition].data_index == -1){        // If the current partition is empty:
            curr_partition = (curr_partition + 1) % 7;          // Go to the next partition without incrementing the clock.
                                                                // Loop back around to zero if it reaches 7.
            continue;                                           // Continue to skip everything below and work on the next partition.
        }

        experiment_data[partitions[curr_partition].data_index].left -= 1;       // Decrement the time left for this partition. This 
                                                                                // simulates "work" being done for one quantum.

        if(experiment_data[partitions[curr_partition].data_index].left == 0){           // If left is zero, then this data is finished.
            experiment_data[partitions[curr_partition].data_index].time_end = clock;    // Set the end time for this data to the clock.

            experiment_data[partitions[curr_partition].data_index].turn_around_time = clock -   // Calculate the turnaround time for this data.
                experiment_data[partitions[curr_partition].data_index].time_start;

            multiple_queues_unequal->turn_around_time +=                                            // Add this data's turnaround time to the cumulative
            experiment_data[partitions[curr_partition].data_index].turn_around_time;                // turnaround time. This is used in calcualting the 
                                                                                                    // average.

            multiple_queues_unequal->relative_turn_around_time +=                                   // Calculate the relative turnaround time for this
                (float)experiment_data[partitions[curr_partition].data_index].turn_around_time /    // data and add the result to the cumulative relative
                experiment_data[partitions[curr_partition].data_index].time;                        // turnaround time. This is used in calculating the average
                                                                                                    // relative turnaround time.

            partitions[curr_partition].data_index = -1; // Clear this partition by setting the data_index to -1.
            num_data_members_in_partition_table--;      // Decrement the number of data members in the partition table.
            
            if(!queues[curr_partition].empty()){                    // If the queue for this partition isn't empty.
                Data data = queues[curr_partition].front();         // Take the item at the front of the queue.
                queues[curr_partition].pop();                       // Pop the front to discard.
                partitions[curr_partition].data_index = data.index; // Set the index of this partition to the item that was at the
                                                                    // front of the queue.

                // TODO: do something about this.
                //experiment_data[partitions[curr_partition].data_index].time_start = clock+1;

                num_data_members_in_partition_table++;              // Increment the number of data members in the partition table.
            }else if(num_data_members_in_partition_table == 0){     // Else if the number of data members in the partition table is zero.
                                                                    // Meaning there's no more data to process.
                break;                                              // Break out of the loop to end this experiment.
            }
        }

        curr_partition = (curr_partition + 1) % 7;                  // Increments the current partition, looping back around to 0 if it reaches 7. 
        clock++;                                                    // Increments the clock after each quantum.
        average_num_data_members_in_partition_table += 
            num_data_members_in_partition_table;                    // Add the number of data items to the variable that will be used
                                                                    // to calculate the average number of data members in the partition table.
    }

    average_num_data_members_in_partition_table /= clock;                       // Calculate the average number of data members in the
                                                                                // partition table.

    multiple_queues_unequal->average_num_data_members_in_partition_table +=     // Add the average (calculated just above) to the cumulative
        average_num_data_members_in_partition_table;                            // value used to get the average.
    multiple_queues_unequal->number_of_failures += number_of_failures;          // Add the number of failures to the cumulative value.
                                                                                // Used to get the average number of failures.

}