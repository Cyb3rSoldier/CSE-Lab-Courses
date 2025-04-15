
package com.mycompany.practicecode;
import java.util.Scanner;

public class ArrayAsInput {
    public static void main(String[] args){
        int n;
        System.out.print("Enter the limit: ");
        Scanner input= new Scanner(System.in);
        n= input.nextInt();
        int[] array= new int[n];
        int sum=0;
        System.out.println("Enter the values: ");
       
       for(int j=0; j<n; j++){
           array[j]= input.nextInt();
       }
       for(int i=0; i<n; i++){
           sum=sum+array[i];
       }
        
        System.out.println("The sum is: "+sum);
        double avg= sum/n;
        System.out.println("The average is: "+avg);
       
    }
}
