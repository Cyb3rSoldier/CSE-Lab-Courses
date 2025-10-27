#include<bits/stdc++.h>
using namespace std;
int main(){

    int coin[] = {1000,500,200,100,50,20,10,5,2,1};
    int n = 10;
    int c1=0,c2=0,c5=0,c10=0,c20=0,c50=0,c100=0,c200= 0, c500=0,c1000=0;
    int amount;
    cout<<"Enter the amount: ";
    cin>>amount;
    int count = 0;
    cout<<"Total coin used: ";
    for(int i =0; i<n; i++){
        while(amount>=coin[i]){
            cout<<coin[i]<<" ";
            amount -= coin[i];
            count++;
            if(coin[i] == 1){
                c1++;
            }
            else if(coin[i] == 2){
                c2++;
            }
            else if(coin[i] == 5){
                c5++;
            }
            else if(coin[i] == 10){
                c10++;
            }
            else if(coin[i] == 20){
                c20++;
            }
            else if(coin[i] == 50){
                c50++;
            }
            else if(coin[i] == 100){
                c100++;
            }
            else if(coin[i] == 200){
                c200++;
            }
            else if(coin[i] == 500){
                c500++;
            }
            else if(coin[i] == 1000){
                c1000++;
            }
        }
    }

    cout<<"\nNumber of coins: "<<endl;
    cout<<"1   : "<<c1<<endl;
    cout<<"2   : "<<c2<<endl;
    cout<<"5   : "<<c5<<endl;
    cout<<"10  : "<<c10<<endl;
    cout<<"20  : "<<c20<<endl;
    cout<<"50  : "<<c50<<endl;
    cout<<"100 : "<<c100<<endl;
    cout<<"200 : "<<c200<<endl;
    cout<<"500 : "<<c500<<endl;
    cout<<"1000: "<<c1000<<endl;
    cout<<"\nCoin used: "<<count;
    return 0;
}
