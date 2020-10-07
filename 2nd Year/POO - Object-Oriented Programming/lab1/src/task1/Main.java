package task1;

public class Main {
    public static void main(String[] args) {
        VeterinaryReport vr = new VeterinaryReport();
        VeterinaryReport vr2 = new VeterinaryReport();

        vr.cats = 99;
        vr.dogs = 199;
        vr2.dogs = 2;

        vr.displayStatistics();
        vr2.displayStatistics();

        System.out.println("The first class method says there are " + vr.getAnimalsCount() + " animals");
        System.out.println("The second class method says there are " + vr2.getAnimalsCount() + " animals");
    }
}

class VeterinaryReport {
     int dogs;
     int cats;

    public int getAnimalsCount() {
        return dogs + cats;
    }

    public void displayStatistics() {
        System.out.println("Total number of animals is " + getAnimalsCount());
    }
}
