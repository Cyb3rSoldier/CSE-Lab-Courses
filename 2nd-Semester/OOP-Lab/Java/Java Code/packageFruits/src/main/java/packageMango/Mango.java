
package packageMango;
import packageFruits.Fruit;
public class Mango extends Fruit{
   
    private int mangoCount;
    public Mango(String taste, String color, int count, String type,int mangoCount){
        super(taste,color,count,type);
        this.mangoCount= mangoCount;
    }
 
    public void printInfo(){
        System.out.println("Count of Fruits: "+getCount());
        /*Default Access Modifier
        System.out.println("Taste of Mangos: "+this.taste);*/
        System.out.println("Color of Mangos: "+this.color);
        System.out.println("Type of Mangos: "+this.type);
        System.out.println("Count of Mangos: "+this.mangoCount);
    }
}
