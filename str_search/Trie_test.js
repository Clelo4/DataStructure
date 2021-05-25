const Trie = require('./Trie');

const patternStrList = [
  'chengjunjie',
  'chen',
  'jack',
  'clelo',
  'you'
];

let trie = new Trie();

patternStrList.forEach(pattern => {
  trie.insert(pattern);
});

const testList = [
  'chengjunjie',
  'chengjunji',
  'chen',
  'jack!',
  'clelo4',
  'chen'
];

testList.forEach((testStr, index) => {
  console.log(`第${index + 1}次测试: ${testStr}, 测试结果${trie.find(testStr) ? '通过' : '不通过'}`);
});
