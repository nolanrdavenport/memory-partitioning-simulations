/**************************************************************************************************
 * File: one_queue_unequal.h
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

#pragma once

#include<iostream>
#include<random>
#include<queue>
#include<list>

#include"main.h"

// Function prototypes
void one_queue_fill_unequal_partitions(Data (&e)[NUMBER_OF_SAMPLES], int &next_data, int &number_of_failures, StaticPartition (&p)[7], int &n, int clock);
void one_queue_unequal_partitioning(Data e[NUMBER_OF_SAMPLES], int number_of_samples, Results* one_queue_unequal);