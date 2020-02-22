ArrayList<Circle> circles;
ArrayList<PVector> spots;
PImage img;

void setup() {
  size(680, 906);
  //background(0);
  img = loadImage("kitten.png");
  img.loadPixels();
  
  circles = new ArrayList<Circle>();
}

void draw() {
  int total = 100;
  int count = 0;
  int attempts = 10;

  while (count < total) {
    Circle newC = newCircle();
    if (newC != null) {
      circles.add(newC);
      count++;
    }
    attempts++;
    if (attempts > 1000) {
      noLoop();
      println("FINISHED");
      break;
    }
  }

  for (Circle c : circles) {
    if (c.growing) {
      if (c.edges()) {
        c.growing = false;
      } else {
        for (Circle other : circles) {
          if (c != other) {
            float d = dist(c.x, c.y, other.x, other.y);
            if (d - 2 < c.r + other.r) {
              c.growing = false;
            }
          }
        }
      }
    }
    c.show();
    c.grow();
  }
}

Circle newCircle() {
  
  float x = random(width);
  float y = random(height);

  boolean valid = true;
  for (Circle c : circles ) {
    float d = dist(x, y, c.x, c.y);
    if (d < c.r) {
      valid = false;
      break;
    }
  }

  if (valid) {
    int index = int(x) + int(y) * img.width;
    color col = img.pixels[index];
    return new Circle(x, y, col);
  }

  return null;
}
