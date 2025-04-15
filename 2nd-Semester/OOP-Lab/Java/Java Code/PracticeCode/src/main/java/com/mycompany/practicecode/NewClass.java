package com.mycompany.practicecode;
import java.util.Scanner;
public class NewClass {
    public static void main(String[] args) {
        int n;
        int sum=0;
        Scanner input= new Scanner(System.in);
        System.out.print("Enter limit: ");
        n= input.nextInt();
        System.out.printf("Enter %d values: ",n);
        int[] array= new int[n];
        for(int i=0; i<n; i++){
            array[i]= input.nextInt();
        }
        
        
        for(int j=n-1; j>=0; j--){
            sum= sum+array[j];
            System.out.print(array[j]+" ");
    }
        System.out.println();
        System.out.println("Sum: "+sum);
    }
    
}
