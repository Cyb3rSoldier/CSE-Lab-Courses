#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> arr(100);
    int target;
    int left, mid, right,totalE;
    cout<<"Enter the size: ";
    cin>>totalE;
    cout<<"Total element in the array: ";
    for(int index=0; index<totalE; index++){
        cin>>arr[index];
    }
    /*
    without arr size declaration
    for(int index=0; index<totalE; index++){
        cin>>x;
        arr.push_back(x);
    }*/
    cout<<"Target is: ";
    cin>>target;
    left=0;
    right= totalE-1;
    while(left<=right){

        mid = left+ (right-left)/2;
        if(arr[mid]==target){
            cout<<"Target index is: "<<mid<<endl;
            return 0;
        }
        else if(arr[left]>target){
            right = mid-1;
        }
        else{
            left = mid+1;
        }

    }
    cout<<"Target Not Found!"<<endl;
    return 0;
}
