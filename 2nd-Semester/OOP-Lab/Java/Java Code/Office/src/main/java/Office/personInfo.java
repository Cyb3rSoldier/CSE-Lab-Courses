
package Office;

public class personInfo {
    public String name;
    private int age;
    protected int sallary;
    String gender;
    public personInfo(String name,int age,int sallary,String gender){
        this.name=name;
        this.age= age;
        this.sallary=sallary;
        this.gender= gender;
    }
    public int getAge(){
        return age;
    }
        

}
