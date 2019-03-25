package sample;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;

import java.io.IOException;
import java.util.Optional;

public class Controller {

    @FXML
    private TableView<Contact> tableView;
    @FXML
    private BorderPane borderPane;
    private ContactData data;

    public void initialize() {
//        TableColumn firstNameCol = new TableColumn("First Name");
//        TableColumn lastNameCol = new TableColumn("Last Name");
//        TableColumn phoneNumberCol = new TableColumn("Phone");
//        TableColumn notesCol = new TableColumn("Notes");
//
//        tableView.getColumns().addAll(firstNameCol, lastNameCol, phoneNumberCol, notesCol);
//        tableView.getColumns().get(0).setMinWidth(150);
//        tableView.getColumns().get(1).setMinWidth(150);
//        tableView.getColumns().get(2).setMinWidth(200);
//        tableView.getColumns().get(3).setMinWidth(300);

        data = new ContactData();
        data.loadContacts();
        tableView.setItems(data.getContacts());
    }

    @FXML
    public void addNewContactWindow() {
        Dialog<ButtonType> dialog = new Dialog<>();
        dialog.initOwner(borderPane.getScene().getWindow());
        dialog.setTitle("New contact");
        dialog.setHeaderText("Use this dialog to create a new contact");
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("newContactWindow.fxml"));

        try {
            dialog.getDialogPane().setContent(fxmlLoader.load());
        } catch (IOException e) {
            System.out.println("Could not load the dialog !");
            e.printStackTrace();
            return;
        }

        dialog.getDialogPane().getButtonTypes().add(ButtonType.OK);
        dialog.getDialogPane().getButtonTypes().add(ButtonType.CANCEL);

        Optional<ButtonType> result = dialog.showAndWait();
        if (result.isPresent() && result.get() == ButtonType.OK) {
            NewContactWindowController newContactWindowController = fxmlLoader.getController();
            Contact newContact = newContactWindowController.getNewContact();
            data.addContact(newContact);
            data.saveContacts();
        } else {

        }
    }

    @FXML
    public void showEditDialog() {
        Contact selectedContact = tableView.getSelectionModel().getSelectedItem();
        if (selectedContact == null) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("No contact selected");
            alert.setHeaderText(null);
            alert.setContentText("Please select the contact you want to edit!");
            alert.showAndWait();
            return;
        }

        Dialog<ButtonType> dialog = new Dialog<>();
        dialog.initOwner(borderPane.getScene().getWindow());
        dialog.setTitle("Edit contact");
        FXMLLoader fxmlLoader = new FXMLLoader();
        fxmlLoader.setLocation(getClass().getResource("newContactWindow.fxml"));
        try {
            dialog.getDialogPane().setContent(fxmlLoader.load());
        } catch (IOException e) {
            System.out.println("Could not load the dialog!");
            e.printStackTrace();
            return;
        }

        dialog.getDialogPane().getButtonTypes().add(ButtonType.OK);
        dialog.getDialogPane().getButtonTypes().add(ButtonType.CANCEL);

        NewContactWindowController newContactWindowController = fxmlLoader.getController();
        newContactWindowController.editContact(selectedContact);

        Optional<ButtonType> result = dialog.showAndWait();
        if (result.isPresent() && result.get() == ButtonType.OK) {
            newContactWindowController.updateContact(selectedContact);
            data.saveContacts();
        }
    }

    @FXML
    public void deleteContact() {
        Contact selectedContact = tableView.getSelectionModel().getSelectedItem();
        if (selectedContact == null) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("No contact selected");
            alert.setHeaderText(null);
            alert.setContentText("Please select the contact you want to delete!");
            alert.showAndWait();
            return;
        }

        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Delete contact");
        alert.setHeaderText(null);
        alert.setContentText("Are you sure you want to delete\n" +
                selectedContact.getFirstName() + " " +
                selectedContact.getLastName());

        Optional<ButtonType> result = alert.showAndWait();
        if (result.isPresent() && result.get() == ButtonType.OK) {
            data.removeContact(selectedContact);
            data.saveContacts();
        }
    }
}

