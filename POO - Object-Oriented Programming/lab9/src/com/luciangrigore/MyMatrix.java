package com.luciangrigore;

public class MyMatrix implements Sumabil<MyMatrix> {
    private int[][] matrix = new int[4][4];

    public int[][] getMatrix() {
        return matrix;
    }

    public int getValue(int i, int j) {
        return matrix[i][j];
    }

    public void setMatrix(int[][] matrix) {
        this.matrix = matrix;
    }

    @Override
    public void addValue(MyMatrix value) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                this.matrix[i][j] += value.getValue(i, j);
            }
        }
    }

    public MyMatrix(int[][] matrix) {
        this.matrix = matrix;
    }
}
