package com.luciangrigore;

class MyVector3 implements Sumabil<MyVector3> {
    private float x, y, z;

    @Override
    public void addValue(MyVector3 value) {
        this.x += value.getX();
        this.y += value.getY();
        this.z += value.getZ();
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public float getZ() {
        return z;
    }

    public void setZ(float z) {
        this.z = z;
    }

    public MyVector3(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
}
