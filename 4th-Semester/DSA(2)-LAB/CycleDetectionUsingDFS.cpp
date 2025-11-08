#include<bits/stdc++.h>
using namespace std;

vector<int> adj[100],ans;
int vis[100],recSt[100];


bool dfs_rec_cycle(int source)
{
    if(recSt[source]==1)
        return true;
    if(vis[source]==1)
        return false;

    vis[source]=1;
    recSt[source]=1;
    //ans.push_back(source);
    for(int j=0;j<adj[source].size();j++)
    {
        int adjacentNode = adj[source][j];
        if(dfs_rec_cycle(adjacentNode))
        {
           return true;
        }
    }
    recSt[source]=0;
    return false;
}


int main()
{
    int node,edge,u,v,i;
    cout<<"Enter the node and Edge: "<<endl;
    cin>>node>>edge;
    cout<<"Enter the edge list: "<<endl;
    /*
    5 6
    0 1
    1 3
    3 0
    2 3
    3 4
    4 2
    */
    for(i=0;i<edge;i++)
    {
        cin>>u>>v;
        adj[u].push_back(v);
        //adj[v].push_back(u);
    }
    cout<<"Enter The Source node Where you want visit bfs: "<<endl;
    int source;
    cin>>source;
    //dfs(source);
    if(dfs_rec_cycle(source))
        cout<<"Cycle exist";
    else cout<<"Cycle doesn't exist";
}


