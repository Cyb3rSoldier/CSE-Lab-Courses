
package labtest;

public class Book {
    public String title;
    public String author;
    public boolean avaibility;
    public Book(String title , String author, boolean avaibility){
        this.title= title;
        this.author= author;
        this.avaibility= avaibility;
    }
    public  void Return(){
        System.out.println("Return Successfully");
    };
    public  void Borrow(){
        System.out.println("Borrowed Syccessfully");
    };
    
}
