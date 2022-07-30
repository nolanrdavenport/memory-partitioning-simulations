/**************************************************************************************************
 * File: dynamic.cpp
 * Author: Nolan Davenport
 * Procedures:
 * 
 * print_dynamic_partitions     - Prints the current set of partitions in memory for the dynamic 
 *                                partitioning style.
 * 
 * compact                      - Performs the compaction algorithm.
 * 
 * perform_first_fit_algorithm  - Performs the first fit placement algorithm. 
 * 
 * dynamic_partitioning         - Performs the experiment for the dynamic partitioning style that 
 *                                uses the first fit placement algorithm.  
 *************************************************************************************************/

#include<iostream>
#include<random>
#include<queue>
#include<list>

#include"main.h"
#include"dynamic.h"

using namespace std;

/**************************************************************************************************
 * void print_dynamic_partitions(list<DynamicPartition> partitions, Data data[NUMBER_OF_SAMPLES], 
 *                               int next_data)
 * 
 * Author: Nolan Davenport
 * Description: Prints the current set of partitions in memory for the dynamic partitioning style.
 *              Used for debugging purposes.
 * 
 * Parameters:
 *  partitions      I/P     list<DynamicPartition>      The list of dynamic partitions to print.
 *  data            I/P     Data[NUMBER_OF_SAMPLES]     The data used in this experiment.
 *  next_data       I/P     int                         The index of the next data member in the queue. 
 *************************************************************************************************/
void print_dynamic_partitions(list<DynamicPartition> partitions, Data data[NUMBER_OF_SAMPLES], int next_data){
    cout << "dynamic partitions: " << endl;         // Print the title. 

    if(partitions.size() == 0){                     // If there's no partitions:
        cout << "no dynamic partitions" << endl;    // Print that there's no partitions.
    }

    int free_space = 56;                                            // Initialize free_space to the size of memory.
    list<DynamicPartition>::iterator it;                            // Create an iterator to loop through the list.
    for(it = partitions.begin(); it != partitions.end(); ++it){     // Loop through the list.
        DynamicPartition p = *it;                                   // Create a local copy of the DynamicPartition located
                                                                    // at the iterator.

        free_space -= p.size;                                       // Subtract the size of this partition from the freespace.

        cout << "data_index: " << p.data_index << " start: " <<     // Print the data_index and start location.
            p.start_location << " end: " <<                         // Print the end location.
            p.start_location + p.size - 1<< " size: " << p.size;    // Print the size.
        cout << " left: " << data[p.data_index].left << endl;       // Print how much time is left.
    }

    cout << "freespace: " << free_space;                            // Print the amount of freespace in the partition list.
    cout << " size of next data: " << data[next_data].size << endl; // Print the size of the next item in the queue.
    
    cout << endl;                                                   // Next line for aesthetics.
}

/**************************************************************************************************
 * int compact(list<DynamicPartition> &partitions)
 * 
 * Author: Nolan Davenport
 * Description: Performs the compaction algorithm.
 * 
 * Parameters:
 *  partitions      I/O     list<DynamicPartition> (&)      The partitions to compact. 
 *  compact         O/P     int                             The amount of free memory at the end
 *                                                          of main memory after compaction.
 *************************************************************************************************/
int compact(list<DynamicPartition> &partitions){
    list<DynamicPartition>::iterator it;                            // Get an iterator used to loop through the partitions list.

    int index = 0;                                                  // Initialize the index to zero. Used to keep track of where
                                                                    // in the list we are.
    int end_last = -1;                                              // Initialize the end location for the last data member to -1.
                                                                    // This is because for the first element, using -1 means that the
                                                                    // start can be at location 0.

    for(it = partitions.begin(); it != partitions.end(); ++it){     // Loop through the partition list.
        it->start_location = end_last+1;                            // Set the start location to the last partitions end + 1.

        end_last = it->start_location + it->size - 1;               // Set end_last to the end of this partition for use in the next loop.
    }

    return MEMORY_END - end_last;                                   // Return the amount of free memory left after compaction.
}

/**************************************************************************************************
 * void perform_first_fit_algorithm(Data (&data)[NUMBER_OF_SAMPLES], list<DynamicPartition> &partitions, 
                                 int &next_data, int &num_data_members_in_partition_table, int clock, 
                                 int &number_of_failures){

 * Author: Nolan Davenport
 * Description: Performs the first fit placement algorithm. 
 * 
 * Parameters:
 *  data                                I/P     Data (&)[NUMBER_OF_SAMPLES]     The data used in this
 *                                                                              experiment.
 *  partitions                          I/O     list<DynamicPartition> (&)      The partitions to perform
 *                                                                              the first fit placement
 *                                                                              algorithm on. 
 *  next_data                           I/O     int (&)                         The index of the next
 *                                                                              data item in the queue.
 *  num_data_members_in_partition_table O/P     int (&)                         The number of data members
 *                                                                              in memory.
 *  clock                               I/P     int                             The clock value.
 *  number_of_failures                  O/P     int (&)                         The number of failures
 *                                                                              in this experiment.
 *************************************************************************************************/
void perform_first_fit_algorithm(Data (&data)[NUMBER_OF_SAMPLES], list<DynamicPartition> &partitions, 
                                 int &next_data, int &num_data_members_in_partition_table, int clock, 
                                 int &number_of_failures){
                                     
    bool inserting = true;                                  // Boolean variable to keep track of whether to continue inserting
                                                            // items into the list.
    while(inserting && next_data != NUMBER_OF_SAMPLES){
        if(partitions.size() == 0){                 // case of empty partitions list.
            DynamicPartition p;                     // Create a DynamicPartition.
            p.data_index = next_data;               // Set the data_index to the item at the front of the queue.
            p.size = data[next_data].size;          // Set the size to the item at the front of the queue.
            p.start_location = 0;                   // Set the start location to zero since this the list was empty before this.
            partitions.push_back(p);                // Push the DynamicPartition onto the list. 
            num_data_members_in_partition_table++;  // Increment the number of data members in the partition table.

            // TODO: do something with this.
            //data[next_data].time_start = clock+1;
            if(p.size > 56){                        // If the size was greater than the entire memory:
                number_of_failures++;               // Increment the number of failures.
                data[next_data].failure = true;     // Set the failure member to true.
            }

            next_data++;                            // Increment next_data to show the new front of the queue.
        }

        int start = 0;                              // Initialize the start location to zero.
        int end = 0;                                // Initialize the end location to zero.

        list<DynamicPartition>::iterator it;        // Create an iterator to parse through the list.
        int index = 0;                              // Initialize an index to understand where we are in the list.

        int free_space = MEMORY_END+1;              // Create a freespace variable and initialize it to all memory. 
                                                    // This will be used to calculate the free space as the list is parsed.

        for(it = partitions.begin(); it != partitions.end(); ++it){ // Keep looping as long as the iterator isn't at the end.
            free_space -= data[it->data_index].size;                // Subtract the size of the current partition from the freespace.
            DynamicPartition p = *it;                               // Dereference the iterator to easily read the information from
                                                                    // the partition.       

            end = p.start_location - 1;                             // Set the end location to before the start of this partition.
                                                                    // This algorithm works from before a partition, until it reaches
                                                                    // the end, in which case it does something else.

            if(end - start + 1 > data[next_data].size){             // If the hole is greater than the size of the data member that
                                                                    // we're trying to enter into the partition list:
                DynamicPartition new_p;                             // Create a DynamicPartition variable.
                new_p.data_index = next_data;                       // Assign the index to the next_data value, which is the front of
                                                                    // the queue.
                new_p.size = data[next_data].size;                  // Set the partition size to the size of the data member that was added.
                new_p.start_location = start;                       // Set the start location based on the star variable.

                partitions.insert(it, new_p);                       // Insert the new partition before the current partition based on the
                                                                    // iterator.

                num_data_members_in_partition_table++;              // Increment the number of members in the partition table.

                // TODO: do something with this.
                //data[next_data].time_start = clock+1;

                next_data++;                                        // Increment next_data to point to the new front of the queue.

                break;
            }else{                                                  // If the hole isn't large enough to insert the item here:
                start = p.start_location + p.size;                  // Set the start to just after the end of this partition.

                if(index == partitions.size() - 1){                 // If this is the last item in the list:
                    // no more partitions after this point. 
                    end = MEMORY_END;                               // Set the end location to the end of memory.

                    if(end - start + 1 >= data[next_data].size){    // Check if the new data item at the head of the queue can fit
                                                                    // in the last section of memory.
                        DynamicPartition new_p;                     // Create a new dynamic partition.
                        new_p.data_index = next_data;               // Set the data index to the index of the item at the front of the queue.
                        new_p.size = data[next_data].size;          // Set the size of the partition to the size of the data member.
                        new_p.start_location = start;               // Set the start location of the partition.

                        partitions.insert(++it, new_p);             // Increment the iterator and then insert the new item.
                                                                    // This is necessary because this algorithm usually works before
                                                                    // the current partition of the loop, but since we're at the end,
                                                                    // the item needs to be inserted after the current partition of
                                                                    // the loop.

                        num_data_members_in_partition_table++;      // Increment the number of data members in the partition table.

                        // TODO: figure out what to do with this.
                        //data[next_data].time_start = clock+1;

                        next_data++;                                // Increment the next_data value to show the new front of the queue.

                        break;                                      // Break out of the loop since this was the end of memory anyways.
                    }else{                                          // If this isn't the end of memory:
                        if(free_space >= data[next_data].size &&    // If the freespace is greater than the size of the item at the front
                            end - start + 1 < data[next_data].size){// of the queue, and if the last hole in memory is too small:
                            compact(partitions);                    // Perform the compaction algorithm on the partition list.
                            free_space = MEMORY_END+1;              // Set the freespace to full memory to reset the free_space calculation
                                                                    // used in the encompassing while loop.
                            break;
                        }

                        inserting = false;                          // If it got to this point, then there is not enough freespace to
                                                                    // insert the item, which is at the front of the queue, into the 
                                                                    // partition list.
                    }
                }
            }

            index++;                                                // Incremenent the index of the partition to keep track of where we are.
        }
    }
}

/**************************************************************************************************
 * void dynamic_partitioning(Data data[NUMBER_OF_SAMPLES], int number_of_samples, Results* first_fit)

 * Author: Nolan Davenport
 * Description: Performs the experiment for the dynamic partitioning style that uses the first fit 
 *              placement algorithm. 
 * 
 * Parameters:
 *  data                I/P     Data[NUMBER_OF_SAMPLES]     The data to be used in this experiment.
 *  number_of_samples   I/P     int                         The number of samples in this experiment.
 *  first_fit           O/P     Results*                    Pointer to the structure that holds the 
 *                                                          results of this experiment.
 *************************************************************************************************/
void dynamic_partitioning(Data data[NUMBER_OF_SAMPLES], int number_of_samples, Results* first_fit){
    Data experiment_data[NUMBER_OF_SAMPLES];        // Create an array to copy the experiment data.
    for(int i = 0; i < NUMBER_OF_SAMPLES; i++){     // Loop through each array element.
        experiment_data[i] = data[i];               // Copy the data[] array into the experiment_data[] array.
    }

    int next_data = 0;                              // Initialize next_data to zero. This is the index to the front of the queue.

    int number_of_failures = 0;                     // Initialize the number of failures to zero.

    list<DynamicPartition> partitions;              // Create the list of partitions for this experiment.

    int num_data_members_in_partition_table = 0;    // Initialize the number of data members in the partition table to zero.

    int clock = 0;                                  // Initialize the clock to zero.
    
    perform_first_fit_algorithm(experiment_data,    // Perform the first fit algorithm on the list of partitions and the experiment data.
        partitions, next_data, 
        num_data_members_in_partition_table, 
        clock, number_of_failures);

    list<DynamicPartition>::iterator it =           // Make an iterator to parse through the list.
        partitions.begin();

    float average_num_data_members_in_partition_table = 0;  // Initialize the average number of data members in the partition
                                                            // table to zero.

    for(;;){                                                    // Clock loop.
        experiment_data[it->data_index].left -= 1;              // Decrement the time left for the data at the current partition.
                                                                // This is to simulate work for one quantum.

        bool just_erased_a_partition = false;                   // Initialize a boolean variable that can track if we just deleted
                                                                // a partition. This will help with tracking the iterator.

        if(experiment_data[it->data_index].left == 0){          // If the data is finishe processing:
            experiment_data[it->data_index].time_end = clock;   // Set the end time for the current data to the clock.

            experiment_data[it->data_index].turn_around_time = clock -      // Calculate the turnaround time for the data member.
                experiment_data[it->data_index].time_start;

            first_fit->turn_around_time +=                                  // Add this data's turnaround time to the cumulative variable.
            experiment_data[it->data_index].turn_around_time;               // This is how the average is calculated.

            first_fit->relative_turn_around_time +=                         // Calculate the relative turnaround time and add it to the
                (float)experiment_data[it->data_index].turn_around_time /   // cumulative variable used to calculate the average.
                experiment_data[it->data_index].time;


            list<DynamicPartition>::iterator it_temp = it++;                // Create a temporary iterator variable and increment the original.
            partitions.erase(it_temp);                                      // Erase the partition located at the iterator.
            just_erased_a_partition = true;                                 // Set this boolean to true.

            int size_before_first_fit = partitions.size();                  // The size of the partition list before the first_fit algorithm.

            num_data_members_in_partition_table--;                          // Decrement the number of data members in the partition table.

            perform_first_fit_algorithm(experiment_data, partitions,        // Perform the first_fit algorithm.
                next_data, num_data_members_in_partition_table, clock, 
                number_of_failures);
            
            if(num_data_members_in_partition_table == 0){                   // If the partition list is empty:
                break;                                                      // Break out of the loop to end the experiment.
            }else if(size_before_first_fit == 0){                           // If the size before the first_fit algorithm was zero,
                                                                            // then the old iterator probably isn't good anymore.
                it = partitions.begin();                                    // Set the iterator to the beginning of list to reset it.
            }
        }

        if(!just_erased_a_partition){       // If a partition wasn't erased, then the iterator wasn't incremented. 
            it++;                           // Increment the iterator.
        }

        if(it == partitions.end()){         // If the iterator is at the end of the list:
            it = partitions.begin();        // Set it to the beginning to continue looping.
        }
        

        clock++;                                                // Increment the clock.
        average_num_data_members_in_partition_table +=          // Add the number of data members in the partition to this variable.
        num_data_members_in_partition_table;                    // This is used to calculate the average.
    }   

    average_num_data_members_in_partition_table /= clock;       // Calculate the average number of data members in the partition table.

    first_fit->average_num_data_members_in_partition_table +=   // Add the average number of data members to the cumulative variable used
        average_num_data_members_in_partition_table;            // to calculate the average later on.
    first_fit->number_of_failures += number_of_failures;        // Add the number of failures to the cumulative variable used to calculate
                                                                // the average.
}