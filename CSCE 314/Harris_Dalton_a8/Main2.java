public class Main2
{
    public static void main(String args[])
    {
        new Main2();
    }
    
    public Main2()
    {
        timeprint tp = new timeprint();
        
        new Thread(tp).start();
        new Thread(new messageprint(7, tp)).start();
        new Thread(new messageprint(15, tp)).start();
    }
}

class timeprint implements Runnable
{
    int counter = 0;

    public void run()
    {
        while(true)
        {
            try
            {
                Thread.sleep(1000);
            }
            
            catch(Exception e)
            {
                e.printStackTrace();
            }
            
            counter++;
            System.out.print(counter + " ");
        }
    }
    
    public synchronized int getcounter()
    {
        return counter;
    }
}

class messageprint implements Runnable
{
    int message, thisismymemoryvariable;
    final timeprint finaltimeprintvariable;
    
    
    messageprint(int namelessvariable1, timeprint namelessvariable2)
    {
        message = namelessvariable1;
        finaltimeprintvariable = namelessvariable2;
        thisismymemoryvariable = 0;
    }
    
    public void run()
    {
        while(true)
        {
            if(finaltimeprintvariable.getcounter() != thisismymemoryvariable)
            {
                thisismymemoryvariable = finaltimeprintvariable.getcounter();
                
                if(thisismymemoryvariable % message == 0 && thisismymemoryvariable != 0)
                {
                    System.out.println("\n" + message + " second message");
                }
                
            }
        }
    }
}