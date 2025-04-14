#include<iostream>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    int arr[n][m];
    bool flag= true;
    cout<<"Input: "<<endl;
    for(int i=0; i<n;i++){
        for(int j=0; j<m; j++){

            cin>>arr[i][j];

        }
    }
    cout<<"Output: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    int trans[m][n];
    cout<<"Transpose matrix: "<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            trans[i][j]=arr[j][i];
            cout<<trans[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(arr[i][j]!=trans[i][j]){
                flag = false;
            }

        }
    }
    if(flag == true){
        cout<<"Symmetric!";
    }
    else{
        cout<<"Not Symmetric!";
    }
    return 0;
}
