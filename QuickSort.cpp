#include<iostream>

using namespace std;

int partition1(int arr[], int left, int right){
    int pivotindex = (int)(left+right)/2;
    int pivot = arr[pivotindex];
    swap(arr[pivotindex], arr[right]);
    int rightmark = right-1;
    int leftmark = left;
    while(leftmark <= rightmark){
        while(leftmark <= rightmark && arr[leftmark] <= pivot)
            leftmark++;
        while(leftmark <= rightmark && arr[rightmark] >= pivot)
            rightmark--;
        if(leftmark < rightmark)
            swap(arr[leftmark++], arr[rightmark--]);
    }
    swap(arr[right], arr[leftmark]);
    return leftmark;
}

int partition2(int arr[], int left, int right){
    int b[right-left+1];
    int acount = left;
    int bcount = 1;
    int pivotindex = (right + left)/2;
    int pivot = arr[pivotindex];
    for(int i = left; i <= right; i++){
        if(i == pivotindex){
            b[0] = arr[i];
        }
        else if(arr[i] < pivot || (arr[i] == pivot && i < pivotindex)){
            arr[acount++] = arr[i];
        }
        else{
            b[bcount++] = arr[i];
        }
    }
    for(int i = 0; i < bcount; i++){
        arr[acount++] = b[i];
    }
    return right - bcount + 1;
}
void quicksort(int arr[], int left, int right){
    if(left < right){
        int pivotindex = partition2(arr, left, right);
        quicksort(arr, left, pivotindex - 1);
        quicksort(arr, pivotindex + 1, right);
    }
}

int main(){
    int arr[] = {6,8,2,5,5,5,7,6};
    quicksort(arr, 0, sizeof(arr)/sizeof(int));
    for(const int& i : arr){
        cout<<i<<" ";
    }
}