class Graph {
  constructor() {
    this.adj = {}; // 邻接表
  }
  addEdge(s, t) {
    if (!this.adj[s]) {
      this.adj[s] = [];
    }
    if (!this.adj[t]) {
      this.adj[t] = [];
    }
    this.adj[s].push(t);
    this.adj[t].push(s);
  }
  // 广度优先搜索（Breadth-First-Search）从s搜索到t
  BFS(s, t) {
    if (s === t) return;
    const queue = []; // 任务队列
    const visited = {}; // 用来记录已经被访问的顶点
    const prev = {}; // 记录搜索路径
    Object.keys(this.adj).forEach(k => {
      prev[k] = -1;
    });
    queue.push(s);
    while (queue.length > 0) {
      let w = queue.shift();
      for (let i = 0; i < this.adj[w].length; i++) {
        let k = this.adj[w][i];
        if (!visited[k]) {
          visited[k] = true;
          prev[k] = w;
          if (k === t) {
            this.print(prev, s, t);
            break;
          }
          queue.push(k);
        }
      }
    }
  }
  // 深度优先搜索（Depth-First-Search）从s搜索到t
  DFS(s, t) {
    const prev = {}; // 记录搜索路径
    const visited = {}; // 用来记录已经被访问的顶点
    Object.keys(this.adj).forEach(k => {
      prev[k] = -1;
    });
    this.recurDfs(prev, visited, s, t);
    this.print(prev, s, t);
  }
  recurDfs(prev, visited, s, t) {
    visited[s] = true;
    if (s === t) {
      return true;
    } else {
      for (let i = 0; i < this.adj[s].length; i++) {
        if (!visited[this.adj[s][i]]) {
          prev[this.adj[s][i]] = s;
          if (this.recurDfs(prev, visited, this.adj[s][i], t)) {
            return true;
          }
        }
      }
    }
    return false;
  }
  print(prev, s, t) {
    if (prev[t] !== -1 && t !== s) {
      this.print(prev, s, prev[t]);
    }
    console.log(t + ' ');
  }
}

module.exports = Graph;
