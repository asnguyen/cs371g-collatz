//Anthony Nguyen
#include <iostream> // cin, cout
#include <cassert>  // assert
#include <string>
#include <utility>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <array>

using namespace std;
bool collatz_read(istream& r, int& i, int& j);
int collatz_eval(int i, int j);
void collatz_print(ostream& w, int i, int j, int v);
void collatz_solve(istream& r, ostream& w);
int my_array[1000000];

// ----
// main
// ----

int main () 
{
    //making the cache: begin
    int i;
    for(i =0; i<=19;++i)
    {
        my_array[((int)exp2(i))] = i+1;
    }
    //making the cache: end
    collatz_solve(cin, cout);
    return 0;
}
bool collatz_read (istream& r, int& i, int& j) 
{
    if (!(r >> i))
        return false;
    r >> j;
    return true;
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i>0 && j>0);
    int max=0;
    int temp_max;
    int k;
    for(k=std::min(i,j);k<=std::max(i,j);k++)
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
                temp_num = 3*temp_num+1;
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

