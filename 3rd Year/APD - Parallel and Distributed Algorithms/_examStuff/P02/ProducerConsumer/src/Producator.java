public class Producator extends Thread {
  private ZonaTampon Tampon;
  private int numar; // ID-ul producatorului

  public Producator(ZonaTampon z, int numar) {
    Tampon = z;
    this.numar = numar;
  }

  public void run() {
    for (int i = 0; i < 10; i++) {
      Tampon.Produ(i);
      System.out.println("Producator " + this.numar + " a transmis: " + i);
      try {
        sleep((int)Math.random() * 100);
      } catch (InterruptedException e) {}
    }
  }
}
