class TestSynchronization1 {
  public static void main(String args[]) {
    Table obj = new Table();// only one object
    MyThread1 t1 = new MyThread1(obj);
    obj = new Table();// only one object
    MyThread2 t2 = new MyThread2(obj);
    t1.start();
    t2.start();
  }
}