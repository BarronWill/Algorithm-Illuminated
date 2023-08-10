#include<iostream>

using namespace std;

void merge(int arr[], int left, int mid, int right){
    int temp[right-left+1];
    int lcount = left;
    int rcount = mid+1;
    int bcount = 0;
    while(lcount<=mid && rcount<=right){
        if(arr[lcount] <= arr[rcount])
            temp[bcount++] = arr[lcount++];
        else
            temp[bcount++] = arr[rcount++];
    }
    if(lcount > mid){
        while(rcount <= right){
            temp[bcount++] = arr[rcount++];
        }
    }
    else{
        while(lcount <= mid){
            temp[bcount++] = arr[lcount++];
        }
    }
    for(int i = 0; i < right - left + 1; i++){
        arr[left+i] = temp[i]; 
    }
}

void MergeSort(int arr[], int left, int right){
    if(left < right){
        int mid = (right+left)/2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}

int main(){
    int arr[] = {6,8,2,5,5,5,7,8};
    MergeSort(arr, 0, sizeof(arr)/sizeof(int));
    for(const int& i : arr){
        cout<<i<<" ";
    }
}