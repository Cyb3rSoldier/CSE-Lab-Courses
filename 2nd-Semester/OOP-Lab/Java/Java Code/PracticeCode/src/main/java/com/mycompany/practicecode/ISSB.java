package com.mycompany.practicecode;
import java.util.Scanner;
public class ISSB {
    public String name;
    public int chestNum;
    public String result;
    public double cgpa;
    public ISSB(){
        this.name= "Omar";
        this.chestNum= 06;
        this.result= "Green Card!";
        this.cgpa=3.96;
    }
    public ISSB(String name,int chestNum,String result,double cgpa){
        this.name= name;
        this.chestNum= chestNum;
        this.result= result;
        this.cgpa= cgpa;
    }
    public void displayInfo(){
        System.out.println("Name: "+this.name);
        System.out.println("Chest Number: "+this.chestNum);
        System.out.println("Result: "+this.result);
        System.out.println("CGPA: "+this.cgpa);
    }
    public static void main(String[] args) {
        
        Scanner inputInt= new Scanner(System.in);
        Scanner inputDouble= new Scanner(System.in);
        Scanner inputString= new Scanner(System.in);
        System.out.print("Enter Name: ");
        String name= inputString.nextLine();
        System.out.print("Enter Chest Number: ");
        int chestNum= inputInt.nextInt();
        System.out.print("Enter Result: ");
        String result= inputString.nextLine();
        System.out.print("Enter CGPA: ");
        double cgpa= inputDouble.nextDouble();
        
        ISSB defCandidate= new ISSB();
        ISSB CustCandidate= new ISSB(name,chestNum,result,cgpa);
        System.out.println("Info of Default Candidate: ");
        defCandidate.displayInfo();
        System.out.println("Info of Customized Candidate: ");
        CustCandidate.displayInfo();
        
    }        
    
}
