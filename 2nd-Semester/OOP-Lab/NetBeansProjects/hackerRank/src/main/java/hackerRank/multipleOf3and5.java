
package hackerRank;
import java.util.Scanner;
public class multipleOf3and5 {
    public static void main(String[] args) {
        int T,N;
        int sum=0;
    Scanner input = new Scanner(System.in);
    T= input.nextInt();
   
    if(T>=1 && T<=100000){
        
        
        for(int i=0;i<T;i++){
            N= input.nextInt();
            
            if(1<=N && N<=1000000000){
                for(int j=0; j<N;j++){
                    if(j%3==0 || j%5==0){
                        sum=sum+j;
                        
                    }
                    
                }
                
            }
            System.out.println(sum);
        }
        
    }
        
   }
    
}
