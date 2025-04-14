
// Online C++ compiler to run C++ program online
#include <iostream>

using namespace std;
struct node {
int data;
node *next;
};
int main() {
// Write C++ code here
node *nptr, *tptr, *header=NULL;
int n;
cout<<"Enter n: ";
cin>>n;
int item;
cout<<"Input "<<n<<" Times: ";
for(int i =0;i<n;i++){
std::cin>>item;
nptr = new node;
nptr->data = item;
nptr->next = NULL;

if(header==NULL){
header = nptr;
tptr = nptr;
}
else{
tptr->next= nptr;
tptr = nptr;

}

}
nptr->next=header;

// let's add an element;
// 3 cases.
// 1. Is it in the header? Let's search

tptr = header;
while(tptr != NULL){
cout<<"data = " <<tptr->data;
cout<<", address = "<<tptr;
cout<<", next address is = "<<tptr->next<<'\n';
tptr=tptr->next;
}

}
