import java.lang.Object.*;
import java.util.*;
import java.lang.reflect.*;

public class Main4
{
    public static void main(String args[])
    {
        try
        {
            Class <?> c = Class.forName(args[0]);
            Method[] methodslist = c.getDeclaredMethods();
            String[] listofthosethatwork;
            Object[] objects = {};
            
            for(Method m : methodslist)
            {
                Object testing = m.getGenericReturnType();
                String usethisstring = "" + testing;
                String mname = m.getName();
                Parameter[] parameters = m.getParameters();
                int counter = 0;
                
                for(Parameter parameter : parameters)
                {
                    Type parameterName = parameter.getParameterizedType();
                    counter++;
                }
                
                if(m.getModifiers() != 0                &&
                   mname.substring(0,4).equals("test")  &&
                   usethisstring.substring(0,4).equals("bool") &&
                   counter == 0
                   )
                {
                    if( (boolean) m.invoke(c, objects))
                        System.out.println("OK: " + m.getName() + " succeeded");
                    
                    else
                        System.out.println("FAILED: " + m.getName() + " failed");
                }
            }
        }
        
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
    }
}

class MyClass
{
    void testingnoworky(int T1, double T2) {}
    static boolean testingthisoneworks() { return true; }
    static boolean wontwork() { return false; }
    boolean testingdoesntwork() { return false; }
    static boolean testingthisshouldntwork(int T1) { return true; }
    static boolean testinganotheronethatworks() { return true; }
}