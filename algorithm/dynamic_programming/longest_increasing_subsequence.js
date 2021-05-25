function getMax(a, b) {
  return a > b ? a : b;
}

class LonestIncreasingSubsequence {
  constructor(list) {
    this.list = list.slice(0, list.length);
    this.start();
  }
  start() {
    const states = new Array(this.list.length).fill(0);
    const n = this.list.length;
    states[0] = 1;
    for (let i = 1; i < n; i++) {
      const curVal = this.list[i];
      let max = 0;
      for (let j = i - 1; j >= 0; j--) {
        if (this.list[j] < curVal) {
          if (states[j] > max) max = states[j];
        }
      }
      states[i] = max + 1;
    }
    let longestIncreasingSubsequence = 0;
    states.forEach(state => {
      if (state > longestIncreasingSubsequence) longestIncreasingSubsequence = state;
    });
    console.log('longestIncreasingSubsequence: ', longestIncreasingSubsequence);
  }
}

new LonestIncreasingSubsequence([0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]);
new LonestIncreasingSubsequence([0, 8, 4, 2, 1, 6, 9, 5, 3, 7]);
