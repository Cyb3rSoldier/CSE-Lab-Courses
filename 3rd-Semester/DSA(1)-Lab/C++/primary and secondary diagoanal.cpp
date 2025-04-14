#include<iostream>
using namespace std;
int main(){
    int n,m;
    int sum=0;
    int sum2=0;
    cout<<"Enter the order: ";
    cin>>n>>m;
    int arr[n][m];
    cout<<"Input: "<<endl;
    for(int i=0; i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr[i][j];
        }
    }
    cout<<"Output: "<<endl;
    for(int i=0; i<n;i++){
        for(int j=0;j<m;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"primary diagonal: ";
    if(m==n){
        for(int i=0; i<n; i++){
            for(int j=0; j<m;j++){
                if(i==j){
                    cout<<arr[i][j]<<" ";
                    sum= sum+arr[i][j];
                }
            }
        }

        cout<<endl;
        cout<<"Sum of Secondary diagonal: "<<sum<<" "<<endl;

        cout<<"Secondary diagonal: ";
        for(int i=0; i<n; i++){
            for(int j=0; j<m;j++){
                if(i+j==n-1){
                    cout<<arr[i][j]<<" ";
                    sum2= sum2+arr[i][j];
                }
            }
        }
        cout<<endl;
        cout<<"Sum of Secondary diagonal: "<<sum2<<" "<<endl;
        cout<<"Sum of Primary and Secondary diagonal: "<<sum+sum2<<endl;
    }
    else{
        cout<<"Not a Square Matrix!";
    }

    return 0;
}
