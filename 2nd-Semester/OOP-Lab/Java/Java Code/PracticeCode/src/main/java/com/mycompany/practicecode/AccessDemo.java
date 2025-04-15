
package com.mycompany.practicecode;

class Vehicle{
    String name= "Generic Vehicle";
    String defaultColor= "Black";
    protected int maxSpeed= 120;
    public void displayFeaturs(){
        System.out.println("Vehicle featured displayed");
    }
}

class Car extends Vehicle{
   
    public Car(){
        
        System.out.println("Name: "+name);
    }
    public void showColor(){
        System.out.println("The car color is: "+defaultColor);
    }
}

public class AccessDemo {
    public static void main(String[] args) {
        Vehicle v = new Vehicle();
        Car c = new Car();
        v.displayFeaturs();
        c.showColor();
        System.out.println("Car Max speed: "+c.maxSpeed);
        System.out.println("Vehicle color: "+ v.defaultColor);
    }
}
