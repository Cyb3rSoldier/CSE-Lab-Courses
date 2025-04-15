
package questionSolve;
import java.util.Scanner;
public class factorial{
    int n;
    public void setNum(int n){
        this.n=n;
    }
    public int getFact(){
        int fact=1;
    for(int i=n; i>0; i--){
        fact= fact*i;
        }
    return fact;
    }
    public static void main(String[] args){
        factorial newFact= new factorial();
        System.out.print("Enter the number: ");
        Scanner input= new Scanner(System.in);
        int num= input.nextInt();
        newFact.setNum(num);
        System.out.println("The factorial is: "+newFact.getFact());
     
    }
}


