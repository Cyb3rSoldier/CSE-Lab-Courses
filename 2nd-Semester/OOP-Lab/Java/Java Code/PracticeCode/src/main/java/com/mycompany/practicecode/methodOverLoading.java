
package com.mycompany.practicecode;
import java.util.Scanner;
public class methodOverLoading {
    int a,b,c;
    double e,f;
    public int add(int a, int b){
        this.a=a;
        this.b=b;
        return (a+b);
    }
    public int add(int a, int b, int c){
        this.a=a;
        this.b=b;
        this.c=c;
        return (a+b+c);
    }
    public double add(double e, double f){
        this.e=e;
        this.f= f;
        return (e+f);
    }
    public static void main(String[] args) {
        methodOverLoading newMethod= new methodOverLoading();
        Scanner inputInt= new Scanner(System.in);
        Scanner inputDouble= new Scanner(System.in);
        System.out.print("Enter Three Integers: ");
        int a= inputInt.nextInt();
        int b= inputInt.nextInt();
        int c= inputInt.nextInt();
        System.out.print("Enter Two Flaots: ");
        double e= inputDouble.nextDouble();
        double f= inputDouble.nextDouble();
        System.out.println("Sum of two Integers: "+newMethod.add(a,b));
        System.out.println("Sum of three Integers: "+newMethod.add(a,b,c));
        System.out.println("Sum of two floats: "+newMethod.add(e,f));
    }
}
