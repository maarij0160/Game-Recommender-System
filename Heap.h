#include<iostream>

using namespace std;

template<class t>
void downheap(vector<t> &data, int size, int x = 0){
    while(x < size){
        int max = x;
        int l = 2*x + 1;
        int r = 2*x + 2;

        if(l<size){
            if(data[max] < data[l]) max = l;
        }
        if(r<size){
            if(data[max] < data[r]) max = r;
        }
        

        if(max == l){
            swap(data[x], data[l]);
            x = l;
        }
        else if(max == r){
            swap(data[x], data[r]);
            x = r;
        }
        else break;
    }
}
