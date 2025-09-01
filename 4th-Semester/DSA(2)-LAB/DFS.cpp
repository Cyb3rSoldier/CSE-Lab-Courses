#include<bits/stdc++.h>
using namespace std;

//Depth-First Search-->>

vector<int> adj[100],res;
int vis[100];

void dfs(int source)
{
    stack<int> st;
    st.push(source);
    while(!st.empty()){
        int cur = st.top();
        st.pop();
        if(vis[cur] == 0){
            vis[cur] = 1;
            res.push_back(cur);
        }

        for(int i =adj[cur].size()-1; i>=0;i--){
            int neighber = adj[cur][i];
            if(vis[neighber]==0){
                cout<<neighber<<" ";
                st.push(neighber);
            }
        }
    }
}

int main()
{
    int node, edge, u, v;
    cout<<"Enter node and edge: ";
    cin>>node>>edge;
    cout<<"Enter u --> v: "<<endl;
    for(int i=0; i<edge; i++)
    {
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0);
    cout<<endl<<"BFS Traversal: ";
    for(int i=0; i<res.size(); i++)
    {
        cout<<res[i]<<" ";
    }
    cout<<endl;
    return 0;
}
