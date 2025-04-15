package com.mycompany.practicecode;
import java.util.Scanner;
public class Parking {
    private String registrationNumber;
    public int parkingHours;
    public String type;
    Scanner inputInt= new Scanner (System.in);
    Scanner inputString= new Scanner(System.in);
    public static void print(){
        System.out.println("Enter Data: ");
    }
    public Parking(){
        System.out.println("Info for 1st Vehicle: ");
        System.out.print("Registration Number: ");
        registrationNumber= inputString.nextLine();
        System.out.print("Parking Hours: ");
        parkingHours= inputInt.nextInt();
        System.out.print("Vehicle Type: ");
        type= inputString.nextLine();
        this.registrationNumber= registrationNumber;
        this.parkingHours= parkingHours;
        this.type= type;
        System.out.println();
    }
    public Parking(String registrationNumber, String type, int parkingHours){
        
        this.registrationNumber= registrationNumber;
       
        this.type= type;
        this.parkingHours= parkingHours;
        
        System.out.println();
    }
    public double calculateParkingFee(){
        this.parkingHours= parkingHours;
        if(parkingHours<2){
            return 5;
        }
        else if(parkingHours>=2 && parkingHours<=5){
            return 10;
        }
        else if(parkingHours>5){
            return 20;
        }
       return 1;
    }
    public void displayInfo(){
        System.out.println("Registration Number: "+registrationNumber);
        System.out.println("Parking Hours: "+parkingHours);
        System.out.println("Type: "+type);
        System.out.println("Parking Fee: $"+calculateParkingFee());
        
    }
    public static void main(String[] args){
        print();
        Parking defaultParking = new Parking();
        Parking peraMeterizedParking = new Parking("lkdjfks","bus",2);
      
        System.out.println("1st Vehicle: ");
        defaultParking.displayInfo();
        System.out.println("");
        System.out.println("2nd Vehicle: ");
        peraMeterizedParking.displayInfo();
    }
}
