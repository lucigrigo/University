package example.sampleForkJoinPool;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MyTask extends RecursiveTask<Void> {
	private final String path;

	public MyTask(String path) {
		this.path = path;
	}

	@Override
	protected Void compute() {
		File file = new File(path);
		if (file.isFile()) {
			System.out.println(file.getPath());
			return null;
		} else if (file.isDirectory()) {
			File[] files = file.listFiles();
			List<MyTask> tasks = new ArrayList<>();
			if (files != null) {
				for (var f : files) {
					MyTask t = new MyTask(f.getPath());
					tasks.add(t);
					t.fork();
				}
			}
			for (MyTask task: tasks) {
				task.join();
			}
		}
		return null;
	}
}
