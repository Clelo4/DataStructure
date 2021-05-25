class EightQueens {
  constructor() {
    this.matrix = new Array(8).fill(0).reduce((acc, cur) => { acc.push(new Array(8).fill(undefined)); return acc; },[]);
    this.allResultCount = 0;
    this.calculate(0);
    this.printAllResult();
  }
  isConflict(x, y) {
    // 比较x轴
    for (let i = 0; i < x; i++) {
      if (this.matrix[y][i]) {
        return true;
      }
    }
    // 比较对角线
    let x_index = x; let y_index = y;
    while (--x_index >= 0 && --y_index >= 0) {
      if (this.matrix[y_index][x_index]) return true;
    }
    x_index = x; y_index = y;
    while (--x_index >= 0 && ++y_index < 8) {
      if (this.matrix[y_index][x_index]) return true;
    }
    return false;
  }
  calculate(targetX) {
    if (targetX === 8) {
      this.print();
    }
    for (let j = 0; j < 8; j++) {
      if (!this.isConflict(targetX, j)) {
        this.matrix[j][targetX] = true;
        this.calculate(targetX + 1);
        this.matrix[j][targetX] = undefined; // 恢复
      }
    }
  }
  print() {
    this.allResultCount++;
    return;
    let result = [];
    for (let i = 0; i < 8; i++) {
      result[i] = this.matrix[i].slice(0, 8);
    }
    console.log('---print eight queens----')
    let start = new Array(8).fill(0);
    start.forEach((k, i) => {
      start[i] = i;
    });
    console.log(' ', start.join(' '));
    for (let i = 0; i < 8; i++) {
      let rowList = [];
      for (let j = 0; j < 8; j++) {
        let result = this.matrix[i][j];
        if (result) rowList.push('*');
        else rowList.push(' ');
      }
      console.log(i + ' ' + rowList.join(' '));
    }
  }
  printAllResult() {
    console.log(this.allResultCount);
  }
}
console.time('start');
let test = new EightQueens();
console.timeEnd('start');