
package javaswing;
import javax.swing.JOptionPane;
public class showInputDialog {
    public static void main(String[] args) {
        String name= JOptionPane.showInputDialog("Enter your Name: ");
        JOptionPane.showMessageDialog(null, name+" WelCome Home!");
        String name2= JOptionPane.showInputDialog(null,"Enter your Name: ","Notification",3);
        JOptionPane.showMessageDialog(null, name+" Welcome!");
    }
}
