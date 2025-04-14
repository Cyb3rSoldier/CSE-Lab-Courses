#include<iostream>
using namespace std;
int main(){
    int a=10;
    //pointer
    int *ptr= &a;
    //pointer to pointer
    int **ptr2= &ptr;

    cout<<"Address of a: "<<&a<<endl;
    cout<<"Address of a store in pointer: "<<ptr<<endl;
    cout<<"Address of pointer: "<<&ptr<<endl;
    cout<<"Address of pointer in pointer2: "<<ptr2<<endl;
    cout<<"Address of pointer2: "<<&ptr2<<endl;

    //dereference operator
    cout<<"Value of a: "<<a<<endl;
    cout<<"Value of a dereferencing pointer: "<<*(ptr)<<endl;
    cout<<"Value of pointer: "<<*(&ptr)<<endl;
    cout<<"Value of pointer dereferencing pointer 2: "<<*(ptr2)<<endl;
    cout<<"Value of pointer2: "<<*(&ptr2)<<endl;

    //Null pointer
    int *ptr3= NULL;
    cout<<"Null pointer: "<<ptr3<<endl;

    return 0;
}
