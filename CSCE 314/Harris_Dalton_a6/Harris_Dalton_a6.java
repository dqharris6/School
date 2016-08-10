// Dalton Harris
// CSCE 314-501
// UIN: 123002242

import java.lang.*;
import java.awt.Graphics;
import java.awt.Color;
import javax.swing.*;
import java.util.Scanner;
import java.util.Random;

public class Harris_Dalton_a6 extends JFrame
{
    public Harris_Dalton_a6()
    {
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(500,500);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }
    
    @Override
    public void paint(Graphics g)
    {
        super.paint(g);
        
        if(input_shape_array!=null)
        {
            for(Shape s : input_shape_array)
            {
                g.setColor(new Color(randInt(0,255),(randInt(0,255)), randInt(0,255)));
                s.draw(g);
            }

        }
        
        else
        {
            for(Shape s : random_shapes)
            {
                g.setColor(new Color(randInt(0,255),(randInt(0,255)), randInt(0,255)));
                s.draw(g);
            }

        }
        
    }
    
    public static int randInt(int min, int max)
    {
        Random rand = new Random();
        int randomNum = rand.nextInt((max - min) + 1) + min;
        return randomNum;
    }
    
    public static Shape[] sortShapes(Shape[] shapes)
    {
        Shape[] shapes_in;
        shapes_in = new Shape[10];
        int shapes_counter = 0;
        Shape temp;
        
        for(int i=0; i < shapes.length-1; i++)
        {
            for(int j=1; j < shapes.length-i; j++)
            {
                if(shapes[j-1].area() > shapes[j].area())
                {
                    temp=shapes[j-1];
                    shapes[j-1] = shapes[j];
                    shapes[j] = temp;
                }
            }
        }
        
        return shapes;
    }
    
    private static Shape[] input_shape_array;
    private static Shape[] random_shapes;
    
    public static void main(String args[])
    {
        Point point1 = new Point(2,1); // point at (2,1)
        Point point2 = new Point(1,2); // another point at (1,2)
        
        //System.out.println(point1.equals(point2));
        
        Rectangle rect1 = new Rectangle(new Point(4,4), new Point(10,10)); // rectangle with topleft point (0,0), bottomright point (10,10)
        //System.out.println("rect1 topleft point = " + rect1.position);
        
        Circle circ1 = new Circle(new Point (1,1), 12); // circle with center (1,1), radius 12
        
        Square square1 = new Square(new Point (5,5), 10); // square with center (5,5), sidelength 10
        
        LineSegment line1 = new LineSegment(new Point(0,0), new Point(0,1));
        //System.out.println("line segment 1 = " + line1);
        
        Triangle tri1 = new Triangle(new Point(0,0), new Point(5,15), new Point(50,10));
        //System.out.println("tri1 area = " + tri1.area());
        //System.out.println("tri1 = " + tri1.toString());
        
        //System.out.println("circle area = " + circ1.area());
        //System.out.println("circle center at " + circ1.center());
        //System.out.println("rectangle area = " + rect1.area());
        // System.out.println("point1 = " + position);
        // System.out.println("point1 string = " + point1.toString());
        //System.out.println("height of rect1 = " + rect1.calculated_width());
        //System.out.println("width of rect1 = " + rect1.calculated_height());
        //System.out.println("square corner = " + square1.position());
        //System.out.println("square area = " + square1.area());
        //System.out.println("square side length = " + square1.sidelength());
        //System.out.println("line length = " + line1.area());
        
        Shape shapes[];
        shapes = new Shape[10];
        shapes[0] = new Rectangle(new Point(1,1), new Point(5,5));
        shapes[1] = new LineSegment(new Point(1,0), new Point(2,0));
        shapes[2] = new Circle(new Point(10,10), 10);
        //System.out.println("shapes[1] = " + shapes[1].toString());
        //System.out.println("shapes[1] area = " + shapes[1].area());
        //System.out.println(shapes[0] + " " + shapes[1] + " " + shapes[2]);
        
        AreaCalculator area59 = new AreaCalculator(shapes);
        //System.out.println("Total area of all shapes = " + area59.calculate(shapes));

        //System.out.println(randInt(0,100));
        
        if (args.length == 0)
        {
            System.out.println("Error: Please input either S or R");
        }
        
        else if(args[0].equals("R") || args[0].equals("r"))
        {
        int loopvariable1 = Integer.parseInt(args[1]);
            
            System.out.println(loopvariable1);
        
        // if R -> take the first integer after R
        // if S -> take the first n doubles after S and the shape indicator
        // we need to take the length of args, throw that into a for loop, and delimit the entire input by semicolon. each substring between the semicolons needs to go into the progression below, and all we will have to do is change the array indexes to be dynamic.
            
        // use built in hasNext() function. while scanner.hasNext == true keep going
            
        // finally at the end, we need to implement a public isEqual() function.
            // @Override public int hashCode()
            // @Override public boolean equals(Object object)
            
        random_shapes = new Shape[loopvariable1];
        
        for(int randomgenerator = 0; randomgenerator < loopvariable1; randomgenerator++)
        {
            int shapepicker = randInt(0,4);
            
            if(shapepicker == 0)
            {
                Triangle randomtri = new Triangle(new Point(randInt(0,100),randInt(0,100)), new Point(randInt(0,100),randInt(0,100)), new Point(randInt(0,100),randInt(0,100)));
                
                System.out.println(randomtri.toString());
                random_shapes[randomgenerator] = randomtri;
            } // triangle
            
            if(shapepicker == 1)
            {
                Rectangle randomrect = new Rectangle(new Point(randInt(0,100),randInt(0,100)), new Point(randInt(0,100),randInt(0,100)));
                
                System.out.println(randomrect.toString());
                random_shapes[randomgenerator] = randomrect;
            } // rectangle
            
            if(shapepicker == 2)
            {
                Circle randomcirc = new Circle(new Point(randInt(0,100),randInt(0,100)), randInt(1,10));
                
                System.out.println(randomcirc.toString());
                random_shapes[randomgenerator] = randomcirc;
            } // circle
            
            if(shapepicker == 3)
            {
                Square randomsq = new Square(new Point(randInt(0,100),randInt(0,100)), randInt(1,10));
                
                System.out.println(randomsq.toString());
                random_shapes[randomgenerator] = randomsq;
            } // square
            
            if(shapepicker == 4)
            {
                LineSegment randomline = new LineSegment(new Point(randInt(0,100),randInt(0,100)), new Point(randInt(0,100),randInt(0,100)));
                
                System.out.println(randomline.toString());
                random_shapes[randomgenerator] = randomline;
            } // linesegment
        }
        
        AreaCalculator random_array_area = new AreaCalculator(shapes);
        System.out.println("\nTotal area of all shapes = " + random_array_area.calculate(random_shapes));
            
            for(int loopdeloop = 0; loopdeloop < random_shapes.length; loopdeloop++)
            {
                Shape[] temp = sortShapes(random_shapes);
                System.out.println(temp[loopdeloop].toString());
            }
            
        }
        
        else if(args[0].equals("S"))
        {
            // this checks the type of shape we want to input
            
            String args1 = args[1];
            Scanner sc = new Scanner(args1).useDelimiter("\\s*;\\s*");
            
            double cmd1, cmd2, cmd3, cmd4, cmd5, cmd6;
            
            // make a new array from whatever the next() argument is, and store each value into an individual index of this array. do this by parsing at the whitespace.
            
            System.out.println("\nRaw Shape Input:");
            int anothercounter = 0;
            int semicoloncount = 0;
            
            int num = args1.replaceAll("[^;]","").length();
            
            String[] nextargs;
            nextargs = new String[num];
            
            input_shape_array = new Shape[num];
            
            int counter = 0;
            
            while(sc.hasNext())
            {
                String test = sc.next();
                nextargs[counter] = test;
                
                String[] argsdoubles = test.split(" ");
            
                String shapeletter = argsdoubles[0].substring(0,1);
            
                if(shapeletter.equals("l") || shapeletter.equals("L"))
                {
                    if(argsdoubles.length == 5)
                    {
                        cmd1 = Double.parseDouble(argsdoubles[1]);
                        cmd2 = Double.parseDouble(argsdoubles[2]);
                        cmd3 = Double.parseDouble(argsdoubles[3]);
                        cmd4 = Double.parseDouble(argsdoubles[4]);
                    
                        Point lpoint1 = new Point(cmd1, cmd2);
                        Point lpoint2 = new Point(cmd3, cmd4);
                    
                        LineSegment cmdline1 = new LineSegment(lpoint1, lpoint2);
                        input_shape_array[counter] = cmdline1;
                        System.out.println(input_shape_array[counter]);
                
                        //System.out.println("area = "+ cmdline1.area());
                    }
                    
                    else
                    {
                        System.out.println("\nError: Wrong number of arguments in input.");
                        return;
                    }
                }
            
                else if(shapeletter.equals("r") || shapeletter.equals("R"))
                {
                    if(argsdoubles.length == 5)
                    {
                        cmd1 = Double.parseDouble(argsdoubles[1]);
                        cmd2 = Double.parseDouble(argsdoubles[2]);
                        cmd3 = Double.parseDouble(argsdoubles[3]);
                        cmd4 = Double.parseDouble(argsdoubles[4]);
                
                        Point lpoint1 = new Point(cmd1, cmd2);
                        Point lpoint2 = new Point(cmd3, cmd4);
                
                        Rectangle cmdrect1 = new Rectangle(lpoint1, lpoint2);
                        input_shape_array[counter] = cmdrect1;
                        System.out.println(input_shape_array[counter]);
                
                        //System.out.println("area = "+ cmdrect1.area());
                    }
                    
                    else
                    {
                        System.out.println("\nError: Wrong number of arguments in input.");
                        return;
                    }
                }
            
                else if(shapeletter.equals("c") || shapeletter.equals("C"))
                {
                    if(argsdoubles.length == 4)
                    {
                        cmd1 = Double.parseDouble(argsdoubles[1]);
                        cmd2 = Double.parseDouble(argsdoubles[2]);
                        
                        if(Double.parseDouble(argsdoubles[3]) == 0)
                        {
                            System.out.println("Error: Radius Cannot be 0.");
                            return;
                        }
                        
                        else
                        {
                            cmd3 = Double.parseDouble(argsdoubles[3]);
                        }
                
                        Point lpoint1 = new Point(cmd1, cmd2);
                    
                        Circle cmdcirc1 = new Circle(lpoint1, cmd3);
                        input_shape_array[counter] = cmdcirc1;
                        System.out.println(input_shape_array[counter]);
                
                        //System.out.println("area = "+ cmdcirc1.area());
                    }
                    
                    else
                    {
                        System.out.println("\nError: Wrong number of arguments in input.");
                        return;
                    }
                }
            
                else if(shapeletter.equals("s") || shapeletter.equals("S"))
                {
                    if(argsdoubles.length == 4)
                    {
                        cmd1 = Double.parseDouble(argsdoubles[1]);
                        cmd2 = Double.parseDouble(argsdoubles[2]);
                        
                        if(Double.parseDouble(argsdoubles[3]) == 0)
                        {
                            System.out.println("Error: Side Length Cannot be 0.");
                            return;
                        }
                        
                        else
                        {
                            cmd3 = Double.parseDouble(argsdoubles[3]);
                        }
                        
                        Point lpoint1 = new Point(cmd1, cmd2);
                
                        Square cmdsq1 = new Square(lpoint1, cmd3);
                        input_shape_array[counter] = cmdsq1;
                        System.out.println(input_shape_array[counter]);
                    
                        //System.out.println("area = "+ cmdsq1.area());
                    }
                    
                    else
                    {
                        System.out.println("\nError: Wrong number of arguments in input.");
                        return;
                    }
                }
            
                else if(shapeletter.equals("t") || shapeletter.equals("T"))
                {
                    if(argsdoubles.length == 7)
                    {
                        cmd1 = Double.parseDouble(argsdoubles[1]);
                        cmd2 = Double.parseDouble(argsdoubles[2]);
                        cmd3 = Double.parseDouble(argsdoubles[3]);
                        cmd4 = Double.parseDouble(argsdoubles[4]);
                        cmd5 = Double.parseDouble(argsdoubles[5]);
                        cmd6 = Double.parseDouble(argsdoubles[6]);
                
                        Point lpoint1 = new Point(cmd1, cmd2);
                        Point lpoint2 = new Point(cmd3, cmd4);
                        Point lpoint3 = new Point(cmd5, cmd6);
                
                        Triangle cmdtri1 = new Triangle(lpoint1, lpoint2, lpoint3);
                        input_shape_array[counter] = cmdtri1;
                        System.out.println(input_shape_array[counter]);
                
                        //System.out.println("area = "+ cmdtri1.area());
                    }
                    
                    else
                    {
                        System.out.println("\nError: Wrong number of arguments in input.");
                        return;
                    }
                }
            
                else
                {
                    System.out.println("Error: Not a Recognized Shape Identifier");
                }
                
                counter++;
                
            }
            
            AreaCalculator scalc = new AreaCalculator(input_shape_array);
            System.out.println("\nTotal area of all shapes = " + scalc.calculate(input_shape_array) + "\n");
            
            // this is where we compare to see if anything is equal
            
            System.out.println("Equal Shapes:");
            Shape[] duplicate_shape_array = input_shape_array;
            int iterations = 0;
            
            for(int bigloopvar = 0; bigloopvar < num; bigloopvar++)
            {
                for(int loopint = iterations; loopint < num; loopint++)
                {
                    if(input_shape_array[bigloopvar].equals(duplicate_shape_array[loopint]) && (loopint != bigloopvar))
                    {
                        System.out.println(input_shape_array[bigloopvar] + " is equal to " + input_shape_array[loopint]);
                    }
                    
                    iterations = bigloopvar + 1;
                }
            }
            
            System.out.println("\nSorted Shapes:");
            
            for(int loopdeloop = 0; loopdeloop < input_shape_array.length; loopdeloop++)
            {
                Shape[] temp = sortShapes(input_shape_array);
                System.out.println(temp[loopdeloop].toString());
            }
        }
        
        else
        {
            System.out.println("Error: Unexpected Input");
        }
    
        new Harris_Dalton_a6();
    }
    
    
}

class Point
{
    private double x; // x coordinate
    private double y; // y coordinate
    
    // Point constructor
    public Point(double x, double y)
    {
        this.x = x;
        this.y = y;
    }
    
    // Point toString constructor
    public String toString()
    {
        return "(" + x + "," + y + ")";
    }
    
    // returns x value of point
    public double getX()
    {
        return x;
    }
    
    // returns y value of point
    public double getY()
    {
        return y;
    }
    
    // overrides point equals function
    @Override
    public boolean equals(Object other)
    {
        if(((Point) this).getX() == ((Point) other).getX() &&
           ((Point) this).getY() == ((Point) other).getY()) return true;
        else return false;
    }
}

abstract class Shape
{
    protected Point position;
    Point anotherpoint;
    public abstract double area();
    public abstract String toString();
    public abstract void draw(Graphics g);
    
    @Override
    public boolean equals(Object other)
    {
        if(((Shape) this).position == ((Shape) other).position
            && ((Shape) this).area() == ((Shape) other).area())
            return true;
        else return false;
    }
    
    @Override
    public int hashCode()
    {
        int result;
        long temp;
        temp = Double.doubleToLongBits(position.getX());
        result = 5*(int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(position.getY());
        result = result + 5*(int) (temp ^ (temp >>> 32));
        temp = Double.doubleToLongBits(area());
        result = 31* result + 5*(int) (temp ^ (temp ^ (temp >>> 32)));
        return result;
    }
    
}

class Rectangle extends Shape
{
    Point position; // top left point
    Point anotherpoint; // bottom right point
    
    // Rectangle constructor
    public Rectangle(Point position, Point anotherpoint)
    {
        this.position = position;
        this.anotherpoint= anotherpoint;
    }
    
    // calculates width between x points
    public double calculated_width()
    {
        return anotherpoint.getX() - position.getX();
    }
    
    // calculates height between y points
    public double calculated_height()
    {
        return anotherpoint.getY() - position.getY();
    }
    
    // returns rectangle area
    public double area()
    {
        return Math.abs(calculated_height() * calculated_width());
    }
    
    public String toString()
    {
        return "r:(" + position.getX() + "," + position.getY() + ")" + "," + "(" + anotherpoint.getX() + "," + anotherpoint.getY() + ")";
    }
    
    public void draw(Graphics g)
    {
        int x = (position.getX()<anotherpoint.getX()) ? 5*(int)position.getX() : 5*(int)anotherpoint.getX();
        int y = (position.getY()<anotherpoint.getY()) ? 5*(int)position.getY() : 5*(int)anotherpoint.getY();
        
        g.fillRect(x, y, 5*(int)calculated_width(), 5*(int)calculated_height());
    }
}

class Circle extends Shape
{
    private double radius; // Circle radius
    Point position; // circle center
    Point anotherpoint = null;
    
    public Circle(Point position, double radius)
    {
        this.position = position;
        this.radius = radius;
    }
    
    // returns point at center of circle
    public Point center()
    {
        return position;
    }
    
    // returns area of circle
    public double area()
    {
        return Math.abs(Math.PI * radius * radius);
    }
    
    public String toString()
    {
        return "c:(" + position.getX() + "," + position.getY() + "), " + "radius = " + radius;
    }
    
    public void draw(Graphics g)
    {
        int x = 5*(int)position.getX() - 5*(int)radius;
        int y = 5*(int)position.getY() - 5*(int)radius;
        
        g.fillOval(x,y,5*(int)radius,5*(int)radius);
    }
    
}

class Square extends Shape
{
    Point position; // topleft point of square
    Point anotherpoint = null;
    private double sidelength; // length of 4 sides of square
    
    public Square(Point position, double sidelength)
    {
        this.position = position;
        this.sidelength = sidelength;
    }
    
    public Point position()
    {
        return position;
    }
    
    public double sidelength()
    {
        return sidelength;
    }
    
    public double area()
    {
        return Math.abs(sidelength * sidelength);
    }
    
    public String toString()
    {
        return "s:(" + position.getX() + "," + position.getY() + ")" + ", side length = " + sidelength;
    }
    
    public void draw(Graphics g)
    {
        g.fillRect(5*(int)position.getX(),5*(int)position.getY(),5*(int)sidelength,5*(int)sidelength);
    }
}

class LineSegment extends Shape
{
    //Point position;
    Point anotherpoint;
    
    public LineSegment(Point position, Point anotherpoint)
    {
        this.position = position;
        this.anotherpoint = anotherpoint;
    }
    
    public Point position()
    {
        return position;
    }
    
    public Point anotherpoint()
    {
        return anotherpoint;
    }
    
    public String toString()
    {
        return "l:(" + position.getX() + "," + position.getY() + ")" + "," + "(" + anotherpoint.getX() + "," + anotherpoint.getY() + ")";
    }
    
    public double area()
    {
        return 0;
    }
    
    public void draw(Graphics g)
    {
        g.drawLine(5*(int)position.getX(),5*(int)position.getY(),5*(int)anotherpoint.getX(),5*(int)anotherpoint.getY());
    }
    
}

class Triangle extends Shape
{
    Point position;
    Point anotherpoint;
    private Point tp3;
    
    public Triangle(Point position, Point anotherpoint, Point tp3)
    {
        this.position = position;
        this.anotherpoint = anotherpoint;
        this.tp3 = tp3;
    }
    
    public Point position()
    {
        return position;
    }
    
    public Point anotherpoint()
    {
        return anotherpoint;
    }
    
    public Point tp3()
    {
        return tp3;
    }
    
    public double area()
    {
        double part1 = (position.getX() * anotherpoint.getY());
        double part2 = (anotherpoint.getX() * tp3.getY());
        double part3 = (tp3.getX() * position.getY());
        double part4 = (position.getX() * tp3.getY());
        double part5 = (tp3.getX() * anotherpoint.getY());
        double part6 = (anotherpoint.getX() * position.getY());
        double mediatestep = Math.abs(part1 + part2 + part3 - part4 - part5 - part6);
        
        return (1.0/2.0) * mediatestep;
    }
    
    public String toString()
    {
        return "t:(" + position.getX() + "," + position.getY() + ")" + "," + "(" + anotherpoint.getX() + "," + anotherpoint.getY() + ")," + "(" + tp3.getX() + "," + tp3.getY() + ")";
    }
    
    public void draw(Graphics g)
    {
        int[] xvalues = new int[]{5*(int)position.getX(), 5*(int)anotherpoint.getX(), 5*(int)tp3.getX()};
        int[] yvalues = new int[]{5*(int)position.getY(), 5*(int)anotherpoint.getY(), 5*(int)tp3.getY()};
        g.fillPolygon(xvalues, yvalues, 3);
    }
}

class AreaCalculator
{
    public AreaCalculator(Shape[] shapes)
    {
        Shape[] shapes_array;
    }
    
    public static double calculate(Shape[] shapes)
    {
        // here we cycle through each element in the array, and take the area and add it to a cumulative total area variable, and return that variable.
    
        double total_area = 0;
        
        for(int loop = 0; loop < shapes.length; loop++)
        {
            total_area = total_area + shapes[loop].area();
        }
        
        return total_area;
    }
}