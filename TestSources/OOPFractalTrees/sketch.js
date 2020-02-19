var tree = [];
var leaves = []

var count = 0;

function setup() {
  createCanvas(400, 400);
  var a = createVector(width / 2, height);
  var b = createVector(width / 2, height - 100);
  var root = new Branch(a, b);

  tree[0] = root;
}

function mousePressed() {
  for (var i = tree.length - 1; i >= 0; i--) {
    if (!tree[i].finished) {
      tree[i].finished = true;
      tree.push(tree[i].branchRight());
      tree.push(tree[i].branchLeft());
    }
  }
  count++;

  if (count == 5) {
    for (var i = 0; i < tree.length; i++) {
      if(!tree[i].finished) {
        var leaf = tree[i].end.copy();
        leaves.push(leaf);
      }
    }
    count = 0;
  }
}

function draw() {
  background(51);

  for (var i = 0; i < tree.length; i++) {
    tree[i].show();
    // tree[i].jitter();
  }

  for (var i = 0; i < leaves.length; i++) {
    fill(255, 0, 100, 100);
    noStroke();
    ellipse(leaves[i].x, leaves[i].y, 8, 8);
    leaves[i].y += random(0, 0.5);
    leaves[i].x += random(-0.2, 0.2);
  }
}
