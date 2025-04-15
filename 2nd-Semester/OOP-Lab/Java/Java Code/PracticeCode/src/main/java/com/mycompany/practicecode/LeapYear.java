
package com.mycompany.practicecode;
import java.util.Scanner;
public class LeapYear {
    public static void main(String[] args){
        int year;
        System.out.print("Enter the Year: ");
        Scanner input= new Scanner(System.in);
        year= input.nextInt();
        if((year%4==0 && year%100!=0)||(year %400==0)){
            System.out.println("Leap Year!");
        }
        else{
            System.out.println("Not a Leap Year!");
        }
    }
}
