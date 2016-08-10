// Dalton Harris
// DONE

import java.util.*;
import java.io.*;

public class test1
{
    public static class Node<T> implements Iterable<T>
    {
        public final T v;
        public Node<T> next;
        
        public Node (T val, Node<T> link)
        {
            v = val;
            next = link;
        }   // Node constructor
        
        public Iterator<T> iterator()
        {
            return new NodeIterator<T>(this);
        }   // iterator constructor
        
    }   // Node class
    
    public static class NodeIterator<T> implements Iterator<T>
    {
        public Node<T> current;
        
        public NodeIterator(Node<T> n)
        {
            this.current = n;
        }   // NodeIterator constructor
        
        public boolean hasNext()
        {
            return current != null;
        }   // hasNext function
        
        public T next()
        {
            if(current == null)
            {
                throw new NoSuchElementException();
            }   // if statement
            
            T value = current.v;
            current = current.next;
            return value;
        }   // next function
        
        public void remove()
        {
            // code goes here
        }   // remove function
        
    }   // NodeIterator class
    
    public static void main(String[] args)
    {
        // This creates the linked list with first element head
        Node<Integer> n_5 = new Node<Integer>(5,null);
        Node<Integer> n_4 = new Node<Integer>(4,n_5);
        Node<Integer> n_3 = new Node<Integer>(3,n_4);
        Node<Integer> n_2 = new Node<Integer>(2,n_3);
        Node<Integer> head = new Node<Integer>(1,n_2);
        
        print(head);
        System.out.println("Sum = " + sum(head));
        
    }   // main function
        
    public static int sum(Node<Integer> testsum)
    {
        int sum = 0;
        
        for(Integer a : testsum)
        {
            sum += a;
        }   // for loop
        
        return sum;
    }   // sum function
        
    public static void print(Node<Integer> testprint)
    {
        for(Integer a : testprint)
        {
            System.out.print(a + "\n");
        }   // for loop
        
    }   // print function
    
}   // test1 class