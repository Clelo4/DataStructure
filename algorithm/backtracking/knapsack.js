class Knapsack {
  constructor(w, wList, vList) {
    this.wList = wList.slice(0, wList.length);
    this.vList = vList.slice(0, vList.length);
    this.w = w;
    this.wMax = 0;
    this.vMax = 0;
    this.calculate(0, 0, 0);
    console.log(this.vMax);
    console.log(this.wMax);
  }
  calculate(i, cw, cv) {
    if (i === this.wList.length || cw === this.w) {
      if (cv > this.vMax) {
        this.vMax = cv;
        this.wMax = cw;
      }
      return;
    }
    this.calculate(i + 1, cw, cv)
    if ((cw + this.wList[i]) <= this.w) {
      this.calculate(i + 1, cw + this.wList[i], cv + this.vList[i]);
    }
  }
}

const test = new Knapsack(100, [24, 13, 345, 234, 30, 20, 45], [91, 2, 3, 4, 5, 6, 7]);