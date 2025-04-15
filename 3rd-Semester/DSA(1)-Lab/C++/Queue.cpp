#include<iostream>
using namespace std;
#define size 100


class Queue
{
    int arr[size];
    int front, back;
public:
    Queue()
    {
        front=back=-1;
    }
    void enqueue(int val)
    {
        if(back==size-1)
        {
            cout<<"Queue is full"<<endl;
            return;
        }
        if(front==-1)
        {
            front++;
        }

        back++;
        arr[back]=val;
        cout<<"Enqueue element is: "<<arr[back]<<endl;
    }
    void dequeue()
    {
        cout<<"Front element is: "<<arr[front]<<endl;
        front++;
        if(front>back)
        {
            cout<<"Queue is empty"<<endl;
            front=back=-1;
        }
    }
    void peek()
    {
        if(front==-1)
        {
            cout<<"Queue is empty"<<endl;
            return;
        }
        cout<<"Front element is: "<<arr[front]<<endl;
    }
    bool isEmpty()
    {
        if(front ==-1)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    void display()
    {
        for(int i=front; i<=back; i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }

};

int main()
{
    Queue q;
    for(int i=0; i<=100; i++)
    {
        q.enqueue(i);
    }
    q.display();
    for(int i=99; i>=0; i--)
    {
        q.dequeue();
    }
    q.display();
    q.peek();
    return 0;
}
