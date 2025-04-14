
package superKeyword;

public class player extends Person{
    public int ratings;
    public player(String name,int chestNum, int contact, char sign, int ratings){
        super(name, chestNum, contact , sign);
        this.ratings= ratings;
    }
    
     @Override
     public void displayINFO(){
         System.out.println("Player INFO: ");
        super.displayINFO();
        System.out.println("Ratings: "+ratings);
    }
}
