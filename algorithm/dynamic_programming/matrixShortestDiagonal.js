class MatrixShortestDiagonal {
  constructor(matrix) {
    this.matrix = matrix;
    this.mini = Number.MAX_SAFE_INTEGER;
    this.run();
    this.dp_v1();
    this.dp_v2();
  }
  run() {
    this.recursive(0, 0, this.matrix.length - 1, this.matrix, this.matrix[0][0]);
    console.log('min', this.mini);
  }
  recursive(x, y, n, w, dist) {
    if (x === n && y === n) {
      if (dist < this.mini) this.mini = dist;
      return;
    }
    if (x < n) {
      this.recursive(x + 1, y, n, w, dist + w[x + 1][y]);
    }
    if (y < n) {
      this.recursive(x, y + 1, n, w, dist + w[x][y + 1]);
    }
  }
  dp_v1() {
    const states = [];
    const n = this.matrix.length;
    for (let i = 0; i < n; i++) {
      states.push(new Array(n).fill(0));
    }
    // 初始化
    states[0][0] = this.matrix[0][0];
    for (let i = 1; i < n; i++) {
      states[0][i] = states[0][i - 1] + this.matrix[0][i];
      states[i][0] = states[i - 1][0] + this.matrix[i][0];
    }
    // 从（1，1）开始
    for (let i = 1; i < n; i++) {
      for (let j = 1; j < n; j++) {
        states[i][j] = min(states[i - 1][j], states[i][j - 1]) + this.matrix[i][j];
      }
    }
    console.log('dp mini: ', states[n - 1][n - 1]);
  }
  dp_v2() {
    const states = [];
    const n = this.matrix.length;
    for (let i = 0; i < n; i++) {
      states.push(new Array(n).fill(0));
    }
    let miniDist = (x, y) => {
      if (x === 0 && y === 0) return this.matrix[0][0];
      if (states[x][y] > 0) return states[x][y]; // 体现动态规划思想的无后效性
      let left = Number.MAX_SAFE_INTEGER;
      let up = Number.MAX_SAFE_INTEGER;
      if (x >= 1) {
        left = miniDist(x - 1, y);
      }
      if (y >= 1) {
        up = miniDist(x , y - 1);
      }
      states[x][y] = min(left, up) + this.matrix[x][y];
      return states[x][y];
    }
    const result = miniDist(n - 1, n - 1);
    console.log('dp_v2: ', states[n - 1][n - 1]);
  }
}

function min(x, y) {
  if (x < y) return x;
  else return y;
}

const testData = [
  [1, 3, 5, 9],
  [2, 1, 3, 4],
  [5, 2, 6, 7],
  [6, 8, 4, 3],
];
const test = new MatrixShortestDiagonal(testData);
test.run();