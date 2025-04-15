
package newOffice;
import java.util.Scanner;
public class MainClass {
    public static void  main(String[] args){
       
        System.out.println("Enter Info: ");
        Scanner inputString= new Scanner(System.in);
        Scanner inputInt= new Scanner(System.in);
        System.out.print("Enter the Name: ");
        String name= inputString.nextLine();
        System.out.print("Enter the Age: ");
        int age= inputInt.nextInt();
        System.out.print("Enter the Sallary: ");
        int sallary = inputInt.nextInt();
        System.out.print("Enter the Gender: ");
        String gender= inputString.nextLine();
        System.out.println();
        
        EmployeeInfo newEmployee= new EmployeeInfo(name,age,sallary,gender);
        System.out.println("Display Info: ");
        newEmployee.printInfo();
    }
}
