class ZonaTampon {
  private int buf; // val. curenta din tampon
  private volatile boolean disponibil = false; // daca o valoare este disponibila in buf

  public synchronized int Consuma() {
    if (!disponibil) { // val. indisponibila
      try {
        this.wait(); // suspenda executia si deblocheaza zavor
      } catch (InterruptedException e) {
      }
    }
    disponibil = false;
    this.notifyAll(); // pune in executie un thread in asteptare
    return buf;
  }

  public synchronized void Produ(int valoare) {
    if (disponibil) {// o valoare in tampon
      try {
        this.wait();
      } catch (InterruptedException e) {
      }
    }
    buf = valoare;
    disponibil = true;
    this.notify();
  }
}
