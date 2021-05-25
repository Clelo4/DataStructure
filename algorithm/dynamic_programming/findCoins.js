class FindCoins {
  constructor(coinType) {
    this.coinType = coinType.sort();
  }
  find(money) {
    let states = [];
    states[0] = 0;
    for (let i = 1; i <= money; i++) {
      for (let j = 0; j < this.coinType.length; j++) {
        let coin = this.coinType[j];
        if (coin > i) {
          break;
        } else {
          if (!states[i]) states[i] = states[i - coin] + 1;
          else {
            if (states[i - coin] + 1 < states[i]) states[i] = states[i - coin] + 1;
          }
        }
      }
    }
    console.log('result: ', states[money]);
  }
}

const test = new FindCoins([1, 3, 5]);
test.find(13);
