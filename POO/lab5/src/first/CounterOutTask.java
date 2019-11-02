package first;

public class CounterOutTask implements Task {
    private static int contor = 0;

    public void increment() {
        this.contor++;
    }

    @Override
    public void execute() {
       this.contor++;
        System.out.println("contor = " + contor);
    }
}
