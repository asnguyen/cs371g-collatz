// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <array>
#include <cassert> // assert
#include <fstream>
#include <iostream> // endl, istream, ostream#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utility>

#include "Collatz.h"
#define ARRAY_SIZE 1000000

using namespace std;

// ------------
// collatz_read
// ------------

bool collatz_read(istream &r, int &i, int &j) {
  if (!(r >> i))
    return false;
  r >> j;
  return true;
}

// ------------
// collatz_eval
// ------------

int collatz_eval(int i, int j) {
  assert(i > 0 && j > 0);
// start making cache
#ifdef ARRAY_SIZE
  int *my_array = new int[ARRAY_SIZE];
  //int my_array[ARRAY_SIZE];
  for (int b = 0; b < ARRAY_SIZE; ++b) {
  my_array[b] = 0;
   //^initializes the array
  }
  for (int a = 0; a <= 19; ++a) {
    my_array[((int)exp2(a))] = a + 1;
    //^fills the cache with the cycle length of all powers of 2
  }
#endif
  // finished making cache
  int max = 0;
  int temp_max = 1;
  for (int k = std::min(i, j); k <= std::max(i, j); k++) {
    int temp_num = k;
    temp_max = 1;
    while (temp_num != 1) {
      if (temp_num % 2 == 0) {
        temp_num /= 2;
        ++temp_max;
      } else {
        temp_num = temp_num + (temp_num >> 1) + 1;
        temp_max += 2;
      }
#ifdef ARRAY_SIZE
      if (temp_num % 2 == 0) {
        temp_num /= 2;
      } else {
        temp_num = 3 * temp_num + 1;
      }
      if (temp_num < ARRAY_SIZE) // test to make sure the temp_num is within the
                              // indices of the cache
      {
        if (my_array[temp_num] != 0) // cache look up
        {
          // cache hit
          temp_max += my_array[temp_num];
          temp_num = 1;
        } else {
          // cache miss
          temp_max++;
        }
      } else {
        if (temp_num > ARRAY_SIZE)
          temp_max++;
      }
#endif
    }
#ifdef ARRAY_SIZE
    my_array[k] = temp_max; //sets the cycle length to use for next time
#endif
    max = std::max(max, temp_max);
  }
  assert(max > 0);

#ifdef ARRAY_SIZE
  delete[] my_array; //frees the memory that was used
  my_array = NULL;
#endif
  return max;
}

// -------------
// collatz_print
// -------------

void collatz_print(ostream &w, int i, int j, int v) {
  w << i << " " << j << " " << v << endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve(istream &r, ostream &w) {
  int i;
  int j;
  while (collatz_read(r, i, j)) {
    const int v = collatz_eval(i, j);
    collatz_print(w, i, j, v);
  }
}
