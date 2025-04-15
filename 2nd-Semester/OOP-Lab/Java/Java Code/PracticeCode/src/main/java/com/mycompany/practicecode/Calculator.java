package com.mycompany.practicecode;
import java.util.Scanner;
public class Calculator {
    public static void main(String[] args){
        int a,b;
        Scanner input= new Scanner(System.in);
        System.out.print("Enter the First Number: ");
        a= input.nextInt();
        System.out.print("Enter the Second Number: ");
        b=input.nextInt();
        System.out.printf("Sum: %d\n",a+b);
        System.out.printf("Sub: %d\n",a-b);
        System.out.printf("Multiplication: %d\n",a*b);
        System.out.printf("Division: %d\n",a/b);
        System.out.printf("Modulus: %d\n",a%b);
    }
    
}
