
package javaswing;
import javax.swing.JOptionPane;

public class messageDialog1 {

    public static void main(String[] args) {
        //1.two perameter (i). center (ii). message
        JOptionPane.showMessageDialog(null,"Invalid Username or Password!");
        //2. Four perameter (i).center (ii).message (iii).title (iv). icon
        JOptionPane.showMessageDialog(null,"Invalid Username or Password!","Warning", JOptionPane.ERROR_MESSAGE);
        //3. 4th perameter using number!
        JOptionPane.showMessageDialog(null,"Invalid Username or Password!","Warning",3);
        
        
        
    }
}
