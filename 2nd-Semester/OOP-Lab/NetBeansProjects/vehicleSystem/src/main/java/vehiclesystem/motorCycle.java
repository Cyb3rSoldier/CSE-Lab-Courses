
package vehiclesystem;

public class motorCycle extends Vehicle{
    public boolean hasSideCar;
    motorCycle(String brand,String model, boolean hasSideCar){
        super(brand,model);
        this.hasSideCar= hasSideCar;
    }
    public void status(){
        if(hasSideCar== true){
            System.out.println(getBrand()+" "+getModel()+" "+" has side Car!");
        }
        else{
            System.out.println(getBrand()+" "+getModel()+"does not have side Car!");
        }
    }
}
