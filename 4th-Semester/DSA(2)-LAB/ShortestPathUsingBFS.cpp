#include<bits/stdc++.h>
using namespace std;

vector<int> adj[100],ans;
int vis[100],cost[100];


void bfs(int source, int destination)
{
    queue<int> q;
    vis[source]=1;
    cost[source]=0;
    q.push(source);

    while(!q.empty())
    {
        int curNode;
        curNode=q.front();
        //ans.push_back(curNode);
        q.pop();
        for(int j=0;j<adj[curNode].size();j++)
        {
            int adjacentNode = adj[curNode][j];
            if(vis[adjacentNode] == 0)
            {
                q.push(adjacentNode);
                vis[adjacentNode] = 1;
                cost[adjacentNode]+=(cost[curNode]+1);
            }
            if(adjacentNode == destination)
                return;
        }
    }
}

int main()
{
    int node,edge,u,v,i,destination;
    cout<<"Enter the node and Edge: "<<endl;
    cin>>node>>edge;
    cout<<"Enter the edge list: "<<endl;
    /*
    5 6
    0 1
    0 3
    1 3
    2 3
    3 4
    2 4
    */
    for(i=0;i<edge;i++)
    {
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout<<"Enter The Source node Where you want visit bfs: "<<endl;
    int source;
    cin>>source;
    cin>>destination;
    //for(i=0;i<node;i++)
       // if(vis[i])
    bfs(source,destination);
    //cout<<length[]
    cout<<"Using BFS shortest path will be: ";
    //for(i=0;i<ans.size();i++)
    //{
    cout<<cost[destination]<<" ";
    //}
    cout<<endl;
}

