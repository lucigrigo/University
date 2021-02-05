public class Consumator extends Thread {
  private ZonaTampon Tampon;
  private int numar; // ID-ul consumatorului

  public Consumator(ZonaTampon z, int numar) {
    Tampon = z;
    this.numar = numar;
  }

  public void run() {
    int valoare = 0;
    for (int i = 0; i < 10; i++) {
      valoare = Tampon.Consuma();
      System.out.println("Consumator" + this.numar + " a preluat " + valoare);
    }
  }
}