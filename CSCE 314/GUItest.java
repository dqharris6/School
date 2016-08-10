import javax.swing.*;
import java.awt.*;

public class GUItest extends JFrame{
    public GUItest(){
        setSize(800,800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }
    
    public static void main(String a[]){
        new GUItest();
    }
    
    public void paint(Graphics g){
        g.drawOval(40, 40, 60, 60); //FOR CIRCLE
        g.drawRect(80, 30, 200, 200); // FOR SQUARE
        g.drawRect(200, 100, 100, 200); // FOR RECT
    }
}