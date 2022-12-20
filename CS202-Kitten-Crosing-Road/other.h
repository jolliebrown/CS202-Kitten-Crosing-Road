#pragma once
#include <iomanip>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

long long Rand(long long l, long long h); // get a random long long number in range [L, H]
int generateNextLaneIndex(int status = 0);
vector <int> generateRangeLanes(int l, int r);
//bool genArray(int n, long long low, long long high, string path); // generate n numbers in range [low, high] to path file
//void runningTime(clock_t start); // time ?
//void runningTime(clock_t start, string mess);

// ---------------------------random functions---------------------------------------------------------------------
//
//long long Rand(long long l, long long h)
//{
//    //srand(time(NULL));
//    return l + (
//        (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
//        (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
//        (long long)rand() * (RAND_MAX + 1) +
//        (long long)rand())
//        % (h - l + 1);
//}
//
