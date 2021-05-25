// AC自动机：使用多模式串匹配实现关键词过滤功能
class Node {
  constructor(char = undefined) {
    this.char = char;
    this.children = {};
    this.isEndingChar = false;
    this.fail = null;
    this.length = -1;
  }
}

class AC {
  constructor(patterns) {
    if (!Array.isArray(patterns)) {
      console.error('patterns必须是Array类型');
      return;
    }
    this.root = new Node();
    patterns.forEach(pattern => {
      this._insert(pattern);
    });
    this._buildFailurePointer();
  }
  _insert(pattern) {
    pattern = (pattern || '').toLowerCase();
    let p = this.root;
    const patternLength = pattern.length;
    for (let i = 0; i < patternLength; i++) {
      let char = pattern[i];
      if (p.children[char] === undefined) {
        p.children[char] = new Node(char);
      }
      p = p.children[char];
    }
    p.length = patternLength;
    p.isEndingChar = true;
  }
  _buildFailurePointer() {
    let p = this.root;
    const queue = new Array();
    p.fail = null;
    queue.push(p);
    while (queue.length > 0) {
      let target = queue.shift();
      let children = target.children;
      Object.keys(children).forEach(child => {
        let tc = target.children[child];
        if (target === this.root) {
          tc.fail = this.root;
        } else {
          let q = target.fail;
          while (q !== null) {
            let qc = q.children[tc.char];
            if (qc) {
              tc.fail = qc;
              break;
            }
            q = q.fail;
          }
          if (q === null) {
            tc.fail = this.root;
          }
        }
        queue.push(tc);
      });
    }
  }
  match(str) {
    let strLength = str.length;
    let p = this.root;
    for (let i = 0; i < strLength; i++) {
      let char = str[i];
      while (p !== this.root && p.children[char] === null) {
        p = p.fail; // 失效指针发挥作用的地方
      }
      p = p.children[char];
      if (p == null) {
        p = this.root; // 如果char始终没有被匹配，则p从root重新开始
      }
      let tmp = p;
      while (tmp !== this.root) { // 打印出可以匹配的模式串
        if (tmp.isEndingChar === true) {
          let posi = i - tmp.length + 1;
          console.log('匹配起始下标：' + posi + ' 长度：' + tmp.length);
        }
        tmp = tmp.fail;
      }
    }
  }
}

module.exports = AC;
