#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    queue<int> q;
    queue<int> temp;

    //push element in the queue
    q.push(10);
    q.push(11);
    q.push(12);
    q.push(13);

    //pop front element in the queue
    q.pop();
    cout<<"Front element of queue: "<<q.front()<<endl;
    temp = q;
    cout<<"Elements of Queue: ";
    while(!temp.empty())
    {
        cout<<temp.front()<<" ";
        temp.pop();
    }

    cout<<endl;
    return 0;

}

