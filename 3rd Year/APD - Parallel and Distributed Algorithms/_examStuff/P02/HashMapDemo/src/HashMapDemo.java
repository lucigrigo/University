import java.util.HashMap;

class HashMapDemo extends Thread { 
    static HashMap<Integer,String> l=new HashMap<Integer,String>(); 
  
    public void run() { 
        try { 
            Thread.sleep(1000); 
            l.put(103,"D"); 
        } catch(InterruptedException e) { 
            System.out.println("Child Thread going to add element"); 
        } 
    } 

    public static void main(String[] args) throws InterruptedException { 
        l.put(100,"A"); 
        l.put(101,"B"); 
        l.put(102,"C"); 
        HashMapDemo t=new HashMapDemo(); 
        t.start(); 
          
        for (Object o : l.entrySet())  { 
            Object s=o; 
            System.out.println(s); 
            Thread.sleep(1000); 
        } 
        System.out.println(l); 
    } 
}