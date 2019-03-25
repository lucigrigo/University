import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class example {

    public static void main(String[] args) {
        try {
            int result = divide();
            System.out.println("Result is " + result);
        } catch (ArithmeticException | NoSuchElementException e) {  //  Catching multiple exceptions
            System.out.println(e.toString());
            System.out.println("Unable to perform division. Autopilot shutting down . . .");
        }
    }

    private static int divide() {
        int x, y;
//        try {
        x = getInt();
        y = getInt();
        System.out.println("X is " + x + " and y is " + y + '\n');
        return x / y;
//        } catch (NoSuchElementException nsee) {
//            throw new NoSuchElementException("no suitable input");
//        } catch (ArithmeticException ae) {
//            throw new ArithmeticException("attempt to divide by zero");
//        }
    }

    private static int getInt() {
        Scanner s = new Scanner(System.in);
        System.out.println("Please enter an integer:");
        while (true) {
            try {
                return s.nextInt();
            } catch (InputMismatchException ime) {
                // go round again. Read past the end of line in input first
                s.next();
                System.out.println("Please enter a number using only digits 0 to 9");
            }
        }
    }
}
