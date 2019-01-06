package com.luciangrigore.todolist;

import com.luciangrigore.todolist.datamodel.TodoData;
import com.luciangrigore.todolist.datamodel.TodoItem;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;

import java.time.LocalDate;

public class DialogController {

    @FXML
    private TextArea detailsArea;
    @FXML
    private TextField shortDescription;
    @FXML
    private DatePicker deadlinePicker;

    public TodoItem processResults() {
        String shortDescriptionString = shortDescription.getText().trim();
        String details = detailsArea.getText().trim();
        LocalDate deadlineValue = deadlinePicker.getValue();

        TodoItem newItem = new TodoItem(shortDescriptionString, details, deadlineValue);

        TodoData.getInstance().addTodoItem(newItem);

        return newItem;
    }
}
