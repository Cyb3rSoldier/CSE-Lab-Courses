
package overrides;

public class Dog extends Animal{
    @Override
    protected void sound(){
        System.out.println("The dog barks.");
    }
}
