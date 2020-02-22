function setup() {
  createCanvas(400, 400);
}

function draw() {
  background(0);

  let hours = hour();
  let minutes = minute();
  let sc = second();

  fill(255);
  noStroke();
  text(hours + ":" + minutes + ":" + seconds, 20, 200);
}
