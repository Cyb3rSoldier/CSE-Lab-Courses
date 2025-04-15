
package ExceptionHandling;
import java.util.Scanner;
public class exception {
    public static void main(String[] args) {
        
        try{
            int a;
            int b;
            Scanner input = new Scanner(System.in);
            System.out.print("Enter the value of a: ");
            a= input.nextInt();
            System.out.print("Enter the value of b: ");
            b= input.nextInt();
            System.out.println("Result: "+(a/b));
            
            int[] c= new int[9];
            c[10]= 77;
        }
        catch(Exception e){
            System.out.println("Exception: "+e);
        }
        finally{
            System.out.println("The last line!");
        }
    }
}
