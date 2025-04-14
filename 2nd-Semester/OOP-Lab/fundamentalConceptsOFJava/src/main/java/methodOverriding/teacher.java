
package methodOverriding;

public class teacher extends person{
    String gender;
   @Override
    void displayINFO(){
        System.out.println("Teacher Class: ");
        System.out.println("Name: "+name);
        System.out.println("Age: "+age);
        System.out.println("Gender: "+gender);
    }
            
}
