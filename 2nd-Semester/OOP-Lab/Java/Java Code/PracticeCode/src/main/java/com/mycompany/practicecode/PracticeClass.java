package com.mycompany.practicecode;
import java.util.Scanner;
public class PracticeClass {
    int a,b;
    public void inputData(){
        Scanner input = new Scanner(System.in);
        System.out.print("Enter value of a= ");
        a= input.nextInt();
        System.out.print("Enter value of b= ");
        b= input.nextInt();
    }
    
    public int calculation(){    
        return a+b;
    }
    public void printInfo(){
        System.out.println("Sum= "+calculation());
    }
    public static void main(String[] args){
        
        PracticeClass c= new PracticeClass();
        c.inputData();
        c.printInfo();
    }
}
