package com.mycompany.practicecode;
import java.util.Scanner;
public class Constructor {
    int a;
    int b;
    Scanner input= new Scanner(System.in);
   public Constructor(){
       System.out.println("Enter the value for 1st method: ");
       System.out.print("Enter the value of a= ");
       a= input.nextInt();
       System.out.print("Enter the value of b= ");
       b= input.nextInt();
       this.a=a;
       this.b=b;
       
   }
   public Constructor(int a, int b){
       System.out.println("Enter the value for 2nd method: ");
       System.out.print("Enter the value of a= ");
       a= input.nextInt();
       System.out.print("Enter the value of b= ");
       b= input.nextInt();
       this.a=a;
       this.b=b;
   }
   public int sum(){
       return a+b;
   }
   public int sub(){
       return a-b;
   }
   public void displayInfo(){
       System.out.println("a= "+this.a);
       System.out.println("b= "+this.b);
       System.out.println("The Sum is: "+sum());
       System.out.println("The Sub is: "+sub());
   }
   public static void main(String[] args ){
       Constructor defaultValue= new Constructor();
       Constructor perameterizedValue= new Constructor(10,4);
       System.out.println("For 1st one: ");
       defaultValue.displayInfo();
       System.out.println();
       System.out.println("For 2nd one: ");
       perameterizedValue.displayInfo();
       System.out.println();
   }
}                              
