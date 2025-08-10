#include<bits/stdc++.h>
using namespace std;

void printArray(vector<int> &arr)
{
    for(int i=0; i<arr.size(); i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int partitionArray(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int pos = low-1;
    for(int index = low; index<high; index++)
    {
        if(arr[index]<pivot)
        {
            pos++;
            swap(arr[index],arr[pos]);
        }
    }
    pos++;
    swap(arr[high],arr[pos]);
    return pos;
}

void quicksort(vector<int> &arr, int low, int high)
{
    if(low<high)
    {
        int pivotPos = partitionArray(arr,low,high);
        quicksort(arr,low,pivotPos-1);
        quicksort(arr,pivotPos+1,high);
    }
}

int main()
{
    vector<int> arr= {9,7,5,3,2,12,9,1};
    quicksort(arr,0,arr.size()-1);
    cout<<"After Sorting the array: "<<endl;
    printArray(arr);
    return 0;
}
