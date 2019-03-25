package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Label;

public class Controller {

    @FXML
    private Label label;

    @FXML
    public void handleClick() {
        label.setText("OK WAS PRESSED");
    }
}
