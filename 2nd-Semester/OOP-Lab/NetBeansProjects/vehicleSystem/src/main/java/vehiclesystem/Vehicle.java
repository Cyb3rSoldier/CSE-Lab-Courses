
package vehiclesystem;

public class Vehicle {

    private String brand;
    private String model;
    Vehicle(String brand, String model){
        this.brand= brand;
        this.model= model;
    }
    public void setBrand(String brand){
        this.brand= brand;
    }
    public void setModel(String model){
        this.model= model;
    }
    public String getBrand(){
        return brand;
    }
    public String getModel(){
        return model;
    }
    public void start(){
        System.out.println(brand+" "+model+" "+" is strarting!");
    }
    public void stop(){
        System.out.println(brand+" "+model+" "+" is stopping!");
    }
}
