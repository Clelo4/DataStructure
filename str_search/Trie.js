// 多模式匹配算法Trie
class Node {
  constructor(char = undefined) {
    this.char = char;
    this.children = {};
    this.isEndingChar = false;
  }
}

class Trie {
  constructor() {
    this.root = new Node();
  }
  insert(pattern) {
    pattern = (pattern || '').toLowerCase();
    let p = this.root;
    for (let i = 0; i < pattern.length; i++) {
      let char = pattern[i];
      if (p.children[char] === undefined) {
        p.children[char] = new Node(char);
      }
      p = p.children[char];
    }
    p.isEndingChar = true;
  }
  find(str) {
    str = (str || '').toLowerCase();
    let p = this.root;
    for (let i = 0; i < str.length; ++i) {
      let char = str[i];
      if (p.children[char] === undefined) {
        return false;
      }
      p = p.children[char];
    }
    if (p.isEndingChar == false) return false;
    else return true;
  }
}

module.exports = Trie;
