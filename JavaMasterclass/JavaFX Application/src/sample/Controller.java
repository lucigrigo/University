package sample;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.effect.DropShadow;
import javafx.scene.layout.GridPane;
import javafx.stage.FileChooser;

import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.List;

public class Controller {

    @FXML
    private Label label;
    @FXML
    private Button button4;
    @FXML
    private GridPane gridPane;
    /*
        @FXML
        private WebView webView;
     */

    public void initialize() {
        button4.setEffect(new DropShadow());
    }

    @FXML
    public void handleMouseEnter() {
        label.setScaleY(2.0);
        label.setScaleX(2.0);
    }

    @FXML
    public void handleMouseExit() {
        label.setScaleY(1.0);
        label.setScaleX(1.0);
    }

    @FXML
    public void handleClick() {
        FileChooser chooser = new FileChooser();
        chooser.setTitle("Save app file");
        chooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Java", "*.java"),
                new FileChooser.ExtensionFilter("PDF", "*.pdf"),
                new FileChooser.ExtensionFilter("Image files", "*.gif", "*.png", "*.jpeg"),
                new FileChooser.ExtensionFilter("All files", "*.*")
        );

        List<File> file = chooser.showOpenMultipleDialog(gridPane.getScene().getWindow());
        if (file != null) {
            for (File i : file) {
                System.out.println(i.getPath());
            }
        } else {
            System.out.println("Chooser was cancelled");
        }
    }

    @FXML
    public void handleLinkClick() {
//        System.out.println("The link was clicked !");
        try {
            Desktop.getDesktop().browse(new URI("http://www.javafx.com"));
        } catch (IOException e) {
            e.printStackTrace();
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }

        /*
            WebEngine engine = webView.getEngine();
            engine.load("http://www.javafx.com");
         */
    }
}
