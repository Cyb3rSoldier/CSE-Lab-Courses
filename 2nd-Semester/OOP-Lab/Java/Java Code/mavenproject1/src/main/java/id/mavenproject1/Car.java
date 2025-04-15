
package id.mavenproject1;

public class Car {
    public String model;
    public String color;
    public int year;
    
    public Car(String model, String color, int year){
    this.model= model;
    this.color= color;
    this.year= year;
}
    public void displayInfo(){
        System.out.println("Model: "+this.model);
        System.out.println("Color: "+this.color);
        System.out.println("Year: "+this.year);
        
    }

    
}
