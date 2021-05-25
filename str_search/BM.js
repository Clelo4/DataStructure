// 计算坏字符规则表
function getBadCharacterMap(pattern) {
  const map = new Map();
  for (let i = 0; i < pattern.length; i++) {
    const char = pattern[i];
    if (!map.has(char)) {
      map.set(char, [i]);
    } else {
      map.get(char).push(i);
    }
  }
  return map;
}
// 计算好后缀规则表
function generateGS(pattern, suffix, prefix) {
  const patternLength = pattern.length;
  for(let i = 0; i < patternLength; i++) {
    suffix[i] = -1;
    prefix[i] = false;
  }
  for (let i = 0; i < patternLength - 1; ++i) {
    let j = i;
    let k = 0; // 公共后缀子串长度
    while (j >= 0 && pattern[j] === pattern[patternLength - 1 - k]) { // 与pattern[0, patternLength - 1]求公共后缀子串
      --j;
      ++k;
      suffix[k] = j + 1; // j表示公共后缀子串在pattern[0, i]中的起始下标
    }
    if (j == -1) prefix[k] = true; // 如果公共后缀子串也是模式串的前缀子串
  }
}

function moveByGS(patternSearchIndex, patternLength, suffix, prefix) {
  const goodSuffixLength = patternLength - 1 - patternSearchIndex;
  if (suffix[goodSuffixLength] !== - 1) {
    return patternSearchIndex - suffix[goodSuffixLength] + 1;
  }
  for (let r = patternSearchIndex + 2; r <= patternLength - 1; ++r) {
    if (prefix[patternLength - r] == true) {
      return r;
    }
  }
  return patternLength;
}


function BMSearch(str, pattern) {
  const suffix = [];
  const prefix = [];

  // 生成pattern的坏字符规则表
  const barCharMap = getBadCharacterMap(pattern);
  // 预先计算好后缀规则表
  generateGS(pattern, suffix, prefix);

  const patternLength = pattern.length;
  let patternSearchIndex = patternLength - 1;
  let strSearchIndex = patternSearchIndex;

  while (strSearchIndex < str.length) {
    patternSearchIndex = patternLength - 1;
    const oldStreSearchIndex = strSearchIndex;
    while (patternSearchIndex >= 0 && pattern[patternSearchIndex] == str[strSearchIndex]) {
      patternSearchIndex--;
      strSearchIndex--;
    }
    if (patternSearchIndex == -1) {
      // 全部匹配成功
      return strSearchIndex + 1;
    } else {
      // 出现坏字符
      const badChar = str[strSearchIndex];
      const barCharList = barCharMap.get(badChar);
      // 在坏字符规则表中从右向左查找第一个比patternSearchIndex小的值
      let findBadCharIndexInPattern = -1;
      if (barCharList) {
        let i = barCharList.length - 1;
        for (; i >= 0 && patternSearchIndex <= barCharList[i]; i--) {
        }
        findBadCharIndexInPattern = (i > - 1) ? barCharList[i] : -1;
      }
      // 移动pattern，strSearchIndex += removeSteps；patternSearchIndex重置为pattern.length - 1
      const badRemoveSteps = patternSearchIndex - findBadCharIndexInPattern;
      if (badRemoveSteps < 0) {
        return -1;
      }

      let BGRemoveSteps = 0;
      // 如果有好后缀的话
      if (patternSearchIndex < patternLength - 1) {
        BGRemoveSteps = moveByGS(patternSearchIndex, patternLength, suffix, prefix);
      }
      strSearchIndex = oldStreSearchIndex + ((badRemoveSteps > BGRemoveSteps) ? badRemoveSteps : BGRemoveSteps);
    }
  }
  // 查找不到
  return -1;
}

module.exports = BMSearch;
