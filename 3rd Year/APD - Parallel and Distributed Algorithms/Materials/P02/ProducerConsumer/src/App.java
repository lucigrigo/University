public class App {
    public static void main(String[] args) {
        ZonaTampon z = new ZonaTampon();
        Producator p1 = new Producator(z, 1);
        Consumator c1 = new Consumator(z, 1);
                        //p1 si c1 folosesc aceeasi ZonaTampon
        p1.start();
        c1.start();
    }
    
}
