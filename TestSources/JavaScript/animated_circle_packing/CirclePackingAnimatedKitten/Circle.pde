class Circle {
  float x;
  float y;
  float r;
  color c;

  boolean growing = true;

  Circle(float x_, float y_, color c_) {
    this.x = x_;
    this.y = y_;
    this.r = 1;
    this.c = c_;
  }

  boolean edges() {
    return (x + r >= width || x - r <= 0 || 
      y + r >= height || y - r <= 0);
  }

  void grow() {
    if (growing) {
      r = r + 0.4;
    }
  }

  void show() {
    fill(this.c);
    noStroke();
    ellipse(x, y, r*2, r*2);
  }
}
