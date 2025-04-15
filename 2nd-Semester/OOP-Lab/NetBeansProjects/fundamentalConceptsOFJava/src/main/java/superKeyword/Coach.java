
package superKeyword;

public class Coach extends Person{
    public int exp;
    Coach(String name,int chestNum, int contact, char sign,int exp){
    super(name, chestNum, contact , sign);
    this.exp= exp;
}
    @Override
    public void displayINFO(){
        System.out.println("Coach Info: ");
        System.out.println("Name: "+name);
        System.out.println("Chest Number: "+getChestNum());
        System.out.println("Contact: "+contact);
        System.out.println("Sign: "+sign);
        System.out.println("Experience: "+exp);
    }
}
