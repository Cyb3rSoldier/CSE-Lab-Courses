package com.mycompany.practicecode;
import java.util.Scanner;
public class BubbleSortingWithMethod {
    int n;
    int temp;
    int[] Array= new int[n];
    Scanner input= new Scanner(System.in);
    public static void numberOfInput(){
        int n;
        Scanner input= new Scanner(System.in);
        System.out.print("Enter the limit of sorting number: ");
        n= input.nextInt();
    }
    public  void inputNumber(){
        System.out.printf("Enter %d numbers to Sort: ",n);
        for(int i=0; i<n; i++){
            Array[i]= input.nextInt();
        }
    }
    public BubbleSortingWithMethod(){
        for(int i=0; i<n; i++){
            boolean swapped= false;
            for(int j=0; j<n-i-1; j++){
                if(Array[j]>Array[j+1]){
                temp= Array[j];
                Array[j]= Array[j+1];
                Array[j+1]= temp;
                swapped= true;
                }
            }
            if(swapped==false){
            break;
        }
        
            
        }
    
    }
    public  void printResult(){
        for(int i= 0; i<n; i++){
            System.out.print(Array[i]+" ");
        }
    }
    public static void main(String[] args){
        numberOfInput();
        BubbleSortingWithMethod bubbleSort= new BubbleSortingWithMethod();
        bubbleSort.printResult();
        
    }
}
