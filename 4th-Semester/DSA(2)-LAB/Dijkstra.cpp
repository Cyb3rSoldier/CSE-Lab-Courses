#include<bits/stdc++.h>
using namespace std;

vector<int> adj[100],adjCost[100];
int vis[100],cost[100];

void dijkstra(int source)
{
    priority_queue<pair<int,int>,
                vector<pair<int,int> >,
                greater<pair<int,int> > > pq;
    pq.push({0,source});
    cost[source]=0;
    //res.push_back(source);
    while(!pq.empty())
    {
        int cur=pq.top().second;
        pq.pop();
       // cout<<cur<<" ++"<<endl;
        for(int i=0;i<adj[cur].size();i++)
        {
            int neighber=adj[cur][i];
            if(cost[neighber]>(cost[cur]+adjCost[cur][i]))
            {
                cost[neighber] = cost[cur]+adjCost[cur][i];
                pq.push({cost[neighber],neighber});
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
    for(int i=0;i<=node;i++)
        cost[i] = 1000000;
    for(int i=0;i<edge;i++)
    {
        cin>>u>>v>>x;
        adj[u].push_back(v);
        adjCost[u].push_back(x);
        adj[v].push_back(u);
        adjCost[v].push_back(x);
    }
    int source = 0;
    cout<<"Enter the Source Node"<<endl;
    cin>>source;
    dijkstra(source);
    //cout<<"BFS Traversal: "<<endl;
    for(int i=0;i<node;i++)
    {
        cout<<cost[i]<<" ";
    }
}

