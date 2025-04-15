
package vehiclesystem;

public class mainClass {
    public static void main(String[] args) {
        car c= new car("Tesla","Mig-29",4);
        c.start();
        c.openTrunk();
        c.stop();
        System.out.println();
        motorCycle m= new motorCycle("Pulsar","mk4",false);
        m.start();
        m.status();
        m.stop();
    }
}
