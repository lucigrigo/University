package com.luciangrigore;

import java.sql.*;

public class Main {

    public static final String DB_NAME = "javatest.db";
    public static final String CONNECTION_STRING = "jdbc:sqlite:C:\\Users\\LuciGrigore\\Documents\\UDEMYCompleteJavaMasterclass\\TestDB\\" + DB_NAME;

    public static final String TABLE_CONTACTS = "contacts";
    public static final String COLUMN_NAME = "name";
    public static final String COLUMN_PHONE = "phone";
    public static final String COLUMN_EMAIL = "email";

    public static void main(String[] args) {
//        try (Connection con = DriverManager.getConnection("jdbc:sqlite:C:\\Users\\LuciGrigore\\Documents\\UDEMYCompleteJavaMasterclass\\TestDB\\testjava.db");
//             Statement statement = con.createStatement()) {
        try {
            Connection con = DriverManager.getConnection(CONNECTION_STRING);
            Statement statement = con.createStatement();

            statement.execute("DROP TABLE IF EXISTS " + TABLE_CONTACTS);
            statement.execute("CREATE TABLE IF NOT EXISTS " + TABLE_CONTACTS +
                    "(" + COLUMN_NAME + " text, " + COLUMN_PHONE + " INTEGER, "
                    + COLUMN_EMAIL + " text)");

            insertContact(statement, "lucian", "nebunie@cutie.net", 12345);
            insertContact(statement, "grigoras", "dela@oras.rrom", 555444);
            insertContact(statement, "jane", "mary@jane.ro", 696969);
            insertContact(statement, "jean", "deLa@craiova.com", 44990022);

            statement.execute("DELETE FROM " + TABLE_CONTACTS + " WHERE " + COLUMN_NAME + "='jean'");
            statement.execute("UPDATE " + TABLE_CONTACTS + " SET " + COLUMN_EMAIL + "='vedem@dacamerge.ro'" +
                    " WHERE " + COLUMN_NAME + "='jane'");

            ResultSet resultSet = statement.executeQuery("SELECT * FROM " + TABLE_CONTACTS);
            while (resultSet.next()) {
                System.out.println(resultSet.getString(COLUMN_NAME) + " " +
                        resultSet.getInt(COLUMN_PHONE) + " " + resultSet.getString(COLUMN_EMAIL));
            }
            resultSet.close();

            //  statement instances should be closed first; then, close the connection
            statement.close();
            con.close();
        } catch (
                SQLException e) {
            System.out.println("something went wrong! " + e.getMessage());
        }
    }

    private static void insertContact(Statement statement, String name, String email, int phone) throws SQLException {
        statement.execute("INSERT INTO " + TABLE_CONTACTS +
                "(" + COLUMN_NAME + ","
                + COLUMN_PHONE + ","
                + COLUMN_EMAIL + ")"
                + " VALUES('" + name + "'," + phone + ", '" + email + "')");
    }
}
