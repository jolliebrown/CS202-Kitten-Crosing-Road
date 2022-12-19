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
//int generateNextLaneIndex(int status = 0) {
//    static int nLane = 0;
//    static int freq[3] = { 5, 5, 2 };
//    nLane += 1;
//    if (nLane % 10 == 0) {
//        if (freq[0] > 2) {
//            freq[0]--;
//            freq[1]++;
//        }
//    }
//    vector<int> randLanes;
//    for (int i = 0; i < 3; i++)
//        for (int j = 0; j < freq[i]; j++) randLanes.push_back(i);
//    int nums = Rand(2, 5);
//    for (int i = 0; i < nums; i++)
//        //random_shuffle(randLanes.begin(), randLanes.end());
//        return randLanes[0];
//}
//
//vector <int> generateRangeLanes(int l, int r) {
//    int freq[3] = { 5, 5, 2 };
//    vector <int> ret;
//    for (int nLane = l; nLane <= r; nLane++) {
//        if (nLane % 10 == 0) {
//            if (freq[0] > 2) {
//                freq[0]--;
//                freq[1]++;
//            }
//        }
//        vector<int> randLanes;
//        for (int i = 0; i < 3; i++)
//            for (int j = 0; j < freq[i]; j++) randLanes.push_back(i);
//        int nums = Rand(2, 5);
//        for (int i = 0; i < nums; i++)
//            //random_shuffle(randLanes.begin(), randLanes.end());
//            ret.push_back(randLanes[0]);
//    }
//    return ret;
//}