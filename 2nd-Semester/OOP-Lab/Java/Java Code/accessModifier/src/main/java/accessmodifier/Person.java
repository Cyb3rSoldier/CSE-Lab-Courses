
package accessmodifier;

public class Person {
    private int id;
    public String name;
    private int age;
    protected String homeAddress;
    protected String currentAddress;
    public Person(int id,String name,int age,String homeAddress,String currentAddress){
        this.id=id;
        this.name= name;
        this.age= age;
        this.homeAddress= homeAddress;
        this.currentAddress= currentAddress;
    }
    public int getID(){
        return id;
    }
    public int getAge(){
        return age;
    }
        

    
}
