#include<iostream>
using namespace std;
int main(){
    int r1,c1,r2,c2;
    cout<<"Order of 1st matrix: ";
    cin>>r1>>c1;
    cout<<"Order of 2nd matrix: ";
    cin>>r2>>c2;
    int a[r1][c1];
    int b[r2][c2];
    if(r1 == r2 && c1 == c2){
        cout<<"input 1st matrix: "<<endl;
        for(int i=0 ; i<r1; i++){
            for(int j=0; j<c1; j++){
                cin>>a[i][j];
            }
        }
        cout<<endl<<"input 2nd matrix: "<<endl;
        for(int i=0 ; i<r2; i++){
            for(int j=0; j<c2; j++){
                cin>>b[i][j];
            }
        }
        cout<<"output of 1st matrix: "<<endl;
        for(int i=0 ; i<r1; i++){
            for(int j=0; j<c1; j++){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"output of 2nd matrix: "<<endl;
        for(int i=0 ; i<r2; i++){
            for(int j=0; j<c2; j++){
                cout<<b[i][j]<<" ";
            }
            cout<<endl;
        }
        int sum[r1][c1];
        int sub[r1][c1];
        for(int i=0; i<r1; i++){
            for(int j=0; j<c1; j++){
                sum[i][j]= a[i][j]+b[i][j];
        }
        }
        cout<<"Sum of the matrix: "<<endl;
        for(int i=0; i<r1; i++){
            for(int j=0; j<c1; j++){
                cout<<sum[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0; i<r1; i++){
            for(int j=0; j<c1; j++){
                sub[i][j]= a[i][j]-b[i][j];
        }
        }
        cout<<"Subtraction of the matrix: "<<endl;
        for(int i=0; i<r1; i++){
            for(int j=0; j<c1; j++){
                cout<<sub[i][j]<<" ";
        }
        cout<<endl;
    }
    }
    else{
        cout<<"Column and row is not Equal!";
    }
    return 0;
}
