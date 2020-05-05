package task2;

public class Student {
    private String name;
//    Integer year = new Integer(0);
    private int year = 0;

    public void setName(String name){
        this.name = name;
    }

    public void setYear(int year){
        this.year = year;
    }

    public String getName(){
        return this.name;
    }

    public int getYear(){
        return this.year;
    }
}
