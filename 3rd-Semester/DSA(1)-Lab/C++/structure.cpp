#include<iostream>
using namespace std;

struct student{
    std::string name;
    float gpa;
    bool enroll;
};

int main(){

    student student1;
    student1.name = "Omar";
    student1.gpa = 3.85;
    student1.enroll = true;

    student student2;
    student2.name = "Rakib";
    student2.gpa = 4.00;
    student2.enroll = false;

    cout<<"Student 1 info: "<<endl;
    cout<<student1.name<<endl;
    cout<<student1.gpa<<endl;
    cout<<student1.enroll<<endl;

    cout<<"Student 2 info: "<<endl;
    cout<<student2.name<<endl;
    cout<<student2.gpa<<endl;
    cout<<student2.enroll<<endl;

    return 0;
}
