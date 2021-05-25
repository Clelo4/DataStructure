// 生成next数组
function getNexts(pattern) {
  const patternLength = pattern.length;
  let next = [];
  next[0] = -1;
  let k = -1;
  for (let i = 1; i < patternLength; i++) {
    while (k !== -1 && pattern[k + 1] !== pattern[i]) {
      k = next[k];
    }
    if (pattern[i] === pattern[k + 1]) {
      ++k;
    }
    next[i] = k;
  }
  return next;
}

function KMPSearch(str, pattern) {
 const next = getNexts(pattern);
  const patternLength = pattern.length;
  const strLength = str.length;
  let j = 0;
  for (let i = 0; i < strLength; i++) {
    while (j > 0 && str[i] !== pattern[j]) {
      j = next[j - 1] + 1;
    }
    if (str[i] === pattern[j]) {
      j++;
    }
    if (j === patternLength) {
      return i - patternLength + 1;
    }
  }
  return -1;
}

module.exports = KMPSearch;
