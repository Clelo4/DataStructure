const fs = require('fs');
const path = require('path');
const KMPSearch = require('./KMP.js');

const testFilePath = path.resolve(__dirname, 'test.txt');

const testFileStr = fs.readFileSync(testFilePath).toString();
const testSearchStr = 'Se("function"==typeof t?t.call(this,this):t,"function"==typeof e?e.call(this,chengjunjiethis):e)}:t:e}function Ee(e,t){var n=t?e?e.concat';

// const testFileStr = "abcacabcbcbacabc";
// const testSearchStr = "cbacabc";

console.log('test by native js: ');
console.time('native');
result = testFileStr.indexOf(testSearchStr);
console.log(result);
console.timeEnd('native');

console.log('\ntest by KMPSearch: ');
console.time('KMPSearch');
result = KMPSearch(testFileStr, testSearchStr);
console.log(result);
console.timeEnd('KMPSearch');
