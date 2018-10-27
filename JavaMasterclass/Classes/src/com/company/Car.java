package com.company;

public class Car {

    private int doors, wheels;
    private String model, engine, color;

    public void setModel(String model) {
        String modelName = model.toLowerCase();
        if (modelName.equals("panamera") || modelName.equals("7series")) {
            this.model = model;
        } else {
            this.model = "Unknown";
        }
    }

    public String getModel() {
        return this.model;
    }
}
