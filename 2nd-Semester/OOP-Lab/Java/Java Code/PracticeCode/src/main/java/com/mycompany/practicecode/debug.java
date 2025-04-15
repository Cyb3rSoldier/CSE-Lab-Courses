package com.mycompany.practicecode;
import java.util.Scanner;
public class debug{
    public static void main(String[] args){
        int sum= 0;
        int n;
        Scanner input= new Scanner(System.in);
        n= input.nextInt();
        for(int i= 0 ; i<=n; i=2+i){
            sum= sum+i;
        }
        System.out.println("Sum: "+sum);
    }
}