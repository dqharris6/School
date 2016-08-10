/*
 We use synchronize because all of the threads have to run at the same time without modifying the PostBoxes incorrectly. I locked the boxed the way I did so that no two threads will be using the function at the same time.q
*/

import java.util.*;
import java.util.concurrent.locks.*;

class PostBox implements Runnable
{
    static final int MAX_SIZE = 10;

    class Message
    {
        String sender;
        String recipient;
        String msg;
        Message(String sender, String recipient, String msg)
        {
            this.sender = sender;
            this.recipient = recipient;
            this.msg = msg;
        }   // Message function
    }   // class Message
    
    private final LinkedList<Message> messages;
    private LinkedList<Message> myMessages;
    private String myId;
    private boolean stop = false;
    
    private final Lock sharedMessageLock;
    private final Condition sendingDoneCondition;
    
    public PostBox(String myId)
    {
        messages = new LinkedList<Message>();
        this.myId = myId;
        this.myMessages = new LinkedList<Message>();
        
        sharedMessageLock = new ReentrantLock();
        sendingDoneCondition = sharedMessageLock.newCondition();
        new Thread(this).start();
    }   // PostBox
    
    public PostBox(String myId, PostBox p)
    {
        this.myId = myId;
        this.messages = p.messages;
        this.myMessages = new LinkedList<Message>();
        
        sharedMessageLock = p.sharedMessageLock;
        sendingDoneCondition = p.sendingDoneCondition;
        new Thread(this).start();
    }   // function PostBox
    
    public String getId()
    {
        return myId;
    }   // getId()
    
    public void stop()
    {   // make it so that this Runnable will stop
        stop = true;
        
    }   // stop()
    
    public void send(String recipient, String msg)
    {   // add a message to the shared message queue
        
        sharedMessageLock.lock();
        
        try
        {
            messages.add(new Message(myId, recipient, msg));
            sendingDoneCondition.signalAll();
        }
        
        finally{sharedMessageLock.unlock();}
        
    }   // send()
    
    public List<String> retrieve()
    {   // return the contents of myMessages and empty myMessages
        
        List<String> liststringtoreturn = null;
        sharedMessageLock.lock();
        
        try
        {
            liststringtoreturn = new LinkedList<String>();
            while(myMessages.size() > 0)
            {
                liststringtoreturn.add("From " + myMessages.get(0).sender + " to " + myMessages.get(0).recipient + ": " + myMessages.get(0).msg);
                myMessages.remove(0);
            }
        }
        
        catch(Exception e)
        {
            e.printStackTrace();
        }
        
        finally
        {
            sharedMessageLock.unlock();
        }
        
        return liststringtoreturn;
        
    }   // retrieve()
    
    public void run()
    {
        // loop forever
        //   1. approximately once every second move all messages
        //      addressed to this post box from the shared message
        //      queue to the private myMessages queue
        //   2. also approximately once every second, if the message
        //      queue has more than MAX_SIZE messages, delete oldest messages
        //      so that size is at most MAX_SIZE
        
        while(!stop)
        {
            try
            {
                Thread.sleep(1000);
            }
            
            catch(Exception e)
            {
                // code goes here
            }
            
            sharedMessageLock.lock();
            
            try
            {
                for(int i = 0; i < messages.size(); i++)
                {
                    if(messages.get(i).recipient.equals(myId))
                    {
                        myMessages.add(messages.remove(i));
                        i--;
                    }
                    
                    while(myMessages.size() > MAX_SIZE)
                    {
                        myMessages.removeFirst();
                    }
                }
            }
            
            finally
            {
                sharedMessageLock.unlock();
            }
        }
        
    }   // run()
    
}   // class PostBox

public class Main1
{
    static void pause(long n)
    {
        try { Thread.sleep(n); } catch (InterruptedException e) {}
    }   // pause
    
    public static void main (String[] args)
    {
        final String bond    = "Bond";
        final String blofeld = "Blofeld";
        final String osato   = "Mr. Osato";
        final PostBox pBond    = new PostBox(bond);
        final PostBox pBlofeld = new PostBox(blofeld, pBond);
        final PostBox pOsato   = new PostBox(osato, pBond);
        
        // send out some messages on another thread
        new Thread( new Runnable()
        {
            public void run() {
                pBond.send(blofeld, "Yes, this is my second life"); pause(1000);
                pBlofeld.send(bond, "You only live twice, Mr. Bond."); pause(500);
                String msg = "I gave Number 11 the strictest orders to eliminate him.";
                pOsato.send(blofeld, msg); pause(2000);
                pOsato.send(bond, msg);
                for (int i=0; i<20; ++i) pOsato.send(bond, "flooding the message queue...");
            }
        }).start();
        
        PostBox[] boxes = { pBond, pBlofeld, pOsato };
        long startTime = System.currentTimeMillis();
       
        // poll for messages in a loop for 5 secs
        while (true)
        {
            for (PostBox box : boxes) {
                for (String m : box.retrieve()) System.out.println(m);
            }
            if (System.currentTimeMillis() - startTime > 5000) break;
        }   // while
        
        // stop each mailbox
        for (PostBox box : boxes)
        {
            box.stop();
        }   // for
    } // end of main()
} // end of Main1