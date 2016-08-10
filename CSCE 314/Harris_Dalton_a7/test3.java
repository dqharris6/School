import java.util.LinkedList;
import java.util.List;
import java.util.*;

class Shop<T>
{
    List<T> stock;
    
    public Shop()
    {
        stock = new java.util.LinkedList<T>();
    }   // Shop constructor
    
    void sell(T item)
    {
        stock.add(item);
    }   // sell function
    
    public T buy()
    {
        return stock.remove(0);
    }   // buy function
    
    void sell(int n, Collection<? super T> items)
    {
        Iterator iterator1 = items.iterator();
        
        while(iterator1.hasNext())
        {
            stock.add((T)iterator1.next());
        }   // while
        
    }   // sell function
    
    void buy(int n, Collection<? super T> items)
    {
        for (T e : stock.subList(0,n))
        {
            items.add(e);
        }   // for
        
        for (int i=0; i<n; ++i)
        {
            stock.remove(0);
        }   // for
    }   // buy function

}   // shop class

public class test3
{
    static public void main(String[] args)
    {
        final Shop<String> myGroceryStore = new Shop<String>();
        myGroceryStore.sell("bananas");
        myGroceryStore.sell("peaches");
        myGroceryStore.sell("oranges");
        
        final Set<String> groceries = new HashSet<String>();
        myGroceryStore.buy(3, groceries);
        
        System.out.println("myGroceryStore:");
        for (final String e : groceries)
        {
            System.out.println(e);
        }   // for
        
        // =====================================================
        System.out.println("");
        // =====================================================
        
        final Shop<String> myPetStore = new Shop<String>();
        myPetStore.sell("dog");
        myPetStore.sell("cat");
        myPetStore.sell("hamster");
        myPetStore.sell("rooster");
        myPetStore.sell("tortuga");
        myPetStore.sell("minion");
        
        final Set<String> pets = new HashSet<String>();
        myPetStore.buy(6, pets);
        
        System.out.println("myPetStore:");
        for (final String e : pets)
        {
            System.out.println(e);
        }   // for
        
        // =====================================================
        System.out.println("");
        // =====================================================
        
        final Shop<Integer> myInts = new Shop<Integer>();
        myInts.sell(1);
        myInts.sell(2);
        myInts.sell(3);
        myInts.sell(4);
        
        final Set<Integer> integers = new HashSet<Integer>();
        myInts.buy(4, integers);
        
        System.out.println("myInts:");
        for (final Integer e : integers)
        {
            System.out.println(e);
        }   // for
        
    }   // main
}   // test3