package com.mycompany.practicecode;
import java.util.Scanner;
public class BubbleSorting {
    public static void main(String[] args){
        int n;
        int temp;
        System.out.print("Enter the limit of Sorting Number: ");
        Scanner input= new Scanner(System.in);
        n= input.nextInt();
        int[] A= new int[n];
        System.out.printf("Enter %d numbers: ",n);
        for(int i=0; i<n; i++){
            A[i]= input.nextInt();
        }
        System.out.println("\nThe Sorted Result: ");
        
        for (int i = 0; i < n-1; i++) {
        boolean swapped= false;
        for (int j = 0; j < n-i-1; j++) {
            
            if (A[j] > A[j+1]) {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                swapped = true;
            }
        }
        
        if (swapped == false){
            break;
        }
    }

        for(int i=0; i<n; i++){
            System.out.print(A[i]+" ");
        }
        System.out.println();
    }
}
