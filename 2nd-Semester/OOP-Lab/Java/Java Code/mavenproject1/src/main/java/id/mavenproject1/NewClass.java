
package id.mavenproject1;

public class NewClass {
    public static void main(String[] args){
        Car car1= new Car("honda","red",2019);
        Car car2= new Car("audi","blue",2020);
        Car car3= new Car("BMW","black",2021);
        System.out.println("CAR1: ");
        car1.displayInfo();
        System.out.println("CAR2: ");
        car2.displayInfo();
        System.out.println("CAR3: ");
        car3.displayInfo();
    }
}
