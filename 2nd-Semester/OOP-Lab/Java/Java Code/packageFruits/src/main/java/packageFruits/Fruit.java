
package packageFruits;

public class Fruit {
    
    String taste;
    public String color;
    private int count;
    protected String type;
    public Fruit(String taste, String color, int count, String type){
        
        this.taste= taste;
        this.color= color;
        this.count= count;
        this.type= type;
        
    }
    public int getCount(){
        return count;
    }
}
