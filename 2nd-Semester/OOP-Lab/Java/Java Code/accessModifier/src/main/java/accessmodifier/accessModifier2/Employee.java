
package accessmodifier.accessModifier2;

import accessmodifier.Person;

public class Employee extends Person{
    public Employee(int id,String name,int age,String homeAddress,String currentAddress){
        super(id,name,age,homeAddress,currentAddress);
    }
    public void printInfo(){
        System.out.println("ID: "+getID());
        System.out.println("Name: "+name);
        System.out.println("Age: "+getAge());
        System.out.println("Home Address: "+homeAddress);
        System.out.println("Current Adderss: "+currentAddress);
    }
    
}