class KnapsackDp {
  constructor(weight, value, w) {
    this.weightList = weight.slice(0, weight.length);
    this.valueList = value.slice(0, value.length);
    this.n = weight.length;
    this.w = w;
  }
  start() {
    const states = [];
    for (let i = 0; i < this.n; i++) {
      states[i] = [];
      for (let j = 0; j < this.w; j++) {
        states[i][j] = -1;
      }
    }
    // 处理第一个
    states[0][0] = 0;
    if (this.weightList[0] < this.w) {
      states[0][this.weightList[0]] = this.valueList[0];
    }
    for (let i = 1; i < this.n; i++) {
      for (let j = 0; j < this.w; j++) {
        if (states[i - 1][j] > -1) states[i][j] = states[i - 1][j];
      }
      // 选中
      for (let j = 0; j <= this.w - this.weightList[i]; j++) {
        if (states[i - 1][j] < 0) continue;
        if ((states[i - 1][j] + this.valueList[i]) > states[i][j + this.weightList[i]]) {
          states[i][j + this.weightList[i]] = states[i - 1][j] + this.valueList[i];
        }
      }
    }
    let maxValue = -1;
    for (let j = 0; j <= this.w; j++) {
      if (states[this.n - 1][j] > maxValue) maxValue = states[this.n - 1][j];
    }
    console.log('max value: ', maxValue);
    let selectList = [];
    let target = -1;
    let lastWeight = -1;
    for (let i = this.n - 1; i >= 1; i--) {
      for (let j = 0; j <= this.w; j++) {
        if (states[i][j] === maxValue) {
          lastWeight = j;
          if (states[i - 1][j] === states[i][j]) {
            // 没选中
            // selectList.unshift(0);
            selectList[i] = 0;
          } else {
            maxValue = maxValue - this.valueList[i];
            // selectList.unshift(1);
            selectList[i] = 1;
          }
          break;
        }
      }
    }
    if (states[0][this.weightList[0]] === maxValue) {
      selectList[0] = 1;
    } else {
      selectList[0] = 0;
    }
    console.log('selectList: ', selectList);
  }
}

const test = new KnapsackDp([24, 13, 345, 234, 30, 20, 45], [91, 2, 3, 4, 5, 6, 7], 100);
test.start()
