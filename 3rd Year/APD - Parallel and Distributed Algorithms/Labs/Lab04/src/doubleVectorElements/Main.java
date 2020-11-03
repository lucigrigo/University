package doubleVectorElements;
/**
 * @author cristian.chilipirea
 *
 */
public class Main {
    static int v[];

	public static void main(String[] args) {
        int N = 100000013;
        v = new int[N];
        int cores = Runtime.getRuntime().availableProcessors();
        Thread[] threads = new Thread[cores];

		for(int i=0;i<N;i++)
			v[i]=i;
		
		// Parallelize me
		// for (int i = 0; i < N; i++) {
		// 	v[i] = v[i] * 2;
		// }

        for(int i = 0; i < cores; ++i) {
            threads[i] = new Thread(new DoubleElems(i, N, cores));
            threads[i].start();
        }

        try {
            for(int i = 0; i < cores; ++i)
                threads[i].join();
        } catch(Exception e) {
            e.printStackTrace();
        }

		for (int i = 0; i < N; i++) {
			if(v[i]!= i*2) {
				System.out.println("Wrong answer " + i);
				System.exit(1);
			}
		}
		System.out.println("Correct");
	}

}
