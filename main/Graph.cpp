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
        _adj[e.from].remove_if([&](const std::pair<int, int>& p) { return p.first == e.to; });
        if (!_directed)
            _adj[e.to].remove_if([&](const std::pair<int, int>& p) { return p.first == e.from; });
    }

    void delete_vertex(int v) {
        _adj[v].clear();
        for (int u = 0; u < _n; ++u)
            _adj[u].remove_if([&](const std::pair<int, int>& p) { return p.first == v; });
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
};

// ═════════════════════════════════════════════════════════════
// Способ 2: список рёбер
// ═════════════════════════════════════════════════════════════
/*
 * _edges: (1->4,1) (4->1,1) (1->2,1) (2->1,1) ...
 *
 * Плюсы:  просто, легко перебирать рёбра
 * Минусы: поиск соседей O(M)
 */
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
        _edges.erase(std::remove_if(_edges.begin(), _edges.end(),
            [&](const Edge& x) { return x.from == e.from && x.to == e.to; }),
            _edges.end());
        if (!_directed)
            _edges.erase(std::remove_if(_edges.begin(), _edges.end(),
                [&](const Edge& x) { return x.from == e.to && x.to == e.from; }),
                _edges.end());
    }

    void delete_vertex(int v) {
        _edges.erase(std::remove_if(_edges.begin(), _edges.end(),
            [&](const Edge& e) { return e.from == v || e.to == v; }),
            _edges.end());
    }

    void print() const {
        for (size_t i = 0; i < _edges.size(); ++i)
            std::cout << "(" << _edges[i].from << "->" << _edges[i].to
            << ", w=" << _edges[i].weight << ") ";
        std::cout << "\n";
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

//int main() {
//    /*
//     *    4 ---- 6
//     *   / \      \
//     *  1   \      3
//     *   \___ 2 __/ \
//     *       /       \
//     *      5 -------- 0
//     */
//    std::cout << "=== List-Smezh ===\n";
//    AdjacencyListGraph ag({
//        {{1,4},1}, {{1,2},1}, {{4,6},1},
//        {{4,2},1}, {{6,3},1}, {{2,3},1},
//        {{2,5},1}, {{3,0},1}, {{5,0},1}
//        }, 7);
//    ag.print();
//
//    std::cout << "\nadd_edge(0, 6):\n";
//    ag.add_edge(0, 6);
//    ag.print();
//
//    std::cout << "\ndelete_edge(2->5):\n";
//    ag.delete_edge({ 2, 5, 1 });
//    ag.print();
//
//    std::cout << "\ndelete_vertex(3):\n";
//    ag.delete_vertex(3);
//    ag.print();
//
//    std::cout << "\n=== List-Edge ===\n";
//    EdgeListGraph eg({
//        {{0,1},5}, {{0,2},3}, {{1,3},2}, {{2,3},7}
//        }, 4, true, true);
//    eg.print();
//
//    std::cout << "\nadd_edge(3->0, w=1):\n";
//    eg.add_edge(3, 0, 1);
//    eg.print();
//
//    std::cout << "\ndelete_edge(0->2):\n";
//    eg.delete_edge({ 0, 2, 3 });
//    eg.print();
//
//    std::cout << "\ndelete_vertex(1):\n";
//    eg.delete_vertex(1);
//    eg.print();
//
//    // ── Дейкстра ─────────────────────────────────────────────
//    /*
//     * Взвешенный граф:
//     *
//     *       2       3
//     *   0 ----- 1 ----- 2
//     *   |               |
//     * 6 |               | 1
//     *   |               |
//     *   3 ----- 4 ----- 5
//     *       5       2
//     *
//     * Кратчайший 0→5: 0→1→2→5, длина = 2+3+1 = 6
//     */
//    std::cout << "\n=== Дейкстра (взвешенный) ===\n";
//    AdjacencyListGraph wg({
//        {{0,1},2}, {{1,2},3}, {{0,3},6},
//        {{3,4},5}, {{4,5},2}, {{2,5},1}
//        }, 6, false, true);
//    wg.print();
//
//    std::vector<int> p1 = dijkstra(wg, 0, 5);
//    std::cout << "\nПуть 0->5: ";
//    for (size_t i = 0; i < p1.size(); ++i)
//        std::cout << p1[i] << (i + 1 < p1.size() ? " -> " : "\n");
//
//    std::cout << "\n=== Дейкстра (невзвешенный) ===\n";
//    AdjacencyListGraph ug({
//        {{0,1},1}, {{1,2},1}, {{0,3},1},
//        {{3,4},1}, {{4,5},1}, {{2,5},1}
//        }, 6, false, false);
//    ug.print();
//
//    std::vector<int> p2 = dijkstra(ug, 0, 5);
//    std::cout << "\nПуть 0->5: ";
//    for (size_t i = 0; i < p2.size(); ++i)
//        std::cout << p2[i] << (i + 1 < p2.size() ? " -> " : "\n");
//
//    std::cout << "\n=== Дейкстра (путь не существует) ===\n";
//    AdjacencyListGraph dg(4, true);
//    dg.add_edge(0, 1);
//    dg.add_edge(2, 3);
//    std::vector<int> p3 = dijkstra(dg, 0, 3);
//    if (p3.empty())
//        std::cout << "Путь 0->3 не существует\n";
//
//    return 0;
//}
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