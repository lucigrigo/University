package parallelTree;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class ReadTreePart implements Runnable {
	TreeNode tree;
	String fileName;

	public ReadTreePart(TreeNode tree, String fileName) {
		this.tree = tree;
		this.fileName = fileName;
	}

	@Override
	public void run() {
		try {
			Scanner scanner = new Scanner(new File(fileName));
			TreeNode treeNode;

			while (scanner.hasNextInt()) {
				int child = scanner.nextInt();
				int root = scanner.nextInt();

				treeNode = tree.getNode(root);
				while (treeNode == null) {
					treeNode = tree.getNode(root);
				}

				treeNode.addChild(new TreeNode(child));
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}
