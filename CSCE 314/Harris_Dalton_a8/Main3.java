import java.lang.Object.*;
import java.lang.reflect.*;

public class Main3
{
    static void displayMethodInfo(Object obj)
    {
        try
        {
            String output = null;
            Class<?> c = obj.getClass();
            String simplename = c.getSimpleName();
            
            Method[] methodslist = c.getDeclaredMethods();
            
            for(Method m : methodslist)
            {
                
                Parameter[] parameters = m.getParameters();
                
                if(m.getModifiers() == 0)
                {
                    output = m.getName() + " (" + simplename;
                    
                    for(Parameter parameter : parameters)
                    {
                        Type parameterName = parameter.getParameterizedType();
                        output +=  ", " + parameterName.getTypeName();
                    }
                }
                
                else
                {
                    output = m.getName() + " (";
                    boolean first = true;
                    
                    for(Parameter parameter : parameters)
                    {
                        
                        Type parameterName = parameter.getParameterizedType();
                        
                        if(first)
                            output += parameterName.getTypeName();
                        else
                            output +=  ", " + parameterName.getTypeName();
                        
                        first = false;
                    }
                }
                
                output+=") -> ";
                
                output+=m.getGenericReturnType();
                
                System.out.println(output);

            }
        }
        
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    
    public static void main(String args[])
    {
        displayMethodInfo(new A());
    }
}

class A
{
    void foo(int T1, double T2) {}
    int bar(int T1, String T2, Object T3) { return 1; }
    static double doo() { return 1.1; }
}