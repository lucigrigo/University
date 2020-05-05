package second;

import first.Task;

import java.util.ArrayList;

public class Stack implements Container {

    private ArrayList<Task> list;

    public Stack() {
        list = new ArrayList<>();
    }

    @Override
    public Task pop() {
        if (list.isEmpty()) return null;
        Task task = list.get(0);
        list.remove(0);
        return task;
    }

    @Override
    public void push(Task task) {
        list.add(0, task);
    }

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public boolean isEmpty() {
        return list.isEmpty();
    }

    @Override
    public void transferFrom(Container container) {
        Task task = container.pop();
        while (task != null) {
            this.push(task);
            task = container.pop();
        }
    }
}
