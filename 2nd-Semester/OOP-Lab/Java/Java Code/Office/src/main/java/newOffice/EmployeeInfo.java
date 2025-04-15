
package newOffice;
import Office.personInfo;
public class EmployeeInfo extends personInfo{
    public EmployeeInfo(String name,int age,int sallary,String gender){
        super(name,age,sallary,gender);
    }
    public void printInfo(){
        System.out.println("Name: "+this.name);
        System.out.println("Age: "+getAge());
        System.out.println("Sallary: "+this.sallary);
        //System.out.println("Gender: "+this.gender);
    }
}
