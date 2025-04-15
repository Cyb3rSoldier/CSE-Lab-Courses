
package com.mycompany.practicecode;
import java.util.Scanner;
public class Assignment1 {
    public static void main(String[] args){
        Scanner input= new Scanner(System.in);
        System.out.println("Enter your Input:");
        String ch1= input.nextLine();
        String ch2= input.nextLine();
        String ch3=ch1;
        ch1=ch2;
        ch2=ch3;
        System.out.print("\nThe Swapped Output: "+ch1+" "+ch2);
        
    }
}
