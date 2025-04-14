
package superKeyword;

public class Person {
    public String name;
    private int chestNum;
    protected int contact;
    char sign;
    public Person(String name,int chestNum, int contact, char sign){
        this.name= name;
        this.chestNum= chestNum;
        this.contact= contact;
        this.sign= sign;
    }
    
    public void setChestNum(int chestNum){
        this.chestNum= chestNum;
    }
    public int getChestNum(){
        return chestNum;
    }
    public void displayINFO(){
        
        System.out.println("Name: "+name);
        System.out.println("Chest Number: "+getChestNum());
        System.out.println("Contact: "+contact);
        System.out.println("Sign: "+sign);
    }
}
