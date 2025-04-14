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
    int mul[r1][c2];
    for(int i=0; i<r1; i++){
        for(int j=0; j<c2; j++){ mul[i][j]=0;}

    }
    if(c1==r2){
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
        cout<<"output of 2nt matrix: "<<endl;
        for(int i=0 ; i<r2; i++){
            for(int j=0; j<c2; j++){
                cout<<b[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"Multiplication of the matrix: "<<endl;
        for(int i=0; i<r1; i++){
            for(int j=0; j<c2; j++){
                for(int k=0; k<r2; k++){
                    mul[i][j]= mul[i][j]+(a[i][k]*b[k][j]);

                }
                cout<<mul[i][j]<<" ";
            }
            cout<<endl;
        }

    }
    else{
        cout<<"Multiplication is not possible!";
    }
    return 0;
}
