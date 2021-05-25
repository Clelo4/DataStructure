const AC = require('./AC');

const patternStrList = [
  'abcd',
  'ce',
  'bcd',
];

let ac = new AC(patternStrList);
ac.match('我是程俊杰，昵称abcd，叫bcd');
