
package methodOverriding;


public class mainClass {
    public static void main(String[] args){
        person p = new person();
        teacher t =new teacher();
        
        p.name= "Omar";
        p.age= 22;
        p.displayINFO();
        t.name= "Rakib";
        t.age= 30;
        t.gender= "Male";
        t.displayINFO();        
    }
}
