
package javaswing;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
public class jFrame {
    public static void main(String[] args) {
        JFrame frame= new JFrame();
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
        //frame.setSize(500,300);//size(width,hight)
        //frame.setLocationRelativeTo(null);//location at center 
        //frame.setLocation(400,200);//lacation(left,top)
        
        frame.setBounds(400,200,500,300);//size and location(left,top,width,height)
        //true= frame can resize
        //false= frame can't resize
        frame.setResizable(true);
        frame.setTitle("FrameDemo");
        
     
        
        
    }
    
    
}
