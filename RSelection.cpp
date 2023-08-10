#include<bits/stdc++.h>

using namespace std;

int Randomized_Selection_Partition(vector<int>& arr, int left, int right){
    int n = arr.size();
    int pivotindex = (right+left)/2;
    int pivot = arr[pivotindex];
    int lcount = left+1;
    swap(arr[left], arr[pivotindex]);
    for(int i = lcount; i < right; i++){
        if(pivot > arr[i]){
            swap(arr[lcount++], arr[i]);
        }
    }
    swap(arr[left], arr[lcount-1]);
    return lcount-1;
}

int Randomized_Selection(vector<int>& arr, int left, int right, int k){
    int n = arr.size();
    if(k >= n || n == 0) return -1;
    if(n == 1)  return arr[0];
    int pivotindex = Randomized_Selection_Partition(arr, left, right);
    if(pivotindex == k){
        return arr[k];
    }
    else if(pivotindex > k){
        return Randomized_Selection(arr, left, pivotindex-1, k);
    }
    else{
        return Randomized_Selection(arr, pivotindex+1, right, k);
    }
}

int main(){
    vector<int> arr = {1,2,3,4};
    int ans = Randomized_Selection(arr,0,arr.size(),0);
    cout<<ans;
}