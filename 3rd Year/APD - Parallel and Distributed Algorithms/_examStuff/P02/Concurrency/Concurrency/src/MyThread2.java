class MyThread2 extends Thread {
  Table t;

  MyThread2(Table t) {
    this.t = t;
  }

  public void run() {
    Table.printTable(100);
  }
}