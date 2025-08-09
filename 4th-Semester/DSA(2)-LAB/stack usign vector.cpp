#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main(){
    stack<int> st;

    //push in the top
    st.push(10);
    st.push(11);
    st.push(12);

    //pop from the top
    st.pop();
    cout<<"Top element of stack: "<<st.top()<<endl;
    cout<<"Elements of the stack: ";
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<endl;
    return 0;
}

