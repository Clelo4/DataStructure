const Graph = require('./graph');

const g = new Graph();
g.addEdge(0, 1);
g.addEdge(0, 3);
g.addEdge(1, 2);
g.addEdge(1, 4);
g.addEdge(2, 5);
g.addEdge(3, 4);
g.addEdge(4, 5);
g.addEdge(4, 6);
g.addEdge(6, 7);

g.DFS(0, 5);
g.BFS(0, 5);
