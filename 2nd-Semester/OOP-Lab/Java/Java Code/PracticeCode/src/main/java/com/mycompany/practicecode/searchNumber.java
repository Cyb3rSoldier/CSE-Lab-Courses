package com.mycompany.practicecode;
import java.util.Scanner;
public class searchNumber {
    public static void main(String[] args){
        int n;
        int num; 
        int temp = 0;
        int count= 0;
        int temp1;
        Scanner input= new Scanner(System.in);
        System.out.print("Enter the limit: ");
        n= input.nextInt();
        int array[]= new int[n];
        System.out.print("Enter the array: ");
        for(int i=0; i<n; i++){
            array[i]= input.nextInt();
        }
        System.out.println("----------------------------------------------");
        System.out.print("The array: ");
        for(int i=0; i<n; i++){
            System.out.print(array[i]+" ");
        }
        System.out.println();
        System.out.print("Enter the number to find in the list: ");
        num= input.nextInt();
        System.out.print("Position: ");
        for(int i=0; i<n; i++){
            if(array[i]==num){
                temp=i+1;
                System.out.print(temp+" ");
            }       
        }
        System.out.println();
        for(int i= 0; i<n; i++){
            if(array[i]==num){
                count++;
            }
        }
        if(temp==0 && count==0){
            System.out.println("Number not Found!");
        }
        else{
        System.out.println("Number of presents: "+count);
        }
        for(int k=0; k<n-1; k++){
            boolean swap = false;
            for(int j=0; j<n-1-k;j++){
                if(array[j]>array[j+1]){
                    temp1=array[j];
                    array[j]=array[j+1];
                    array[j+1]=temp1;
                    swap= true;
                }   
            }
                if(swap==false){
                    break;
                }
        }
        System.out.print("Sorted result: ");
        for(int k=0; k<n; k++){
                System.out.print(array[k]+" ");
            }
    }
}
