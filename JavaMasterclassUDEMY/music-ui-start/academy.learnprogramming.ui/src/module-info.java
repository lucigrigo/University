module academy.learnprogramming.ui {
    requires javafx.controls;
    requires javafx.fxml;
    requires academy.learnprogramming.db;
//    requires academy.learnprogramming.common;

    exports academy.learnprogramming.ui to javafx.graphics, javafx.fxml;
    opens academy.learnprogramming.ui to javafx.fxml;
}