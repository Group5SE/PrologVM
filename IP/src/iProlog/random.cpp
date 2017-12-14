
#include <iostream>
#include <vector>

using namespace std;
namespace iProlog{

    vector <int> a = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    int seed = 23456;
    int random(int seed)
    {
        int sqn = seed*seed;
        int next_num=0;
        int trim = 4;
        sqn = sqn / a[trim];
        for(int i=0; i < 6; i++){
            next_num += (sqn%(a[trim]))*(a[i]);
            sqn = sqn/10;
        }
        return next_num;
    }
}

/*
    C++ OUTPUT:
    Enter the #-digit random numbers you want: 3
290, 410, 810, 610, 210, 410, 810, 610, 210,
C:\Users\karth\Desktop>a.exe
Enter the #-digit random numbers you want: 4
1049, 12004, 41920, 75724, 93128, 37787, 87143, -60641, -82724

JAVA OUTPUT:
Enter the #-digit random numbers you want:
3
The random numbers are:
290, 410, 810, 610, 210, 410, 810, 610, 210, ...
Enter the #-digit random numbers you want:
4
The random numbers are:
1049, 12004, 41920, 75724, 93128, 37787, 87143, -60641, -82724, ...
*/