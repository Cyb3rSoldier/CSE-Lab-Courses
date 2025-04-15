package hackerRank;
import java.util.Scanner;
public class lowestNumberWithPosition {
    public static void main(String[] args) {
        int N,A;
        Scanner input= new Scanner(System.in);
        N= input.nextInt();
        int[] array= new int[N];
        for(int i=0; i<N; i++){
            A= input.nextInt();
            
            array[i]=A;
        }
        int minValue= array[0];
        int position= 1;
        for(int i=0; i<N;i++){
            if(array[i]<minValue){
                minValue=array[i];
                position= i+1;
            }     
        }
            System.out.println(minValue+" "+position);
    }
}
