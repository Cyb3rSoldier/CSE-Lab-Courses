#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void printArray(vector<int> &arr)
{
    cout<<"Sorted Array: ";
    for(int i=0; i<arr.size(); i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
void mergeArray(vector<int> &arr, int low, int mid, int high)
{
    int leftArraySize = mid-low+1;
    int rightArraySize = high-mid;
    vector<int>leftArray(leftArraySize),rightArray(rightArraySize);

    //copying to the left array
    for(int i=low; i<=mid; i++)
    {
        leftArray[i-low] = arr[i];
    }

    //copying to the right array
    for(int i=mid+1; i<=high; i++)
    {
        rightArray[i-(mid+1)] = arr[i];
    }

    int leftPoint = 0, rightPoint= 0, arrayPos = low;
    while((leftPoint < leftArraySize) && (rightPoint<rightArraySize))
    {
        if(leftArray[leftPoint]<rightArray[rightPoint])
        {
            arr[arrayPos] = leftArray[leftPoint];
            leftPoint++;
        }
        else
        {
            arr[arrayPos] = rightArray[rightPoint];
            rightPoint++;
        }
        arrayPos++;
    }
    while (leftPoint<leftArraySize)
    {
        arr[arrayPos] = leftArray[leftPoint];
        leftPoint++;
        arrayPos++;
    }
    while(rightPoint<rightArraySize)
    {
        arr[arrayPos] = rightArray[rightPoint];
        rightPoint++;
        arrayPos++;
    }

}
void merge_sort(vector<int> &arr,int low, int high)
{
    if(low<high)
    {
        int mid = (low+high)/2;
        merge_sort(arr,low,mid);
        merge_sort(arr,mid+1, high);
        mergeArray(arr,low,mid,high);
    }
}
int main()
{
    vector<int>arr= {4,7,1,2,8,8,9};
    merge_sort(arr, 0,arr.size()-1);
    printArray( arr);
    return 0;
}
