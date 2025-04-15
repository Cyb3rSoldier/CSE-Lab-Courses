   package com.mycompany.practicecode;
   import java.util.Scanner;
    public class Assignment{
    public static void main(String[] args){
        int n;
        int OddNumber=1;
        int sum=0;
        System.out.print("Enter the terms: ");
        Scanner input= new Scanner(System.in);
        n= input.nextInt();
        System.out.println("The odd numbers are: ");
        for(int i=1;i<=n;i++){
            System.out.println(OddNumber);
            sum= sum+OddNumber;
            OddNumber+=2;
            
           
        }
        System.out.println("The Sum of odd Natural Number upto 5 terms is: "+sum);
    }
}