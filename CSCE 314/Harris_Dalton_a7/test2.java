// Dalton Harris
//

import java.util.*;
import java.io.*;

class LinkedList<T> implements Iterable<T>
{
    private Node<T> head;
    
    public LinkedList()
    {
        head = null;
    }   // LinkedList function
    
    public void addtohead(Node<T> t)
    {
        t.next = head;
        head = t;
    }   // addtohead function
    
    public void addtotail(Node<T> t)
    {
        if (head == null)
        {
            addtohead(t);
        }   // if
        
        else
        {
            Node<T> temp = head;
            
            while(temp.next != null)
            {
                temp = temp.next;
            }   // while
            
            t.next = null;
            temp.next = t;
        }   // else
    }   // addtotail function
    
    public LinkedList(Iterable<T> iterable)
    {
        for(T e : iterable)
        {
            addtotail(new Node<T>(e, null));
        }   // for
    }   // LinkedList iterable
    
    public LinkedList<T> reverse()
    {
        Node<T> tmp = null;
        for (T e : this) { tmp = new Node<T>(e, tmp); }
        head = tmp;
        return this;
    }   // reverse function
    
    public String toString()
    {
        StringBuffer return_this = new StringBuffer();
        for(Object o : this)
        {
            return_this.append(o + " ");
        }   // for
        
        return "[ " + return_this.toString() + "]";
    }   // toString function
    
    public Iterator<T> iterator()
    {
        return new LinkedListIterator();
    }   // iterator function
    
    private class Node<T>
    {
        public final T v;
        public Node<T> next;
        public Node (T val, Node<T> link)
        {
            v = val; next = link;
        }   // Node constructor
    }   // Node<T>
    
    private class LinkedListIterator implements Iterator<T>
    {
        private Node<T> nextnode;
        
        public LinkedListIterator()
        {
            nextnode = head;
        }   // LinkedListIterator constructor
        
        public boolean hasNext()
        {
            return nextnode != null;
        }   // hasNext function
        
        public T next()
        {
            if(!hasNext())
            {
                throw new NoSuchElementException();
            }   // if
            
            T return_this = nextnode.v;
            nextnode = nextnode.next;
            return return_this;
        }   // next function
        
        public void remove()
        {
            // code goes here
        }   // remove
        
    }   // LinkedListIterator
    
}   // LinkedList<T>

public class test2
{
    static public void main(String[] args)
    {
        // =========================================================
        // NOTE: THIS IS DR. LEE'S MAIN() CODE DIRECTLY FROM THE PDF
        // =========================================================
        
        LinkedList<Integer> empty_list = new LinkedList<Integer>();
        LinkedList<Integer> list =
        new LinkedList<Integer>(Arrays.asList(1, 2, 3, 4, 5, 6));
        System.out.println(empty_list);
        System.out.println(empty_list.reverse());
        System.out.println(list);
        System.out.println(list.reverse());
        int sum = 0;
        for (int e : list) { sum += e; }
        System.out.println(sum);
        
    }   // main
    
}   // test2 class