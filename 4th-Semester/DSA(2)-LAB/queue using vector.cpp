#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main(){
    stack<int> st;
    st.push(10);
    st.push(11);
    st.push(12);

    cout<<"top element of stack: "<<st.top()<<endl;

    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    return 0;
}

