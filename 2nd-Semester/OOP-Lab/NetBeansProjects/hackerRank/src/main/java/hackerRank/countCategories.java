
package hackerRank;
import java.util.Scanner;
public class countCategories {
    public static void main(String[] args){
        int n,a;
        int countEven=0;
        int countOdd=0;
        int countPositive=0;
        int countNegative=0;
        Scanner input= new Scanner(System.in);
        n= input.nextInt();
        int[] array= new int[n];
        int l= array.length;
        for(int i= 0;i<n;i++){
            a= input.nextInt();
            array[i]= a;
        }
        for(int i=0; i<n;i++){
            if(array[i]%2==0){
                countEven++;
            }
            else if(array[i]%2!=0){
                countOdd++;
            }
            if(array[i]<0){
                countNegative++;
            }
            else if(array[i]>0){
                countPositive++;
            }
        }
        System.out.println("Even: "+countEven);
        System.out.println("Odd: "+countOdd);
        System.out.println("Positive: "+countPositive);
        System.out.println("Negative: "+countNegative);
        System.out.println("Length: "+l);
    }
}
