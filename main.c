//
//  main.c
//  algo
//
//  Created by Hien Nguyen on 2/4/19.
//  Copyright © 2019 Hien Nguyen. All rights reserved.
//

#include <>
#include <time.h>
#include <algorithm>

void main() {
    clock_t begin1, stop1, begin2, stop2;
    
    
    const int m = 2000; // will exhaust all my memory or close to it
    const int size = 3 * m;
    begin1 = clock(); // start clock
    int **array1 = (int**)calloc(size,sizeof(int));
    for (int i = 0; i < size; i++)
    {
        array1[i] = (int *)calloc(800000,sizeof(int));    //allocate each spot in the array with size 800000
        
    }
    stop1 = clock();
    for (int i = 0; i < size; i += 2)
    {
        free(array1[i]);    //free half of it
    }
    
    begin2 = clock();
    int **array2 = (int**)calloc(m , sizeof(int));
    for (int i = 0; i < m; i++)
    {
        array2[i] = (int *)calloc(900000,sizeof(int));    //second array with size m gets allocated with sizez 900000
        
    }
    stop2 = clock();
    auto time1 = (stop1 - begin1) / 1000.00;
    auto time2 = (stop2 - begin2) / 1000.00;
    printf("Time for first array: %.5f\n", time1); //timer for both
    printf("Time for second array: %.5f\n", time2);
    system("pause");
};
