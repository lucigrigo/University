function setup() {
  createCanvas(400, 400);
  angleMode(DEGREES);
}

function draw() {
  background(0);
  translate(200, 200);
  rotate(-90);

  let hours = hour();
  let minutes = minute();
  let seconds = second();

  strokeWeight(8);
  noFill();

  stroke(255, 100, 150);
  let secAngle = map(seconds, 0, 60, 0, 360);
  arc(0, 0, 300, 300, 0, secAngle);

  stroke(100, 150, 255);
  let minAngle = map(minutes, 0, 60, 0, 360);
  arc(0, 0, 270, 270, 0, minAngle);

  stroke(100, 255, 150);
  let hourAngle = map(hours % 12, 0, 12, 0, 360);
  arc(0, 0, 240, 240, 0, hourAngle);

  push();
  rotate(secAngle);
  stroke(255, 100, 150);
  line(0, 0, 100, 0);
  pop();

  push();
  rotate(minAngle);
  stroke(100, 150, 255);
  line(0, 0, 100, 0);
  pop();

  push();
  rotate(hourAngle);
  stroke(100, 255, 150);
  line(0, 0, 100, 0);
  pop();

  stroke(255);
  point(0, 0);

  // fill(255);
  // noStroke();
  // text(hours + ':' + minutes + ':' + seconds, 20, 200);
}
