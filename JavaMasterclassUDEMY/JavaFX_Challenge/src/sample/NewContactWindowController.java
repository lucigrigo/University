package sample;

import javafx.fxml.FXML;
import javafx.scene.control.ContextMenu;
import javafx.scene.control.TextField;

public class NewContactWindowController {

    @FXML
    private TextField firstName;
    @FXML
    private TextField lastName;
    @FXML
    private TextField phoneNumber;
    @FXML
    private TextField notes;

    public Contact getNewContact() {
        String fName = firstName.getText();
        String lName = lastName.getText();
        String pNumber = phoneNumber.getText();
        String nts = notes.getText();

        Contact newContact = new Contact(fName, lName, pNumber, nts);
        return newContact;
    }

    public void editContact(Contact contact) {
        firstName.setText(contact.getFirstName());
        lastName.setText(contact.getLastName());
        phoneNumber.setText(contact.getPhoneNumber());
        notes.setText(contact.getNotes());
    }

    public void updateContact(Contact newContact) {
        newContact.setFirstName(firstName.getText());
        newContact.setLastName(lastName.getText());
        newContact.setPhoneNumber(phoneNumber.getText());
        newContact.setNotes(notes.getText());
    }
}
