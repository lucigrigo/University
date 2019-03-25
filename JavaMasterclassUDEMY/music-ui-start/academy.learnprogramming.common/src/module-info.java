module academy.learnprogramming.common {
    requires java.sql;
    requires javafx.fxml;
    requires javafx.controls;
//    requires kotlin.stdlib;

    opens academy.learnprogramming.common;
    exports academy.learnprogramming.common;
}