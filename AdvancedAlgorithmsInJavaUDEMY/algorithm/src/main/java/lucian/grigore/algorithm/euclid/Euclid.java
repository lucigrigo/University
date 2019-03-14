package lucian.grigore.algorithm.euclid;

//  EUCLID ALGORITHM
//  it calculates the greatest common divisor (GCD) between two numbers
public class Euclid {

    public int gcd(int number, int divisor) {
        int remaining = (number % divisor);

        if (remaining != 0) {
            return gcd(divisor, remaining);
        } else {
            return divisor;
        }
    }

    public int gcd2(int number, int divisor) {
        while(divisor != 0) {
            int temp = divisor;
            divisor = number % divisor;
            number = temp;
        }
        return number;
    }
}
