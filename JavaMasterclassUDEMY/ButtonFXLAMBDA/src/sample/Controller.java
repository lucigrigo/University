package sample;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Button;

public class Controller {

    @FXML
    private Button clickMeButton;

    public void initialize() {
//        clickMeButton.setOnAction(new EventHandler<ActionEvent>() {
//            @Override
//            public void handle(ActionEvent actionEvent) {
//                System.out.println("AU, ma doare. Dar imi plake");
//            }
//        });

        // a lambda expr. with only 1 parameter can have it typed without parentheses
        clickMeButton.setOnAction(actionEvent -> System.out.println("you clicked me!"));
    }
}
