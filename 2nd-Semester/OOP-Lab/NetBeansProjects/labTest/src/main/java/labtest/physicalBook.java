
package labtest;


public class physicalBook extends Book{
    public String location;
    physicalBook(String title , String author, boolean avaibility, String location){
        super(title,author,avaibility);
        this.location= location;
    }
    @Override
    public  void Return(){
        System.out.println("Physical Book Info: ");
        super.Return();
    };
    @Override
    public  void Borrow(){
        System.out.println("Physical Book Info: ");
        super.Borrow();
    };
}
