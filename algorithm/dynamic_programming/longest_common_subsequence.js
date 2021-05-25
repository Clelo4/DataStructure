class LongestCommonSubsequence {
  constructor(str1, str2) {
    this.s1 = str1;
    this.s2 = str2;
    this.states = [];
    for (let i = 0; i < str1.length; i++) {
      this.states.push(new Array(str2.length).fill(-1));
    }
    this.start(this.s1.length - 1, this.s2.length - 1);
    console.log(this.states);
    console.log('result: ', this.states[this.s1.length - 1][this.s2.length - 1]);
    this.backtrackMiniDist = Number.MAX_SAFE_INTEGER;
    // this.backtrack(0, 0, 0);
    console.log('backtrack result: ', this.backtrackMiniDist);
    this.dp_v1();
    this.dp_v2();
  }
  start(i, j) {
    if (i < 0) return 0;
    if (j < 0) return 0;
    const val = this.states[i][j];
    if (val >= 0) return val;
    const v1 = this.start(i - 1, j);
    const v2 = this.start(i, j - 1);
    let v3 = this.start(i - 1, j - 1);
    if (this.s1[i] === this.s2[j]) {
      this.states[i][j] = max(v3 + 1, max(v1, v2));
      return this.states[i][j];
    } else {
      this.states[i][j] = max(v3, max(v1, v2));
      return this.states[i][j];
    }
  }
  backtrack(i, j, eDist) {
    if (i === this.s1.length || j === this.s2.length) {
      if (i < this.s1.length) eDist += (this.s1.length - i);
      if (j < this.s2.length) eDist += (this.s2.length - j);
      if (eDist < this.backtrackMiniDist) this.backtrackMiniDist = eDist;
      return;
    }
    if (this.s1[i] === this.s2[j]) {
      this.backtrack(i + 1, j + 1, eDist);
    } else {
      this.backtrack(i + 1, j, eDist + 1);
      this.backtrack(i, j + 1, eDist + 1);
      this.backtrack(i + 1, j + 1, eDist + 1);
    }
  }
  dp_v1() {
    const states = [];
    for (let i = 0; i < this.s1.length; i++) {
      states.push(new Array(this.s2.length).fill(0));
    }
    states[0][0] = 0;
    for (let i = 1; i < this.s2.length; i++) {
      states[0][i] = states[0][i - 1] + 1;
    }
    for (let i = 1; i < this.s1.length; i++) {
      states[i][0] = states[i - 1][0] + 1;
    }
    for (let i = 1; i < this.s1.length; i++) {
      for (let j = 1; j < this.s2.length; j++) {
        let v1 = states[i - 1][j];
        let v2 = states[i][j - 1];
        let v3 = states[i - 1][j - 1];
        if (this.s1[i] === this.s2[j]) {
          states[i][j] = min(v3, min(v1, v2));
        } else {
          states[i][j] = min(v3, min(v1, v2)) + 1;
        }
      }
    }
    console.log('dp_v1: ', states[this.s1.length - 1][this.s2.length - 1]);
  }
  dp_v2() {
    const states = [];
    for (let i = 0; i < this.s1.length; i++) {
      states.push(new Array(this.s2.length).fill(0));
    }
    if (this.s1[0] === this.s2[0]) states[0][0] = 1;
    for (let i  = 1; i < this.s2.length; i++) {
      states[0][i] = states[0][0];
    }
    for (let i = 1; i < this.s1.length; i++) {
      states[i][0] = states[0][0];
    }
    for (let i = 1; i < this.s1.length; i++) {
      for (let j = 1; j < this.s2.length; j++) {
        let v1 = states[i - 1][j];
        let v2 = states[i][j - 1];
        let v3 = states[i - 1][j - 1];
        if (this.s1[i] === this.s2[j]) {
          states[i][j] = max(v3 + 1, max(v1, v2));
        } else {
          states[i][j] = max(v3, max(v1, v2));
        }
      }
    }
    console.log('dp_v2: ', states[this.s1.length - 1][this.s2.length - 1]);
  }
}

function max(x, y) {
  if (x < y) return y;
  else return x;
}
function min(x, y) {
  if (x > y) return y;
  else return x;
}

const test = new LongestCommonSubsequence([0, 8, 4, 2, 1, 6, 9, 5, 3, 7].join(''), [0, 8, 4, 2, 1, 6, 9, 5, 3, 7].sort().join(''));
