/**************************************************************************************************
 * File: dynamic.h
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

#pragma once

#include<iostream>
#include<random>
#include<queue>
#include<list>

#include"main.h"

using namespace std;

// Function prototypes
void print_dynamic_partitions(list<DynamicPartition> partitions, Data e[NUMBER_OF_SAMPLES], int next_data);
int compact(list<DynamicPartition> &partitions);
void perform_first_fit_algorithm(Data (&e)[NUMBER_OF_SAMPLES], list<DynamicPartition> &partitions, int &next_data, int &num_data_members_in_partition_table, int clock, int &number_of_failures);
void dynamic_partitioning(Data e[NUMBER_OF_SAMPLES], int number_of_samples, Results* first_fit);