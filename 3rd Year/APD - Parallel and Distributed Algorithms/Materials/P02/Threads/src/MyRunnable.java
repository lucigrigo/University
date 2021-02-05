public class MyRunnable implements Runnable {
  private final long countUntil;

  MyRunnable(long countUntil) {
      this.countUntil = countUntil;
  }

  @Override
  public void run() {
      long sum = 0;
      for (long i = 1; i < countUntil; i++) {
          sum += i;
      }
      try { Thread.sleep(2000); } catch(Exception e) {} 
      System.out.println(sum);
  }
}