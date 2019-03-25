package sample;

import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.concurrent.Service;
import javafx.concurrent.Task;
import javafx.concurrent.Worker;
import javafx.concurrent.WorkerStateEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.ProgressBar;

import java.security.Provider;

public class Controller {

    //    private Task<ObservableList<String>> task;
    @FXML
    private ListView listView;
    @FXML
    private ProgressBar progressBar;
    @FXML
    private Label progressLabel;
    private Service<ObservableList<String>> service;

    public void initialize() {
//        progressBar.visibleProperty().set(false);
//        progressLabel.disableProperty().set(true);
//        task = new Task<ObservableList<String>>() {
//            @Override
//            protected ObservableList<String> call() throws Exception {
//                String[] names = {
//                        "Luci Grigore",
//                        "Marian Godina",
//                        "Pustiul deVizavi",
//                        "Marian Fantastik"};
//
//                ObservableList<String> employees = FXCollections.observableArrayList();
//                for (int i = 0; i < names.length; i++) {
//                    employees.add(names[i]);
//                    updateMessage("Added " + names[i] + " to the list.");
//                    updateProgress(i + 1, names.length);
//                    Thread.sleep(500);
//                }
//
//                return employees;
//            }
//        };

        progressLabel.setVisible(false);
        progressBar.setVisible(false);

        service = new EmployeeService();

        progressBar.progressProperty().bind(service.progressProperty());
        listView.itemsProperty().bind(service.valueProperty());
        progressLabel.textProperty().bind(service.messageProperty());

        progressBar.visibleProperty().bind(service.runningProperty());
        progressLabel.visibleProperty().bind(service.runningProperty());

//        service.setOnRunning(new EventHandler<WorkerStateEvent>() {
//            @Override
//            public void handle(WorkerStateEvent workerStateEvent) {
//                progressBar.setVisible(true);
//                progressLabel.setVisible(true);
//            }
//        });
//
//        service.setOnSucceeded(new EventHandler<WorkerStateEvent>() {
//            @Override
//            public void handle(WorkerStateEvent workerStateEvent) {
//                progressLabel.setVisible(false);
//                progressBar.setVisible(false);
//            }
//        });


//        listView.itemsProperty().bind(task.valueProperty());
//        progressLabel.textProperty().bind(task.messageProperty());
//        progressBar.progressProperty().bind(task.progressProperty());
    }

    @FXML
    public void buttonPressed() {
        //        new Thread(task).start();
//        Thread t = new Thread(task);
//        t.start();

//        progressBar.visibleProperty().set(true);
//        progressLabel.disableProperty().set(false);

        if (service.getState().equals(Service.State.SUCCEEDED)) {
            service.reset();
            service.start();
        } else if (service.getState().equals(Service.State.READY)) {
            service.start();
        }

//        while (!t.getState().equals(Thread.State.TERMINATED)) {
//            progressBar.visibleProperty().set(false);
//            progressLabel.disableProperty().set(true);
//        }
    }
}
