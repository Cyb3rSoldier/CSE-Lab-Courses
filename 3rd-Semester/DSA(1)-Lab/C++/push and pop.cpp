#include<iostream>
using namespace std;
#define Size 100

//Stack: Last In First Out (LIFO)

class Stack
{
    int arr[Size];
    int top;
public:
    Stack()
    {
        top=-1;
    }
    void push(int val)
    {
        if(top == Size-1)
        {
            cout<<"Stack is full"<<endl;
            return;
        }
        else
        {
            top++;
            arr[top]=val;
        }
    }
    void pop()
    {
        if(top == -1)
        {
            cout<<"Stack is empty"<<endl;
            return;
        }
        cout<<"Top element is: "<<arr[top]<<endl;
        top--;
    }
    void peek()
    {
        cout<<"Peek element is : "<<arr[top]<<endl;
    }
    bool isEmpty()
    {
        if(top == -1)
        {
            return true;
        }
        else
            return false;
    }
    void display()
    {
        for(int i=top; i>=0; i--)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }


};
int main()
{
    Stack s;
    for(int i=0; i<=100; i++)
    {
        s.push(i);
    }
    s.display();
    s.pop();
    s.display();
    s.peek();

    return 0;
}
