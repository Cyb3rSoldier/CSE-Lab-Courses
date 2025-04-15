
package BeeCrowd;

import java.util.Scanner;

public class SimpleSort {
    public static void main(String[] args){
        Scanner input= new Scanner(System.in);
        int[] array= new int[3];
        for(int i= 0; i<3; i++){
            array[i]= input.nextInt();
        }
        if(array[0]<array[1] && array[0]<array[2]){
            System.out.println(array[0]);
            if(array[1]<array[2]){
                System.out.println(array[1]);
                System.out.println(array[2]);
            }
            else if(array[2]<array[1]){
                System.out.println(array[2]);
                System.out.println(array[1]);
            }
        }
        else if(array[1]<array[0] && array[1]<array[2]){
           System.out.println(array[1]); 
           if(array[0]<array[2]){
               System.out.println(array[0]);
               System.out.println(array[2]);
           }
           else if(array[2]<array[0]){
               System.out.println(array[2]);
               System.out.println(array[0]);
           }
        }
        else if(array[2]<array[0] && array[2]<array[1]){
            System.out.println(array[2]);
           if(array[0]<array[1]){
               System.out.println(array[0]);
               System.out.println(array[1]);
           }
           else if(array[1]<array[0]){
               System.out.println(array[1]);
               System.out.println(array[0]);
           }
        }
        System.out.println();
        for(int i=0; i<3; i++){
            System.out.println(array[i]);
        }
    }
    
}
