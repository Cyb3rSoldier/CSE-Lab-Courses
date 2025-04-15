
package hackerRank;
import java.util.Scanner;
public class inputInOneLine {
    public static void main(String[] args) {
        int  a,b,c,d;
        Scanner input= new Scanner(System.in);
        a= input.nextInt();
        b= input.nextInt();
        c= input.nextInt();
        d= input.nextInt();
       
        int x=(a*b)-(c*d);
        System.out.println("Difference = "+x);
    }
}
