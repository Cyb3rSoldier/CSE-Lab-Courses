
package id.midpreparation;

public class Student {

    public int rollNo;
    public String name,address;
    
    public void Record(int r, String n, String a){
        this.rollNo=r;
        this.name=n;
        this.address=a;
    }
    
    public void disPlayiInfo(){
        System.out.println("Roll No: "+this.rollNo);
        System.out.println("Name: "+this.name);
        System.out.println("Address: "+this.address);
    }
  
}
