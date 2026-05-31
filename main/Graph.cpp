#define RBtree
#ifdef RBtree
#include <iostream>
#include <string>
#include "../lib_RBtree/RBtree.h" 

int main() {
    RBTree<int, std::string> tree;

    int keys[] = { 10, 20, 30, 5, 15, 3, 7, 25, 31, 24 };
    for (int k : keys)
        tree.insert(k, std::to_string(k));

    std::cout << "RBTree:\n";
    tree.print();

    return 0;
}

#endif

#ifdef Graph
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <limits>

static constexpr int INF = std::numeric_limits<int>::max();

struct Edge {
    int from, to, weight;
};


class AdjacencyListGraph {
    int _n;
    bool _directed, _weighted;
    std::vector<std::list<std::pair<int, int>>> _adj;
public:
    AdjacencyListGraph(int n, bool directed = false, bool weighted = false)
        : _n(n), _directed(directed), _weighted(weighted), _adj(n) {
    }

    AdjacencyListGraph(std::vector<std::pair<std::pair<int, int>, int>> edges,
        int n, bool directed = false, bool weighted = false)
        : _n(n), _directed(directed), _weighted(weighted), _adj(n)
    {
        for (size_t i = 0; i < edges.size(); ++i)
            add_edge(edges[i].first.first, edges[i].first.second, edges[i].second);
    }

    void add_edge(int u, int v, int w = 1) {
        int wt = _weighted ? w : 1;
        _adj[u].push_back({ v, wt });
        if (!_directed) _adj[v].push_back({ u, wt });
    }

    void delete_edge(Edge e) {
        remove_neighbor(_adj[e.from], e.to);
        if (!_directed)
            remove_neighbor(_adj[e.to], e.from);
    }

    void delete_vertex(int v) {
        _adj[v].clear();
        for (int u = 0; u < _n; ++u)
            remove_neighbor(_adj[u], v);
    }

    int size() const { return _n; }
    const std::list<std::pair<int, int>>& neighbors(int v) const { return _adj[v]; }

    void print() const {
        for (int v = 0; v < _n; ++v) {
            std::cout << v << ": ";
            for (auto it = _adj[v].begin(); it != _adj[v].end(); ++it)
                std::cout << "(" << it->first << ", w=" << it->second << ") ";
            std::cout << "\n";
        }
    }
private:
    void remove_neighbor(std::list<std::pair<int, int>>& lst, int target) {
        for (auto it = lst.begin(); it != lst.end(); ) {
            if (it->first == target)
                it = lst.erase(it);
            else
                ++it;
        }
    }
};

class EdgeListGraph {
    int _n;
    bool _directed, _weighted;
    std::vector<Edge> _edges;
public:
    EdgeListGraph(int n, bool directed = false, bool weighted = false)
        : _n(n), _directed(directed), _weighted(weighted) {
    }

    EdgeListGraph(std::vector<std::pair<std::pair<int, int>, int>> edges,
        int n, bool directed = false, bool weighted = false)
        : _n(n), _directed(directed), _weighted(weighted)
    {
        for (size_t i = 0; i < edges.size(); ++i)
            add_edge(edges[i].first.first, edges[i].first.second, edges[i].second);
    }

    void add_edge(int u, int v, int w = 1) {
        int wt = _weighted ? w : 1;
        _edges.push_back({ u, v, wt });
        if (!_directed) _edges.push_back({ v, u, wt });
    }

    void delete_edge(Edge e) {
        remove_directed_edge(e.from, e.to);
        if (!_directed)
            remove_directed_edge(e.to, e.from);
    }

    void delete_vertex(int v) {
        std::vector<Edge> kept; 
        for (size_t i = 0; i < _edges.size(); ++i)
            if (_edges[i].from != v && _edges[i].to != v) kept.push_back(_edges[i]);
        _edges = kept;                          
    }

    void print() const {
        for (size_t i = 0; i < _edges.size(); ++i)
            std::cout << "(" << _edges[i].from << "->" << _edges[i].to
            << ", w=" << _edges[i].weight << ") ";
        std::cout << "\n";
    }
private:
    void remove_directed_edge(int from, int to) {
        std::vector<Edge> kept;
        for (size_t i = 0; i < _edges.size(); ++i)
            if (!(_edges[i].from == from && _edges[i].to == to))
                kept.push_back(_edges[i]);
        _edges = kept;
    }
};


std::vector<int> dijkstra(const AdjacencyListGraph& g, int start, int end) {
    int n = g.size();
    std::vector<int> dist(n, INF);
    std::vector<int> prev(n, -1);

    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>
    > pq;

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;
        if (u == end)   break;

        const std::list<std::pair<int, int>>& nbrs = g.neighbors(u);
        for (auto it = nbrs.begin(); it != nbrs.end(); ++it) {
            int v = it->first;
            int w = it->second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }

    if (dist[end] == INF) return {};

    std::vector<int> path;
    for (int v = end; v != -1; v = prev[v])
        path.push_back(v);
    std::reverse(path.begin(), path.end());
    return path;
}

int main() {
    /*
     *    4 ---- 6
     *   / \      \
     *  1   \      3
     *   \___ 2 __/ \
     *       /       \
     *      5 -------- 0
     */
    std::cout << "=== Adjacency List ===\n";
    AdjacencyListGraph ag({
        {{1,4},1}, {{1,2},1}, {{4,6},1},
        {{4,2},1}, {{6,3},1}, {{2,3},1},
        {{2,5},1}, {{3,0},1}, {{5,0},1}
        }, 7);
    ag.print();

    std::cout << "\nadd_edge(0, 6):\n";
    ag.add_edge(0, 6);
    ag.print();

    std::cout << "\ndelete_edge(2->5):\n";
    ag.delete_edge({ 2, 5, 1 });
    ag.print();

    std::cout << "\ndelete_vertex(3):\n";
    ag.delete_vertex(3);
    ag.print();

    std::cout << "\n=== Edge List ===\n";
    EdgeListGraph eg({
        {{0,1},5}, {{0,2},3}, {{1,3},2}, {{2,3},7}
        }, 4, true, true);
    eg.print();

    std::cout << "\nadd_edge(3->0, w=1):\n";
    eg.add_edge(3, 0, 1);
    eg.print();

    std::cout << "\ndelete_edge(0->2):\n";
    eg.delete_edge({ 0, 2, 3 });
    eg.print();

    std::cout << "\ndelete_vertex(1):\n";
    eg.delete_vertex(1);
    eg.print();

    // ── Dijkstra ──────────────────────────────────────────────
    /*
     * Weighted graph:
     *
     *       2       3
     *   0 ----- 1 ----- 2
     *   |               |
     * 6 |               | 1
     *   |               |
     *   3 ----- 4 ----- 5
     *       5       2
     *
     * Shortest path 0->5: 0->1->2->5, length = 2+3+1 = 6
     */
    std::cout << "\n=== Dijkstra (weighted) ===\n";
    AdjacencyListGraph wg({
        {{0,1},2}, {{1,2},3}, {{0,3},6},
        {{3,4},5}, {{4,5},2}, {{2,5},1}
        }, 6, false, true);
    wg.print();

    std::vector<int> p1 = dijkstra(wg, 0, 5);
    std::cout << "\nShortest path 0->5: ";
    for (size_t i = 0; i < p1.size(); ++i)
        std::cout << p1[i] << (i + 1 < p1.size() ? " -> " : "\n");

    std::cout << "\n=== Dijkstra (unweighted) ===\n";
    AdjacencyListGraph ug({
        {{0,1},1}, {{1,2},1}, {{0,3},1},
        {{3,4},1}, {{4,5},1}, {{2,5},1}
        }, 6, false, false);
    ug.print();

    std::vector<int> p2 = dijkstra(ug, 0, 5);
    std::cout << "\nShortest path 0->5: ";
    for (size_t i = 0; i < p2.size(); ++i)
        std::cout << p2[i] << (i + 1 < p2.size() ? " -> " : "\n");

    std::cout << "\n=== Dijkstra (no path) ===\n";
    AdjacencyListGraph dg(4, true);
    dg.add_edge(0, 1);
    dg.add_edge(2, 3);
    std::vector<int> p3 = dijkstra(dg, 0, 3);
    if (p3.empty())
        std::cout << "No path from 0 to 3\n";

    return 0;
}
#endif