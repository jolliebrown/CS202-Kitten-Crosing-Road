#pragma once
#include "other.h"
//using namespace std;
//
//
//// ---------------------------random functions---------------------------------------------------------------------
//
long long Rand(long long l, long long h)
{
    //srand(time(NULL));
    return l + (
        (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
        (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
        (long long)rand() * (RAND_MAX + 1) +
        (long long)rand())
        % (h - l + 1);
}
//
//bool genArray(int n, long long low, long long high, string path) {
//    ofstream f(path);
//    if (!f.is_open()) {
//        cout << "Can't open file " << path << endl;
//        return false;
//    }
//    f << n << endl;
//    for (int i = 0; i < n; i++) {
//        long long getNumber = Rand(low, high);
//        f << getNumber << " ";
//    }
//    f.close();
//    return true;
//}
//
//// ---------------------------running time-------------------------------------------------------------
//
//void runningTime(clock_t start) {
//    double time = (double)(clock() - start) / CLOCKS_PER_SEC;
//    cout << "Running time: " << time << "s\n";
//}
//
//void runningTime(clock_t start, string mess) {
//    double time = (double)(clock() - start) / CLOCKS_PER_SEC;
//    cout << "Running time " << mess << ": " << time << "s\n";
//}
//





vector <int> generateRangeLanes(int l, int r){
    int freq[3] = { 6, 4, 2 };
    vector <int> ret;
    for (int nLane = l; nLane <= r; nLane++) {
        if (nLane % 10 == 0) {
            if (freq[0] > 2) {
                freq[0]--;
                freq[1]++;
            }
        }
        vector<int> randLanes;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < freq[i]; j++) randLanes.push_back(i);
        int nums = Rand(2, 5);
       // for (int i = 0; i < nums; i++)
         //   random_shuffle(randLanes.begin(), randLanes.end());
        int id = Rand(0, randLanes.size() - 1);
        ret.push_back(randLanes[id]);
        for (int u : randLanes) cout << u << " ";
        cout << endl;
    }
    
    return ret;
}