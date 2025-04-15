package packageMango;
import java.util.Scanner;
public class MainClass {
    public static void main(String[] args){
        
        Scanner inputInt= new Scanner(System.in);
        Scanner inputString= new Scanner(System.in);
        System.out.println("Enter Info: ");
        System.out.print("Enter Fruits count: ");
        int count= inputInt.nextInt();
        System.out.print("Enter the Taste: ");
        String taste= inputString.nextLine();
        System.out.print("Enter the Color: ");
        String color = inputString.nextLine();
        System.out.print("Enter Mangos count: ");
        int mangoCount= inputInt.nextInt();
        System.out.print("Enter the Type: ");
        String type = inputString.nextLine();
        System.out.println();
        
        Mango newMango= new Mango(taste,color,count,type,mangoCount);
      
        System.out.println("Display Info: ");
        newMango.printInfo();
        
    }
}
