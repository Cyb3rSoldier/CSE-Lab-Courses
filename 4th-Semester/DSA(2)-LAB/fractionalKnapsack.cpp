
#include<bits/stdc++.h>
using namespace std;


struct item{
    int value;
    int weight;
};

bool cmp(item a,item b)
{
    double r1 = (double)a.value/a.weight;
    double r2 = (double)b.value/b.weight;
    return r1>r2;
}

int fractionalKnapsack(int w,vector<item> &items)
{
    sort(items.begin(),items.end(),cmp);
    double finalValue = 0.0;
    for(int i=0;i<items.size();i++)
    {
        if(items[i].weight<=w)
        {
            finalValue+=items[i].value;
            w-=items[i].weight;
        }
        else{
            finalValue+= items[i].value * ((double)w/items[i].weight);
            break;
        }
    }
    return finalValue;
}

int main()
{
    int w=50,n=5,i;
    vector<item> items(n);
    cout<<"Enter "<<n<<" items (value,weight)"<<endl;
    for(i=0;i<n;i++)
    {
        cin>>items[i].value>>items[i].weight;
    }
    int maxValue = fractionalKnapsack(w,items);
    cout<<"Maximum value in Knapsack is "<<maxValue<<endl;
}

