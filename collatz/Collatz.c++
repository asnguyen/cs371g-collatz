// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream#include <string>
#include <utility>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <array>


#include "Collatz.h"
//#define array_size 1000000

using namespace std;

// ------------
// collatz_read
// ------------

bool collatz_read (istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i>0 && j>0);
    //start making cache
    int *my_array=new int[1000000];
    for (int b=0;b<1000000;++b)
    {
        my_array[b]=0;
    }
    for(int a=0;a<=19;++a)
    {
        my_array[((int)exp2(a))]=a+1;
    }
    //finished making cache
    int max=0;
    int temp_max=1;
    for(int k=std::min(i,j);k<=std::max(i,j);k++)
    {
        int temp_num=k;
        temp_max=1;
        while(temp_num!=1)
        {
            if(temp_num%2==0)
            {
                temp_num /= 2;
            }
            else
            {
                temp_num = 3*temp_num + 1;
            }
            if(temp_num<1000000)
            {
                if(my_array[temp_num]!=0)
                {
                    temp_max+=my_array[temp_num];
                    temp_num=1;
                }
                else
                {
                    temp_max++;
                }
            }
            else
            {
                if(temp_num>1000000)
                temp_max++;
            }
        }
        my_array[k]=temp_max;
        max=std::max(max,temp_max);

    }
    assert(max>0); 
    delete[] my_array;
    my_array=NULL;
    return max;}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
