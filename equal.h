/**************************************************************************************************
 * File: equal.h
 * Author: Nolan Davenport
 * Procedures:
 * 
 * equal_partitioning   - Performs the experiment for the equal partitioning style. 
 *************************************************************************************************/

#pragma once

#include<iostream>
#include<random>
#include<queue>
#include<list>

#include"main.h"

// Function prototype
void equal_partitioning(Data e[NUMBER_OF_SAMPLES], int number_of_samples, Results* equal);