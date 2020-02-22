class Circle {
  float x;
  float y;
  float r;

  boolean growing = true;

  Circle(float x_, float y_) {
    this.x = x_;
    this.y = y_;
    this.r = 1;
  }

  boolean edges() {
    return (x + r >= width || x - r <= 0 || 
      y + r >= height || y - r <= 0);
  }

  void grow() {
    if (growing) {
      r = r + 0.5;
    }
  }

  void show() {
    stroke(255);
    strokeWeight(2);
    noFill();
    ellipse(x, y, r*2, r*2);
  }
}
