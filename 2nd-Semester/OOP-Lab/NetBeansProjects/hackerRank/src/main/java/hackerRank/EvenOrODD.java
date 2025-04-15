
package hackerRank;
import java.util.Scanner;
public class EvenOrODD {
    public static void main(String[] args) {
        int T,N;
        Scanner input = new Scanner(System.in);
        T= input.nextInt();
        int[] result= new int[T];
        for(int i= 0; i<T; i++){
            N= input.nextInt();
            result[i]= N;
        }
        for(int i=0; i<T;i++){
            if(result[i]%2==0){
                System.out.println("EVEN");
            }
            else if(result[i]%2!=0){
                System.out.println("ODD");
            }
        }
    }
}
