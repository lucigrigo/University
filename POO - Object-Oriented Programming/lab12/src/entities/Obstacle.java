package entities;

public class Obstacle {

    private int xPos = -1;
    private int yPos = -1;

    public Obstacle(int xPos, int yPos) {
        this.xPos = xPos;
        this.yPos = yPos;
    }

    public int getxPos() {
        return xPos;
    }

    public int getyPos() {
        return yPos;
    }
}
