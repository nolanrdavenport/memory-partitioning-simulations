/**************************************************************************************************
 * File: multiple_queues_unequal.h
 * Author: Nolan Davenport
 * Procedures:
 * 
 * preprocess_multiple_queues           - Places the experiment data into the multiple queues based 
 *                                        on their sizes. 
 * 
 * multiple_queues_unequal_partitioning - Performs the experiment for multiple queues using an 
 *                                        unequal partitioning style. 
 *************************************************************************************************/

#pragma once

#include<iostream>
#include<random>
#include<queue>
#include<list>

#include"main.h"

using namespace std;

// Function prototypes
void preprocess_multiple_queues(queue<Data> (&queues)[7], Data(&e)[NUMBER_OF_SAMPLES], int &number_of_failures);
void multiple_queues_unequal_partitioning(Data e[NUMBER_OF_SAMPLES], int number_of_samples, Results* multiple_queues_unequal);