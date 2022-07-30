/**************************************************************************************************
 * File: main.cpp
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

#include<iostream>
#include<random>
#include<queue>
#include<list>
#include<ctime>

#include"main.h"
#include"equal.h"
#include"one_queue_unequal.h"
#include"multiple_queues_unequal.h"
#include"dynamic.h"

using namespace std;

/**************************************************************************************************
 * void setup_unequal_static_partitions(StaticPartition (&partitions)[7])
 * 
 * Author: Nolan Davenport
 * Description: Sets up the sizes for the unequal partitions and initializes each partition. 
 * 
 * Parameters:
 *  partitions  I/O     StaticPartition (&)[7]      The partition table that will have unequal sizes. 
 *************************************************************************************************/
void setup_unequal_static_partitions(StaticPartition (&partitions)[7]){
    partitions[0].size = 2;     // Partition 0 is 2MB large.
    partitions[1].size = 4;     // Partition 1 is 4MB large.
    partitions[2].size = 6;     // Partition 2 is 6MB large.
    partitions[3].size = 8;     // Partition 3 is 8MB large.
    partitions[4].size = 8;     // Partition 4 is 8MB large.
    partitions[5].size = 12;    // Partition 5 is 12MB large.
    partitions[6].size = 16;    // Partition 6 is 16MB large.
}

/**************************************************************************************************
 * void report_results(Results* equal, Results* one_queue_unequal, 
 *                     Results* multiple_queues_unequal, Results* first_fit)
 * 
 * Author: Nolan Davenport
 * Description: Reports the results after all experiments are complete. 
 * 
 * Parameters:
 *  equal                       I/P     Results*    The results for the equal partition style experiments.
 *  one_queue_unequal           I/P     Results*    The results for the one queue unequal partition style 
 *                                                  experiments. 
 *  multiple_queues_unequal     I/P     Results*    The results for the multiple queues unequal partition
 *                                                  style experiments. 
 *  first_fit                   I/P     Results*    The results for the dynamic partitioning experiments 
 *                                                  that uses the first fit placement algorithm. 
 *************************************************************************************************/
void report_results(Results* equal, Results* one_queue_unequal, 
                    Results* multiple_queues_unequal, Results* first_fit){
    
    // Calculate the results for the equal partition style. 
    equal->number_of_failures =                             // This value was calculated once per experiment, so
        equal->number_of_failures / NUMBER_OF_EXPERIMENTS;  // to get the average, divide by NUMBER_OF_EXPERIMENTS. 

    equal->turn_around_time =                               // turn_around_time held the total
        equal->turn_around_time /                           // turnaround time. To get the average, divide
        (NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES);        // by NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES.

    equal->relative_turn_around_time =                      // relative_turn_around_time held the total
        equal->relative_turn_around_time /                  // relative turnaround time. To get the average, divide
        (NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES);        // by NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES.

    equal->average_num_data_members_in_partition_table /=   // this value was calculated once per experiment, so
        NUMBER_OF_EXPERIMENTS;                              // only divide by NUMBER_OF_EXPERIMENTS. 

    // Calculate the results for the one queue unequal partition style. 
    one_queue_unequal->number_of_failures =                             // This value was calculated once per experiment, so
        one_queue_unequal->number_of_failures / NUMBER_OF_EXPERIMENTS;  // to get the average, divide by NUMBER_OF_EXPERIMENTS. 

    one_queue_unequal->turn_around_time =                               // turn_around_time held the total
        one_queue_unequal->turn_around_time /                           // turnaround time. To get the average, divide
        (NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES);                    // by NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES.

    one_queue_unequal->relative_turn_around_time =                      // relative_turn_around_time held the total
        one_queue_unequal->relative_turn_around_time /                  // relative turnaround time. To get the average, divide
        (NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES);                    // by NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES.

    one_queue_unequal->average_num_data_members_in_partition_table /=   // this value was calculated once per experiment, so
        NUMBER_OF_EXPERIMENTS;                                          // only divide by NUMBER_OF_EXPERIMENTS. 

    // Calculate the results for the multiple queue unequal partition style.
    multiple_queues_unequal->number_of_failures =                           // This value was calculated once per experiment, so
        multiple_queues_unequal->number_of_failures / NUMBER_OF_EXPERIMENTS;// to get the average, divide by NUMBER_OF_EXPERIMENTS. 

    multiple_queues_unequal->turn_around_time =                             // turn_around_time held the total
        multiple_queues_unequal->turn_around_time /                         // turnaround time. To get the average, divide
        (NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES);                        // by NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES.

    multiple_queues_unequal->relative_turn_around_time =                    // relative_turn_around_time held the total
        multiple_queues_unequal->relative_turn_around_time /                // relative turnaround time. To get the average, divide
        (NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES);                        // by NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES.

    multiple_queues_unequal->average_num_data_members_in_partition_table /= // this value was calculated once per experiment, so
        NUMBER_OF_EXPERIMENTS;                                              // only divide by NUMBER_OF_EXPERIMENTS. 

    // Calculate the results for the dynamic partition style using first_fit. 
    first_fit->number_of_failures =                             // This value was calculated once per experiment, so
        first_fit->number_of_failures / NUMBER_OF_EXPERIMENTS;  // to get the average, divide by NUMBER_OF_EXPERIMENTS. 

    first_fit->turn_around_time =                               // turn_around_time held the total
        first_fit->turn_around_time /                           // turnaround time. To get the average, divide
        (NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES);            // by NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES.

    first_fit->relative_turn_around_time =                      // relative_turn_around_time held the total
        first_fit->relative_turn_around_time /                  // relative turnaround time. To get the average, divide
        (NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES);            // by NUMBER_OF_EXPERIMENTS * NUMBER_OF_SAMPLES.

    first_fit->average_num_data_members_in_partition_table /=   // this value was calculated once per experiment, so
        NUMBER_OF_EXPERIMENTS;                                  // only divide by NUMBER_OF_EXPERIMENTS. 
    
    // Print results for the equal partition style. 
    cout << "equal average number_of_failures: " <<                         // Print average number of failures.
        equal->number_of_failures << endl;
    cout << "equal average turn_around_time: " <<                           // Print average turnaround time. 
        equal->turn_around_time << endl;
    cout << "equal average relative_turn_around_time: " <<                  // Print average relative turnaround time. 
        equal->relative_turn_around_time << endl;
    cout << "equal average number of data members in StaticPartition table: " <<  // Print average number of members in partition table. 
        equal->average_num_data_members_in_partition_table << endl << endl;

    // Print results for the one queue unequal partition style. 
    cout << "one_queue average number_of_failures: " <<                         // Print average number of failures.
        one_queue_unequal->number_of_failures << endl;
    cout << "one_queue average turn_around_time: " <<                           // Print average turnaround time. 
        one_queue_unequal->turn_around_time << endl;
    cout << "one_queue average relative_turn_around_time: " <<                  // Print average relative turnaround time.
        one_queue_unequal->relative_turn_around_time << endl;
    cout << "one_queue average number of data members in StaticPartition table: " <<  // Print average number of members in partition table. 
        one_queue_unequal->average_num_data_members_in_partition_table << endl << endl; 

    // Print results for the multiple queue unequal partition style.
    cout << "multiple_queue average number_of_failures: " <<                            // Print average number of failures.
        multiple_queues_unequal->number_of_failures << endl;
    cout << "multiple_queue average turn_around_time: " <<                              // Print average turnaround time. 
        multiple_queues_unequal->turn_around_time << endl;
    cout << "multiple_queue average relative_turn_around_time: " <<                     // Print average relative turnaround time.
        multiple_queues_unequal->relative_turn_around_time << endl;
    cout << "multiple_queue average number of data members in StaticPartition table: " <<     // Print average number of members in partition table. 
        multiple_queues_unequal->average_num_data_members_in_partition_table << endl << endl;

    // Prints results for the dynamic partition style using first_fit. 
    cout << "dynamic average number_of_failures: " <<                         // Print average number of failures.
        first_fit->number_of_failures << endl;
    cout << "dynamic average turn_around_time: " <<                           // Print average turnaround time. 
        first_fit->turn_around_time << endl;
    cout << "dynamic average relative_turn_around_time: " <<                  // Print average relative turnaround time.
        first_fit->relative_turn_around_time << endl;
    cout << "dynamic average number of data members in DynamicPartition list: " <<  // Print average number of members in partition table. 
        first_fit->average_num_data_members_in_partition_table << endl << endl;
}

/**************************************************************************************************
 * int main(int argc, char* argv[])
 * 
 * Author: Nolan Davenport
 * Description: Entry point for this program. Initializes the data and initiates the experiments. 
 * 
 * Parameters:
 *  argc    I/P     int         The number of arguments on the command line.
 *  argv    I/P     char *[]    The arguments on the command line.
 *  main    O/P     int         Status code (not currently used).
 *************************************************************************************************/
int main(int argc, char* argv[]){
    // Create structures that will hold the results. 
    Results* equal = new Results();                     // Create the Results structure for the equal partitioning style. 
    Results* one_queue_unequal = new Results();         // Create the Results structure for the one queue unequal partitioning style. 
    Results* multiple_queues_unequal = new Results();   // Create the Results structure for the multiple queues unequal partitioning style.
    Results* first_fit = new Results();                 // Create the Results structure for the dynamic partitioning style. 

    time_t seed = time(nullptr);    // Create a seed based on the current time to ensure randomness.
    default_random_engine gen;      // The random engine to generate random numbers. 
    gen.seed(seed);                 // Set the engines seed based on the time. 

    poisson_distribution<int> poisson_dist(8);          // Create the poisson distribution to use for the size.
                                                        // This uses a mean of 8. 
    uniform_int_distribution<int> uniform_dist(1,10);   // Create the uniform distribution to use for the time. 
                                                        // It will have values 1 through 10 inclusively. 

    for(int experiment = 0; experiment < NUMBER_OF_EXPERIMENTS; experiment++){  // Loop through experiments. 
        Data experiment_data[NUMBER_OF_SAMPLES];                        // Create data array for use in exp    
        for(int sample = 0; sample < NUMBER_OF_SAMPLES; sample++){      // Loop through samples. 
            experiment_data[sample].size = max(1, poisson_dist(gen));   // Set the size of the sample according to the
                                                                        // poisson distribution made earlier. 

            experiment_data[sample].time = uniform_dist(gen);           // Sets the time based on uniform distribution
                                                                        // made earlier. 

            // Setting a couple other members
            experiment_data[sample].index = sample;                         // This member helps us know the data index for
                                                                            // use in partitioning. 
            experiment_data[sample].left = experiment_data[sample].time;    // Initiate the time left to the time. 
        }

        equal_partitioning(experiment_data, NUMBER_OF_SAMPLES, equal);  // Perform equal partitions experiment.

        one_queue_unequal_partitioning(experiment_data,                 // Perform one queue unequal experiment.
            NUMBER_OF_SAMPLES, one_queue_unequal);

        multiple_queues_unequal_partitioning(experiment_data,           // Perform multiple queues unequal experiment.
            NUMBER_OF_SAMPLES, multiple_queues_unequal);   

        dynamic_partitioning(experiment_data,                           // Perform dynamic partitioning experiment.
            NUMBER_OF_SAMPLES, first_fit);
    }

    report_results(equal, one_queue_unequal, multiple_queues_unequal, first_fit);   // Report the results. 

    // Delete each Results structure pointer. 
    delete equal;                   // Delete the equal Results structure pointer. 
    delete one_queue_unequal;       // Delete the one_queue_unequal Results structure pointer. 
    delete multiple_queues_unequal; // Delete the multiple_queues_unequal Results structure pointer. 
    delete first_fit;               // Delete the first_fit Results structure pointer. 

    return 0;                       // Return to end the program.
}