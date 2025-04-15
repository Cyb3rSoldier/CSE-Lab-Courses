
package overrides;

public class Cat extends Animal{
    @Override
    protected void sound(){
        System.out.println("The cat meows.");
    }
}
