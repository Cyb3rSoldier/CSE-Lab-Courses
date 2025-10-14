#include<bits/stdc++.h>
#define inf 100000000
using namespace std;

int cost[100][100];

void floydWarshall(int node){
    int i,j,k;
    for(k=0;k<node;k++)
    {for( int i=0;i<node;i++)
    {
        for(int j=0;j<node;j++)
        {
            if(cost[i][k]!=inf && cost[k][j]!=inf)
                cost[i][j]=min(cost[i][j],cost[i][k]+cost[k][j]);
        }
    }
    }
}

int main()
{
    int node,edge,u,v,x;
    /*
    5 5
    0 1 4
    0 2 8
    1 4 6
    2 3 2
    3 4 10
    */
    cout<<"Enter node and Edge: ";
    cin>>node>>edge;
    for( int i=0;i<node;i++)
    {
        for(int j=0;j<node;j++)
        {
            if(i==j)
                cost[i][j]=0;
            else cost[i][j]=inf;
        }
    }
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v>>x;
        cost[u][v]=x;
        cost[v][u]=x;
    }
    floydWarshall(node);
    for( int i=0;i<node;i++)
    {
        for(int j=0;j<node;j++)
        {
            cout<<cost[i][j]<<" ";
        }
        cout<<endl;
    }

}
