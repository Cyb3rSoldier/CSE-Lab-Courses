
package labtest;

public class eBook extends Book{
    public String url;
    eBook(String title , String author, boolean avaibility, String url){
        super(title, author, avaibility);
        this.url= url;
    }
    @Override
    public  void Return(){
        System.out.println("eBook Info: ");
        super.Return();
    };
    @Override
    public  void Borrow(){
        System.out.println("eBook Info: ");
        super.Borrow();
    }
}
