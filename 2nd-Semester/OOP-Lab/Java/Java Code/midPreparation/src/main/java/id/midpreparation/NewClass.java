package id.midpreparation;

public class NewClass {
    public static void main(String[] args){
        Student s1= new Student();
        Student s2= new Student();
        
        s1.rollNo= 06;
        s1.name= "Omar";
        s1.address= "Dhaka";
        s2.rollNo= 69;
        s2.name= "Nadiaa";
        s2.address= "Uganda";
        
        System.out.println("Info of 1st Student: ");
        System.out.println("Roll: "+s1.rollNo);
        System.out.println("Name: "+s1.name);
        System.out.println("Address: "+s1.address);
        System.out.println("Info of 2nd Student: ");
        System.out.println("Roll: "+s2.rollNo);
        System.out.println("Name: "+s2.name);
        System.out.println("Address: "+s2.address);                  
    }
}
