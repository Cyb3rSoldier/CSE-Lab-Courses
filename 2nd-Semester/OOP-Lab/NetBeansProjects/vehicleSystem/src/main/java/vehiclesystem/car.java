
package vehiclesystem;


public class car extends Vehicle{
    int numDoors;
    car(String brand, String model, int numDoors){
        super(brand, model);
        this.numDoors= numDoors;
    }
    public void openTrunk(){
        System.out.println(getBrand()+" "+getModel()+" "+"Trunk is open!");
    }
}
